#include "coord/gate/gate_packet.h"
#include "coord/builtin/error.h"
#include <cstring>
namespace coord {
namespace gate {

int PacketEncode(byte_slice& packet, PacketType type, const char* data, size_t len) {
    int err = packet.Reserve(sizeof(PacketHeader) + len);
    if(err < 0) {
        return err;
    }
    PacketHeader* header = (PacketHeader*)packet.Data();
    header->type = type;
    header->length[0] = (len >> 16) & 0xff;
    header->length[1] = (len >> 8) & 0xff;
    header->length[2] = (len) & 0xff;
    if (data != NULL){
        memcpy(packet.Data() + sizeof(PacketHeader), data, len);
    }
    packet.Resize(sizeof(PacketHeader) + len);
    return 0;
}

int PacketHeaderEncode(byte_slice& packet, PacketType type, size_t len) {
    int err = packet.Reserve(sizeof(PacketHeader));
    if(err < 0) {
        return err;
    }
    PacketHeader* header = (PacketHeader*)packet.Data();
    header->type = type;
    header->length[0] = (len >> 16) & 0xff;
    header->length[1] = (len >> 8) & 0xff;
    header->length[2] = (len) & 0xff;
    packet.Resize(sizeof(PacketHeader));
    return 0;
}

int PacketDecode(Packet& packet, char* data, size_t len) {
    PacketHeader *header = (PacketHeader*)data;
    uint32_t length = (header->length[0] << 16) | (header->length[1] << 8) | header->length[2];
    if (len < length + sizeof(PacketHeader)) {
        return -1;
    }
    packet.type = header->type;
    packet.length = length;
    packet.data = data + sizeof(PacketHeader);
    return 0; 
}


}
}  