#include "coord/base/base_packet.h"
#include "coord/coordx.h"
namespace coord {

int base_packet_header_encode(byte_slice& packet, base_packet_type type, size_t len) {
    int err = packet.Reserve(sizeof(base_packet_header));
    if(err < 0) {
        return err;
    }
    base_packet_header* header = (base_packet_header*)packet.Data();
    header->type = type;
    header->length[0] = (len >> 16) & 0xff;
    header->length[1] = (len >> 8) & 0xff;
    header->length[2] = (len) & 0xff;
    packet.Resize(sizeof(base_packet_header));
    return 0;
}

int base_packet_encode(byte_slice& packet, base_packet_type type, const char* data, size_t len) {
    int err = packet.Reserve(sizeof(base_packet_header) + len);
    if(err < 0) {
        return err;
    }
    base_packet_header* header = (base_packet_header*)packet.Data();
    header->type = type;
    header->length[0] = (len >> 16) & 0xff;
    header->length[1] = (len >> 8) & 0xff;
    header->length[2] = (len) & 0xff;
    if (data != NULL){
        memcpy(packet.Data() + sizeof(base_packet_header), data, len);
    }
    packet.Resize(sizeof(base_packet_header) + len);
    return 0;
}

int base_packet_encode(byte_slice& packet, base_packet_type type, ::google::protobuf::Message* message) {
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = base_packet_header_encode(header, type, 0);
    if (err < 0){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //packet body
    byte_slice body = packet.Slice(packet.Len(), packet.Len());
    body.Reserve(message->ByteSizeLong());
    char* end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)body.Data());
    body.Resize(end - body.Data());
    packet.Resize(packet.Len() + body.Len());
    //重新写packet header 
    header.Resize(0);
    err = base_packet_header_encode(header, type, body.Len());
    if (err < 0){
        return err;
    } 
    return 0;
}

int base_packet_decode(base_packet& packet, char* data, size_t len) {
    base_packet_header *header = (base_packet_header*)data;
    uint32_t length = (header->length[0] << 16) | (header->length[1] << 8) | header->length[2];
    if (len < length + sizeof(base_packet_header)) {
        return -1;
    }
    packet.type = header->type;
    packet.length = length;
    packet.data = data + sizeof(base_packet_header);
    return 0; 
}


} 
