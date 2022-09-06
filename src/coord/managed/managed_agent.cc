#include "coord/managed/managed_agent.h"
#include "coord/managed/managed.h"
#include "coord/config/config.h"
#include "coord/managed/managed_server.h"
#include "coord/managed/managed_request.h"
#include "coord/managed/managed_notify.h"
#include "coord/pipe/pipe_agent.h"
#include "coord/coord.h"
namespace coord {

namespace managed {

RC_IMPLEMENT(ManagedAgent, "coord::managed::ManagedAgent")

ManagedAgent::ManagedAgent(Coord *coord, Managed* managed, managed_server* server, pipe::PipeAgent* pipeAgent) : internal_agent(coord) {
    this->managed = managed;
    this->server = server;
    this->pipeAgent = pipeAgent;
    this->pipeAgent->SetHandler(this);
    this->status = base_agent_status_none;
    this->coord->DontDestory(this->pipeAgent);
}

ManagedAgent::~ManagedAgent() {
    if (nullptr != this->pipeAgent) {
        this->pipeAgent->SetHandler(nullptr);
        this->coord->Destory(this->pipeAgent);
        this->pipeAgent = nullptr;
    }
}

void ManagedAgent::recvAgentNew(pipe::PipeAgent* pipeAgent){
}

void ManagedAgent::EvClose(pipe::PipeAgent* agent){
    this->coord->CoreLogDebug("[%s] EvClose sessionId=%d", this->TypeName(), this->SessionId);
    this->server->recvAgentClose(this);
}

void ManagedAgent::EvError(pipe::PipeAgent* agent){
    this->coord->CoreLogDebug("[%s] EvError sessionId=%d", this->TypeName(), this->SessionId);
}

int ManagedAgent::EvData(pipe::PipeAgent* agent, char* data, size_t len){
    this->coord->CoreLogDebug("[%s] EvData, len=%ld", this->TypeName(), len);
    if(len < sizeof(base_packet_header)) {
        return 0;
    } 
    base_packet_header *header = (base_packet_header*)data;
    uint32_t length = (header->length[0] << 16) | (header->length[1] << 8) | header->length[2];
    if (len < length + sizeof(base_packet_header)) {
        return 0;
    }
    static thread_local base_packet packet;
    int err = base_packet_decode(packet, data, len);
    if(err < 0){
        return 0;
    }    
    this->recvPacket(&packet);
    return length + sizeof(base_packet_header);
}

void ManagedAgent::recvRequest(ManagedRequest* request) {
    this->managed->recvRequest(request);
}

void ManagedAgent::recvNotify(ManagedNotify* notify) {
    this->managed->recvNotify(notify);
}

void ManagedAgent::Close() {
    this->pipeAgent->Close();
}

int ManagedAgent::send(const char* data, size_t len) {
    return this->pipeAgent->Send(data, len);
}

int ManagedAgent::send(byte_slice& data) {
    return this->pipeAgent->Send(data);
}

void ManagedAgent::recvPacket(base_packet* packet) {
    this->coord->CoreLogDebug("[%s] recvPacket, type=%d", this->TypeName(), packet->type);
    switch(packet->type) {
        case base_packet_type_handshake:{
            this->recvPacketHandShake(packet);
        }break;
        case base_packet_type_handshakeack:{
            this->recvPacketHandShakeAck(packet);
        }break;
        case base_packet_type_data:{
            this->recvPacketData(packet);
        }break;
        case base_packet_type_heartbeat:{
    //      this->recvHeartbeat(packet);
        }break;
    }
    this->lastHeartbeatTime = this->coord->Now();
}

void ManagedAgent::recvPacketHandShake(base_packet* packet) {
    if(this->status != base_agent_status_none) {
        this->coord->CoreLogDebug("[%s] recvPacketHandShake failed, status=%d, error='status not start'", this->TypeName(), this->status);
        return;
    }
    base_handshake_request& request = this->handshakeRequest;
    base_handshake_response& response = this->handshakeResponse;
    google::protobuf::io::ArrayInputStream stream(packet->data, packet->length);
    if(request.ParseFromZeroCopyStream(&stream) == 0){
        this->coord->CoreLogError("[%s] recvPacketHandShake.ParseFromZeroCopyStream failed", this->TypeName());
        return;
    }
    this->coord->CoreLogDebug("[%s] recvPacketHandShake", this->TypeName());
    response.set_code(0);
    this->SendPacket(base_packet_type_handshake, &response);
    this->status = base_agent_status_handshake;
}

void ManagedAgent::recvPacketHandShakeAck(base_packet* packet) {
    this->coord->CoreLogDebug("[%s] recvPacketHandShakeAck", this->TypeName());
    // 状态错误
    if(this->status != base_agent_status_handshake) {
        this->coord->CoreLogDebug("[%s] recvPacketHandShakeAck failed, status=%d, error='status not handshake'" , this->TypeName(), this->status);
        return;
    }
    this->status = base_agent_status_working;;
}

void ManagedAgent::recvPacketData(base_packet* packet) {
    static thread_local base_message message;
    if(this->status != base_agent_status_working) {
        this->coord->CoreLogDebug("[%s] recvPacketData failed, status=%d, error='status not working'", this->TypeName(), this->status);
        return;
    }
    // 解码message
    int err = base_message_decode(message, packet->data, packet->length);
    if (err < 0){
        this->coord->CoreLogDebug("[%s] recvPacketData failed, error=%d", this->TypeName(), err);
        return;
    }
    this->coord->CoreLogDebug("[%s] recvPacketData type=%d, data-type=%d, id=%d, route='%s', len=%d", this->TypeName(), message.type, message.dataType, message.id, message.route, message.length);
    switch(message.type){
        case base_message_type_request: {
            ManagedRequest* request = new ManagedRequest(this->coord, this);
            base_request_decode(&message, request);
            this->recvRequest(request);
            this->coord->Destory(request);
            break;
        }
        case base_message_type_notify: {
            ManagedNotify* notify = new ManagedNotify(this->coord, this);
            base_notify_decode(&message, notify);
            this->recvNotify(notify);
            this->coord->Destory(notify);
            break;
        }break;
        default:{
        }
    }
}



}
}        
