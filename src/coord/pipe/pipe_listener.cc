#include "coord/pipe/pipe_listener.h"
#include "coord/pipe/pipe_agent.h"
#include "coord/object/object.h"
#include "coord/log/log.h"
#include "coord/coord.h"
#include <uv.h>
#include <limits>

namespace coord {
namespace pipe {

CC_IMPLEMENT(PipeListener, "coord::pipe::PipeListener")

static void uv_connection_cb(uv_stream_t *server, int status) {
    PipeListener* listener = (PipeListener*)server->data;
    listener->recvPipeNew(status);
}

PipeListener* NewPipeListener(Coord* coord) {
    PipeListener* listener = new PipeListener(coord);
    return listener; 
}

PipeListener::PipeListener(Coord* coord) : coord(coord) {
    this->ipc = 0;
    this->handler = NULL;
}

PipeListener::~PipeListener() {

}

void PipeListener::recvPipeNew(int status) {
    if (status < 0) {
        this->coord->CoreLogDebug("[PipeListener] recvPipeNew failed, error='%s'", uv_strerror(status));
        return;
    }
    PipeAgent *agent = newPipeAgent(this->coord, this);
    uv_pipe_init(&this->coord->loop, (uv_pipe_t*)&agent->handle, this->ipc);
    int err = 0;
    err = uv_accept((uv_stream_t*)&this->server, (uv_stream_t*) &agent->handle);
    if (err < 0) {
        delete agent;
        this->coord->CoreLogDebug("[PipeListener] recvPipeNew.uv_accept failed, error='%s'", uv_strerror(err));
        return;
    }
    uv_os_sock_t sockfd;
    err = uv_fileno((uv_handle_t*)&agent->handle, &sockfd);
    if (err < 0) {
        delete agent;
        this->coord->CoreLogDebug("[PipeListener] recvPipeNew.uv_fileno failed, error='%s'", uv_strerror(err));
        return;
    } 
    agent->sockfd = sockfd;
    int sessionId = sockfd;
    agent->sessionId = sessionId;
    agent->handle.data = agent;
    auto it = this->agentDict.find(sessionId);
    if (it != this->agentDict.end()){
        delete agent;
        this->coord->CoreLogDebug("[PipeListener] recvPipeNew failed, sessionId=%d, error='sessionId conflict'", sessionId);
        return;
    }

    char remoteAddr[32];
    size_t remoteAddrLen =  sizeof(remoteAddr);
    err = uv_pipe_getpeername((uv_pipe_t*)&agent->handle, remoteAddr, &remoteAddrLen);
    if (err == 0){
        agent->remoteAddr = remoteAddr;
    }
    this->agentDict[sessionId] = agent;
    this->coord->CoreLogDebug("[PipeListener] recvPipeNew, sockfd=%d, sessionId=%d", sockfd, sessionId);
    if(this->handler)this->handler->recvPipeNew(this, agent);
    agent->recvPipeNew();
}

int PipeListener::Listen(const std::string& path, int ipc, int backlog){
    this->ipc = ipc;
    this->coord->CoreLogDebug("[PipeListener] path='%s', ipc=%d", path.c_str(), ipc);
    this->server.data = this;
    uv_pipe_init(&this->coord->loop, &this->server, 0);
    int err = uv_pipe_bind(&this->server, path.c_str());
    if (err) {
        this->coord->CoreLogError("[PipeListener] Bind failed, error='%s'", uv_strerror(err));
        return err;
    }
    err = uv_listen((uv_stream_t*) &this->server, backlog, uv_connection_cb);
    if (err) {
        this->coord->CoreLogError("[PipeListener] Listen failed, error='%s'", uv_strerror(err));
        return -1;
    }
    return 0;
}

void PipeListener::recvAgentClose(PipeAgent* agent) {
    this->coord->CoreLogDebug("[PipeListener] recvAgentClose ref=%d", agent->_ref);
    auto it = this->agentDict.find(agent->sessionId);
    if (it == this->agentDict.end()) {
        this->coord->CoreLogDebug("[PipeListener] recvAgentClose failed, sessionid=%d, error='agent not found'", agent->sessionId);
    } else {
        this->agentDict.erase(it);
        this->coord->Destory(agent);
    }
}

void PipeListener::SetHandler(IPipeHandler* handler) {
    this->handler = handler;
}

void PipeListener::Close() {
   this->coord->CoreLogError("[PipeListener] Close failed, error='not implement'");
}

}
}