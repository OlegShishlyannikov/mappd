// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: composition_info.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_composition_5finfo_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_composition_5finfo_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_composition_5finfo_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_composition_5finfo_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_composition_5finfo_2eproto;
class composition_info_t;
class composition_info_tDefaultTypeInternal;
extern composition_info_tDefaultTypeInternal _composition_info_t_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::composition_info_t* Arena::CreateMaybeMessage<::composition_info_t>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class composition_info_t :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:composition_info_t) */ {
 public:
  composition_info_t();
  virtual ~composition_info_t();

  composition_info_t(const composition_info_t& from);
  composition_info_t(composition_info_t&& from) noexcept
    : composition_info_t() {
    *this = ::std::move(from);
  }

  inline composition_info_t& operator=(const composition_info_t& from) {
    CopyFrom(from);
    return *this;
  }
  inline composition_info_t& operator=(composition_info_t&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const composition_info_t& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const composition_info_t* internal_default_instance() {
    return reinterpret_cast<const composition_info_t*>(
               &_composition_info_t_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(composition_info_t& a, composition_info_t& b) {
    a.Swap(&b);
  }
  inline void Swap(composition_info_t* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline composition_info_t* New() const final {
    return CreateMaybeMessage<composition_info_t>(nullptr);
  }

  composition_info_t* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<composition_info_t>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const composition_info_t& from);
  void MergeFrom(const composition_info_t& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(composition_info_t* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "composition_info_t";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_composition_5finfo_2eproto);
    return ::descriptor_table_composition_5finfo_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
    kNameHashFieldNumber = 2,
    kCompositionTypeHashFieldNumber = 3,
  };
  // required bytes id = 1 [default = ""];
  bool has_id() const;
  private:
  bool _internal_has_id() const;
  public:
  void clear_id();
  const std::string& id() const;
  void set_id(const std::string& value);
  void set_id(std::string&& value);
  void set_id(const char* value);
  void set_id(const void* value, size_t size);
  std::string* mutable_id();
  std::string* release_id();
  void set_allocated_id(std::string* id);
  private:
  const std::string& _internal_id() const;
  void _internal_set_id(const std::string& value);
  std::string* _internal_mutable_id();
  public:

  // required bytes name_hash = 2 [default = ""];
  bool has_name_hash() const;
  private:
  bool _internal_has_name_hash() const;
  public:
  void clear_name_hash();
  const std::string& name_hash() const;
  void set_name_hash(const std::string& value);
  void set_name_hash(std::string&& value);
  void set_name_hash(const char* value);
  void set_name_hash(const void* value, size_t size);
  std::string* mutable_name_hash();
  std::string* release_name_hash();
  void set_allocated_name_hash(std::string* name_hash);
  private:
  const std::string& _internal_name_hash() const;
  void _internal_set_name_hash(const std::string& value);
  std::string* _internal_mutable_name_hash();
  public:

  // required bytes composition_type_hash = 3 [default = ""];
  bool has_composition_type_hash() const;
  private:
  bool _internal_has_composition_type_hash() const;
  public:
  void clear_composition_type_hash();
  const std::string& composition_type_hash() const;
  void set_composition_type_hash(const std::string& value);
  void set_composition_type_hash(std::string&& value);
  void set_composition_type_hash(const char* value);
  void set_composition_type_hash(const void* value, size_t size);
  std::string* mutable_composition_type_hash();
  std::string* release_composition_type_hash();
  void set_allocated_composition_type_hash(std::string* composition_type_hash);
  private:
  const std::string& _internal_composition_type_hash() const;
  void _internal_set_composition_type_hash(const std::string& value);
  std::string* _internal_mutable_composition_type_hash();
  public:

  // @@protoc_insertion_point(class_scope:composition_info_t)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr id_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_hash_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr composition_type_hash_;
  friend struct ::TableStruct_composition_5finfo_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// composition_info_t

// required bytes id = 1 [default = ""];
inline bool composition_info_t::_internal_has_id() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool composition_info_t::has_id() const {
  return _internal_has_id();
}
inline void composition_info_t::clear_id() {
  id_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& composition_info_t::id() const {
  // @@protoc_insertion_point(field_get:composition_info_t.id)
  return _internal_id();
}
inline void composition_info_t::set_id(const std::string& value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:composition_info_t.id)
}
inline std::string* composition_info_t::mutable_id() {
  // @@protoc_insertion_point(field_mutable:composition_info_t.id)
  return _internal_mutable_id();
}
inline const std::string& composition_info_t::_internal_id() const {
  return id_.GetNoArena();
}
inline void composition_info_t::_internal_set_id(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void composition_info_t::set_id(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  id_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:composition_info_t.id)
}
inline void composition_info_t::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:composition_info_t.id)
}
inline void composition_info_t::set_id(const void* value, size_t size) {
  _has_bits_[0] |= 0x00000001u;
  id_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:composition_info_t.id)
}
inline std::string* composition_info_t::_internal_mutable_id() {
  _has_bits_[0] |= 0x00000001u;
  return id_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* composition_info_t::release_id() {
  // @@protoc_insertion_point(field_release:composition_info_t.id)
  if (!_internal_has_id()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return id_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void composition_info_t::set_allocated_id(std::string* id) {
  if (id != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  id_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:composition_info_t.id)
}

// required bytes name_hash = 2 [default = ""];
inline bool composition_info_t::_internal_has_name_hash() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool composition_info_t::has_name_hash() const {
  return _internal_has_name_hash();
}
inline void composition_info_t::clear_name_hash() {
  name_hash_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000002u;
}
inline const std::string& composition_info_t::name_hash() const {
  // @@protoc_insertion_point(field_get:composition_info_t.name_hash)
  return _internal_name_hash();
}
inline void composition_info_t::set_name_hash(const std::string& value) {
  _internal_set_name_hash(value);
  // @@protoc_insertion_point(field_set:composition_info_t.name_hash)
}
inline std::string* composition_info_t::mutable_name_hash() {
  // @@protoc_insertion_point(field_mutable:composition_info_t.name_hash)
  return _internal_mutable_name_hash();
}
inline const std::string& composition_info_t::_internal_name_hash() const {
  return name_hash_.GetNoArena();
}
inline void composition_info_t::_internal_set_name_hash(const std::string& value) {
  _has_bits_[0] |= 0x00000002u;
  name_hash_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void composition_info_t::set_name_hash(std::string&& value) {
  _has_bits_[0] |= 0x00000002u;
  name_hash_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:composition_info_t.name_hash)
}
inline void composition_info_t::set_name_hash(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000002u;
  name_hash_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:composition_info_t.name_hash)
}
inline void composition_info_t::set_name_hash(const void* value, size_t size) {
  _has_bits_[0] |= 0x00000002u;
  name_hash_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:composition_info_t.name_hash)
}
inline std::string* composition_info_t::_internal_mutable_name_hash() {
  _has_bits_[0] |= 0x00000002u;
  return name_hash_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* composition_info_t::release_name_hash() {
  // @@protoc_insertion_point(field_release:composition_info_t.name_hash)
  if (!_internal_has_name_hash()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000002u;
  return name_hash_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void composition_info_t::set_allocated_name_hash(std::string* name_hash) {
  if (name_hash != nullptr) {
    _has_bits_[0] |= 0x00000002u;
  } else {
    _has_bits_[0] &= ~0x00000002u;
  }
  name_hash_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name_hash);
  // @@protoc_insertion_point(field_set_allocated:composition_info_t.name_hash)
}

// required bytes composition_type_hash = 3 [default = ""];
inline bool composition_info_t::_internal_has_composition_type_hash() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool composition_info_t::has_composition_type_hash() const {
  return _internal_has_composition_type_hash();
}
inline void composition_info_t::clear_composition_type_hash() {
  composition_type_hash_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _has_bits_[0] &= ~0x00000004u;
}
inline const std::string& composition_info_t::composition_type_hash() const {
  // @@protoc_insertion_point(field_get:composition_info_t.composition_type_hash)
  return _internal_composition_type_hash();
}
inline void composition_info_t::set_composition_type_hash(const std::string& value) {
  _internal_set_composition_type_hash(value);
  // @@protoc_insertion_point(field_set:composition_info_t.composition_type_hash)
}
inline std::string* composition_info_t::mutable_composition_type_hash() {
  // @@protoc_insertion_point(field_mutable:composition_info_t.composition_type_hash)
  return _internal_mutable_composition_type_hash();
}
inline const std::string& composition_info_t::_internal_composition_type_hash() const {
  return composition_type_hash_.GetNoArena();
}
inline void composition_info_t::_internal_set_composition_type_hash(const std::string& value) {
  _has_bits_[0] |= 0x00000004u;
  composition_type_hash_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void composition_info_t::set_composition_type_hash(std::string&& value) {
  _has_bits_[0] |= 0x00000004u;
  composition_type_hash_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:composition_info_t.composition_type_hash)
}
inline void composition_info_t::set_composition_type_hash(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000004u;
  composition_type_hash_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:composition_info_t.composition_type_hash)
}
inline void composition_info_t::set_composition_type_hash(const void* value, size_t size) {
  _has_bits_[0] |= 0x00000004u;
  composition_type_hash_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:composition_info_t.composition_type_hash)
}
inline std::string* composition_info_t::_internal_mutable_composition_type_hash() {
  _has_bits_[0] |= 0x00000004u;
  return composition_type_hash_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* composition_info_t::release_composition_type_hash() {
  // @@protoc_insertion_point(field_release:composition_info_t.composition_type_hash)
  if (!_internal_has_composition_type_hash()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000004u;
  return composition_type_hash_.ReleaseNonDefaultNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void composition_info_t::set_allocated_composition_type_hash(std::string* composition_type_hash) {
  if (composition_type_hash != nullptr) {
    _has_bits_[0] |= 0x00000004u;
  } else {
    _has_bits_[0] &= ~0x00000004u;
  }
  composition_type_hash_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), composition_type_hash);
  // @@protoc_insertion_point(field_set_allocated:composition_info_t.composition_type_hash)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_composition_5finfo_2eproto
