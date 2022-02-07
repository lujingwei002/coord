#include "hostd/hostd_server.h"
#include "hostd.h"
#include "hostd/hostd_agent.h"
#include "coord/net/init.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace hostd {

HostdServer* newHostdServer(coord::Coord* coord, Hostd* hostd) {
    auto self = new HostdServer(coord, hostd);
    return self;
}

HostdServer::HostdServer(coord::Coord *coord, Hostd* hostd) {
    this->coord = coord;
    this->hostd = hostd;
    this->listener = NULL;
}

HostdServer::~HostdServer() {
    if(this->listener) {
        delete this->listener;
        this->listener = NULL;
    }
     for(auto it = this->agentDict.begin(); it != this->agentDict.end();) {
        HostdAgent* agent = it->second;
        this->coord->Destory(agent);
        ++it;
    }
    this->agentDict.clear();
}

int HostdServer::start() {
    this->coord->LogDebug("[HostdServer] start, host=%s, port=%d", this->hostd->config.Host.c_str(), this->hostd->config.Port);
    coord::net::TcpListener *listener = coord::net::NewTcpListener(this->coord);
    listener->SetHandler(this);
    int err = listener->Listen(this->hostd->config.Host.c_str(), this->hostd->config.Port);
    if (err < 0) {
        delete listener;
        return err;
    }
    this->listener = listener;
    return 0;
}

void HostdServer::recvTcpNew(coord::net::TcpListener* listener, coord::net::TcpAgent* tcpAgent){
    int sessionId = tcpAgent->sessionId;
    this->coord->LogDebug("[HostdServer] recvTcpNew sessionId=%d", sessionId);
    tcpAgent->SetRecvBuffer(4096);
    HostdAgent *agent = newHostdAgent(this->coord, this->hostd, this, tcpAgent);
    agent->sessionId = sessionId;
    agent->remoteAddr = tcpAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
    agent->recvTcpNew(tcpAgent);
}

void HostdServer::recvTcpClose(HostdAgent* agent){
    int sessionId = agent->sessionId;
    this->coord->LogDebug("[HostdServer] recvTcpClose sessionId=%d", sessionId);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->LogDebug("[HostdServer] recvTcpClose failed, sessionId=%d, error='agent not found'", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void HostdServer::close() {
    
}

}
      