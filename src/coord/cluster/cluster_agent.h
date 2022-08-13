#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
//#include "protobuf/cluster.pb.h"
#include "proto/coord.pb.h"
#include "coord/cluster/cluster_packet.h"
#include "coord/base/internal_agent.h"
#include "coord/net/tcp_agent.h"
#include "coord/protobuf/declare.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;


namespace cluster {//tolua_export

class cluster_server;
class cluster_packet;
class Cluster;

enum cluster_agent_status {
	cluster_agent_status_none = 0,
	cluster_agent_status_handshake = 1,
	cluster_agent_status_working = 2,
	cluster_agent_status_closed = 3,
};

class cluster_agent : public internal_agent, public net::ITcpAgentHandler  {//tolua_export
public:
    cluster_agent(Coord *coord, Cluster* cluster,  cluster_server* server, net::TcpAgent* tcpAgent);
    virtual ~cluster_agent();
public:
    ///处理网络数据
    int recvData(char* data, size_t len);
    //处理packet
    void recvPacket(cluster_packet* packet);
    //处理握手
    void recvHandShake(cluster_packet* packet);
    //处理握手确认
    void recvHandShakeAck(cluster_packet* packet);
    //处理消息包
    void recvData(cluster_packet* packet);
    //处理心跳包
    void recvHeartbeat(cluster_packet* packet);
    //发送proto
    int sendPacket(packet_type type, ::google::protobuf::Message* message);
    //发送网络数据
    int sendPacket(packet_type type, const char* data, size_t len);
    //定时检查和发送心跳包
    void heartbeat();
    //关闭链接
    void close();
    virtual int send(byte_slice& data);
    virtual int send(const char* data, size_t len);
    //响应request
    int response(uint64_t id, int code, const char* data, size_t len);
    //响应request
    int response(uint64_t id, int code, byte_slice& data);
    int response(uint64_t id, int code, protobuf::MessageRef& proto);
    int response(uint64_t id, int code, ::google::protobuf::Message* message);
    //implement net::ITcpAgentHandler begin
    virtual void recvTcpNew(net::TcpAgent* agent);
    virtual void recvTcpClose(net::TcpAgent* agent);
    virtual void recvTcpError(net::TcpAgent* agent);
    virtual int recvTcpData(net::TcpAgent* agent, char* data, size_t len);
    //implement net::ITcpAgentHandler end
public:
    cluster_server*             server;
    Cluster*                    cluster;
    int                         status;             //当前状态
    cluster_handshake_request   handshakeRequest;   
    cluster_handshake_response  handshakeResponse;
    cluster_handshake_ack       handshakeAck;
    uint64_t                    lastHeartbeatTime;  //上次收到消息的时间戳
    std::string                 name;               //节点名字
    uint64_t                    version;            //节点版本
    net::TcpAgent*              tcpAgent;
};//tolua_export

cluster_agent* newClusterAgent(Coord* coord, Cluster* cluster,  cluster_server* server, net::TcpAgent* tcpAgent);
}//tolua_export
}//tolua_export


