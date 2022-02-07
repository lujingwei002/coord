#pragma once 

#include "coord/component/component.h"
#include "coord/builtin/slice.h"
#include <stdlib.h>
#include <libuv/uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export

namespace gate {

enum MessageType {
	MessageType_Request     = 0x00,
	MessageType_Notify      = 0x01,
	MessageType_Response    = 0x02,
	MessageType_Push        = 0x03,
};

struct Message {
    MessageType type;
    uint64_t id;
    bool compressed;
    bool encrypt;
    char route[257];
    char *data;
    uint32_t length;
};

int MessageDecode(Message& message, char* data, size_t len);
int MessageHeaderEncode(byte_slice& packet, MessageType type, uint64_t id, const char* route);

}//tolua_export
}//tolua_export


