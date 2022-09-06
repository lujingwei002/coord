#include "coord/net/tcp_listener.h"
#include "coord/net/tcp_agent.h"
#include "coord/object/object.h"
#include "coord/coord.h"
#include <uv.h>
#include <limits>

namespace coord {
namespace net {

RC_IMPLEMENT(TcpListener, "coord::net::TcpListener")

static void uv_connection_cb(uv_stream_t *server, int status) {
    TcpListener* listener = (TcpListener*)server->data;
    listener->recvTcpNew(status);
}

TcpListener* NewTcpListener(Coord* coord) {
    TcpListener* listener = new TcpListener(coord);
    return listener; 
}

TcpListener::TcpListener(Coord* coord) : coord(coord) {
    this->handler = NULL;
}

TcpListener::~TcpListener() {

}

void TcpListener::recvTcpNew(int status) {
    if (status < 0) {
        this->coord->CoreLogDebug("[TcpListener] recvTcpNew failed, error='%s'", uv_strerror(status));
        return;
    }
    TcpAgent *agent = newTcpAgent(this->coord, this);
    uv_tcp_init(&this->coord->loop, (uv_tcp_t*)&agent->handle);
    int err = 0;
    err = uv_accept((uv_stream_t*)&this->server, (uv_stream_t*) &agent->handle);
    if (err < 0) {
        delete agent;
        this->coord->CoreLogDebug("[TcpListener] recvTcpNew.uv_accept failed, error='%s'", uv_strerror(err));
        return;
    }
    uv_os_sock_t sockfd;
    err = uv_fileno((uv_handle_t*)&agent->handle, &sockfd);
    if (err < 0) {
        delete agent;
        this->coord->CoreLogDebug("[TcpListener] recvTcpNew.uv_fileno failed, error='%s'", uv_strerror(err));
        return;
    } 
    agent->sockfd = sockfd;
    int sessionId = sockfd;
    agent->sessionId = sessionId;
    agent->handle.data = agent;
    auto it = this->agentDict.find(sessionId);
    if (it != this->agentDict.end()){
        delete agent;
        this->coord->CoreLogDebug("[TcpListener] recvTcpNew failed, sessionId=%d, error='sessionId conflict'", sessionId);
        return;
    }
    struct sockaddr_in remoteSockAddr;
    int remoteSockAddrLen =  sizeof(remoteSockAddr);
    char remoteAddr[32];
    err = uv_tcp_getpeername((uv_tcp_t*)&agent->handle, (struct sockaddr *)&remoteSockAddr, &remoteSockAddrLen);
    if (err == 0){
        int err = uv_ip4_name(&remoteSockAddr, remoteAddr, sizeof(remoteAddr));
        if (err == 0){
            agent->remoteAddr = remoteAddr;
        }
    }
    this->agentDict[sessionId] = agent;
    this->coord->CoreLogDebug("[TcpListener] recvTcpNew, sockfd=%d, sessionId=%d", sockfd, sessionId);
    if(this->handler)this->handler->recvTcpNew(this, agent);
    agent->recvTcpNew();
}

int TcpListener::Listen(const char* host, unsigned short port, int backlog){
    this->coord->CoreLogDebug("[TcpListener] Listen, host:%s, port=%d", host, port);
    this->server.data = this;
    uv_tcp_init(&this->coord->loop, &this->server);
    sockaddr_in addr;
    uv_ip4_addr(host, port, &addr);
    uv_tcp_bind(&this->server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &this->server, backlog, uv_connection_cb);
    if (r) {
        this->coord->CoreLogError("[TcpListener] Listen failed, error='%s'", uv_strerror(r));
        return -1;
    }
    return 0;
}

void TcpListener::recvAgentClose(TcpAgent* agent) {
    this->coord->CoreLogDebug("[TcpListener] recvAgentClose ref=%d", agent->_ref);
    auto it = this->agentDict.find(agent->sessionId);
    if (it == this->agentDict.end()) {
        this->coord->CoreLogDebug("[TcpListener] recvAgentClose failed, sessionid=%d, error='agent not found'", agent->sessionId);
    } else {
        this->agentDict.erase(it);
        this->coord->Destory(agent);
    }
}

void TcpListener::SetHandler(ITcpHandler* handler) {
    this->handler = handler;
}

void TcpListener::Close() {
   this->coord->CoreLogError("[TcpListener] Close failed, error='not implement'");
}

}
}