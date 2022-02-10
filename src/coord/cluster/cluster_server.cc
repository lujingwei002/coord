#include "coord/cluster/cluster_server.h"
#include "coord/cluster/cluster.h"
#include "coord/net/tcp_listener.h"
#include "coord/cluster/cluster_packet.h"
#include "coord/cluster/cluster_agent.h"
#include "coord/config/config.h"
#include "coord/coord.h"
namespace coord {
namespace cluster {

cluster_server* newClusterServer(Coord* coord, Cluster* cluster) {
    auto self = new cluster_server(coord, cluster);
    return self;
}

cluster_server::cluster_server(Coord *coord, Cluster* cluster) {
    this->coord = coord;
    this->cluster = cluster;
    this->listener = nullptr;
}

cluster_server::~cluster_server() {
    if(this->listener) {
        delete this->listener;
        this->listener = nullptr;
    }
     for(auto it = this->agentDict.begin(); it != this->agentDict.end();) {
        cluster_agent* agent = it->second;
        this->coord->Destory(agent);
        ++it;
    }
    this->agentDict.clear();
}

int cluster_server::main() {
    this->coord->coreLogDebug("[cluster_server] main, host=%s, port=%d", this->cluster->config.Host.c_str(), this->cluster->config.Port);
    net::TcpListener *listener = net::NewTcpListener(this->coord);
    listener->SetHandler(this);
    int err = listener->Listen(this->cluster->config.Host.c_str(), this->cluster->config.Port);
    if (err < 0) {
        delete listener;
        return err;
    }
    this->listener = listener;
    return 0;
}

void cluster_server::recvTcpNew(net::TcpListener* listener, net::TcpAgent* tcpAgent){
    int sessionId = tcpAgent->sessionId;
    this->coord->coreLogDebug("[cluster_server] recvTcpNew sessionId=%d", sessionId);
    tcpAgent->SetRecvBuffer(this->cluster->config.RecvBuffer);
    cluster_agent *agent = newClusterAgent(this->coord, this->cluster, this, tcpAgent);
    agent->sessionId = sessionId;
    agent->remoteAddr = tcpAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
}

void cluster_server::recvTcpClose(cluster_agent* agent){
    int sessionId = agent->sessionId;
    this->coord->coreLogDebug("[cluster_server] recvTcpClose sessionId=%d", sessionId);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->coreLogDebug("[cluster_server] recvTcpClose failed, sessionId=%d, error='agent not found'", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void cluster_server::heartbeat() {
    for(auto const it : this->agentDict){
        it.second->heartbeat();
    }
}

void cluster_server::close() {
    
}

}
}        