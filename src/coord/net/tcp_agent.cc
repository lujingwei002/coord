#include "coord/net/tcp_agent.h"
#include "coord/net/tcp_listener.h"
#include "coord/net/write_req.h"
#include "coord/coord.h"

namespace coord {
namespace net {

RC_IMPLEMENT(TcpAgent, "coord::net::TcpAgent")

static void uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    TcpAgent* agent = (TcpAgent*)handle->data;
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
    TcpAgent* agent = (TcpAgent*)client->data;
    agent->recvTcpClose();
}

static void uv_read_cb(uv_stream_t *client, ssize_t byteRead, const uv_buf_t *buf){
    TcpAgent* agent = (TcpAgent*)client->data;
    if (byteRead < 0) {
        agent->recvTcpError(byteRead);
    } else {
        if(byteRead > 0){
            agent->recvBuffer.PushBack(byteRead);
        }
        agent->recvTcpData();
    }
}

static void uv_write_cb(uv_write_t* req, int status) {
   // printf("uv_write_cb %d\n", status);
    WriteReq* req1 = (WriteReq*)req->data;
    delete req1;
}

TcpAgent* newTcpAgent(Coord* coord, TcpListener* listener) {
    TcpAgent* agent = new TcpAgent(coord, listener);
    return agent;
}

TcpAgent::TcpAgent(Coord* coord, TcpListener* listener) : recvBuffer(1024) {
    this->coord = coord;
    this->listener = listener;
    this->handler = NULL;
    this->status = TcpAgentStatus_CONNECTED;
}

TcpAgent::~TcpAgent() {
    this->coord->CoreLogDebug("[TcpAgent] ~TcpAgent");
}

void TcpAgent::SetRecvBuffer(size_t size) {
    this->recvBuffer.Reserve(size);
}

void TcpAgent::SetHandler(ITcpAgentHandler* handler) {
    this->handler = handler;
}

int TcpAgent::Send(const void* data, size_t len) {
    byte_slice buffer;
    coordx::Append(buffer, (const char*)data, len);
    return this->Send(buffer);
}

int TcpAgent::Send(byte_slice& data) {
    this->coord->CoreLogDebug("[TcpAgent] Send, sessionId=%d, len=%d", this->sessionId,  data.Len());
    if( this->status != TcpAgentStatus_CONNECTED) {
        this->coord->CoreLogDebug("[TcpAgent] Send failed, sessionId=%d, len=%d, status=%d, error='status err'", this->sessionId,  data.Len(), this->status);
        return -1;
    }
    uv_buf_t buf[] = {
        { .base = (char*)data.Data(), .len = data.Len()},
    };
    WriteReq* req = new WriteReq(data);
    int err = uv_write(&req->req, (uv_stream_t *)&this->handle, buf, 1, uv_write_cb);
    if (err < 0){
        this->coord->CoreLogError("[TcpAgent] Send failed, sessionId=%d, error='%s'", this->sessionId, uv_strerror(err));
        return err;
    }
    return 0;
}

void TcpAgent::recvTcpData() {
    this->coord->CoreLogDebug("[TcpAgent] recvTcpData, len=%d", this->recvBuffer.Len());
    if (!this->handler){
        return;
    }
    while(this->recvBuffer.Len() > 0) {
        size_t byteRead = this->handler->recvTcpData(this, this->recvBuffer.Front(), this->recvBuffer.Len());
        if (byteRead <= 0) {
            break;
        }
        this->recvBuffer.PopFront(byteRead);
    }
    this->recvBuffer.Truncate();
}

void TcpAgent::recvTcpNew() {
    this->coord->CoreLogDebug("[TcpAgent] recvTcpNew, sessionid=%d", this->sessionId);
    int err = uv_read_start((uv_stream_t*) &this->handle, uv_alloc_cb, uv_read_cb);
    if (err < 0) {
        this->coord->CoreLogDebug("[TcpAgent] recvTcpNew.uv_read_start failed, error='%s'", uv_strerror(err));
        return;
    }
}

void TcpAgent::recvTcpError(int status) {
    this->coord->CoreLogDebug("[TcpAgent] recvTcpError, sessionid=%d, error='%s'", this->sessionId, uv_err_name(status));
    this->status = TcpAgentStatus_ERROR;
    if(status != UV_EOF){
        if(this->handler)this->handler->recvTcpError(this);
    }
    this->Close();
}

void TcpAgent::recvTcpClose() {
    this->coord->CoreLogDebug("[TcpAgent] recvTcpClose, sessionid=%d", this->sessionId);
    this->status = TcpAgentStatus_CLOSED;
    if(this->handler)this->handler->recvTcpClose(this);
    this->listener->recvAgentClose(this);
}

void TcpAgent::Close() {
    if(this->status == TcpAgentStatus_CLOSING || this->status == TcpAgentStatus_CLOSED) {
        this->coord->CoreLogError("[TcpAgent] close failed1 %d", this->status);
        return;
    }
    if(uv_is_closing((uv_handle_t*)&this->handle)) {
        this->coord->CoreLogError("[TcpAgent] close failed2");
        return;
    }
    this->status = TcpAgentStatus_CLOSING;
    uv_close((uv_handle_t*)&this->handle, uv_close_cb);
}


}
}