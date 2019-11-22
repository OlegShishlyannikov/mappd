// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: composition_info.proto

#ifndef PROTOBUF_INCLUDED_composition_5finfo_2eproto
#define PROTOBUF_INCLUDED_composition_5finfo_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_composition_5finfo_2eproto 

namespace protobuf_composition_5finfo_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_composition_5finfo_2eproto
class composition_info_t;
class composition_info_tDefaultTypeInternal;
extern composition_info_tDefaultTypeInternal _composition_info_t_default_instance_;
namespace google {
namespace protobuf {
template<> ::composition_info_t* Arena::CreateMaybeMessage<::composition_info_t>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class composition_info_t : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:composition_info_t) */ {
 public:
  composition_info_t();
  virtual ~composition_info_t();

  composition_info_t(const composition_info_t& from);

  inline composition_info_t& operator=(const composition_info_t& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  composition_info_t(composition_info_t&& from) noexcept
    : composition_info_t() {
    *this = ::std::move(from);
  }

  inline composition_info_t& operator=(composition_info_t&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const composition_info_t& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const composition_info_t* internal_default_instance() {
    return reinterpret_cast<const composition_info_t*>(
               &_composition_info_t_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(composition_info_t* other);
  friend void swap(composition_info_t& a, composition_info_t& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline composition_info_t* New() const final {
    return CreateMaybeMessage<composition_info_t>(NULL);
  }

  composition_info_t* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<composition_info_t>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const composition_info_t& from);
  void MergeFrom(const composition_info_t& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(composition_info_t* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required bytes id = 1 [default = ""];
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  const ::std::string& id() const;
  void set_id(const ::std::string& value);
  #if LANG_CXX11
  void set_id(::std::string&& value);
  #endif
  void set_id(const char* value);
  void set_id(const void* value, size_t size);
  ::std::string* mutable_id();
  ::std::string* release_id();
  void set_allocated_id(::std::string* id);

  // required bytes name_hash = 2 [default = ""];
  bool has_name_hash() const;
  void clear_name_hash();
  static const int kNameHashFieldNumber = 2;
  const ::std::string& name_hash() const;
  void set_name_hash(const ::std::string& value);
  #if LANG_CXX11
  void set_name_hash(::std::string&& value);
  #endif
  void set_name_hash(const char* value);
  void set_name_hash(const void* value, size_t size);
  ::std::string* mutable_name_hash();
  ::std::string* release_name_hash();
  void set_allocated_name_hash(::std::string* name_hash);

  // required bytes composition_type_hash = 3 [default = ""];
  bool has_composition_type_hash() const;
  void clear_composition_type_hash();
  static const int kCompositionTypeHashFieldNumber = 3;
  const ::std::string& composition_type_hash() const;
  void set_composition_type_hash(const ::std::string& value);
  #if LANG_CXX11
  void set_composition_type_hash(::std::string&& value);
  #endif
  void set_composition_type_hash(const char* value);
  void set_composition_type_hash(const void* value, size_t size);
  ::std::string* mutable_composition_type_hash();
  ::std::string* release_composition_type_hash();
  void set_allocated_composition_type_hash(::std::string* composition_type_hash);

  // @@protoc_insertion_point(class_scope:composition_info_t)
 private:
  void set_has_id();
  void clear_has_id();
  void set_has_name_hash();
  void clear_has_name_hash();
  void set_has_composition_type_hash();
  void clear_has_composition_type_hash();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr name_hash_;
  ::google::protobuf::internal::ArenaStringPtr composition_type_hash_;
  friend struct ::protobuf_composition_5finfo_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// composition_info_t

// required bytes id = 1 [default = ""];
inline bool composition_info_t::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void composition_info_t::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void composition_info_t::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void composition_info_t::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_id();
}
inline const ::std::string& composition_info_t::id() const {
  // @@protoc_insertion_point(field_get:composition_info_t.id)
  return id_.GetNoArena();
}
inline void composition_info_t::set_id(const ::std::string& value) {
  set_has_id();
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:composition_info_t.id)
}
#if LANG_CXX11
inline void composition_info_t::set_id(::std::string&& value) {
  set_has_id();
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:composition_info_t.id)
}
#endif
inline void composition_info_t::set_id(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_id();
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:composition_info_t.id)
}
inline void composition_info_t::set_id(const void* value, size_t size) {
  set_has_id();
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:composition_info_t.id)
}
inline ::std::string* composition_info_t::mutable_id() {
  set_has_id();
  // @@protoc_insertion_point(field_mutable:composition_info_t.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* composition_info_t::release_id() {
  // @@protoc_insertion_point(field_release:composition_info_t.id)
  if (!has_id()) {
    return NULL;
  }
  clear_has_id();
  return id_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void composition_info_t::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    set_has_id();
  } else {
    clear_has_id();
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:composition_info_t.id)
}

// required bytes name_hash = 2 [default = ""];
inline bool composition_info_t::has_name_hash() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void composition_info_t::set_has_name_hash() {
  _has_bits_[0] |= 0x00000002u;
}
inline void composition_info_t::clear_has_name_hash() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void composition_info_t::clear_name_hash() {
  name_hash_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name_hash();
}
inline const ::std::string& composition_info_t::name_hash() const {
  // @@protoc_insertion_point(field_get:composition_info_t.name_hash)
  return name_hash_.GetNoArena();
}
inline void composition_info_t::set_name_hash(const ::std::string& value) {
  set_has_name_hash();
  name_hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:composition_info_t.name_hash)
}
#if LANG_CXX11
inline void composition_info_t::set_name_hash(::std::string&& value) {
  set_has_name_hash();
  name_hash_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:composition_info_t.name_hash)
}
#endif
inline void composition_info_t::set_name_hash(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_name_hash();
  name_hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:composition_info_t.name_hash)
}
inline void composition_info_t::set_name_hash(const void* value, size_t size) {
  set_has_name_hash();
  name_hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:composition_info_t.name_hash)
}
inline ::std::string* composition_info_t::mutable_name_hash() {
  set_has_name_hash();
  // @@protoc_insertion_point(field_mutable:composition_info_t.name_hash)
  return name_hash_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* composition_info_t::release_name_hash() {
  // @@protoc_insertion_point(field_release:composition_info_t.name_hash)
  if (!has_name_hash()) {
    return NULL;
  }
  clear_has_name_hash();
  return name_hash_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void composition_info_t::set_allocated_name_hash(::std::string* name_hash) {
  if (name_hash != NULL) {
    set_has_name_hash();
  } else {
    clear_has_name_hash();
  }
  name_hash_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name_hash);
  // @@protoc_insertion_point(field_set_allocated:composition_info_t.name_hash)
}

// required bytes composition_type_hash = 3 [default = ""];
inline bool composition_info_t::has_composition_type_hash() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void composition_info_t::set_has_composition_type_hash() {
  _has_bits_[0] |= 0x00000004u;
}
inline void composition_info_t::clear_has_composition_type_hash() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void composition_info_t::clear_composition_type_hash() {
  composition_type_hash_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_composition_type_hash();
}
inline const ::std::string& composition_info_t::composition_type_hash() const {
  // @@protoc_insertion_point(field_get:composition_info_t.composition_type_hash)
  return composition_type_hash_.GetNoArena();
}
inline void composition_info_t::set_composition_type_hash(const ::std::string& value) {
  set_has_composition_type_hash();
  composition_type_hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:composition_info_t.composition_type_hash)
}
#if LANG_CXX11
inline void composition_info_t::set_composition_type_hash(::std::string&& value) {
  set_has_composition_type_hash();
  composition_type_hash_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:composition_info_t.composition_type_hash)
}
#endif
inline void composition_info_t::set_composition_type_hash(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_composition_type_hash();
  composition_type_hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:composition_info_t.composition_type_hash)
}
inline void composition_info_t::set_composition_type_hash(const void* value, size_t size) {
  set_has_composition_type_hash();
  composition_type_hash_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:composition_info_t.composition_type_hash)
}
inline ::std::string* composition_info_t::mutable_composition_type_hash() {
  set_has_composition_type_hash();
  // @@protoc_insertion_point(field_mutable:composition_info_t.composition_type_hash)
  return composition_type_hash_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* composition_info_t::release_composition_type_hash() {
  // @@protoc_insertion_point(field_release:composition_info_t.composition_type_hash)
  if (!has_composition_type_hash()) {
    return NULL;
  }
  clear_has_composition_type_hash();
  return composition_type_hash_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void composition_info_t::set_allocated_composition_type_hash(::std::string* composition_type_hash) {
  if (composition_type_hash != NULL) {
    set_has_composition_type_hash();
  } else {
    clear_has_composition_type_hash();
  }
  composition_type_hash_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), composition_type_hash);
  // @@protoc_insertion_point(field_set_allocated:composition_info_t.composition_type_hash)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_composition_5finfo_2eproto
