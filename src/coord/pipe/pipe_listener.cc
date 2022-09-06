#include "coord/pipe/pipe_listener.h"
#include "coord/pipe/pipe_agent.h"
#include "coord/object/object.h"
#include "coord/coord.h"
#include <uv.h>
#include <limits>

namespace coord {
namespace pipe {

RC_IMPLEMENT(PipeListener, "coord::pipe::PipeListener")

/// 状态
enum pipe_listener_status {
    pipe_listener_status_nil = 0,
    pipe_listener_status_start = 1,
    pipe_listener_status_closing = 4,
    pipe_listener_status_closed = 5,
};

void PipeListener::uv_close_cb(uv_handle_t* server) {
    PipeListener* listener = (PipeListener*)server->data;
    listener->evClose();
}

// 新链接
void PipeListener::uv_pipe_connection_cb(uv_stream_t *server, int status) {
    PipeListener* listener = (PipeListener*)server->data;
    listener->evConnection(status);
}

PipeListener* NewPipeListener(Coord* coord) {
    PipeListener* listener = new PipeListener(coord);
    return listener; 
}

PipeListener::PipeListener(Coord* coord) : coord(coord) {
    this->handler = nullptr;
    this->status = pipe_listener_status_nil;
    this->destoryDelay = false;
}

PipeListener::~PipeListener() {
}

void PipeListener::evConnection(int status) {
    if (status < 0) {
        this->coord->CoreLogDebug("[%s] evConnection failed, error='%s'", this->TypeName(), uv_strerror(status));
        return;
    }
    PipeAgent *agent = new PipeAgent(this->coord, this);
    uv_pipe_init(&this->coord->loop, (uv_pipe_t*)&agent->handle, 0);
    int err = 0;
    err = uv_accept((uv_stream_t*)&this->server, (uv_stream_t*) &agent->handle);
    if (err < 0) {
        this->coord->Destory(agent);
        this->coord->CoreLogDebug("[%s] evConnection.uv_accept failed, error='%s'", this->TypeName(), uv_strerror(err));
        return;
    }
    uv_os_sock_t sockfd;
    err = uv_fileno((uv_handle_t*)&agent->handle, &sockfd);
    if (err < 0) {
        this->coord->Destory(agent);
        this->coord->CoreLogDebug("[%s] evConnection.uv_fileno failed, error='%s'", this->TypeName(), uv_strerror(err));
        return;
    } 
    agent->sockfd = sockfd;
    int sessionId = sockfd;
    agent->SessionId = sessionId;
    agent->handle.data = agent;
    auto it = this->agentDict.find(sessionId);
    if (it != this->agentDict.end()){
        this->coord->Destory(agent);
        this->coord->CoreLogDebug("[%s] evConnection failed, sessionId=%d, error='sessionId conflict'", this->TypeName(), sessionId);
        return;
    }
    char remoteAddr[32];
    size_t remoteAddrLen =  sizeof(remoteAddr);
    err = uv_pipe_getpeername((uv_pipe_t*)&agent->handle, remoteAddr, &remoteAddrLen);
    if (err == 0){
        agent->RemoteAddr = remoteAddr;
    }
    this->agentDict[sessionId] = agent;
    this->coord->CoreLogDebug("[%s] evConnection, sockfd=%d, sessionId=%d", this->TypeName(), sockfd, sessionId);
    if(this->handler)this->handler->EvConnection(this, agent);
    agent->evConnection();
}

int PipeListener::Listen(const std::string& path, int backlog){
    this->coord->CoreLogDebug("[%s] listen, path='%s'", this->TypeName(), path.c_str());
    this->server.data = this;
    uv_pipe_init(&this->coord->loop, &this->server, 0);
    int err = uv_pipe_bind(&this->server, path.c_str());
    if (err) {
        this->coord->CoreLogError("[%s] Bind failed, error='%s'", this->TypeName(), uv_strerror(err));
        return err;
    }
    err = uv_listen((uv_stream_t*) &this->server, backlog, uv_pipe_connection_cb);
    if (err) {
        this->coord->CoreLogError("[%s] Listen failed, error='%s'", this->TypeName(), uv_strerror(err));
        return -1;
    }
    this->status = pipe_listener_status_start;
    return 0;
}

void PipeListener::ifNotAgentDestoryMySelf() {
    if (this->agentDict.size() <= 0) {
        this->status = pipe_listener_status_closed;
        if(this->handler)this->handler->EvClose(this);
        if (this->destoryDelay) delete this;
    }
}

void PipeListener::recvAgentClose(PipeAgent* agent) {
    this->coord->CoreLogDebug("[%s] recvAgentClose", this->TypeName());
    auto it = this->agentDict.find(agent->SessionId);
    if (it == this->agentDict.end()) {
        this->coord->CoreLogDebug("[%s] recvAgentClose failed, sessionid=%d, error='agent not found'", this->TypeName(), agent->SessionId);
    } else {
        this->agentDict.erase(it);
        this->coord->Destory(agent);
    }
    if (this->status == pipe_listener_status_closing) {
        this->ifNotAgentDestoryMySelf();
    }
}

void PipeListener::evClose() {
    this->coord->CoreLogDebug("[%s] evClose", this->TypeName());
    this->ifNotAgentDestoryMySelf();
}

void PipeListener::SetHandler(IPipeHandler* handler) {
    this->handler = handler;
}

void PipeListener::Destory() {
    if(this->status == pipe_listener_status_nil) {
        this->status = pipe_listener_status_closed;
        delete this;
    } else if(this->status == pipe_listener_status_closed) {
        this->status = pipe_listener_status_closed;
        delete this;
    } else if(this->status == pipe_listener_status_closing) {
        this->destoryDelay = true;
    } else if(this->status == pipe_listener_status_start) {
        this->destoryDelay = true;
        this->status = pipe_listener_status_closing;
        // 关闭所有连接
        for (auto it: this->agentDict) {
            it.second->Close();
        }
        uv_close((uv_handle_t*)&this->server, PipeListener::uv_close_cb);
    }
}

int PipeListener::Close() {
    if (this->status == pipe_listener_status_closing) {
        return ErrorIsClosing;
    } else if (this->status == pipe_listener_status_closed) {
        return ErrorIsClosed;
    } else if (this->status == pipe_listener_status_start) {
        this->status = pipe_listener_status_closing;
        // 关闭所有连接
        for (auto it: this->agentDict) {
            it.second->Close();
        }
        uv_close((uv_handle_t*)&this->server, PipeListener::uv_close_cb);
        return 0;
    } else {
        return ErrorInvalidStatus;
    }
}

}
}
