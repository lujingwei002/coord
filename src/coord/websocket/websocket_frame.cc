#include "coord/websocket/websocket_frame.h"
#include "coord/websocket/websocket_agent.h"
#include "coord/websocket/websocket_server.h"
#include "coord/coord.h"

namespace coord {
namespace websocket {

RC_IMPLEMENT(Frame, "coord::websocket::Frame")

Frame* newWebSocketFrame(Coord* coord, Agent* agent) {
    Frame* request = new Frame(coord, agent);
    return request;
}

Frame::Frame(Coord* coord, Agent* agent) {
    this->agent = agent;
    this->coord = coord;
    this->sessionId = agent->sessionId;
    this->payloadLen = 0;
    this->payload = 0;
    this->headerLen = 0;
    this->frameLen = 0;
    memset(&this->header, 0, sizeof(this->header));
}

Frame::~Frame() {
}

size_t Frame::parse(char* data, size_t len) {
    this->coord->CoreLogDebug("[Frame] parse, recv a frame");
    this->headerLen = 0;
    this->payloadLen = 0;
    this->frameLen = 0;
    if(len < sizeof(this->header)){
        return 0;
    }
    websocket_frame_header* header = (websocket_frame_header*)data;
    this->coord->CoreLogDebug("[Frame] parse, fin(%d) rsv(%d) mask(%d) opcode(%d) payload_len(%d)", header->fin, header->rsv, header->mask, header->opcode, header->payloadLen);
    uint64_t realHeaderLen = sizeof(this->header);
    uint64_t realPayloadLen = header->payloadLen;
    uint64_t realFrameLen = 0;
    //掩码
    unsigned char *mask = 0;
    //负载
    char *payloadData = 0;
    if (header->payloadLen == 126){
        realHeaderLen = sizeof(this->header) + 2;
    }
    else if (header->payloadLen == 127){
        realHeaderLen = sizeof(this->header) + 8;
    }
    if (header->mask == 1){
        mask = (unsigned char *)data + realHeaderLen;
        realHeaderLen += 4;
    }
    //负载
    payloadData = (char *)data + realHeaderLen;
    //测试数据长度
    if (len < realHeaderLen){
        return 0;
    }
    //解释负载长度
    if (header->payloadLen == 126){
        //2个字节的长度
        realPayloadLen = ntohs(*((uint16_t*)(data + sizeof(this->header))));
    }
    else if (header->payloadLen == 127){
        realPayloadLen = ntohl(*((uint64_t*)(data + sizeof(this->header))));
    }
    realFrameLen = realHeaderLen + realPayloadLen;
    //测试数据长度
    if (len < realFrameLen){
        return 0;
    }
    this->coord->CoreLogDebug("[Frame] parse, realPayloadLen(%ld)", realPayloadLen);
    //用掩码修改数据
    if (header->mask == 1){
        for (uint64_t i = 0; i < realPayloadLen; i++) {
            payloadData[i] = payloadData[i] ^ mask[i % 4];
        }
    }
    this->header = *header;
    this->payloadLen = realPayloadLen;
    this->headerLen = realHeaderLen;
    this->frameLen = realFrameLen;
    this->payload = payloadData;
    this->isComplete = true;
    return this->frameLen;
}


}
}