#include "coord/gate/gate_agent.h"
#include "coord/builtin/slice.h"
#include "coord/gate/gate_packet.h"
#include "coord/gate/gate_message.h"
#include "coord/gate/gate_request.h"
#include "coord/gate/gate_notify.h"
#include "coord/gate/gate_session.h"
#include "coord/websocket/websocket_frame.h"
#include "coord/coord.h"
#include "coord/gate/gate.h"
#include "coord/encrypt/rsa.h"
#include "coord/encrypt/des.h"
#include "coord/protobuf/init.h"
#include "coord/encrypt/rsa.h"
#include "json/json.hpp"
//#include "gamepb/gamepb.pb.h"


using json = nlohmann::json;

namespace coord {
namespace gate {
CC_IMPLEMENT(GateAgent, "coord::gate::GateAgent")

GateAgent* newGateAgent(Coord* coord, Gate* gate, net::TcpAgent* tcpAgent) {
    GateAgent* gateAgent = new GateAgent(coord, gate, tcpAgent);
    return gateAgent;
}

GateAgent* newGateAgent(Coord* coord, Gate* gate, websocket::Agent* webSocketAgent) {
    GateAgent* gateAgent = new GateAgent(coord, gate, webSocketAgent);
    return gateAgent;
}

GateAgent::GateAgent(Coord* coord, Gate* gate, net::TcpAgent* tcpAgent) {
    this->coord = coord;
    this->gate = gate;
    this->status = GateAgentStatus_Start;
    this->session = NULL;
    this->tcpAgent = tcpAgent;
    this->tcpAgent->SetHandler(this);
    this->webSocketAgent = NULL;
    //this->coord->DontDestory(this->tcpAgent);
}

GateAgent::GateAgent(Coord* coord, Gate* gate, websocket::Agent* webSocketAgent) {
    this->coord = coord;
    this->gate = gate;
    this->status = GateAgentStatus_Start;
    this->session = NULL;
    this->tcpAgent = NULL;
    this->webSocketAgent = webSocketAgent;
    this->webSocketAgent->SetHandler(this);
    this->coord->DontDestory(this->webSocketAgent);
}

GateAgent::~GateAgent() {
    this->coord->coreLogDebug("[GateAgent] ~GateAgent");
    if (this->session != NULL){
        delete this->session;
        this->session = NULL;
    }
    if(this->tcpAgent != NULL) {
        this->tcpAgent->SetHandler(NULL);
        this->coord->Destory(this->tcpAgent);
        this->tcpAgent = NULL;
    }
    if(this->webSocketAgent != NULL) {
        this->webSocketAgent->SetHandler(NULL);
        this->coord->Destory(this->webSocketAgent);
        this->webSocketAgent = NULL;
    }
}

int GateAgent::recvData(char* data, size_t len) {
    if(len < sizeof(PacketHeader)) {
        return 0;
    } 
    PacketHeader *header = (PacketHeader*)data;
    uint32_t length = (header->length[0] << 16) | (header->length[1] << 8) | header->length[2];
    if (len < length + sizeof(PacketHeader)) {
        return 0;
    }
    static thread_local Packet packet;
    int err = PacketDecode(packet, data, len);
    if(err < 0){
        return 0;
    }    
    this->recvPacket(&packet);
    return length + sizeof(PacketHeader);
}   

void GateAgent::recvPacket(Packet* packet) {
    this->coord->coreLogDebug("[GateAgent] recvPacket, type=%d", packet->type);
    switch(packet->type) {
        case PacketType_Handshake:{
            this->recvHandShake(packet);
        }break;
        case PacketType_HandshakeAck:{
            this->recvHandShakeAck(packet);
        }break;
        case PacketType_Data:{
            this->recvData(packet);
        }break;
        case PacketType_Heartbeat:{
        }break;
    }
    this->lastHeartbeatTime = this->coord->Now();
} 

void GateAgent::sendHandShakeFail() {

}

void GateAgent::recvHandShake(Packet* packet) {
    auto body = nlohmann::json::parse(packet->data, packet->data + packet->length);
    if (this->gate->config.RsaEncrypt) {
        //协议需要加密，接收和解码随机字符串
        static thread_local byte_slice secret(0, 0);
        if (body["sys"] == nullptr || body["sys"]["token"] == nullptr){
            //查找token失败
            this->coord->coreLogDebug("[GateAgent] recvHandShake failed, err='token not found'");
            nlohmann::json response = {{"code", 500}};
            auto data = response.dump();
            this->send(PacketType_Handshake, data.c_str(), data.length());
            return;
        }
        std::string token = body["sys"]["token"].get<std::string>();
        int err = encrypt::RsaPrivateDecrypt((unsigned char*)token.c_str(), token.length(), (unsigned char * )this->gate->rsaPrivateKey.c_str(), secret);
        if (err < 0){
            //解码失败
            this->coord->coreLogDebug("[GateAgent] recvHandShake failed, err=%d", err);
            nlohmann::json response = {{"code", 500}};
            auto data = response.dump();
            this->send(PacketType_Handshake, data.c_str(), data.length());
            return;
        }
        this->secret.assign((char*)secret.Data(), secret.Len());
    } 
    nlohmann::json response = {
        {"code", 200},
        {"sys", {{"heartbeat", this->gate->config.Heartbeat},{"session", this->sessionId}}}
    };
    auto data = response.dump();
    this->send(PacketType_Handshake, data.c_str(), data.length());
    this->status = GateAgentStatus_Handshake;
    this->coord->coreLogDebug("[GateAgent] recvHandShake, secret=%s", this->secret.c_str());
} 

void GateAgent::recvHandShakeAck(Packet* packet) {
    if(this->status != GateAgentStatus_Handshake) {
        this->coord->coreLogDebug("[GateAgent] recvData failed, status=%d, error='status not handshake'", this->status);
        return;
    }
    this->status = GateAgentStatus_Working;
    GateSession* session = newGateSession(this->coord, this);
    this->session = session;
    this->gate->recvGateSessionNew(this->session);
} 

void GateAgent::recvData(Packet* packet) {
    if(this->status != GateAgentStatus_Working) {
        this->coord->coreLogDebug("[GateAgent] recvData failed, status=%d, error='status not working'", this->status);
        return;
    }
    static thread_local Message message;
    int err = MessageDecode(message, packet->data, packet->length);
    if (err < 0){
        this->coord->coreLogDebug("[GateAgent] recvData failed, err=%d", err);
        return;
    }
    if (this->gate->config.RsaEncrypt) {
        //解码数据
        size_t rawLength = 0;
        err = encrypt::des::Decrypt(message.data, message.length, this->secret.c_str(), message.data, &rawLength);
        if (err < 0){
            this->coord->coreLogDebug("[GateAgent] recvData failed, err=%d", err);
            return;
        }
        message.length = rawLength;
    }
    //发送到逻辑层
    //gamepb::LoginRequest req;
    this->coord->coreLogDebug("[GateAgent] recvData type=%d, id=%d, route=%s, len=%d", message.type, message.id, message.route, message.length);
    switch(message.type){
        case MessageType_Request: {
            GateRequest* request = newGateRequest(this->coord, this);
            //this->coord->pushRequestPipeline(request);
            request->id = message.id;
            request->route = message.route;
            request->payload.Resize(0);
            coord::Append(request->payload, message.data, message.length);
            this->gate->recvGateRequest(this->session, request);
            //this->coord->popRequestPipeline();
            this->coord->Destory(request);
            break;
        }
        case MessageType_Notify: {
            GateNotify* notify = newGateNotify(this->coord, this);
            notify->route = message.route;
            notify->payload.Resize(0);
            coord::Append(notify->payload, message.data, message.length);
            this->gate->recvGateNotify(this->session, notify);
            this->coord->Destory(notify);
            break;
        }break;
        default:{
            
        }
    }
} 

void GateAgent::recvClose() {
    this->gate->recvGateSessionClose(this->session);
    this->gate->recvAgentClose(this);
} 

int GateAgent::send(const char* data, size_t len) {
    if(this->tcpAgent != NULL){
        return this->tcpAgent->Send(data, len);
    } else {
        this->webSocketAgent->SendBinaryFrame(data, len);
    }
    return -1;
}

int GateAgent::send(byte_slice& data) {
    if(this->tcpAgent != NULL) {
        return this->tcpAgent->Send(data);
    } else {
        this->webSocketAgent->SendBinaryFrame(data);
    }
    return -1;
}

int GateAgent::send(PacketType type, const char* data, size_t len) {
    static thread_local byte_slice packet(0, 0);
    int err = PacketEncode(packet, type, data, len);
    if (err < 0){
        this->coord->coreLogDebug("[GateAgent] Send failed, err=%d", err);
        return err;
    }
    this->send(packet.Data(), packet.Len());
    return 0;
}

int GateAgent::push(const char* route, protobuf::Reflect* proto){
    return this->push(route, proto->GetMessage());
}

int GateAgent::push(const char* route, google::protobuf::Message* proto){
    this->coord->coreLogDebug("[GateAgent] Push, sessionId=%d, route=%s, proto=%s", this->sessionId, route, proto->DebugString().c_str());
    byte_slice response;
    //packet header
    byte_slice packetHeader = response.Slice(response.Len(), response.Len());
    int err = PacketHeaderEncode(packetHeader, PacketType_Data, 0);
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + packetHeader.Len());
    //message header
    byte_slice messageHeader = response.Slice(response.Len(), response.Len());
    err = MessageHeaderEncode(messageHeader, MessageType_Push, 0, route);
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + messageHeader.Len());
    //message body
    byte_slice messageBody = response.Slice(response.Len(), response.Len());
    err = protobuf::Serialize(messageBody, proto);
    if(err){
        return err;
    }
    //加密
    err = encrypt::des::Encrypt(messageBody, this->secret.c_str());
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + messageBody.Len());
    //重新写packet header 
    packetHeader.Resize(0);
    err = PacketHeaderEncode(packetHeader, PacketType_Data, messageHeader.Len() + messageBody.Len());
    if (err < 0){
        return err;
    } 
    this->send(response);
    return 0; 
}

int GateAgent::response(uint64_t id, const char* route, protobuf::Reflect* proto) {
    return this->response(id, route, proto->GetMessage());
}

int GateAgent::response(uint64_t id, const char* route, ::google::protobuf::Message* proto) {
    this->coord->coreLogDebug("[GateAgent] Response, sessionId=%d, id=%d, route=%s, proto=%s", this->sessionId, id, route, proto->DebugString().c_str());
    byte_slice response;
    //packet header
    byte_slice packetHeader = response.Slice(response.Len(), response.Len());
    int err = PacketHeaderEncode(packetHeader, PacketType_Data, 0);
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + packetHeader.Len());
    //message header
    byte_slice messageHeader = response.Slice(response.Len(), response.Len());
    err = MessageHeaderEncode(messageHeader, MessageType_Response, id, route);
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + messageHeader.Len());
    //message body
    byte_slice messageBody = response.Slice(response.Len(), response.Len());
    err = protobuf::Serialize(messageBody, proto);
    if(err){
        return err;
    }
    //加密
    err = encrypt::des::Encrypt(messageBody, this->secret.c_str());
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + messageBody.Len());
    //重新写packet header 
    packetHeader.Resize(0);
    err = PacketHeaderEncode(packetHeader, PacketType_Data, messageHeader.Len() + messageBody.Len());
    if (err < 0){
        return err;
    } 
    this->send(response);
    return 0; 
}

int GateAgent::response(uint64_t id, const char* route, const byte_slice& data) {
    return this->response(id, route, data.Data(), data.Len());
}

int GateAgent::response(uint64_t id, const char* route, const char* data, size_t len) {
    this->coord->coreLogDebug("[GateAgent] Response, sessionId=%d, id=%d, route=%s", this->sessionId, id, route);
    byte_slice response;
    //packet header
    byte_slice packetHeader = response.Slice(response.Len(), response.Len());
    int err = PacketHeaderEncode(packetHeader, PacketType_Data, 0);
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + packetHeader.Len());
    //message header
    byte_slice messageHeader = response.Slice(response.Len(), response.Len());
    err = MessageHeaderEncode(messageHeader, MessageType_Response, id, route);
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + messageHeader.Len());
    //message body
    byte_slice messageBody = response.Slice(response.Len(), response.Len());
    coord::Append(messageBody, data, len);

    //加密
    err = encrypt::des::Encrypt(messageBody, this->secret.c_str());
    if (err < 0){
        return err;
    }
    response.Resize(response.Len() + messageBody.Len());
    //重新写packet header 
    packetHeader.Resize(0);
    err = PacketHeaderEncode(packetHeader, PacketType_Data, messageHeader.Len() + messageBody.Len());
    if (err < 0){
        return err;
    } 
    this->send(response);
    return 0; 
}


void GateAgent::kick(const char* reason) {
    this->send(PacketType_Kick, reason, strlen(reason));
}

void GateAgent::heartbeatInterval() {
    if(this->status != GateAgentStatus_Working){
        return;
    }
    uint64_t deadline = this->coord->Now() - 2 * this->gate->config.Heartbeat*1000;
    if(this->lastHeartbeatTime < deadline){
        this->coord->coreLogError("[GateAgent] heartbeatInterval deadline=%ld\n", deadline);
        return;
    }
    this->send(PacketType_Heartbeat, NULL, 0);
}

void GateAgent::registerInterval() {
    printf("registerInterval 22222\n");
}

void GateAgent::recvTcpNew(net::TcpAgent* agent) {
    
}

void GateAgent::recvTcpClose(net::TcpAgent* agent){
    this->coord->coreLogDebug("[GateAgent] recvTcpClose, sessionId=%d", this->sessionId);
    this->recvClose();
}

void GateAgent::recvTcpError(net::TcpAgent* agent){
    this->coord->coreLogDebug("[Gate] recvTcpError, sessionId=%d", sessionId);
}

int GateAgent::recvTcpData(net::TcpAgent* agent, char* data, size_t len){
    return this->recvData(data, len);
}

void GateAgent::recvWebSocketClose(websocket::Agent* agent) {
    this->coord->coreLogDebug("[GateAgent] recvWebSocketClose, sessionId=%d", this->sessionId);
    this->recvClose();
}

void GateAgent::recvWebSocketFrame(websocket::Agent* agent, websocket::Frame* frame) {
    this->recvData(frame->payload, frame->payloadLen);
}

void GateAgent::close() {
    if(this->tcpAgent != NULL){
        this->tcpAgent->Close();
    } else if (this->webSocketAgent != NULL) {
        this->webSocketAgent->Close();
    }
}

}
} 
