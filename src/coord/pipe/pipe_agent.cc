#include "coord/pipe/pipe_agent.h"
#include "coord/pipe/pipe_listener.h"
#include "coord/net/write_req.h"
#include "coord/coord.h"

namespace coord {
namespace pipe {

CC_IMPLEMENT(PipeAgent, "coord::pipe::PipeAgent")

static void uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    PipeAgent* agent = (PipeAgent*)handle->data;
    //printf("uv_alloc_cb %ld\n", agent->recvBuffer.Available());
    if(agent->recvBuffer.Available() <= 0){
        buf->base = NULL;
        buf->len = 0;
    } else {
        buf->base = agent->recvBuffer.Back();
        buf->len = agent->recvBuffer.Available();
    }
}

static void uv_close_cb(uv_handle_t* client) {
    PipeAgent* agent = (PipeAgent*)client->data;
    agent->recvPipeClose();
}

static void uv_read_cb(uv_stream_t *client, ssize_t byteRead, const uv_buf_t *buf){
    PipeAgent* agent = (PipeAgent*)client->data;
    if (byteRead < 0) {
        agent->recvPipeError(byteRead);
    } else {
        if(byteRead > 0){
            agent->recvBuffer.PushBack(byteRead);
        }
        agent->recvPipeData();
    }
}

static void uv_write_cb(uv_write_t* req, int status) {
   // printf("uv_write_cb %d\n", status);
    net::WriteReq* req1 = (net::WriteReq*)req->data;
    delete req1;
}

PipeAgent* newPipeAgent(Coord* coord, PipeListener* listener) {
    PipeAgent* agent = new PipeAgent(coord, listener);
    return agent;
}

PipeAgent::PipeAgent(Coord* coord, PipeListener* listener) : recvBuffer(1024) {
    this->coord = coord;
    this->listener = listener;
    this->handler = NULL;
    this->status = PipeAgentStatus_CONNECTED;
}

PipeAgent::~PipeAgent() {
    this->coord->CoreLogDebug("[PipeAgent] ~PipeAgent");
}

void PipeAgent::SetRecvBuffer(size_t size) {
    this->recvBuffer.Reserve(size);
}

void PipeAgent::SetHandler(IPipeAgentHandler* handler) {
    this->handler = handler;
}

int PipeAgent::Send(const void* data, size_t len) {
    byte_slice buffer;
    coord::Append(buffer, (const char*)data, len);
    return this->Send(buffer);
}

int PipeAgent::Send(byte_slice& data) {
    this->coord->CoreLogDebug("[PipeAgent] Send, sessionId=%d, len=%d", this->sessionId,  data.Len());
    if( this->status != PipeAgentStatus_CONNECTED) {
        this->coord->CoreLogDebug("[PipeAgent] Send failed, sessionId=%d, len=%d, status=%d, error='status err'", this->sessionId,  data.Len(), this->status);
        return -1;
    }
    uv_buf_t buf[] = {
        { .base = (char*)data.Data(), .len = data.Len()},
    };
    net::WriteReq* req = new net::WriteReq(data);
    int err = uv_write(&req->req, (uv_stream_t *)&this->handle, buf, 1, uv_write_cb);
    if (err < 0){
        this->coord->CoreLogError("[PipeAgent] Send failed, sessionId=%d, error='%s'", this->sessionId, uv_strerror(err));
        return err;
    }
    return 0;
}

void PipeAgent::recvPipeData() {
    this->coord->CoreLogDebug("[PipeAgent] recvPipeData, len=%d", this->recvBuffer.Len());
    if (!this->handler){
        return;
    }
    while(this->recvBuffer.Len() > 0) {
        size_t byteRead = this->handler->recvPipeData(this, this->recvBuffer.Front(), this->recvBuffer.Len());
        if (byteRead <= 0) {
            break;
        }
        this->recvBuffer.PopFront(byteRead);
    }
    this->recvBuffer.Truncate();
}

void PipeAgent::recvPipeNew() {
    this->coord->CoreLogDebug("[PipeAgent] recvPipeNew, sessionid=%d", this->sessionId);
    int err = uv_read_start((uv_stream_t*) &this->handle, uv_alloc_cb, uv_read_cb);
    if (err < 0) {
        this->coord->CoreLogDebug("[PipeAgent] recvPipeNew.uv_read_start failed, error='%s'", uv_strerror(err));
        return;
    }
}

void PipeAgent::recvPipeError(int status) {
    this->coord->CoreLogDebug("[PipeAgent] recvPipeError, sessionid=%d, error='%s'", this->sessionId, uv_err_name(status));
    this->status = PipeAgentStatus_ERROR;
    if(status != UV_EOF){
        if(this->handler)this->handler->recvPipeError(this);
    }
    this->Close();
}

void PipeAgent::recvPipeClose() {
    this->coord->CoreLogDebug("[PipeAgent] recvPipeClose, sessionid=%d", this->sessionId);
    this->status = PipeAgentStatus_CLOSED;
    if(this->handler)this->handler->recvPipeClose(this);
    this->listener->recvAgentClose(this);
}

void PipeAgent::Close() {
    if(this->status == PipeAgentStatus_CLOSING || this->status == PipeAgentStatus_CLOSED) {
        this->coord->CoreLogError("[PipeAgent] close failed1 %d", this->status);
        return;
    }
    if(uv_is_closing((uv_handle_t*)&this->handle)) {
        this->coord->CoreLogError("[PipeAgent] close failed2");
        return;
    }
    this->status = PipeAgentStatus_CLOSING;
    uv_close((uv_handle_t*)&this->handle, uv_close_cb);
}


}
}