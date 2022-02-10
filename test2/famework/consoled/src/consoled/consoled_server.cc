#include "consoled/consoled_server.h"
#include "consoled.h"
#include "consoled/consoled_agent.h"
#include "coord/net/init.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace consoled {

ConsoledServer* newConsoledServer(coord::Coord* coord, Consoled* consoled) {
    auto self = new ConsoledServer(coord, consoled);
    return self;
}

ConsoledServer::ConsoledServer(coord::Coord *coord, Consoled* consoled) {
    this->coord = coord;
    this->consoled = consoled;
    this->listener = NULL;
}

ConsoledServer::~ConsoledServer() {
    if(this->listener) {
        delete this->listener;
        this->listener = NULL;
    }
     for(auto it = this->agentDict.begin(); it != this->agentDict.end();) {
        ConsoledAgent* agent = it->second;
        this->coord->Destory(agent);
        ++it;
    }
    this->agentDict.clear();
}

int ConsoledServer::start() {
    this->coord->LogDebug("[ConsoledServer] start, host=%s, port=%d", this->consoled->config.Host.c_str(), this->consoled->config.Port);
    coord::net::TcpListener *listener = coord::net::NewTcpListener(this->coord);
    listener->SetHandler(this);
    int err = listener->Listen(this->consoled->config.Host.c_str(), this->consoled->config.Port);
    if (err < 0) {
        delete listener;
        return err;
    }
    this->listener = listener;
    return 0;
}

void ConsoledServer::recvTcpNew(coord::net::TcpListener* listener, coord::net::TcpAgent* tcpAgent){
    int sessionId = tcpAgent->sessionId;
    this->coord->LogDebug("[ConsoledServer] recvTcpNew sessionId=%d", sessionId);
    tcpAgent->SetRecvBuffer(4096);
    ConsoledAgent *agent = newConsoledAgent(this->coord, this->consoled, this, tcpAgent);
    agent->sessionId = sessionId;
    agent->remoteAddr = tcpAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
    agent->recvTcpNew(tcpAgent);
}

void ConsoledServer::recvTcpClose(ConsoledAgent* agent){
    int sessionId = agent->sessionId;
    this->coord->LogDebug("[ConsoledServer] recvTcpClose sessionId=%d", sessionId);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->LogDebug("[ConsoledServer] recvTcpClose failed, sessionId=%d, error='agent not found'", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void ConsoledServer::close() {
    
}

}
      