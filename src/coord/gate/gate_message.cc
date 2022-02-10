#include "coord/gate/gate_message.h"
#include "coord/builtin/error.h"
namespace coord {
namespace gate {

const int MESSAGE_HEADER_LENGTH = 2;
const int MESSAGE_ROUTE_COMPRESS_MASK = 0x01;
const int MESSAGE_TYPE_MASK       = 0x07;

static bool routable(MessageType t) {
	return t == MessageType_Request || t == MessageType_Notify || t == MessageType_Push;
}

static bool invalidType(MessageType t) {
	return t < MessageType_Request || t > MessageType_Push;
}

int MessageDecode(Message& message, char* data, size_t len) {
    if (len < MESSAGE_HEADER_LENGTH){
        return -1;
    }
    uint8_t flag = *(uint8_t*)data;
    message.type = (MessageType)(flag >> 1 & MESSAGE_TYPE_MASK);
    size_t offset = 1;
    if (message.type < MessageType_Request || message.type > MessageType_Push) {
        return -1;
    }
    if (message.type == MessageType_Request || message.type == MessageType_Response) {
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
    if (routable(message.type)){
        if(flag & MESSAGE_ROUTE_COMPRESS_MASK) {
            message.compressed = true;
           // uint16_t code = *(uint16_t*)(data+offset);
            offset = offset + 2;
            return -1;
        } else {
            message.compressed = false;
            uint8_t routeLength = data[offset];
            offset = offset + 1;
            if(offset + routeLength > len){
                return -1;
            }
            memcpy(message.route, data + offset, routeLength);
            message.route[routeLength] = 0;
            offset += routeLength;
        }
    }
    if (offset > len){
        return -1;
    }
    message.data = data + offset;
    message.length = len - offset;
    return 0;
}

int MessageHeaderEncode(byte_slice& message, MessageType type, uint64_t id, const char* route) {
    if (invalidType(type)){
        return -1;
    }
    uint8_t flag = ((uint8_t)type) << 1;
    bool compressed = false;
    uint16_t code = 0;
    if (compressed) {
        flag = flag | MESSAGE_ROUTE_COMPRESS_MASK;
    }
    //int offset = 1;
    coord::Append(message, (char)flag);
    if (type == MessageType_Request || type == MessageType_Response) {
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
    if (routable(type)){
        if(compressed){
            coord::Append(message, (char)(code >> 8)&0xff);
            coord::Append(message, (char)(code&0xff));
        } else {
            coord::Append(message, (char)strlen(route));
            coord::Append(message, route, strlen(route));
        }
    }
    return 0;
}

}
}  