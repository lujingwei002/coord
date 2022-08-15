#include "coord/cluster/cluster_packet.h"
#include "coord/coordx.h"
#include <cstring>
namespace coord {
namespace cluster {

int clkusterPacketEncode(byte_slice& packet, packet_type type, const char* data, size_t len) {
    int err = packet.Reserve(sizeof(cluster_packet_header) + len);
    if(err < 0) {
        return err;
    }
    cluster_packet_header* header = (cluster_packet_header*)packet.Data();
    header->type = type;
    header->length[0] = (len >> 16) & 0xff;
    header->length[1] = (len >> 8) & 0xff;
    header->length[2] = (len) & 0xff;
    if (data != NULL){
        memcpy(packet.Data() + sizeof(cluster_packet_header), data, len);
    }
    packet.Resize(sizeof(cluster_packet_header) + len);
    return 0;
}

int clusterPacketHeaderEncode(byte_slice& packet, packet_type type, size_t len) {
    int err = packet.Reserve(sizeof(cluster_packet_header));
    if(err < 0) {
        return err;
    }
    cluster_packet_header* header = (cluster_packet_header*)packet.Data();
    header->type = type;
    header->length[0] = (len >> 16) & 0xff;
    header->length[1] = (len >> 8) & 0xff;
    header->length[2] = (len) & 0xff;
    packet.Resize(sizeof(cluster_packet_header));
    return 0;
}

int clusterPacketDecode(cluster_packet& packet, char* data, size_t len) {
    cluster_packet_header *header = (cluster_packet_header*)data;
    uint32_t length = (header->length[0] << 16) | (header->length[1] << 8) | header->length[2];
    if (len < length + sizeof(cluster_packet_header)) {
        return -1;
    }
    packet.type = header->type;
    packet.length = length;
    packet.data = data + sizeof(cluster_packet_header);
    return 0; 
}


}
}  