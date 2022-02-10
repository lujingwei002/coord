#include "coord/cluster/cluster_client.h"
#include "coord/cluster/cluster.h"
#include "coord/config/config.h"
#include "coord/net/tcp_client.h"
#include "coord/cluster/cluster_message.h"
#include "coord/cluster/cluster_promise.h"
#include "coord/cluster/cluster_result.h"
#include "coord/protobuf/init.h"
#include "json/json.hpp"
#include "coord/coord.h"
namespace coord {
namespace cluster {

cluster_client* newClusterClient(Coord* coord, Cluster* cluster, const char* name, uint64_t version, const char* host, uint16_t port) {
    cluster_client* self = new cluster_client(coord, cluster, name, version, host, port);
    return self;
}

cluster_client::cluster_client(Coord *coord, Cluster* cluster, const char* name, uint64_t version, const char* host, uint16_t port) 
    : name(name), host(host), port(port), version(version) {
    this->coord = coord;
    this->cluster = cluster;
    this->client = NULL;
    this->status = cluster_client_status_start;
    this->requestId = 0;
}

cluster_client::~cluster_client() {
    this->coord->coreLogDebug("[cluster_client] ~cluster_client");
    if(this->client != NULL) {
        this->client->SetHandler(NULL);
        this->coord->Destory(this->client);
        this->client = NULL;
    }
}

int cluster_client::connect() {
    if(this->client != NULL) {
        return -1;
    }
    net::TcpClient* client = net::newTcpClient(this->coord);
    client->SetRecvBuffer(4096);
    client->SetHandler(this);
    int err = client->Connect(this->host.c_str(), this->port);
    if (err < 0) {
        this->coord->coreLogError("[cluster_client] connect failed, error=%d", err);
        return err;
    }
    this->client = client;
    return 0;
}

void cluster_client::tryReconnect() {
    if(this->client == NULL) {
        return;
    }
    if(this->client->GetStatus() != net::TcpClientStatus_CLOSED) {
        return;
    }
    int err = client->Reconnect(this->host.c_str(), this->port);
    if (err < 0) {
        this->coord->coreLogError("[cluster_client] tryReconnect failed, error=%d", err);
        return;
    }
}

void cluster_client::recvTcpConnect(){
    this->coord->coreLogDebug("[cluster_client] recvTcpConnect, name=%s, host=%s, port=%d", 
            this->name.c_str(), this->host.c_str(), this->port);

    this->sendHandshake();
}

void cluster_client::recvTcpClose(){
    this->coord->coreLogDebug("[cluster_client] recvTcpClose, name=%s, host=%s, port=%d", 
            this->name.c_str(), this->host.c_str(), this->port);
}

void cluster_client::recvTcpError(int err){
    this->coord->coreLogDebug("[cluster_client] recvTcpError, name=%s, host=%s, port=%d", 
            this->name.c_str(), this->host.c_str(), this->port);
} 

int cluster_client::recvTcpData(char* data, size_t len){
    this->coord->coreLogDebug("[cluster_client] recvTcpData, name=%s, len=%ld", 
            this->name.c_str(), len);
    if(len < sizeof(cluster_packet_header)) {
        return 0;
    } 
    cluster_packet_header *header = (cluster_packet_header*)data;
    uint32_t length = (header->length[0] << 16) | (header->length[1] << 8) | header->length[2];
    if (len < length + sizeof(cluster_packet_header)) {
        return 0;
    }
    static thread_local cluster_packet packet;
    int err = clusterPacketDecode(packet, data, len);
    if(err < 0){
        return 0;
    }    
    this->recvPacket(&packet);
    return length + sizeof(cluster_packet_header);
}

void cluster_client::recvConnectError(const char* err) {
   this->coord->coreLogError("[cluster_client] recvConnectError, name=%s, host=%s, port=%d, error='%s'", 
        this->name.c_str(), this->host.c_str(), this->port, err);
}

void cluster_client::recvPacket(cluster_packet* packet) {
    this->coord->coreLogDebug("[cluster_client] recvPacket, name=%s, type=%d", 
        this->name.c_str(), packet->type);
    switch(packet->type) {
        case packet_type_handshake:{
            this->recvHandShake(packet);
        }break;
        case PacketType_Data:{
            this->recvData(packet);
        }break;
        case PacketType_Heartbeat:{
            this->recvHeartbeat(packet);
        }break;
    }
}

void cluster_client::onDestory() {
    if (this->promiseDict.size() > 0) {
        Result* result = newResult(this->coord, this);
        result->Code = 501;
        for(auto it = this->promiseDict.begin(); it != this->promiseDict.end();) {
            Promise* promise = it->second;
            result->route = promise->route;
            result->reqTime = promise->reqTime;
            promise->reject(result);
            this->coord->Destory(promise);
            ++it;   
        }
        this->coord->Destory(result);
        this->promiseDict.clear();
    }
}

void cluster_client::recvData(cluster_packet* packet) {
    if(this->status != cluster_client_status_working) {
        this->coord->coreLogDebug("[cluster_client] recvData failed, status=%d, error='status not working'", this->status);
        return;
    }
    static thread_local cluster_message message;
    int err = clusterMessageDecode(message, packet->data, packet->length);
    if (err < 0){
        this->coord->coreLogDebug("[cluster_client] recvData failed, err=%d", err);
        return;
    }
    //发送到逻辑层
    this->coord->coreLogDebug("[cluster_client] recvData type=%d, id=%d, route=%s, len=%d", message.type, message.id, message.route, message.length);
    switch(message.type){
        case message_type_response: {
            auto it = this->promiseDict.find(message.id);
            if (it != this->promiseDict.end()) {
                Promise* promise = it->second;
                Result* result = newResult(this->coord, this);
                result->Code = message.code;
                result->route = promise->route;
                result->reqTime = promise->reqTime;
                result->payload.Resize(0);
                coord::Append(result->payload, message.data, message.length);
                if (result->Code == 0) {
                    promise->resolve(result);
                } else {
                    promise->reject(result);
                }
                this->coord->Destory(result);
                this->promiseDict.erase(it);
                this->coord->Destory(promise);
                break; 
            }
            break;
        } 
        default:{
            
        }
    }
} 

void cluster_client::recvHandShake(cluster_packet* packet) {
    if(this->status != cluster_client_status_start) {
        this->coord->coreLogError("[cluster_client] recvHandShake failed, status=%d, error='status not handshake'", this->status);
        return;
    }
    google::protobuf::io::ArrayInputStream stream(packet->data, packet->length);
    if(this->handshakeResponse.ParseFromZeroCopyStream(&stream) == 0){
        this->coord->coreLogError("[cluster_agent] recvHandShake.ParseFromZeroCopyStream failed");
        return;
    }
    this->coord->coreLogDebug("[cluster_client] recvHandShake, code=%ld", this->handshakeResponse.code());
    this->sendPacket(packet_type_handshakeack, &this->handshakeAck);
    this->status = cluster_client_status_working;
    this->flushPacketCache();
}

void cluster_client::recvHeartbeat(cluster_packet* packet) {
    this->coord->coreLogDebug("[cluster_client] recvHeartbeat");
    this->sendPacket(PacketType_Heartbeat, NULL, 0);
}

int cluster_client::sendHandshake() {
    this->handshakeRequest.set_nodename(this->name);
    this->handshakeRequest.set_host(this->host);
    this->handshakeRequest.set_port(this->port);
    this->handshakeRequest.set_version(this->version);
    int err = this->sendPacket(packet_type_handshake, &this->handshakeRequest);
    return err;
}

int cluster_client::sendPacket(packet_type type, ::google::protobuf::Message* message) {
    byte_slice packet;
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = clusterPacketHeaderEncode(header, type, 0);
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
    err = clusterPacketHeaderEncode(header, type, body.Len());
    if (err < 0){
        return err;
    } 
    return this->client->Send(packet);
}

int cluster_client::sendPacket(packet_type type, const char* data, size_t len) {
    static thread_local byte_slice packet;
    int err = clkusterPacketEncode(packet, type, data, len);
    if (err < 0){
        this->coord->coreLogDebug("[cluster_client] Send failed, err=%d", err);
        return err;
    }
    this->client->Send(packet);
    return 0;
}

int cluster_client::notify(const char* route, const char* data, size_t len) {
    this->coord->coreLogError("[cluster_client] notify, route=%s", route);
    byte_slice packet;
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = clusterPacketHeaderEncode(header, PacketType_Data, 0);
    if (err < 0){
        return err;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = clusterMessageHeaderEncode(message, message_type_notify, 0, route);
    if (err < 0){
        return err;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    coord::Append(payload, data, len);
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = clusterPacketHeaderEncode(header, PacketType_Data, message.Len() + payload.Len());
    if (err < 0){
        return err;
    } 
    return  this->sendPacket(packet);
}

Promise* cluster_client::request(const char* route, const char* data, size_t len) {
    this->coord->coreLogDebug("[cluster_client] request, route=%s", route);
    byte_slice packet;
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = clusterPacketHeaderEncode(header, PacketType_Data, 0);
    if (err < 0){
        return NULL;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    int requestId = ++this->requestId;
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = clusterMessageHeaderEncode(message, message_type_request, requestId, route);
    if (err < 0){
        return NULL;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    coord::Append(payload, data, len);
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = clusterPacketHeaderEncode(header, PacketType_Data, message.Len() + payload.Len());
    if (err < 0){
        return NULL;
    } 
    err =  this->sendPacket(packet);
    if (err < 0) {
        return NULL;
    }
    Promise* promise = cluster::newPromise(this->coord);
    promise->route = route;
    this->promiseDict[requestId] = promise;
    return promise;
}

Promise* cluster_client::request(const char* route, google::protobuf::Message* proto) {
    this->coord->coreLogDebug("[cluster_client] request, route=%s", route);
    byte_slice packet;
    //packet header
    byte_slice header = packet.Slice(packet.Len(), packet.Len());
    int err = clusterPacketHeaderEncode(header, PacketType_Data, 0);
    if (err < 0){
        return NULL;
    }
    packet.Resize(packet.Len() + header.Len());
    //message header
    int requestId = ++this->requestId;
    byte_slice message = packet.Slice(packet.Len(), packet.Len());
    err = clusterMessageHeaderEncode(message, message_type_request, requestId, route);
    if (err < 0){
        return NULL;
    }
    packet.Resize(packet.Len() + message.Len());
    //message body
    byte_slice payload = packet.Slice(packet.Len(), packet.Len());
    err = protobuf::Serialize(payload, proto);
    if(err){
        return NULL;
    }
    packet.Resize(packet.Len() + payload.Len());
    //重新写packet header 
    header.Resize(0);
    err = clusterPacketHeaderEncode(header, PacketType_Data, message.Len() + payload.Len());
    if (err < 0){
        return NULL;
    } 
    err =  this->sendPacket(packet);
    if (err < 0) {
        return NULL;
    }
    Promise* promise = cluster::newPromise(this->coord);
    promise->route = route;
    this->promiseDict[requestId] = promise;
    return promise;
}

int cluster_client::sendPacket(byte_slice& packet) {
    if(this->status == cluster_client_status_start) {
        this->packetCache.push_back(packet);
        return 0;
    }
    return this->client->Send(packet);
}

void cluster_client::flushPacketCache() {
    if(this->status != cluster_client_status_working) {
        return;
    }
    for(auto it : this->packetCache) {
        this->sendPacket(it);
    }
}

}
}         