#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/net/tcp_client.h"
#include "coord/cluster/cluster_packet.h"
#include "coord/protobuf/declare.h"
#include "proto/coord.pb.h"
#include <google/protobuf/message.h>
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>
namespace coord {//tolua_export
    

class Coord;

namespace cluster {//tolua_export

class Cluster;
class Promise;
enum cluster_client_status {
	cluster_client_status_start = 0,
	cluster_client_status_handshake = 1,
	cluster_client_status_working = 2,
	cluster_client_status_closed = 3,
};

class cluster_client : public net::ITcpClientHandler, public RcObject {//tolua_export
public:
    cluster_client(Coord *coord, Cluster* cluster, const char* name, uint64_t version, const char* host, uint16_t port);
    virtual ~cluster_client();
public:
    int notify(const char* route, const char* data, size_t len);
    Promise* request(const char* route, const char* data, size_t len);
    Promise* request(const char* route, google::protobuf::Message* message);
public:
    virtual void onDestory(); 
    //implement net::ITcpClientHandler begin
    virtual void recvTcpConnect();
    virtual void recvTcpClose();
    virtual void recvTcpError(int err);
    virtual void recvTcpConnectError(const char* err);
    virtual int recvTcpData(char* data, size_t len);
    //implement net::ITcpClientHandler end
    int sendHandshake();
    int sendPacket(packet_type type, ::google::protobuf::Message* message);
    int sendPacket(packet_type type, const char* data, size_t len);
    int sendPacket(byte_slice& packet);
    void recvPacket(cluster_packet* packet);    
    void recvData(cluster_packet* packet); 
    void recvHandShake(cluster_packet* packet);
    void recvHeartbeat(cluster_packet* packet);
    void flushPacketCache();
public:
    int connect(); 
    void tryReconnect();
public:
    Coord*                      coord;
    Cluster*                    cluster;
    std::string                 name;               //节点名字
    std::string                 host;
    int16_t                     port;
    net::TcpClient*             client;
    cluster_handshake_request   handshakeRequest;
    cluster_handshake_response  handshakeResponse;
    cluster_handshake_ack       handshakeAck;
    uint64_t                    version;            //节点版本
    std::vector<byte_slice>     packetCache;
    int                         status;
    int                         requestId;
    std::map<int, Promise*>     promiseDict;
};//tolua_export

cluster_client* newClusterClient(Coord* coord, Cluster* cluster, const char* name, uint64_t version, const char* host, uint16_t port);
}//tolua_export
}//tolua_export


