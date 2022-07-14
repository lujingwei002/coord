#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/pipe/pipe_agent.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;

namespace protobuf {
class Reflect;
}

namespace run {//tolua_export

class ManagedPipeServer;
class ManagedPipeRequest;
class Running;
enum ManagedPipeAgentStatus {
	ManagedPipeAgentStatus_Start = 0,
	ManagedPipeAgentStatus_Handshake = 1,
	ManagedPipeAgentStatus_Working = 2,
	ManagedPipeAgentStatus_Closed = 3,
};

class ManagedPipeAgent : public Destoryable, public pipe::IPipeAgentHandler  {//tolua_export
CC_CLASS(ManagedPipeAgent);
public:
    ManagedPipeAgent(Coord *coord, Running* running,  ManagedPipeServer* server, pipe::PipeAgent* pipeAgent);
    virtual ~ManagedPipeAgent();
public:

    int Response(const char* data, size_t len);
    int Response(const char* fmt, ...);
public:
    //关闭链接
    void close();
    int send(byte_slice& data);
    int send(const char* data, size_t len);
    void recvPacket(const char* data, size_t len);
    void recvRequest(ManagedPipeRequest* request);
    void recvPipeNew(pipe::PipeAgent* agent);
    //implement pipe::IPipeAgentHandler begin
    virtual void recvPipeClose(pipe::PipeAgent* agent);
    virtual void recvPipeError(pipe::PipeAgent* agent);
    virtual int recvPipeData(pipe::PipeAgent* agent, char* data, size_t len);
    //implement pipe::IPipeAgentHandler end
public:
    Coord*              coord;
    ManagedPipeServer*  server;
    Running*            running;
    int                 sessionId;
    std::string         remoteAddr;
    int                 status;
    uint64_t            lastHeartbeatTime;
    std::string         name;
    uint64_t            version;
    pipe::PipeAgent*    pipeAgent;
};//tolua_export

ManagedPipeAgent* newManagedPipeAgent(Coord* coord, Running* running,  ManagedPipeServer* server, pipe::PipeAgent* pipeAgent);
}//tolua_export
}//tolua_export


