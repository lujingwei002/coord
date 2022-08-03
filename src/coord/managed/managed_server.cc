#include "coord/managed/managed_server.h"
#include "coord/managed/managed.h"
#include "coord/managed/managed_agent.h"
#include "coord/pipe/pipe_listener.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace coord {
namespace managed {

CC_IMPLEMENT(managed_server, "coord::managed::managed_server")

managed_server::managed_server(Coord *coord, Managed* managed) {
    this->coord = coord;
    this->managed = managed;
    this->listener = nullptr;
}

managed_server::~managed_server() {
    if(this->listener) {
        this->listener->SetHandler(nullptr);
        this->coord->Destory(this->listener);
        this->listener = nullptr;
    }
     for(auto it = this->agentDict.begin(); it != this->agentDict.end();) {
        ManagedAgent* agent = it->second;
        this->coord->Destory(agent);
        ++it;
    }
    this->agentDict.clear();
}

int managed_server::start() {
    this->coord->CoreLogDebug("[managed_server] start, path=%s", this->coord->Environment->ManagedSockPath.c_str());
    pipe::PipeListener *listener = pipe::NewPipeListener(this->coord);
    listener->SetHandler(this);
    int err = listener->Listen(this->coord->Environment->ManagedSockPath, 1);
    if (err < 0) {
        this->coord->Destory(this->listener);
        return err;
    }
    this->listener = listener;
    return 0;
}

void managed_server::EvClose(pipe::PipeListener* listener){
}

// 新连接事件
void managed_server::EvConnection(pipe::PipeListener* listener, pipe::PipeAgent* pipeAgent){
    int sessionId = pipeAgent->SessionId;
    this->coord->CoreLogDebug("[managed_server] EvConnection sessionId=%d", sessionId);
    pipeAgent->SetRecvBuffer(4096);
    ManagedAgent *agent = new ManagedAgent(this->coord, this->managed, this, pipeAgent);
    agent->SessionId = sessionId;
    agent->RemoteAddr = pipeAgent->RemoteAddr;
    this->agentDict[sessionId] = agent;
    agent->recvAgentNew(pipeAgent);
}

// agent关闭通知
void managed_server::recvAgentClose(ManagedAgent* agent){
    int sessionId = agent->SessionId;
    this->coord->CoreLogDebug("[managed_server] recvAgentClose sessionId=%d", sessionId);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->CoreLogDebug("[managed_server] recvAgentClose failed, sessionId=%d, error='agent not found'", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

int managed_server::close() {
    if (nullptr == this->listener) {
        return ErrorInvalidStatus;
    }
    return this->listener->Close();
}

}
}       
