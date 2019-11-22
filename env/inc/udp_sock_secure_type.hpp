#ifndef UDP_SOCK_SECURE_TYPE_HPP
#define UDP_SOCK_SECURE_TYPE_HPP

#include <cstdint>

enum struct udp_sock_secure_t : uint32_t {
  CLIENT_UNICAST_SECURE_AES = 1u,
  SERVER_UNICAST_SECURE_AES,
  CLIENT_MULTICAST_SECURE_AES,
  SERVER_MULTICAST_SECURE_AES,
  CLIENT_BROADCAST_SECURE_AES,
  SERVER_BROADCAST_SECURE_AES
};

#endif /* UDP_SOCK_SECURE_TYPE_HPP */
