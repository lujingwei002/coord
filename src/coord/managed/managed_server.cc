#include "coord/managed/managed_server.h"
#include "coord/managed/managed.h"
#include "coord/net/tcp_listener.h"
#include "coord/managed/managed_agent.h"
#include "coord/config/config.h"
#include "coord/coord.h"
namespace coord {
namespace managed {

ManagedServer* newManagedServer(Coord* coord, Managed* managed) {
    auto self = new ManagedServer(coord, managed);
    return self;
}

ManagedServer::ManagedServer(Coord *coord, Managed* managed) {
    this->coord = coord;
    this->managed = managed;
    this->listener = NULL;
}

ManagedServer::~ManagedServer() {
    if(this->listener) {
        delete this->listener;
        this->listener = NULL;
    }
     for(auto it = this->agentDict.begin(); it != this->agentDict.end();) {
        ManagedAgent* agent = it->second;
        this->coord->Destory(agent);
        ++it;
    }
    this->agentDict.clear();
}

int ManagedServer::start() {
    this->coord->coreLogDebug("[ManagedServer] start, host=%s, port=%d", this->managed->config.Host.c_str(), this->managed->config.Port);
    net::TcpListener *listener = net::NewTcpListener(this->coord);
    listener->SetHandler(this);
    int err = listener->Listen(this->managed->config.Host.c_str(), this->managed->config.Port);
    if (err < 0) {
        delete listener;
        return err;
    }
    this->listener = listener;
    return 0;
}

void ManagedServer::recvTcpNew(net::TcpListener* listener, net::TcpAgent* tcpAgent){
    int sessionId = tcpAgent->sessionId;
    this->coord->coreLogDebug("[ManagedServer] recvTcpNew sessionId=%d", sessionId);
    tcpAgent->SetRecvBuffer(4096);
    ManagedAgent *agent = newManagedAgent(this->coord, this->managed, this, tcpAgent);
    agent->sessionId = sessionId;
    agent->remoteAddr = tcpAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
    agent->recvTcpNew(tcpAgent);
}

void ManagedServer::recvTcpClose(ManagedAgent* agent){
    int sessionId = agent->sessionId;
    this->coord->coreLogDebug("[ManagedServer] recvTcpClose sessionId=%d", sessionId);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->coreLogDebug("[ManagedServer] recvTcpClose failed, sessionId=%d, error='agent not found'", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void ManagedServer::close() {
    
}

}
}        