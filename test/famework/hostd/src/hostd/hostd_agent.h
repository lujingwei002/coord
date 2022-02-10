#pragma once 

#include "coord/builtin/init.h"
#include "coord/net/init.h"
#include <vector>
#include <iostream>
#include <map>

namespace coord {
class Coord;
}

namespace hostd {//tolua_export

class HostdServer;
class HostdRequest;
class Hostd;
enum HostdAgentStatus {
	HostdAgentStatus_Start = 0,
	HostdAgentStatus_Handshake = 1,
	HostdAgentStatus_Working = 2,
	HostdAgentStatus_Closed = 3,
};

class HostdAgent : public coord::Destoryable, public coord::net::ITcpAgentHandler  {//tolua_export
CC_CLASS(HostdAgent);
public:
    HostdAgent(coord::Coord *coord, Hostd* hostd,  HostdServer* server, coord::net::TcpAgent* tcpAgent);
    virtual ~HostdAgent();
public:

    int Response(const char* data, size_t len);
    int Response(const char* fmt, ...);
public:
    //关闭链接
    void close();
    int send(coord::byte_slice& data);
    int send(const char* data, size_t len);
    void recvPacket(const char* data, size_t len);
    void recvRequest(HostdRequest* request);
    void recvTcpNew(coord::net::TcpAgent* agent);
    //implement net::ITcpAgentHandler begin
    virtual void recvTcpClose(coord::net::TcpAgent* agent);
    virtual void recvTcpError(coord::net::TcpAgent* agent);
    virtual int recvTcpData(coord::net::TcpAgent* agent, char* data, size_t len);
    //implement net::ITcpAgentHandler end
public:
    coord::Coord* coord;
    HostdServer* server;
    Hostd* hostd;
    int sessionId;
    std::string remoteAddr;
    int status;
    uint64_t lastHeartbeatTime;
    std::string name;
    uint64_t version;
    coord::net::TcpAgent* tcpAgent;
};//tolua_export

HostdAgent* newHostdAgent(coord::Coord* coord, Hostd* hostd,  HostdServer* server, coord::net::TcpAgent* tcpAgent);
}//tolua_export



