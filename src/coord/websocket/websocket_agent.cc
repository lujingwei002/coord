#include "coord/websocket/websocket_agent.h"
#include "coord/websocket/websocket_server.h"
#include "coord/websocket/websocket_frame.h"
#include "coord/http/http_base.h"
#include "coord/coord.h"
namespace coord {
namespace websocket {
RC_IMPLEMENT(Agent, "coord::websocket::Agent")

Agent* newAgent(Coord* coord, Server* server, http::HttpAgent* httpAgent) {
    Agent* agent = new Agent(coord, server, httpAgent);
    return agent;
}

Agent::Agent(Coord* coord, Server* server, http::HttpAgent* httpAgent) {
    this->coord = coord;
    this->server = server;
    this->httpAgent = httpAgent;
    this->frame = nullptr;
    this->httpAgent->SetHandler(this);
    this->coord->DontDestory(this->httpAgent);
    this->handler = nullptr;
}

Agent::~Agent() {
    this->coord->CoreLogDebug("[websocket::Agent] ~");
    //释放末完成的frame
    if(this->frame != nullptr){
        delete this->frame;
        this->frame = nullptr;
    }
    if(this->httpAgent != nullptr) {
        this->httpAgent->SetHandler(nullptr);
        this->coord->Destory(this->httpAgent);
        this->httpAgent = nullptr;
    }
}    

void Agent::recvHttpClose(http::HttpAgent* agent){
    this->coord->CoreLogDebug("[websocket::Agent] recvHttpClose sessionId=%d", this->sessionId);
    if(this->handler != nullptr) {
        this->handler->recvWebSocketClose(this);
    } else {
        this->server->recvWebSocketClose(this);
    }
    this->server->recvAgentClose(this);
}

int Agent::recvHttpData(http::HttpAgent* agent, char* data, size_t len) {
    Frame* frame = this->frame;
    if(frame == nullptr){
        frame = newWebSocketFrame(this->coord, this);
        this->frame = frame;
    }
    size_t byteRead = frame->parse(data, len);
    if(frame->isComplete){
        this->recvWebSocketFrame(frame);  
        this->coord->Destory(frame);
        this->frame = nullptr;
    } 
    return byteRead;
}

void Agent::recvWebSocketFrame(Frame* frame) {
    try{
        if(frame->header.opcode == websocket_frame_type_close){
            this->recvWebSocketCloseFrame(frame);
        } else if(frame->header.opcode == websocket_frame_type_Text){
            //文本数据
            this->recvWebSocketDataFrame(frame);
        } else if(frame->header.opcode == websocket_frame_type_binary){
            //二进制数据
            this->recvWebSocketDataFrame(frame);
        } else if(frame->header.opcode == websocket_frame_type_ping){ 
            //PING
            this->recvWebSocketPingFrame(frame);
        }
    } catch(http::HttpException& e){
        this->coord->CoreLogError("[Agent] recvWebSocketFrame failed, error=%s", e.What());
    }
}

void Agent::recvWebSocketDataFrame(Frame* frame){
    int sessionId = this->sessionId;
    this->coord->CoreLogDebug("[websocket::Agent] recvWebSocketDataFrame, sessionId=%d", sessionId);
    if(this->handler != nullptr) {
        this->handler->recvWebSocketFrame(this, frame);
    } else {
        this->server->recvWebSocketFrame(this, frame);
    }
}

void Agent::recvWebSocketCloseFrame(Frame* frame){
    int sessionId = this->sessionId;
    this->coord->CoreLogDebug("[websocket::Agent] recvWebSocketCloseFrame, sessionId=%d", sessionId);
    this->Close();
} 

void Agent::recvWebSocketPingFrame(Frame* frame){
    int sessionId = this->sessionId;
    this->coord->CoreLogDebug("[websocket::Agent] recvWebSocketPingFrame, sessionId=%d", sessionId);
    this->sendPongFrame();
}

void Agent::Close() {
    this->httpAgent->Close();
}

void Agent::SetHandler(IAgentHandler* handler) {
    this->handler = handler;
}

int Agent::send(byte_slice& data) {
    return this->httpAgent->send(data);
}

//发送字符串帧
int Agent::SendStringFrame(const char* str){
    return this->sendFrame(websocket_frame_type_Text, str, strlen(str) + 1);
}

int Agent::sendPongFrame(){
    return this->sendFrame(websocket_frame_type_pong, NULL, 0);
}

int Agent::SendBinaryFrame(const char* data, size_t len){
    return this->sendFrame(websocket_frame_type_binary, data, len);
}

int Agent::SendBinaryFrame(byte_slice& data) {
    return this->sendFrame(websocket_frame_type_binary, data);
}

//发送帧
int Agent::sendFrame(int opcode, const char* data, size_t len) {
   this->coord->CoreLogDebug("[websocket::Agent] sendFrame sessionId=%d, opcode=%d, len=%d", this->sessionId, opcode, len);
    websocket_frame_header header;
    header.fin = 1;//结束帧
    header.rsv = 0;
    header.opcode = opcode;
    header.mask = 0;//没有掩码
    byte_slice frame;
    if (len > 0xFFFF){
        this->coord->CoreLogError("[websocket::Agent] sendFrame failed, data too large");
    } else if(len >= 126) {
        header.payloadLen = 126;
        frame.Reserve(sizeof(header) + sizeof(uint16_t) + len);
        frame.Resize(0);
        coordx::Append(frame, (char *)&header, sizeof(header));
        coordx::Append(frame, (len>>8)&0xFF);
        coordx::Append(frame, (len)&0xFF);
        coordx::Append(frame, data, len);
        return this->send(frame);
    } else {
        header.payloadLen = len;
        frame.Reserve(sizeof(header) + len);
        frame.Resize(0);
        coordx::Append(frame, (char *)&header, sizeof(header));
        coordx::Append(frame, data, len);
        return this->send(frame);
    }
    return 0;
}

//发送帧
int Agent::sendFrame(int opcode, byte_slice& data) {
   this->coord->CoreLogDebug("[websocket::Agent] sendFrame sessionId=%d, opcode=%d, len=%d", this->sessionId, opcode, data.Len());
    websocket_frame_header header;
    header.fin = 1;//结束帧
    header.rsv = 0;
    header.opcode = opcode;
    header.mask = 0;//没有掩码
    size_t len = data.Len();
    byte_slice frame;
    if (len > 0xFFFF){
        this->coord->CoreLogError("[websocket::Agent] sendFrame failed, data too large");
    } else if(len >= 126) {
        header.payloadLen = 126;
        frame.Reserve(sizeof(header) + sizeof(uint16_t) + len);
        frame.Resize(0);
        coordx::Append(frame, (char *)&header, sizeof(header));
        coordx::Append(frame, (len>>8)&0xFF);
        coordx::Append(frame, (len)&0xFF);
        int err = this->send(frame);
        if (err) {
            return err;
        }
        //减少拷贝，分段发送
        return this->send(data);
    } else {
        header.payloadLen = len;
        frame.Reserve(sizeof(header) + len);
        frame.Resize(0);
        coordx::Append(frame, (char *)&header, sizeof(header));
        int err = this->send(frame);
        if (err) {
            return err;
        }
        //减少拷贝，分段发送
        return this->send(data);
    }
    return 0;
}



}
}