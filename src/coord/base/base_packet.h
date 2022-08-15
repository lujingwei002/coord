#pragma once 

#include "coord/coordx.h"
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

enum base_packet_type {
    base_packet_type_handshake       = 1,
    base_packet_type_handshakeack    = 2,
    base_packet_type_heartbeat       = 3,
    base_packet_type_data            = 4,
    base_packet_type_kick            = 5,
};

struct base_packet_header {
    uint8_t type;
    uint8_t length[3];
};


struct base_packet {
    uint8_t     type;
    uint32_t    length;
    char*       data;
};

int base_packet_encode(byte_slice& packet, base_packet_type type, const char* data, size_t len);
int base_packet_encode(byte_slice& packet, base_packet_type type, ::google::protobuf::Message* message);

int base_packet_header_encode(byte_slice& packet, base_packet_type type, size_t len);
int base_packet_decode(base_packet& packet, char* data, size_t len);


}//tolua_export


