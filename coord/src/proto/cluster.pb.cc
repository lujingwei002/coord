// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cluster.proto

#include "cluster.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace clusterpb {
constexpr HandshakeRequest::HandshakeRequest(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : nodename_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , host_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , version_(int64_t{0})
  , port_(0){}
struct HandshakeRequestDefaultTypeInternal {
  constexpr HandshakeRequestDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~HandshakeRequestDefaultTypeInternal() {}
  union {
    HandshakeRequest _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT HandshakeRequestDefaultTypeInternal _HandshakeRequest_default_instance_;
constexpr HandshakeResponse::HandshakeResponse(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : code_(0){}
struct HandshakeResponseDefaultTypeInternal {
  constexpr HandshakeResponseDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~HandshakeResponseDefaultTypeInternal() {}
  union {
    HandshakeResponse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT HandshakeResponseDefaultTypeInternal _HandshakeResponse_default_instance_;
constexpr HandshakeAck::HandshakeAck(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized){}
struct HandshakeAckDefaultTypeInternal {
  constexpr HandshakeAckDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~HandshakeAckDefaultTypeInternal() {}
  union {
    HandshakeAck _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT HandshakeAckDefaultTypeInternal _HandshakeAck_default_instance_;
constexpr GateInstead::GateInstead(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : userid_(uint64_t{0u}){}
struct GateInsteadDefaultTypeInternal {
  constexpr GateInsteadDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~GateInsteadDefaultTypeInternal() {}
  union {
    GateInstead _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT GateInsteadDefaultTypeInternal _GateInstead_default_instance_;
}  // namespace clusterpb
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_cluster_2eproto[4];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_cluster_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_cluster_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_cluster_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeRequest, nodename_),
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeRequest, host_),
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeRequest, port_),
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeRequest, version_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeResponse, code_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::clusterpb::HandshakeAck, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::clusterpb::GateInstead, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::clusterpb::GateInstead, userid_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::clusterpb::HandshakeRequest)},
  { 9, -1, sizeof(::clusterpb::HandshakeResponse)},
  { 15, -1, sizeof(::clusterpb::HandshakeAck)},
  { 20, -1, sizeof(::clusterpb::GateInstead)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::clusterpb::_HandshakeRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::clusterpb::_HandshakeResponse_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::clusterpb::_HandshakeAck_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::clusterpb::_GateInstead_default_instance_),
};

const char descriptor_table_protodef_cluster_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rcluster.proto\022\tclusterpb\"Q\n\020HandshakeR"
  "equest\022\020\n\010NodeName\030\001 \001(\t\022\014\n\004Host\030\002 \001(\t\022\014"
  "\n\004Port\030\003 \001(\005\022\017\n\007Version\030\004 \001(\003\"!\n\021Handsha"
  "keResponse\022\014\n\004Code\030\001 \001(\005\"\016\n\014HandshakeAck"
  "\"\035\n\013GateInstead\022\016\n\006userId\030\001 \001(\004B\016Z\014./;cl"
  "usterpbb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_cluster_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_cluster_2eproto = {
  false, false, 215, descriptor_table_protodef_cluster_2eproto, "cluster.proto", 
  &descriptor_table_cluster_2eproto_once, nullptr, 0, 4,
  schemas, file_default_instances, TableStruct_cluster_2eproto::offsets,
  file_level_metadata_cluster_2eproto, file_level_enum_descriptors_cluster_2eproto, file_level_service_descriptors_cluster_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_cluster_2eproto_getter() {
  return &descriptor_table_cluster_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_cluster_2eproto(&descriptor_table_cluster_2eproto);
namespace clusterpb {

// ===================================================================

class HandshakeRequest::_Internal {
 public:
};

HandshakeRequest::HandshakeRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:clusterpb.HandshakeRequest)
}
HandshakeRequest::HandshakeRequest(const HandshakeRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  nodename_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_nodename().empty()) {
    nodename_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_nodename(), 
      GetArenaForAllocation());
  }
  host_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_host().empty()) {
    host_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_host(), 
      GetArenaForAllocation());
  }
  ::memcpy(&version_, &from.version_,
    static_cast<size_t>(reinterpret_cast<char*>(&port_) -
    reinterpret_cast<char*>(&version_)) + sizeof(port_));
  // @@protoc_insertion_point(copy_constructor:clusterpb.HandshakeRequest)
}

void HandshakeRequest::SharedCtor() {
nodename_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
host_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&version_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&port_) -
    reinterpret_cast<char*>(&version_)) + sizeof(port_));
}

HandshakeRequest::~HandshakeRequest() {
  // @@protoc_insertion_point(destructor:clusterpb.HandshakeRequest)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void HandshakeRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  nodename_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  host_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void HandshakeRequest::ArenaDtor(void* object) {
  HandshakeRequest* _this = reinterpret_cast< HandshakeRequest* >(object);
  (void)_this;
}
void HandshakeRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void HandshakeRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void HandshakeRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:clusterpb.HandshakeRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  nodename_.ClearToEmpty();
  host_.ClearToEmpty();
  ::memset(&version_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&port_) -
      reinterpret_cast<char*>(&version_)) + sizeof(port_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* HandshakeRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string NodeName = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_nodename();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "clusterpb.HandshakeRequest.NodeName"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string Host = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_host();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "clusterpb.HandshakeRequest.Host"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 Port = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          port_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int64 Version = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          version_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* HandshakeRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:clusterpb.HandshakeRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string NodeName = 1;
  if (!this->nodename().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_nodename().data(), static_cast<int>(this->_internal_nodename().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "clusterpb.HandshakeRequest.NodeName");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_nodename(), target);
  }

  // string Host = 2;
  if (!this->host().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_host().data(), static_cast<int>(this->_internal_host().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "clusterpb.HandshakeRequest.Host");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_host(), target);
  }

  // int32 Port = 3;
  if (this->port() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_port(), target);
  }

  // int64 Version = 4;
  if (this->version() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(4, this->_internal_version(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:clusterpb.HandshakeRequest)
  return target;
}

size_t HandshakeRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:clusterpb.HandshakeRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string NodeName = 1;
  if (!this->nodename().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_nodename());
  }

  // string Host = 2;
  if (!this->host().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_host());
  }

  // int64 Version = 4;
  if (this->version() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_version());
  }

  // int32 Port = 3;
  if (this->port() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_port());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void HandshakeRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:clusterpb.HandshakeRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const HandshakeRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<HandshakeRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:clusterpb.HandshakeRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:clusterpb.HandshakeRequest)
    MergeFrom(*source);
  }
}

void HandshakeRequest::MergeFrom(const HandshakeRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:clusterpb.HandshakeRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from.nodename().empty()) {
    _internal_set_nodename(from._internal_nodename());
  }
  if (!from.host().empty()) {
    _internal_set_host(from._internal_host());
  }
  if (from.version() != 0) {
    _internal_set_version(from._internal_version());
  }
  if (from.port() != 0) {
    _internal_set_port(from._internal_port());
  }
}

void HandshakeRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:clusterpb.HandshakeRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HandshakeRequest::CopyFrom(const HandshakeRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:clusterpb.HandshakeRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HandshakeRequest::IsInitialized() const {
  return true;
}

void HandshakeRequest::InternalSwap(HandshakeRequest* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &nodename_, GetArenaForAllocation(),
      &other->nodename_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &host_, GetArenaForAllocation(),
      &other->host_, other->GetArenaForAllocation()
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(HandshakeRequest, port_)
      + sizeof(HandshakeRequest::port_)
      - PROTOBUF_FIELD_OFFSET(HandshakeRequest, version_)>(
          reinterpret_cast<char*>(&version_),
          reinterpret_cast<char*>(&other->version_));
}

::PROTOBUF_NAMESPACE_ID::Metadata HandshakeRequest::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_cluster_2eproto_getter, &descriptor_table_cluster_2eproto_once,
      file_level_metadata_cluster_2eproto[0]);
}

// ===================================================================

class HandshakeResponse::_Internal {
 public:
};

HandshakeResponse::HandshakeResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:clusterpb.HandshakeResponse)
}
HandshakeResponse::HandshakeResponse(const HandshakeResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  code_ = from.code_;
  // @@protoc_insertion_point(copy_constructor:clusterpb.HandshakeResponse)
}

void HandshakeResponse::SharedCtor() {
code_ = 0;
}

HandshakeResponse::~HandshakeResponse() {
  // @@protoc_insertion_point(destructor:clusterpb.HandshakeResponse)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void HandshakeResponse::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void HandshakeResponse::ArenaDtor(void* object) {
  HandshakeResponse* _this = reinterpret_cast< HandshakeResponse* >(object);
  (void)_this;
}
void HandshakeResponse::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void HandshakeResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void HandshakeResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:clusterpb.HandshakeResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  code_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* HandshakeResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 Code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          code_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* HandshakeResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:clusterpb.HandshakeResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 Code = 1;
  if (this->code() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_code(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:clusterpb.HandshakeResponse)
  return target;
}

size_t HandshakeResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:clusterpb.HandshakeResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 Code = 1;
  if (this->code() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_code());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void HandshakeResponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:clusterpb.HandshakeResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const HandshakeResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<HandshakeResponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:clusterpb.HandshakeResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:clusterpb.HandshakeResponse)
    MergeFrom(*source);
  }
}

void HandshakeResponse::MergeFrom(const HandshakeResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:clusterpb.HandshakeResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.code() != 0) {
    _internal_set_code(from._internal_code());
  }
}

void HandshakeResponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:clusterpb.HandshakeResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HandshakeResponse::CopyFrom(const HandshakeResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:clusterpb.HandshakeResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HandshakeResponse::IsInitialized() const {
  return true;
}

void HandshakeResponse::InternalSwap(HandshakeResponse* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(code_, other->code_);
}

::PROTOBUF_NAMESPACE_ID::Metadata HandshakeResponse::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_cluster_2eproto_getter, &descriptor_table_cluster_2eproto_once,
      file_level_metadata_cluster_2eproto[1]);
}

// ===================================================================

class HandshakeAck::_Internal {
 public:
};

HandshakeAck::HandshakeAck(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:clusterpb.HandshakeAck)
}
HandshakeAck::HandshakeAck(const HandshakeAck& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:clusterpb.HandshakeAck)
}

void HandshakeAck::SharedCtor() {
}

HandshakeAck::~HandshakeAck() {
  // @@protoc_insertion_point(destructor:clusterpb.HandshakeAck)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void HandshakeAck::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void HandshakeAck::ArenaDtor(void* object) {
  HandshakeAck* _this = reinterpret_cast< HandshakeAck* >(object);
  (void)_this;
}
void HandshakeAck::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void HandshakeAck::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void HandshakeAck::Clear() {
// @@protoc_insertion_point(message_clear_start:clusterpb.HandshakeAck)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* HandshakeAck::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* HandshakeAck::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:clusterpb.HandshakeAck)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:clusterpb.HandshakeAck)
  return target;
}

size_t HandshakeAck::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:clusterpb.HandshakeAck)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void HandshakeAck::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:clusterpb.HandshakeAck)
  GOOGLE_DCHECK_NE(&from, this);
  const HandshakeAck* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<HandshakeAck>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:clusterpb.HandshakeAck)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:clusterpb.HandshakeAck)
    MergeFrom(*source);
  }
}

void HandshakeAck::MergeFrom(const HandshakeAck& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:clusterpb.HandshakeAck)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void HandshakeAck::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:clusterpb.HandshakeAck)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HandshakeAck::CopyFrom(const HandshakeAck& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:clusterpb.HandshakeAck)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HandshakeAck::IsInitialized() const {
  return true;
}

void HandshakeAck::InternalSwap(HandshakeAck* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
}

::PROTOBUF_NAMESPACE_ID::Metadata HandshakeAck::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_cluster_2eproto_getter, &descriptor_table_cluster_2eproto_once,
      file_level_metadata_cluster_2eproto[2]);
}

// ===================================================================

class GateInstead::_Internal {
 public:
};

GateInstead::GateInstead(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:clusterpb.GateInstead)
}
GateInstead::GateInstead(const GateInstead& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  userid_ = from.userid_;
  // @@protoc_insertion_point(copy_constructor:clusterpb.GateInstead)
}

void GateInstead::SharedCtor() {
userid_ = uint64_t{0u};
}

GateInstead::~GateInstead() {
  // @@protoc_insertion_point(destructor:clusterpb.GateInstead)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void GateInstead::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void GateInstead::ArenaDtor(void* object) {
  GateInstead* _this = reinterpret_cast< GateInstead* >(object);
  (void)_this;
}
void GateInstead::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void GateInstead::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void GateInstead::Clear() {
// @@protoc_insertion_point(message_clear_start:clusterpb.GateInstead)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  userid_ = uint64_t{0u};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* GateInstead::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint64 userId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          userid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* GateInstead::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:clusterpb.GateInstead)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint64 userId = 1;
  if (this->userid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(1, this->_internal_userid(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:clusterpb.GateInstead)
  return target;
}

size_t GateInstead::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:clusterpb.GateInstead)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint64 userId = 1;
  if (this->userid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_userid());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void GateInstead::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:clusterpb.GateInstead)
  GOOGLE_DCHECK_NE(&from, this);
  const GateInstead* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<GateInstead>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:clusterpb.GateInstead)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:clusterpb.GateInstead)
    MergeFrom(*source);
  }
}

void GateInstead::MergeFrom(const GateInstead& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:clusterpb.GateInstead)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.userid() != 0) {
    _internal_set_userid(from._internal_userid());
  }
}

void GateInstead::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:clusterpb.GateInstead)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GateInstead::CopyFrom(const GateInstead& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:clusterpb.GateInstead)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GateInstead::IsInitialized() const {
  return true;
}

void GateInstead::InternalSwap(GateInstead* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(userid_, other->userid_);
}

::PROTOBUF_NAMESPACE_ID::Metadata GateInstead::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_cluster_2eproto_getter, &descriptor_table_cluster_2eproto_once,
      file_level_metadata_cluster_2eproto[3]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace clusterpb
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::clusterpb::HandshakeRequest* Arena::CreateMaybeMessage< ::clusterpb::HandshakeRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::clusterpb::HandshakeRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::clusterpb::HandshakeResponse* Arena::CreateMaybeMessage< ::clusterpb::HandshakeResponse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::clusterpb::HandshakeResponse >(arena);
}
template<> PROTOBUF_NOINLINE ::clusterpb::HandshakeAck* Arena::CreateMaybeMessage< ::clusterpb::HandshakeAck >(Arena* arena) {
  return Arena::CreateMessageInternal< ::clusterpb::HandshakeAck >(arena);
}
template<> PROTOBUF_NOINLINE ::clusterpb::GateInstead* Arena::CreateMaybeMessage< ::clusterpb::GateInstead >(Arena* arena) {
  return Arena::CreateMessageInternal< ::clusterpb::GateInstead >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
