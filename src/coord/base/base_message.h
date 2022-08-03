#pragma once 

#include "coord/component/component.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/argument.h"
#include <cstdlib>
#include <uv.h>
#include <map>
#include <string>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor_database.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

namespace coord {//tolua_export

enum base_message_type {
	base_message_type_request     = 0x00,
	base_message_type_notify      = 0x01,
	base_message_type_response    = 0x02,
	base_message_type_push        = 0x03,
};

enum base_message_data_type {
    base_message_data_type_none     = 0,
    base_message_data_type_string   = 1,
    base_message_data_type_custom   = 2,
    base_message_data_type_argument = 3,
    base_message_data_type_protobuf = 4,
    base_message_data_type_table    = 5,
    base_message_data_type_json     = 6,
};

// ------------------------------------------
// |   type   |  flag  |       other        |
// |----------|--------|--------------------|
// | request  |-xxx000-|<message id>|<route>|
// | notify   |-xxx001-|<route>             |
// | response |-xxx010-|<message id>|<code> |
// | push     |-xxx011-|<route>             |
// ------------------------------------------

struct base_message {
    base_message_type   type;
    uint64_t            id;
    bool                encrypt;
    char                route[257];
    char*               data;
    uint32_t            length;
    int                 code;
    int                 dataType;   // 数据类型
};

int base_message_decode(base_message& message, char* data, size_t len);

int base_message_header_encode(byte_slice& packet, base_message_type type, uint64_t id, const char* route, int code);
int base_response_encode(byte_slice& packet, uint64_t id, int code, const char* data, size_t len);
int base_response_encode(byte_slice& packet, uint64_t id, int code, Argument* argument);
int base_response_encode(byte_slice& packet, uint64_t id, int code, ::google::protobuf::Message* proto);

int base_notify_encode(byte_slice& packet, const char* route, const char* data, size_t len);
int base_notify_encode(byte_slice& packet, const char* route, ::google::protobuf::Message* proto);
int base_request_encode(byte_slice& packet, const char* route, int requestId, ::google::protobuf::Message* proto);
int base_request_encode(byte_slice& packet, const char* route, int requestId, const char* data, size_t len);
int base_request_encode(byte_slice& packet, const char* route, int requestId, Argument* argument);

int base_message_response_header_encode(byte_slice& message, base_message_type type, base_message_data_type dataType, uint64_t id, int code);

template<typename TRequest>
int base_request_decode(base_message* message, TRequest* request) {
    request->Id = message->id;
    request->Route = message->route;
    request->dataType = message->dataType;
    request->payload.Resize(0);
    coord::Append(request->payload, message->data, message->length);
    return 0;
}

template<typename TNotify>
int base_notify_decode(base_message* message, TNotify* notify) {
    notify->Route = message->route;
    notify->dataType = message->dataType;
    notify->payload.Resize(0);
    coord::Append(notify->payload, message->data, message->length);
    return 0;
}

template<typename TResult>
int base_result_decode(base_message* message, TResult* result) {
    result->Code = message->code;
    result->dataType = message->dataType;
    result->payload.Resize(0);
    coord::Append(result->payload, message->data, message->length);
    return 0;
}

}//tolua_export


