#include "coord/run/managed_pipe_server.h"
#include "coord/run/running.h"
#include "coord/pipe/pipe_listener.h"
#include "coord/run/managed_pipe_agent.h"
#include "coord/config/config.h"
#include "coord/coord.h"
namespace coord {
namespace run {

ManagedPipeServer* newManagedPipeServer(Coord* coord, Running* running) {
    auto self = new ManagedPipeServer(coord, running);
    return self;
}

ManagedPipeServer::ManagedPipeServer(Coord *coord, Running* running) {
    this->coord = coord;
    this->running = running;
    this->listener = NULL;
}

ManagedPipeServer::~ManagedPipeServer() {
    if(this->listener) {
        delete this->listener;
        this->listener = NULL;
    }
     for(auto it = this->agentDict.begin(); it != this->agentDict.end();) {
        ManagedPipeAgent* agent = it->second;
        this->coord->Destory(agent);
        ++it;
    }
    this->agentDict.clear();
}

int ManagedPipeServer::start() {
    this->coord->CoreLogDebug("[ManagedPipeServer] start, path=%s", this->coord->Environment->ManagedSockPath.c_str());
    pipe::PipeListener *listener = pipe::NewPipeListener(this->coord);
    listener->SetHandler(this);
    int err = listener->Listen(this->coord->Environment->ManagedSockPath, 1);
    if (err < 0) {
        delete listener;
        return err;
    }
    this->listener = listener;
    return 0;
}

void ManagedPipeServer::recvPipeNew(pipe::PipeListener* listener, pipe::PipeAgent* pipeAgent){
    int sessionId = pipeAgent->sessionId;
    this->coord->CoreLogDebug("[ManagedServer] recvPipeNew sessionId=%d", sessionId);
    pipeAgent->SetRecvBuffer(4096);
    ManagedPipeAgent *agent = newManagedPipeAgent(this->coord, this->running, this, pipeAgent);
    agent->sessionId = sessionId;
    agent->remoteAddr = pipeAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
    agent->recvPipeNew(pipeAgent);
}

void ManagedPipeServer::recvPipeClose(ManagedPipeAgent* agent){
    int sessionId = agent->sessionId;
    this->coord->CoreLogDebug("[ManagedPipeServer] recvPipeClose sessionId=%d", sessionId);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->CoreLogDebug("[ManagedPipeServer] recvPipeClose failed, sessionId=%d, error='agent not found'", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void ManagedPipeServer::close() {
    
}

}
}        