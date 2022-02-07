#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/net/tcp_agent.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;

namespace protobuf {
class Reflect;
}

namespace managed {//tolua_export

class ManagedServer;
class ManagedRequest;
class Managed;
enum ManagedAgentStatus {
	ManagedAgentStatus_Start = 0,
	ManagedAgentStatus_Handshake = 1,
	ManagedAgentStatus_Working = 2,
	ManagedAgentStatus_Closed = 3,
};

class ManagedAgent : public Destoryable, public net::ITcpAgentHandler  {//tolua_export
CC_CLASS(ManagedAgent);
public:
    ManagedAgent(Coord *coord, Managed* managed,  ManagedServer* server, net::TcpAgent* tcpAgent);
    virtual ~ManagedAgent();
public:

    int Response(const char* data, size_t len);
    int Response(const char* fmt, ...);
public:
    //关闭链接
    void close();
    int send(byte_slice& data);
    int send(const char* data, size_t len);
    void recvPacket(const char* data, size_t len);
    void recvRequest(ManagedRequest* request);
    void recvTcpNew(net::TcpAgent* agent);
    //implement net::ITcpAgentHandler begin
    virtual void recvTcpClose(net::TcpAgent* agent);
    virtual void recvTcpError(net::TcpAgent* agent);
    virtual int recvTcpData(net::TcpAgent* agent, char* data, size_t len);
    //implement net::ITcpAgentHandler end
public:
    Coord* coord;
    ManagedServer* server;
    Managed* managed;
    int sessionId;
    std::string remoteAddr;
    int status;
    uint64_t lastHeartbeatTime;
    std::string name;
    uint64_t version;
    net::TcpAgent* tcpAgent;
};//tolua_export

ManagedAgent* newManagedAgent(Coord* coord, Managed* managed,  ManagedServer* server, net::TcpAgent* tcpAgent);
}//tolua_export
}//tolua_export


