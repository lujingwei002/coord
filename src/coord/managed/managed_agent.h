#pragma once 


#include "coord/base/internal_agent.h"
#include "proto/coord.pb.h"
#include "coord/base/base_packet.h"
#include "coord/base/base_message.h"
#include "coord/pipe/pipe_agent.h"
#include "coord/managed/declare.h"
#include "coord/protobuf/declare.h"
#include <vector>
#include <iostream>
#include <map>

namespace coord {
    class Coord;
}

namespace coord {//tolua_export
namespace managed {//tolua_export

class ManagedAgent : public internal_agent, public pipe::IPipeAgentHandler  {//tolua_export
RC_CLASS(ManagedAgent);
friend managed_server;
friend ManagedResponse;
friend coord::pipe::PipeAgent;
private:
    ManagedAgent(Coord *coord, Managed* managed,  managed_server* server, pipe::PipeAgent* pipeAgent);
    virtual ~ManagedAgent();
public:
    /// 关闭链接
    void Close();//tolua_export
private:
    void recvRequest(ManagedRequest* request);
    void recvNotify(ManagedNotify* notify);
    void recvPacket(base_packet* packet);
    void recvPacketHandShake(base_packet* packet);
    void recvPacketHandShakeAck(base_packet* packet);
    void recvPacketData(base_packet* packet);
    void recvAgentNew(pipe::PipeAgent* pipeAgent);
protected:
    virtual int send(const char* data, size_t len);
    virtual int send(byte_slice& data);
    //implement pipe::IPipeAgentHandler begin
    virtual void EvClose(pipe::PipeAgent* agent);
    virtual void EvError(pipe::PipeAgent* agent);
    virtual int EvData(pipe::PipeAgent* agent, char* data, size_t len);
    //implement pipe::IPipeAgentHandler end
private:
    managed_server*         server;
    Managed*                managed;
    pipe::PipeAgent*        pipeAgent;
    int                     status;
    uint64_t                lastHeartbeatTime;
    base_handshake_request  handshakeRequest;   
    base_handshake_response handshakeResponse;
    base_handshake_ack      handshakeAck;
};//tolua_export

}//tolua_export
}//tolua_export


