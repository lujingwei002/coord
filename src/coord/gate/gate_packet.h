#pragma once 

#include "coord/component/component.h"
#include "coord/coordx.h"
#include <stdlib.h>
#include <uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export

namespace gate {


enum PacketType {
    PacketType_Handshake    = 1,
    PacketType_HandshakeAck = 2,
    PacketType_Heartbeat    = 3,
    PacketType_Data         = 4,
    PacketType_Kick         = 5,
};

struct PacketHeader {
    uint8_t type;
    uint8_t length[3];
};

struct PacketData {
    PacketHeader    header;
    char            data[0];
};

struct Packet {
    uint8_t     type;
    uint32_t    length;
    char*       data;
};

int PacketEncode(byte_slice& packet, PacketType type, const char* data, size_t len);
int PacketHeaderEncode(byte_slice& packet, PacketType type, size_t len);

int PacketDecode(Packet& packet, char* data, size_t len);

}//tolua_export
}//tolua_export


