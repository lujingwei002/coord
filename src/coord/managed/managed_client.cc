#include "coord/managed/managed_client.h"
#include "coord/managed/managed.h"
#include "coord/config/config.h"
#include "coord/net/tcp_client.h"
//#include "coord/managed/managed_message.h"
#include "coord/managed/managed_promise.h"
#include "coord/managed/managed_result.h"
#include "coord/builtin/error.h"
#include "json/json.hpp"
#include "coord/coord.h"
namespace coord {
namespace managed {

CC_IMPLEMENT(ManagedClient, "coord::managed::ManagedClient")
    
ManagedClient::ManagedClient(Coord *coord, Managed* managed, const std::string& path, int ipc) : base_client(coord), path(path), ipc(ipc) {
    this->managed = managed;
    this->client = nullptr;
    this->connectPromise = nullptr;
    this->status = base_client_status_nil;
}

ManagedClient::~ManagedClient() {
    if(nullptr != this->client) {
        this->client->SetHandler(nullptr);
        this->coord->Destory(this->client);
        this->client = nullptr;
    }
}

int ManagedClient::Notify(const std::string& route, const char* data, size_t len) {
    if (this->status != base_client_status_working) {
        return ErrorNotReady;
    }
    return this->notify(route, data, len);
}

ManagedPromise* ManagedClient::Request(const std::string& route, Argument* argument) {
    if (this->status != base_client_status_working) {
        this->coord->CoreLogError("[%s] %s fail, route=%s, error=%d", this->TypeName(), __FUNCTION__, route.c_str(), ErrorNotReady);
        return nullptr;
    }
    return this->request(route, argument);
}

ManagedPromise* ManagedClient::Request(const std::string& route, const char* data, size_t len) {
    if (this->status != base_client_status_working) {
        this->coord->CoreLogError("[%s] %s fail, route=%s, error=%d", this->TypeName(), __FUNCTION__, route.c_str(), ErrorNotReady);
        return nullptr;
    }
    return this->request(route, data, len);
}

ManagedPromise* ManagedClient::Request(const std::string& route, google::protobuf::Message* proto) {
    if (this->status != base_client_status_working) {
        this->coord->CoreLogError("[%s] %s fail, route=%s, error=%d", this->TypeName(), __FUNCTION__, route.c_str(), ErrorNotReady);
        return nullptr;
    }
    return this->request(route, proto);
}

ManagedPromise* ManagedClient::Connect() {
    if (this->status != base_client_status_nil) {
        return nullptr;
    }
    if(nullptr != this->client) {
        return nullptr;
    }
    pipe::PipeClient* client = new pipe::PipeClient(this->coord);
    client->SetRecvBuffer(4096);
    client->SetHandler(this);
    int err = client->Connect(this->path.c_str(), this->ipc);
    if (err < 0) {
        this->coord->CoreLogError("[ManagedClient] Connect failed, path='%s', error=%d", this->path.c_str(), err);
        return nullptr;
    }
    this->client = client;
    if (this->connectPromise) {
        return nullptr;
    }
    auto promise = new ManagedPromise(this->coord);
    if (nullptr == promise) {
        return nullptr;
    }
    this->connectPromise = promise;
    return promise;
}

void ManagedClient::responseConnect(int err) {
    if (nullptr == this->connectPromise) {
        return;
    }
    if (err) {
        this->connectPromise->reject(this, nullptr);
        this->coord->Destory(this->connectPromise);
        this->connectPromise = nullptr;
    } else {
        this->connectPromise->resolve(this, nullptr);
        this->coord->Destory(this->connectPromise);
        this->connectPromise = nullptr;
    }
}

void ManagedClient::EvConnect(){
    this->coord->CoreLogDebug("[ManagedClient] EvConnect, path=%s, ipc=%d", this->path.c_str(), this->ipc);
    this->status = base_client_status_connnected;
    int err = this->sendHandshakePacket();
    if (err) {
        this->responseConnect(err);
        // 主动关闭
        err = this->client->Close();
        if (err) {
            this->coord->CoreLogError("[ManagedClient] EvConnect Close fail, error='%s'", err);
        }
    } else {
        this->status = base_client_status_handshake;
    }
}

void ManagedClient::EvConnectError(int err) {
   this->coord->CoreLogError("[ManagedClient] EvConnectError, path=%s, ipc=%d, error=%d", this->path.c_str(), this->ipc, err);
    if (this->status != base_client_status_connecting) {
        return;
    }
    this->responseConnect(err);
}

void ManagedClient::EvClose(){
    this->coord->CoreLogDebug("[ManagedClient] EvClose, path=%s, ipc=%d", this->path.c_str(), this->ipc);
    this->status = base_client_status_closed;
}

void ManagedClient::EvError(int err){
    this->coord->CoreLogDebug("[ManagedClient] EvError, path=%s, ipc=%d", this->path.c_str(), this->ipc);
} 

void ManagedClient::recvPacket(managed_packet* packet) {
    this->coord->CoreLogDebug("[%s] recvPacket, type=%d", this->TypeName(), packet->type);
    switch(packet->type) {
        case base_packet_type_handshake:{
            this->recvPacketHandShake(packet);
        }break;
        case base_packet_type_data:{
            this->recvPacketData(packet);
        }break;
        case base_packet_type_heartbeat:{
            this->recvPacketHeartbeat(packet);
        }break;
    }
}  

void ManagedClient::recvPacketHeartbeat(managed_packet* packet) {
    this->coord->CoreLogDebug("[%s] recvPacetHeartbeat", this->TypeName());
    this->sendPacket(base_packet_type_heartbeat, nullptr, 0);
}

int ManagedClient::EvData(char* data, size_t len){
    this->coord->CoreLogDebug("[ManagedClient] EvData, len=%ld", len);
    this->coord->CoreLogDebug("[%s] recvPipeData, len=%ld", this->TypeName(), len);
    if(len < sizeof(managed_packet_header)) {
        return 0;
    } 
    managed_packet_header *header = (managed_packet_header*)data;
    uint32_t length = (header->length[0] << 16) | (header->length[1] << 8) | header->length[2];
    if (len < length + sizeof(managed_packet_header)) {
        return 0;
    }
    static thread_local managed_packet packet;
    int err = base_packet_decode(packet, data, len);
    if(err < 0){
        return 0;
    }    
    this->recvPacket(&packet);
    return length + sizeof(managed_packet_header);
}

int ManagedClient::Send(byte_slice& packet) {
    return this->client->Send(packet);
}

void ManagedClient::onDestory() {
    // 连接回调
    this->responseConnect(ErrorDestory);
    // request 回调
    if (this->promiseDict.size() > 0) {
        ManagedResult* result = new ManagedResult(this->coord);
        result->Code = 501;
        for(auto it = this->promiseDict.begin(); it != this->promiseDict.end();) {
            ManagedPromise* promise = it->second;
            result->ReqTime = promise->reqTime;
            result->Route = promise->route;
            promise->reject(this, result);
            this->coord->Destory(promise);
            ++it;   
        }
        this->coord->Destory(result);
        this->promiseDict.clear();
    }
} 

int ManagedClient::Close() {
    return this->client->Close();
}

void ManagedClient::recvPacketHandShake(managed_packet* packet) {
    if(this->status != base_client_status_handshake) {
        this->coord->CoreLogError("[%s] recvHandShake failed, status=%d, error='status not handshake'", this->TypeName(), this->status);
        return;
    }
    google::protobuf::io::ArrayInputStream stream(packet->data, packet->length);
    if(this->handshakeResponse.ParseFromZeroCopyStream(&stream) == 0){
        this->coord->CoreLogError("[%s] recvHandShake.ParseFromZeroCopyStream failed", this->TypeName());
        return;
    }
    this->coord->CoreLogDebug("[%s] recvHandShake, code=%ld", this->TypeName(), this->handshakeResponse.code());
    this->sendPacket(base_packet_type_handshakeack, &this->handshakeAck);
    this->status = base_client_status_working;
    this->responseConnect(0);
}

void ManagedClient::recvPacketData(managed_packet* packet) {
    static thread_local base_message message;
    if(this->status != base_client_status_working) {
        this->coord->CoreLogDebug("[%s] recvData failed, status=%d, error='status not working'", this->TypeName(), this->status);
        return;
    }
    int err = base_message_decode(message, packet->data, packet->length);
    if (err < 0){
        this->coord->CoreLogDebug("[%s] recvData failed, err=%d", this->TypeName(), err);
        return;
    }
    this->coord->CoreLogDebug("[%s] recvData type=%d, id=%d, route=%s, len=%d", this->TypeName(), message.type, message.id, message.route, message.length);
    switch(message.type){
        case base_message_type_response: {
            auto it = this->promiseDict.find(message.id);
            if (it != this->promiseDict.end()) {
                ManagedPromise* promise = it->second;
                ManagedResult* result = new ManagedResult(this->coord);
                result->ReqTime = promise->reqTime;
                result->Route = promise->route;
                base_result_decode(&message, result);
                this->promiseDict.erase(it);
                if (result->Code == 0) {
                    promise->resolve(this, result);
                } else {
                    promise->reject(this, result);
                }
                this->coord->Destory(result);
                this->coord->Destory(promise);
                break; 
            }
            break;
        } 
        default:{
            
        }
    }
} 

int ManagedClient::sendHandshakePacket() {
    this->handshakeRequest.set_version(1);
    return this->sendPacket(base_packet_type_handshake, &this->handshakeRequest);
}

}
} 
