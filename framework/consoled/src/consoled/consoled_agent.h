#pragma once 

#include "coord/builtin/init.h"
#include "coord/net/init.h"
#include <vector>
#include <iostream>
#include <map>

namespace coord {
class Coord;
}

namespace consoled {//tolua_export

class ConsoledServer;
class ConsoledRequest;
class Consoled;

enum ConsoledAgentStatus {
	ConsoledAgentStatus_Start = 0,
	ConsoledAgentStatus_Handshake = 1,
	ConsoledAgentStatus_Working = 2,
	ConsoledAgentStatus_Closed = 3,
};

class ConsoledAgent : public coord::Destoryable, public coord::net::ITcpAgentHandler  {//tolua_export
CC_CLASS(ConsoledAgent);
public:
    ConsoledAgent(coord::Coord *coord, Consoled* consoled,  ConsoledServer* server, coord::net::TcpAgent* tcpAgent);
    virtual ~ConsoledAgent();
public:
    int Response(const char* data, size_t len);
    int Response(const char* fmt, ...);
public:
    //关闭链接
    void close();
    int send(coord::byte_slice& data);
    int send(const char* data, size_t len);
    void recvPacket(const char* data, size_t len);
    void recvRequest(ConsoledRequest* request);
    void recvTcpNew(coord::net::TcpAgent* agent);
    //implement net::ITcpAgentHandler begin
    virtual void recvTcpClose(coord::net::TcpAgent* agent);
    virtual void recvTcpError(coord::net::TcpAgent* agent);
    virtual int recvTcpData(coord::net::TcpAgent* agent, char* data, size_t len);
    //implement net::ITcpAgentHandler end
public:
    coord::Coord*           coord;
    ConsoledServer*         server;
    Consoled*               consoled;
    int                     sessionId;
    std::string             remoteAddr;
    int                     status;
    uint64_t                lastHeartbeatTime;
    std::string             name;
    uint64_t                version;
    coord::net::TcpAgent*   tcpAgent;
};//tolua_export

ConsoledAgent* newConsoledAgent(coord::Coord* coord, Consoled* consoled,  ConsoledServer* server, coord::net::TcpAgent* tcpAgent);
}//tolua_export



