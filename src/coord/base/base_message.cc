#include "coord/base/base_message.h"
#include "coord/coordx.h"
#include "coord/base/base_packet.h"
#include "coord/protobuf/protobuf.h"
namespace coord {

const int BASE_MESSAGE_HEADER_LENGTH        = 2;
const int BASE_MESSAGE_ROUTE_COMPRESS_MASK  = 0x01;
const int BASE_MESSAGE_TYPE_MASK            = 0x07;
const int BASE_MESSAGE_DATA_TYPE_MASK       = 0x07;

static bool invalid_type(base_message_type t) {
	return t < base_message_type_request || t > base_message_type_push;
}

int base_message_decode(base_message& message, char* data, size_t len) {
    if (len < BASE_MESSAGE_HEADER_LENGTH){
        return -1;
    }
    uint8_t flag = *(uint8_t*)data;
    message.type = (base_message_type)(flag >> 1 & BASE_MESSAGE_TYPE_MASK);
    message.dataType = (base_message_data_type)(flag >> 4 & BASE_MESSAGE_DATA_TYPE_MASK);
    size_t offset = 1;
    if (message.type < base_message_type_request || message.type > base_message_type_push) {
        return -1;
    }
    if (message.type == base_message_type_request || message.type == base_message_type_response) {
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
    if (message.type == base_message_type_request || message.type == base_message_type_notify ||  message.type == base_message_type_push) {
        uint8_t routeLength = data[offset];
        offset = offset + 1;
        if(offset + routeLength > len){
            return -1;
        }
        memcpy(message.route, data + offset, routeLength);
        message.route[routeLength] = 0;
        offset += routeLength;
    }
    if (message.type == base_message_type_response) {
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

int base_message_header_encode(byte_slice& message, base_message_type type, base_message_data_type dataType, uint64_t id, const char* route, int code) {
    if (invalid_type(type)){
        return -1;
    }
    uint8_t flag = (((uint8_t)dataType) << 4) | (((uint8_t)type) << 1);
    //int offset = 1;
    coordx::Append(message, (char)flag);
    if (type == base_message_type_request || type == base_message_type_response) {
        uint64_t n = id;
        for (;;) {
            uint8_t b = uint8_t(n % 128);
            n = n >> 7;
            if (n != 0){
                coordx::Append(message, (char)(b + 128));
            } else {
                coordx::Append(message, (char)b);
                break;
            }
        } 
    }
    if (type == base_message_type_request || type == base_message_type_notify ||  type == base_message_type_push) {
        coordx::Append(message, (char)strlen(route));
        coordx::Append(message, route, strlen(route));
    }
    if (type == base_message_type_response) {
        coordx::Append(message, (char*)&code, sizeof(code));
    }
    return 0;
}

int base_message_response_header_encode(byte_slice& message, base_message_type type, base_message_data_type dataType, uint64_t id, int code) {
    return base_message_header_encode(message, type, dataType, id, nullptr, code);
}

int base_message_request_header_encode(byte_slice& message, base_message_type type, base_message_data_type dataType, uint64_t id, const char* route) {
    return base_message_header_encode(message, type, dataType, id, route, 0);
}

int base_message_notify_header_encode(byte_slice& message, base_message_type type, base_message_data_type dataType, const char* route) {
    return base_message_header_encode(message, type, dataType, 0, route, 0);
}

int base_response_encode(byte_slice& packet, uint64_t id, int code, const char* data, size_t len) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_response_header_encode(message, base_message_type_response, base_message_data_type_custom, id, code);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    coordx::Append(payload, data, len);
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}

int base_response_encode(byte_slice& packet, uint64_t id, int code, Argument* argument) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_response_header_encode(message, base_message_type_response, base_message_data_type_argument, id, code);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    err = argument->Serialize(payload);
    if (err) {
        return err;
    }
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}

int base_response_encode(byte_slice& packet, uint64_t id, int code, ::google::protobuf::Message* proto) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_response_header_encode(message, base_message_type_response, base_message_data_type_protobuf, id, code);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    err = protobuf::Serialize(payload, proto);
    if(err){
        return err;
    }
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}

int base_notify_encode(byte_slice& packet, const char* route, const char* data, size_t len) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err) {
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_notify_header_encode(message, base_message_type_notify, base_message_data_type_custom, route);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    coordx::Append(payload, data, len);
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}

int base_notify_encode(byte_slice& packet, const char* route, ::google::protobuf::Message* proto) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_notify_header_encode(message, base_message_type_notify, base_message_data_type_protobuf, route);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    err = protobuf::Serialize(payload, proto);
    if(err){
        return err;
    }
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}

int base_request_encode(byte_slice& packet, const char* route, int requestId, ::google::protobuf::Message* proto) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_request_header_encode(message, base_message_type_request, base_message_data_type_protobuf, requestId, route);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    err = protobuf::Serialize(payload, proto);
    if(err){
        return err;
    }
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}

int base_request_encode(byte_slice& packet, const char* route, int requestId, const char* data, size_t len) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_request_header_encode(message, base_message_type_request, base_message_data_type_custom, requestId, route);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    coordx::Append(payload, data, len);
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}

int base_request_encode(byte_slice& packet, const char* route, int requestId, Argument* argument) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, base_packet_type_data, 0);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = base_message_request_header_encode(message, base_message_type_request, base_message_data_type_argument, requestId, route);
    if (err){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    err = argument->Serialize(payload);
    if (err) {
        return err;
    }
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, base_packet_type_data, message.Len() + payload.Len());
    return err;
}


}  
