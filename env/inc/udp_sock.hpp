#ifndef UDP_SOCK_HPP
#define UDP_SOCK_HPP

#include "base_socket.hpp"
#include "udp_sock_type.hpp"

#include <errno.h>
#include <future>
#include <thread>

template <uint32_t family, udp_sock_t socket_class>
struct udp_socket : public base_socket<family, SOCK_DGRAM, IPPROTO_UDP> {
public:
  static constexpr int32_t socktype = SOCK_DGRAM;
  static constexpr int32_t protocol = IPPROTO_UDP;
  static constexpr int32_t epollevents = EPOLLIN | EPOLLET;

  enum struct state_t : int32_t { RUNNING, STOPPED };
  enum struct recv_behavior_t : uint32_t { HOOK, RET, HOOK_RET };
  enum struct send_behavior_t : uint32_t { HOOK_ON, HOOK_OFF };

  using this_t = udp_socket<family, socket_class>;
  using base_t = base_socket<family, socktype, protocol>;

  static constexpr bool is_ipv6 = base_t::is_ipv6;

  using sockaddr_inet_t = std::conditional_t<is_ipv6, struct sockaddr_in6, struct sockaddr_in>;
  using inet_addr_t = std::conditional_t<is_ipv6, struct in6_addr, struct in_addr>;

  template <udp_sock_t sc = socket_class>
  explicit udp_socket(
      const std::string &iface,
      typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || (!is_ipv6 && sc == udp_sock_t::SERVER_BROADCAST) ||
                                  sc == udp_sock_t::SERVER_MULTICAST,
                              udp_sock_t>::type * = nullptr)
      : base_t(iface), epfd_(::epoll_create1(EPOLL_CLOEXEC)), state_(state_t::STOPPED),
        events_(reinterpret_cast<struct epoll_event *>(
            std::malloc(this->epoll_max_events() * sizeof(struct epoll_event)))) {}

  template <udp_sock_t sc = socket_class>
  explicit udp_socket(
      const std::string &iface,
      typename std::enable_if<sc == udp_sock_t::CLIENT_UNICAST || (!is_ipv6 && sc == udp_sock_t::CLIENT_BROADCAST),
                              udp_sock_t>::type * = nullptr)
      : base_t(iface), epfd_(::epoll_create1(EPOLL_CLOEXEC)),
        events_(reinterpret_cast<struct epoll_event *>(
            std::malloc(this->epoll_max_events() * sizeof(struct epoll_event)))) {
    setup_();
  }

  template <udp_sock_t sc = socket_class>
  explicit udp_socket(const std::string &iface, const std::string &mcast_gr_addr, uint16_t srv,
                      typename std::enable_if<sc == udp_sock_t::CLIENT_MULTICAST, udp_sock_t>::type * = nullptr)
      : base_t(iface), epfd_(::epoll_create1(EPOLL_CLOEXEC)),
        events_(reinterpret_cast<struct epoll_event *>(
            std::malloc(this->epoll_max_events() * sizeof(struct epoll_event)))) {
    setup_(mcast_gr_addr, srv);
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_MULTICAST, RetType>::type setup(const std::string &mcast_gr_addr,
                                                                                   uint16_t port) {
    setup_(mcast_gr_addr, port);
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || (!is_ipv6 && sc == udp_sock_t::SERVER_BROADCAST),
                          RetType>::type
  setup(uint16_t port) {
    setup_(port);
  }

  const auto &on_receive() const { return on_receive_; }
  const auto &on_send() const { return on_send_; }

  void stop_threads() const { return const_cast<const base_t *>(this)->stop_tp(); }
  template <udp_sock_t sc = socket_class, typename RetType = bool>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || (!is_ipv6 && sc == udp_sock_t::SERVER_BROADCAST) ||
                              sc == udp_sock_t::SERVER_MULTICAST,
                          RetType>::type
  running() const {
    return state_ == state_t::RUNNING;
  }

  template <send_behavior_t sb = send_behavior_t::HOOK_ON, udp_sock_t sc = socket_class,
            typename RetType = std::conditional_t<
                sb == send_behavior_t::HOOK_ON, int32_t,
                std::conditional_t<sb == send_behavior_t::HOOK_OFF, std::pair<int32_t, sockaddr_inet_t>, void>>>
  typename std::enable_if<!is_ipv6 && (sc == udp_sock_t::CLIENT_BROADCAST || sc == udp_sock_t::SERVER_BROADCAST),
                          RetType>::type
  send(uint16_t port, const void *const msg, size_t size) const {
    struct addrinfo *dgram_addrinfo, hints;
    fd_set write_fd_set;
    struct timeval write_timeout = {base_t::send_timeout() / 1000, 0u};

    std::memset(&hints, 0x0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = socktype;
    hints.ai_protocol = protocol;

    int32_t rc;
    if ((rc = ::getaddrinfo(this->iface_info().broadcast.data(), std::to_string(port).c_str(), &hints,
                            &dgram_addrinfo)) != 0 ||
        dgram_addrinfo == nullptr) {
      throw std::runtime_error(fmt::format("Invalid address or port: \"{0}\",\"{1} (errno = {2}), ({3}), {4}:{5}\"",
                                           this->iface_info().broadcast.data(), std::to_string(port), gai_strerror(rc),
                                           __func__, __FILE__, __LINE__));
    }

  sendto:
    if ((rc = ::sendto(sock_fd_, msg, size, 0u, dgram_addrinfo->ai_addr, dgram_addrinfo->ai_addrlen)) < 0) {
      if (errno != EAGAIN) {
        if (errno == ECONNREFUSED || errno == EHOSTUNREACH || errno == ENETUNREACH || errno == ECONNRESET ||
            errno == ECONNABORTED || errno == EPIPE) {
          ::freeaddrinfo(dgram_addrinfo);
          throw std::runtime_error(fmt::format("Network error (errno = {0}), ({1}), {2}:{3}\r\n", strerror(errno),
                                               __func__, __FILE__, __LINE__));
        } else {
          ::freeaddrinfo(dgram_addrinfo);
          throw std::runtime_error(
              fmt::format("Sendto error (errno = {0}), ({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
        }
      } else {
        FD_ZERO(&write_fd_set);
        FD_SET(sock_fd_, &write_fd_set);

        if ((rc = ::select(sock_fd_ + 1, &write_fd_set, nullptr, nullptr, &write_timeout)) <= 0) {
          ::freeaddrinfo(dgram_addrinfo);
          throw std::runtime_error(fmt::format("Send timeout of select() error (errno = {0}), ({1}), {2}:{3}",
                                               strerror(errno), __func__, __FILE__, __LINE__));
        } else
          goto sendto;
      }
    } else if (!rc) {
      ::freeaddrinfo(dgram_addrinfo);
      throw std::runtime_error(fmt::format("Network error (errno = {0}), ({1}), {2}:{3}\r\n", strerror(errno), __func__,
                                           __FILE__, __LINE__));
    } else {
      if constexpr (sb == send_behavior_t::HOOK_ON) {

        sockaddr_inet_t to;
        std::memcpy(&to, reinterpret_cast<sockaddr_inet_t *>(dgram_addrinfo->ai_addr), dgram_addrinfo->ai_addrlen);
        ::freeaddrinfo(dgram_addrinfo);
        void *data = std::calloc(size, sizeof(char));
        std::memcpy(data, msg, size);
        this->tp().push([this, to, size, data](int32_t thr_id) -> void {
          this->on_send()(to, std::shared_ptr<void>(data, [](const auto &data) -> void { std::free(data); }), size,
                          this);
        });

        return rc;
      } else if constexpr (sb == send_behavior_t::HOOK_OFF) {

        sockaddr_inet_t to;
        std::memcpy(&to, reinterpret_cast<sockaddr_inet_t *>(dgram_addrinfo->ai_addr), dgram_addrinfo->ai_addrlen);
        ::freeaddrinfo(dgram_addrinfo);
        return {rc, std::move(to)};
      }
    }
  }

  template <send_behavior_t sb = send_behavior_t::HOOK_ON, udp_sock_t sc = socket_class,
            typename RetType = std::conditional_t<
                sb == send_behavior_t::HOOK_ON, int32_t,
                std::conditional_t<sb == send_behavior_t::HOOK_OFF, std::pair<int32_t, sockaddr_inet_t>, void>>>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || sc == udp_sock_t::CLIENT_UNICAST ||
                              sc == udp_sock_t::SERVER_MULTICAST || sc == udp_sock_t::CLIENT_MULTICAST,
                          RetType>::type
  send(const std::string &addr, uint16_t port, const void *const msg, size_t size) const {
    struct addrinfo *dgram_addrinfo, hints;
    fd_set write_fd_set;
    struct timeval write_timeout = {base_t::send_timeout() / 1000, 0u};

    std::memset(&hints, 0x0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = socktype;
    hints.ai_protocol = protocol;

    int32_t rc;
    if ((rc = ::getaddrinfo(addr.c_str(), std::to_string(port).c_str(), &hints, &dgram_addrinfo)) != 0 ||
        dgram_addrinfo == nullptr) {
      throw std::runtime_error(fmt::format("Invalid address or port: \"{0}\",\"{1} (errno = {2}), ({3}), {4}:{5}\"",
                                           addr, std::to_string(port), gai_strerror(rc), __func__, __FILE__, __LINE__));
    }

  sendto:
    if ((rc = ::sendto(sock_fd_, msg, size, 0, dgram_addrinfo->ai_addr, dgram_addrinfo->ai_addrlen)) < 0) {
      if (errno != EAGAIN) {
        if (errno == ECONNREFUSED || errno == EHOSTUNREACH || errno == ENETUNREACH || errno == ECONNRESET ||
            errno == ECONNABORTED || errno == EPIPE) {
          throw std::runtime_error(fmt::format("Network error (errno = {0}), ({1}), {2}:{3}\r\n", strerror(errno),
                                               __func__, __FILE__, __LINE__));
        } else {
          throw std::runtime_error(
              fmt::format("Sendto error (errno = {0}), ({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
        }
      } else {
        FD_ZERO(&write_fd_set);
        FD_SET(sock_fd_, &write_fd_set);

        if ((rc = ::select(sock_fd_ + 1, &write_fd_set, nullptr, nullptr, &write_timeout)) <= 0) {
          ::freeaddrinfo(dgram_addrinfo);
          throw std::runtime_error(fmt::format("Send timeout of select() error (errno = {0}), ({1}), {2}:{3}",
                                               strerror(errno), __func__, __FILE__, __LINE__));
        } else
          goto sendto;
      }
    } else if (!rc) {
      throw std::runtime_error(fmt::format("Network error (errno = {0}), ({1}), {2}:{3}\r\n", strerror(errno), __func__,
                                           __FILE__, __LINE__));
    } else {
      if constexpr (sb == send_behavior_t::HOOK_ON) {

        sockaddr_inet_t to;
        std::memcpy(&to, reinterpret_cast<sockaddr_inet_t *>(dgram_addrinfo->ai_addr), dgram_addrinfo->ai_addrlen);
        ::freeaddrinfo(dgram_addrinfo);
        void *data = std::calloc(size, sizeof(char));
        std::memcpy(data, msg, size);
        this->tp().push([this, to, data, size](int32_t thr_id) -> void {
          this->on_send()(to, std::shared_ptr<void>(data, [](const auto &data) -> void { std::free(data); }), size,
                          this);
        });
      } else if constexpr (sb == send_behavior_t::HOOK_OFF) {

        sockaddr_inet_t to;
        std::memcpy(&to, reinterpret_cast<sockaddr_inet_t *>(dgram_addrinfo->ai_addr), dgram_addrinfo->ai_addrlen);
        ::freeaddrinfo(dgram_addrinfo);
        return {rc, std::move(to)};
      }
    }
  }

  template <recv_behavior_t rb = recv_behavior_t::HOOK,
            typename RetType = std::conditional_t<
                rb == recv_behavior_t::HOOK, int32_t,
                std::conditional_t<rb == recv_behavior_t::RET || rb == recv_behavior_t::HOOK_RET,
                                   std::vector<std::tuple<int32_t, std::shared_ptr<void>, sockaddr_inet_t>>, void>>>
  RetType recv() const {
    int32_t num_ready;
    int32_t recvd_size = 0;
    fd_set read_fd_set;
    struct timeval read_timeout = {base_t::receive_timeout() / 1000, 0u};
    std::vector<std::tuple<int32_t, std::shared_ptr<void>, sockaddr_inet_t>> ret;

    if ((num_ready = ::epoll_wait(epfd_, events_, this->epoll_max_events(), base_t::receive_timeout())) < 0)
      throw std::runtime_error(
          fmt::format("Epoll wait error (errno = {0}) ({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));

    for (uint32_t i = 0u; i < num_ready; i++) {
      if ((events_[i].data.fd == sock_fd_) && ((events_[i].events & EPOLLIN) == EPOLLIN)) {
        sockaddr_inet_t from;
        socklen_t fromlen = sizeof(from);
        int32_t bytes_pending, rc;

        if ((rc = ::ioctl(sock_fd_, FIONREAD, &bytes_pending)) < 0) {
          throw std::runtime_error(
              fmt::format("IOctl error (errno = {0}), ({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
        }

        void *data = std::malloc(bytes_pending + 1u);
        int32_t recvd;
      recv:
        if ((recvd = ::recvfrom(sock_fd_, data, bytes_pending, 0u, reinterpret_cast<struct sockaddr *>(&from),
                                &fromlen)) < 0) {
          if (errno != EAGAIN) {
            std::free(data);
            throw std::runtime_error(fmt::format("Receiveing error (errno = {0}), ({1}), {2}:{3}", strerror(errno),
                                                 __func__, __FILE__, __LINE__));
          } else {
            FD_ZERO(&read_fd_set);
            FD_SET(sock_fd_, &read_fd_set);

            if ((rc = ::select(sock_fd_ + 1, &read_fd_set, nullptr, nullptr, &read_timeout)) <= 0) {
              throw std::runtime_error(fmt::format("Send timeout of select() error (errno = {0}), ({1}), {2}:{3}",
                                                   strerror(errno), __func__, __FILE__, __LINE__));
            } else
              goto recv;
          }
        } else if (recvd) {
          *(reinterpret_cast<char *>(data) + recvd) = '\0';
          if constexpr (rb == recv_behavior_t::HOOK) {
            this->tp().push([this, from, data, size = recvd](int32_t thr_id) -> void {
              this->on_receive()(from, std::shared_ptr<void>(data, [](const auto &data) -> void { std::free(data); }),
                                 size, this);
            });
          } else if constexpr (rb == recv_behavior_t::RET || rb == recv_behavior_t::HOOK_RET) {

            ret.push_back(
                std::make_tuple(recvd, std::shared_ptr<void>(data, [](const auto &data) -> void { std::free(data); }),
                                std::move(from)));

            if constexpr (rb == recv_behavior_t::HOOK_RET) {
              this->tp().push([this, peer = std::get<2u>(ret.back()), data = std::get<1u>(ret.back()),
                               size = data = std::get<0u>(ret.back())](int32_t thr_id) -> void {
                this->on_receive()(peer, data, size, this);
              });
            }
          }

          recvd_size += recvd;
        }
      }
    }

    if constexpr (rb == recv_behavior_t::HOOK) {

      return recvd_size;
    } else if constexpr (rb == recv_behavior_t::RET || rb == recv_behavior_t::HOOK_RET) {

      return std::move(ret);
    }
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || sc == udp_sock_t::SERVER_MULTICAST ||
                              sc == udp_sock_t::SERVER_BROADCAST,
                          RetType>::type
  start(uint64_t duration_ms = 0) const {
    bool nonblock = duration_ms == 0;
    if (nonblock) {
      listen_thread_ = std::thread([this]() -> void { listen_(); });

    } else {
      this->tp().push(
          [this](int32_t thr_id, uint64_t duration_ms, std::atomic_bool *trigger) -> void {
            std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
            *trigger = false;
          },
          duration_ms, &listen_enabled_);
      listen_();
    }
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || sc == udp_sock_t::SERVER_MULTICAST ||
                              (!is_ipv6 && sc == udp_sock_t::SERVER_BROADCAST),
                          RetType>::type
  stop() {
    listen_enabled_ = false;
    if (listen_thread_.joinable())
      listen_thread_.join();
  }

  void reset() {
    clear_<socket_class>();
    clear_hooks_();
  }

  virtual ~udp_socket() {
    reset();
    clear_epoll_();
  }

protected:
  const int32_t &fd__() const { return sock_fd_; }
  std::atomic_bool &listen_enabled__() const { return listen_enabled_; }
  std::atomic<state_t> &state__() const { return state_; }
  std::thread &listen_thread__() const { return listen_thread_; }

private:
  int32_t sock_fd_;
  int32_t epfd_;
  struct epoll_event *events_;
  mutable std::thread listen_thread_;

  mutable std::atomic_bool listen_enabled_;
  mutable std::mutex mtx_;
  mutable std::atomic<state_t> state_;
  struct addrinfo *target;

  const hook_t<void(sockaddr_inet_t, std::shared_ptr<void>, size_t, const this_t *)> on_receive_;
  const hook_t<void(sockaddr_inet_t, std::shared_ptr<void>, size_t, const this_t *)> on_send_;

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || sc == udp_sock_t::CLIENT_UNICAST, RetType>::type
  setup_(uint16_t port = 0u) {
    struct addrinfo *addr_info, hints;
    int32_t rc, trueflag = 1;
    const char *addr_str;

    if constexpr (sc == udp_sock_t::SERVER_UNICAST) {
      std::memset(&hints, 0x0, sizeof(hints));
      hints.ai_family = family;
      hints.ai_socktype = socktype;
      hints.ai_protocol = protocol;
      addr_str = this->iface_info().host_addr.data();

      if ((rc = ::getaddrinfo(addr_str, std::to_string(port).c_str(), &hints, &addr_info)) != 0 ||
          addr_info == nullptr) {
        throw std::runtime_error(fmt::format("Invalid address or port: \"{0}\",\"{1} (errno : {2}), ({3}), {4}:{5}\"",
                                             addr_str, std::to_string(port), gai_strerror(rc), __func__, __FILE__,
                                             __LINE__));
      }

      if constexpr (is_ipv6)
        reinterpret_cast<sockaddr_inet_t *>(addr_info->ai_addr)->sin6_scope_id = this->iface_info().scopeid;
    }

    open_();

    if ((rc = ::setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof trueflag)) < 0) {
      throw std::runtime_error(
          fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
    }

    if ((rc = ::setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEPORT, &trueflag, sizeof trueflag)) < 0) {
      throw std::runtime_error(
          fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
    }

    if constexpr (sc == udp_sock_t::SERVER_UNICAST) {
      bind_(addr_info);
      ::freeaddrinfo(addr_info);
    }
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<!is_ipv6 && (sc == udp_sock_t::SERVER_BROADCAST || sc == udp_sock_t::CLIENT_BROADCAST),
                          RetType>::type
  setup_(uint16_t port = 0u) {
    struct addrinfo *addr_info, hints;
    int32_t rc, trueflag = 1;

    if constexpr (sc == udp_sock_t::SERVER_BROADCAST) {
      std::memset(&hints, 0x0, sizeof(hints));
      hints.ai_family = family;
      hints.ai_socktype = socktype;
      hints.ai_protocol = protocol;

      if ((rc = ::getaddrinfo(this->iface_info().broadcast.data(), std::to_string(port).c_str(), &hints, &addr_info)) !=
              0 ||
          addr_info == nullptr) {
        throw std::runtime_error(fmt::format("Invalid address or port: \"{0}\",\"{1} (errno : {2}), ({3}), {4}:{5}\"",
                                             this->iface_info().broadcast.data(), std::to_string(port),
                                             gai_strerror(rc), __func__, __FILE__, __LINE__));
      }

      if constexpr (is_ipv6)
        reinterpret_cast<sockaddr_inet_t *>(addr_info->ai_addr)->sin6_scope_id = this->iface_info().scopeid;
    }

    open_();

    if ((rc = ::setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof trueflag)) < 0) {
      throw std::runtime_error(
          fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
    }

    if ((rc = ::setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEPORT, &trueflag, sizeof trueflag)) < 0) {
      throw std::runtime_error(
          fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
    }

    if ((rc = ::setsockopt(sock_fd_, SOL_SOCKET, SO_BROADCAST, &trueflag, sizeof(trueflag))) < 0) {
      throw std::runtime_error(
          fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
    }

    if constexpr (sc == udp_sock_t::SERVER_BROADCAST) {

      bind_(addr_info);
      ::freeaddrinfo(addr_info);
    }
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_MULTICAST || sc == udp_sock_t::CLIENT_MULTICAST, RetType>::type
  setup_(const std::string &multicast_group_addr, uint16_t port) {
    using inet_mreq_t = std::conditional_t<is_ipv6, struct ipv6_mreq, struct ip_mreq>;

    struct addrinfo *addr_info, hints;
    int32_t rc, trueflag = 1;
    inet_addr_t *p_mcast_group_addr, p_mcast_req_multiaddr;
    inet_mreq_t mcast_req;

    std::memset(&hints, 0x0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = socktype;
    hints.ai_protocol = protocol;

    if ((rc = ::getaddrinfo(multicast_group_addr.c_str(), std::to_string(port).c_str(), &hints, &addr_info)) != 0 ||
        addr_info == nullptr) {
      throw std::runtime_error(fmt::format("Invalid address or port: \"{0}\",\"{1} (errno : {2}), ({3}), {4}:{5}\"",
                                           multicast_group_addr, std::to_string(port), gai_strerror(rc), __func__,
                                           __FILE__, __LINE__));
    }

    if constexpr (is_ipv6)
      reinterpret_cast<sockaddr_inet_t *>(addr_info->ai_addr)->sin6_scope_id = this->iface_info().scopeid;

    open_();

    if ((rc = ::setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &trueflag, sizeof trueflag)) < 0) {
      throw std::runtime_error(
          fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
    }

    if ((rc = ::setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEPORT, &trueflag, sizeof trueflag)) < 0) {
      throw std::runtime_error(
          fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
    }

    if constexpr (is_ipv6) {
      p_mcast_group_addr = &reinterpret_cast<sockaddr_inet_t *>(addr_info->ai_addr)->sin6_addr;
      std::memcpy(&mcast_req.ipv6mr_multiaddr, p_mcast_group_addr, sizeof(mcast_req.ipv6mr_multiaddr));
      mcast_req.ipv6mr_interface = 0u;

    } else {
      p_mcast_group_addr = &reinterpret_cast<sockaddr_inet_t *>(addr_info->ai_addr)->sin_addr;
      std::memcpy(&mcast_req.imr_multiaddr, p_mcast_group_addr, sizeof(mcast_req.imr_multiaddr));
      mcast_req.imr_interface.s_addr = ::htonl(INADDR_ANY);
    }

    if constexpr (is_ipv6) {
      if (::setsockopt(sock_fd_, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, reinterpret_cast<char *>(&mcast_req),
                       sizeof(mcast_req)) != 0)
        throw std::runtime_error(fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__,
                                             __FILE__, __LINE__));

    } else {
      if (::setsockopt(sock_fd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, reinterpret_cast<char *>(&mcast_req),
                       sizeof(mcast_req)) != 0) {
        throw std::runtime_error(fmt::format("Setsockopt error (errno = {0}),({1}), {2}:{3}", strerror(errno), __func__,
                                             __FILE__, __LINE__));
      }
    }

    if constexpr (sc == udp_sock_t::SERVER_MULTICAST) {
      bind_(addr_info);
    }

    ::freeaddrinfo(addr_info);
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || (!is_ipv6 && sc == udp_sock_t::SERVER_BROADCAST) ||
                              sc == udp_sock_t::SERVER_MULTICAST,
                          RetType>::type
  clear_() {
    stop();
    if (::epoll_ctl(epfd_, EPOLL_CTL_DEL, sock_fd_, nullptr) < 0u)
      throw std::runtime_error(
          fmt::format("Epoll ctl error (errno = {0}), ({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));

    ::close(sock_fd_);
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::CLIENT_UNICAST || (!is_ipv6 && sc == udp_sock_t::CLIENT_BROADCAST) ||
                              sc == udp_sock_t::CLIENT_MULTICAST,
                          RetType>::type
  clear_() {
    if (::epoll_ctl(epfd_, EPOLL_CTL_DEL, sock_fd_, nullptr) < 0u)
      throw std::runtime_error(
          fmt::format("Epoll ctl error (errno = {0}), ({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));

    ::close(sock_fd_);
  }

  void clear_hooks_() {
    this->on_receive().clear();
    this->on_send().clear();
  }

  void clear_epoll_() {
    ::close(epfd_);
    std::free(events_);
    events_ = nullptr;
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || (!is_ipv6 && sc == udp_sock_t::SERVER_BROADCAST) ||
                              sc == udp_sock_t::SERVER_MULTICAST,
                          RetType>::type
  bind_(const struct addrinfo *addr_info) {
    int32_t rc;
    if ((rc = ::bind(sock_fd_, addr_info->ai_addr, addr_info->ai_addrlen)) != 0) {
      clear_<socket_class>();
      throw std::runtime_error(fmt::format("Could not bind UDP socket (errno = {0}), ({1}), {2}:{3}\"", strerror(rc),
                                           __func__, __FILE__, __LINE__));
    }
  }

  void open_() {
    if ((sock_fd_ = ::socket(family, socktype | SOCK_CLOEXEC | SOCK_NONBLOCK, protocol)) < 0) {
      clear_<socket_class>();
      throw std::runtime_error(fmt::format("Could not create socket, ({0}), {1}:{2}", __func__, __FILE__, __LINE__));
    }

    struct epoll_event event;
    std::memset(&event, 0x0, sizeof(event));
    event.events = epollevents;
    event.data.fd = sock_fd_;

    if (::epoll_ctl(epfd_, EPOLL_CTL_ADD, sock_fd_, &event) < 0u)
      throw std::runtime_error(
          fmt::format("Epoll ctl error (errno = {0}), ({1}), {2}:{3}", strerror(errno), __func__, __FILE__, __LINE__));
  }

  template <udp_sock_t sc = socket_class, typename RetType = void>
  typename std::enable_if<sc == udp_sock_t::SERVER_UNICAST || (!is_ipv6 && sc == udp_sock_t::SERVER_BROADCAST) ||
                              sc == udp_sock_t::SERVER_MULTICAST,
                          RetType>::type
  listen_() const {
    listen_enabled_ = true;
    state_ = state_t::RUNNING;

    while (listen_enabled_)
      static_cast<void>(recv());
    state_ = state_t::STOPPED;
  }
};

#endif /* UDP_SOCK_HPP */