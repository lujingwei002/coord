#include "coord/cluster/cluster_message.h"
#include "coord/builtin/error.h"
#include <cstring>
namespace coord {
namespace cluster {

const int MESSAGE_HEADER_LENGTH = 2;
const int MESSAGE_ROUTE_COMPRESS_MASK = 0x01;
const int MESSAGE_TYPE_MASK       = 0x07;

static bool invalidType(message_type t) {
	return t < message_type_request || t > message_type_push;
}

int clusterMessageDecode(cluster_message& message, char* data, size_t len) {
    if (len < MESSAGE_HEADER_LENGTH){
        return -1;
    }
    uint8_t flag = *(uint8_t*)data;
    message.type = (message_type)(flag >> 1 & MESSAGE_TYPE_MASK);
    size_t offset = 1;
    if (message.type < message_type_request || message.type > message_type_push) {
        return -1;
    }
    if (message.type == message_type_request || message.type == message_type_response) {
        uint64_t id = 0;
        for (size_t i = offset; i < len; i++){
            uint8_t b = data[i];
            id += (uint64_t)(b&0x7f) << (uint64_t)(7*(i-offset));
            if (b < 128){
                offset = i + 1;
                break;
            }
        }
        message.id = id;
    }
    if (offset >= len) {
        return -1;
    } 
    if (message.type == message_type_request || message.type == message_type_notify ||  message.type == message_type_push) {
        uint8_t routeLength = data[offset];
        offset = offset + 1;
        if(offset + routeLength > len){
            return -1;
        }
        memcpy(message.route, data + offset, routeLength);
        message.route[routeLength] = 0;
        offset += routeLength;
    }
    if (message.type == message_type_response) {
        message.code = *((int*)(data + offset));
        offset += sizeof(int);
    }
    if (offset > len){
        return -1;
    }
    message.data = data + offset;
    message.length = len - offset;
    return 0;
}

int clusterMessageHeaderEncode(byte_slice& message, message_type type, uint64_t id, const char* route, int code) {
    if (invalidType(type)){
        return -1;
    }
    uint8_t flag = ((uint8_t)type) << 1;
    //int offset = 1;
    coord::Append(message, (char)flag);
    if (type == message_type_request || type == message_type_response) {
        uint64_t n = id;
        for (;;) {
            uint8_t b = uint8_t(n % 128);
            n = n >> 7;
            if (n != 0){
                coord::Append(message, (char)(b + 128));
            } else {
                coord::Append(message, (char)b);
                break;
            }
        } 
    }
    if (type == message_type_request || type == message_type_notify ||  type == message_type_push) {
        coord::Append(message, (char)strlen(route));
        coord::Append(message, route, strlen(route));
    }
    if (type == message_type_response) {
        coord::Append(message, (char*)&code, sizeof(code));
    }
    return 0;
}

}
}  