#include "coord/pipe/pipe_agent.h"
#include "coord/pipe/pipe_listener.h"
#include "coord/net/write_req.h"
#include "coord/coord.h"

namespace coord {
namespace pipe {

CC_IMPLEMENT(PipeAgent, "coord::pipe::PipeAgent")

enum pipe_agent_status {
    pipe_agent_status_connected = 0,
    pipe_agent_status_closing = 1,
    pipe_agent_status_closed = 2,
};

void PipeAgent::uv_shutdown_cb(uv_shutdown_t* req, int status) {  
    PipeAgent* agent = (PipeAgent*)req->data;
    agent->evShutdown();
} 

void PipeAgent::uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    PipeAgent* agent = (PipeAgent*)handle->data;
    if(agent->recvBuffer.Available() <= 0){
        buf->base = NULL;
        buf->len = 0;
    } else {
        buf->base = agent->recvBuffer.Back();
        buf->len = agent->recvBuffer.Available();
    }
}

void PipeAgent::uv_close_cb(uv_handle_t* handle) {
    PipeAgent* agent = (PipeAgent*)handle->data;
    agent->evClose();
}

void PipeAgent::uv_read_cb(uv_stream_t *handle, ssize_t byteRead, const uv_buf_t *buf){
    PipeAgent* agent = (PipeAgent*)handle->data;
    if (byteRead < 0) {
        agent->evError(byteRead);
    } else {
        if(byteRead > 0){
            agent->recvBuffer.PushBack(byteRead);
        }
        agent->evData();
    }
}

void PipeAgent::uv_write_cb(uv_write_t* req, int status) {
    net::WriteReq* req1 = (net::WriteReq*)req->data;
    delete req1;
}

PipeAgent::PipeAgent(Coord* coord, PipeListener* listener) : recvBuffer(1024) {
    this->coord = coord;
    this->listener = listener;
    this->handler = nullptr;
    this->status = pipe_agent_status_connected;
}

PipeAgent::~PipeAgent() {
}

void PipeAgent::SetRecvBuffer(size_t size) {
    this->recvBuffer.Reserve(size);
}

void PipeAgent::SetHandler(IPipeAgentHandler* handler) {
    this->handler = handler;
}

int PipeAgent::Send(const void* data, size_t len) {
    byte_slice buffer;
    coordx::Append(buffer, (const char*)data, len);
    return this->Send(buffer);
}

int PipeAgent::Send(byte_slice& data) {
    this->coord->CoreLogDebug("[PipeAgent] send, sessionId=%d, len=%d", this->SessionId,  data.Len());
    if( this->status != pipe_agent_status_connected) {
        this->coord->CoreLogDebug("[PipeAgent] send fail, sessionId=%d, len=%d, status=%d, error='status err'", this->SessionId,  data.Len(), this->status);
        return -1;
    }
    uv_buf_t buf[] = {
        { .base = (char*)data.Data(), .len = data.Len()},
    };
    net::WriteReq* req = new net::WriteReq(data);
    int err = uv_write(&req->req, (uv_stream_t *)&this->handle, buf, 1, PipeAgent::uv_write_cb);
    if (err < 0){
        this->coord->CoreLogError("[PipeAgent] send fail, sessionId=%d, error='%s'", this->SessionId, uv_strerror(err));
        return err;
    }
    return 0;
}

void PipeAgent::evData() {
    this->coord->CoreLogDebug("[PipeAgent] ev data, len=%d", this->recvBuffer.Len());
    if (!this->handler){
        return;
    }
    while(this->recvBuffer.Len() > 0) {
        size_t byteRead = this->handler->EvData(this, this->recvBuffer.Front(), this->recvBuffer.Len());
        if (byteRead <= 0) {
            break;
        }
        this->recvBuffer.PopFront(byteRead);
    }
    this->recvBuffer.Truncate();
}

void PipeAgent::evConnection() {
    this->coord->CoreLogDebug("[PipeAgent] ev connection, sessionid=%d", this->SessionId);
    int err = uv_read_start((uv_stream_t*) &this->handle, PipeAgent::uv_alloc_cb, uv_read_cb);
    if (err < 0) {
        this->coord->CoreLogDebug("[PipeAgent] ev connection. uv_read_start fail, error='%s'", uv_strerror(err));
        return;
    }
}

void PipeAgent::evError(int status) {
    this->coord->CoreLogDebug("[PipeAgent] ev error, sessionid=%d, error='%s'", this->SessionId, uv_err_name(status));
    if(status != UV_EOF){
        if(this->handler)this->handler->EvError(this);
    }
    this->Close();
}

void PipeAgent::evShutdown() {
    this->coord->CoreLogDebug("[PipeAgent] ev shutdown");
    uv_close((uv_handle_t*)&this->handle, PipeAgent::uv_close_cb);
}

void PipeAgent::evClose() {
    this->coord->CoreLogDebug("[PipeAgent] ev close, sessionid=%d", this->SessionId);
    this->status = pipe_agent_status_closed;
    if(this->handler)this->handler->EvClose(this);
    this->listener->recvAgentClose(this);
}

int PipeAgent::Close() {
    if(this->status == pipe_agent_status_closing) {
        return ErrorIsClosing;
    } else if(this->status == pipe_agent_status_closed) {
        return ErrorIsClosed;
    } else {
        //发送完缓冲区里的数据，再关闭
        this->status = pipe_agent_status_closing;
        uv_read_stop((uv_stream_t*) &this->handle);
        this->shutdownReq.data = this;
        uv_shutdown(&this->shutdownReq, (uv_stream_t*)&this->handle, PipeAgent::uv_shutdown_cb);
        return 0;
    }
    return 0;
}


}
}
