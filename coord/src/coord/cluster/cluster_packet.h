#pragma once 

#include "coord/component/component.h"
#include "coord/builtin/slice.h"
#include <cstdlib>
#include <libuv/uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export

namespace cluster {


enum packet_type {
    packet_type_handshake       = 1,
    packet_type_handshakeack    = 2,
    PacketType_Heartbeat        = 3,
    PacketType_Data             = 4,
    PacketType_Kick             = 5,
};

struct cluster_packet_header {
    uint8_t type;
    uint8_t length[3];
};


struct cluster_packet {
    uint8_t     type;
    uint32_t    length;
    char*       data;
};

int clkusterPacketEncode(byte_slice& packet, packet_type type, const char* data, size_t len);
int clusterPacketHeaderEncode(byte_slice& packet, packet_type type, size_t len);
int clusterPacketDecode(cluster_packet& packet, char* data, size_t len);

}//tolua_export
}//tolua_export


