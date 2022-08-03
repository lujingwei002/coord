#include "coord/cluster/cluster_agent.h"
#include "coord/cluster/cluster.h"
#include "coord/config/config.h"
#include "coord/cluster/cluster_packet.h"
#include "coord/cluster/cluster_server.h"
#include "coord/cluster/cluster_message.h"
#include "coord/cluster/cluster_notify.h"
#include "coord/cluster/cluster_request.h"
#include "coord/protobuf/init.h"
#include "coord/net/tcp_agent.h"
#include "proto/cluster.pb.h"
#include "coord/coord.h"
namespace coord {
namespace cluster {

cluster_agent* newClusterAgent(Coord* coord, Cluster* cluster,  cluster_server* server, net::TcpAgent* tcpAgent) {
    auto self = new cluster_agent(coord, cluster, server, tcpAgent);
    return self;
}

cluster_agent::cluster_agent(Coord *coord, Cluster* cluster,  cluster_server* server, net::TcpAgent* tcpAgent) : base_agent(coord) {
    this->cluster = cluster;
    this->server = server;
    this->tcpAgent = tcpAgent;
    this->status = cluster_agent_status_none;
    this->coord->DontDestory(this->tcpAgent);
    this->tcpAgent->SetHandler(this);
}

cluster_agent::~cluster_agent() {
    this->coord->CoreLogDebug("[cluster_agent] ~cluster_agent");
    this->coord->Destory(this->tcpAgent);
}

void cluster_agent::recvPacket(cluster_packet* packet) {
    this->coord->CoreLogDebug("[cluster_agent] recvPacket, type=%d", packet->type);
    switch(packet->type) {
        case packet_type_handshake:{
            this->recvHandShake(packet);
        }break;
        case packet_type_handshakeack:{
            this->recvHandShakeAck(packet);
        }break;
        case PacketType_Data:{
            this->recvData(packet);
        }break;
        case PacketType_Heartbeat:{
            this->recvHeartbeat(packet);
        }break;
    }
    this->lastHeartbeatTime = this->coord->Now();
} 

void cluster_agent::recvData(cluster_packet* packet) {
    if(this->status != cluster_agent_status_working) {
        this->coord->CoreLogDebug("[cluster_agent] recvData failed, status=%d, error='status not working'", this->status);
        return;
    }
    static thread_local cluster_message message;
    int err = clusterMessageDecode(message, packet->data, packet->length);
    if (err < 0){
        this->coord->CoreLogDebug("[cluster_agent] recvData failed, error=%d", err);
        return;
    }
    //发送到逻辑层
    //gamepb::LoginRequest req;
    this->coord->CoreLogDebug("[cluster_agent] recvData type=%d, id=%d, route='%s', len=%d", message.type, message.id, message.route, message.length);
    switch(message.type){
        case message_type_request: {
            Request* request = newRequest(this->coord, this);
            request->Id = message.id;
            request->Route = message.route;
            request->payload.Resize(0);
            coord::Append(request->payload, message.data, message.length);
            this->cluster->recvClusterRequest(request);
            this->coord->Destory(request);
            break;
        }
        case message_type_notify: {
            GateNotify* notify = newNotify(this->coord, this);
            notify->Route = message.route;
            notify->payload.Resize(0);
            coord::Append(notify->payload, message.data, message.length);
            this->cluster->recvClusterNotify(notify);
            this->coord->Destory(notify);
            break;
        }break;
        default:{
            
        }
    }
} 

void cluster_agent::recvHandShake(cluster_packet* packet) {
    if(this->status != cluster_agent_status_none) {
        this->coord->CoreLogDebug("[cluster_agent] recvHandShake failed, status=%d, error='status not start'", this->status);
        return;
    }
    cluster_handshake_request& request = this->handshakeRequest;
    cluster_handshake_response& response = this->handshakeResponse;
    google::protobuf::io::ArrayInputStream stream(packet->data, packet->length);
    if(request.ParseFromZeroCopyStream(&stream) == 0){
        this->coord->CoreLogError("[cluster_agent] recvHandShake.ParseFromZeroCopyStream failed");
        return;
    }
    this->name = request.nodename();
    this->version = request.version();
    this->coord->CoreLogDebug("[cluster_agent] recvHandShake, name=%s, version=%ld, host=%s, port=%ld", 
        request.nodename().c_str(), request.version(), request.host().c_str(), request.port());
    response.set_code(0);
    this->sendPacket(packet_type_handshake, &response);
    this->status = cluster_agent_status_handshake;
    //通知cluster检测新进来的节点
    this->cluster->reload(this->name.c_str(), this->version);
}

void cluster_agent::recvHandShakeAck(cluster_packet* packet) {
    this->coord->CoreLogDebug("[cluster_agent] recvHandShakeAck");
    if(this->status != cluster_agent_status_handshake) {
        this->coord->CoreLogDebug("[cluster_agent] recvHandShakeAck failed, status=%d, error='status not handshake'", this->status);
        return;
    }
    this->status = cluster_agent_status_working;;
} 

void cluster_agent::recvHeartbeat(cluster_packet* packet) {
    this->coord->CoreLogDebug("[cluster_agent] recvHeartbeat");
}

int cluster_agent::sendPacket(packet_type type, ::google::protobuf::Message* message) {
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
    return this->send(packet);
}

int cluster_agent::sendPacket(packet_type type, const char* data, size_t len) {
    static thread_local byte_slice packet(0, 0);
    int err = clkusterPacketEncode(packet, type, data, len);
    if (err < 0){
        this->coord->CoreLogDebug("[cluster_agent] Send failed, err=%d", err);
        return err;
    }
    this->send(packet);
    return 0;
}

void cluster_agent::heartbeat() {
   // this->coord->CoreLogDebug("[cluster_agent] heartbeat");
    if(this->status != cluster_agent_status_working){
        return;
    }
    uint64_t deadline = this->coord->Now() - 2 * this->cluster->config.Heartbeat*1000;
    if(this->lastHeartbeatTime < deadline){
        this->coord->CoreLogError("[cluster_agent] heartbeat failed, deadline=%ld\n", deadline);
        this->close();
        return;
    }
    this->sendPacket(PacketType_Heartbeat, NULL, 0);
}

int cluster_agent::response(uint64_t id, int code, byte_slice& data) {
    return this->response(id, code, data.Data(), data.Len());
}

int cluster_agent::response(uint64_t id, int code, const char* data, size_t len) {
    this->coord->CoreLogDebug("[cluster_agent] Response, sessionId=%d, id=%d, len=%d", this->SessionId, id, len);
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
    err = clusterMessageHeaderEncode(message, message_type_response, id, NULL, code);
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
    this->send(packet);
    return 0; 
}

int cluster_agent::response(uint64_t id, int code, protobuf::Reflect& proto) {
    return this->response(id, code, proto.GetMessage());
}

int cluster_agent::response(uint64_t id, int code, ::google::protobuf::Message* proto) {
    this->coord->CoreLogError("[cluster_agent] Response, sessionId=%d, id=%d", this->SessionId, id);
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
    err = clusterMessageHeaderEncode(message, message_type_response, id, NULL, code);
    if (err < 0){
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
    err = clusterPacketHeaderEncode(header, PacketType_Data, message.Len() + payload.Len());
    if (err < 0){
        return err;
    } 
    this->send(packet);
    return 0; 
}

void cluster_agent::recvTcpNew(net::TcpAgent* tcpAgent){
    this->coord->CoreLogDebug("[cluster_agent] recvTcpNew sessionId=%d", this->SessionId);
}

void cluster_agent::recvTcpClose(net::TcpAgent* agent){
    this->coord->CoreLogDebug("[cluster_agent] recvTcpClose sessionId=%d", this->SessionId);
    this->server->recvTcpClose(this);
}

void cluster_agent::recvTcpError(net::TcpAgent* agent){
    this->coord->CoreLogDebug("[cluster_agent] recvTcpError sessionId=%d", this->SessionId);
}

int cluster_agent::recvTcpData(net::TcpAgent* agent, char* data, size_t len){
    this->coord->CoreLogDebug("[cluster_agent] recvTcpData, len=%ld", len);
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

void cluster_agent::close() {
    this->tcpAgent->Close();
}

int cluster_agent::send(byte_slice& data) {
    return this->tcpAgent->Send(data);
}

int cluster_agent::send(const char* data, size_t len) {
    return -1;
}

}
}        
