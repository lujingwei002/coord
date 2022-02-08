#pragma once 

#include "coord/component/component.h"
#include "coord/builtin/slice.h"
#include <cstdlib>
#include <uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export

namespace cluster {

enum message_type {
	message_type_request     = 0x00,
	message_type_notify      = 0x01,
	message_type_response    = 0x02,
	message_type_push        = 0x03,
};

// ------------------------------------------
// |   type   |  flag  |       other        |
// |----------|--------|--------------------|
// | request  |----000-|<message id>|<route>|
// | notify   |----001-|<route>             |
// | response |----010-|<message id>|<code> |
// | push     |----011-|<route>             |
// ------------------------------------------

struct cluster_message {
    message_type    type;
    uint64_t        id;
    bool            encrypt;
    char            route[257];
    char*           data;
    uint32_t        length;
    int             code;
};

int clusterMessageDecode(cluster_message& message, char* data, size_t len);
int clusterMessageHeaderEncode(byte_slice& packet, message_type type, uint64_t id, const char* route, int code = 0);

}//tolua_export
}//tolua_export


