#include "coord/pipe/pipe_client.h"
#include "coord/net/write_req.h"
#include "coord/coord.h"

namespace coord {
namespace pipe {

CC_IMPLEMENT(PipeClient, "coord::pipe::PipeClient")

/// 状态
enum pipe_client_status {
    pipe_client_status_nil = 0,
    pipe_client_status_connecting = 1,
    pipe_client_status_connected = 2,
    pipe_client_status_closing = 4,
    pipe_client_status_closed = 5,
};

enum pipe_client_close_reason {
    pipe_client_close_reason_nil = 0,
    pipe_client_close_reason_connect_error = 1,     // 连接出错，需要关闭连接
    pipe_client_close_reason_connect_cancel = 2,    // 在connecting时，调用close或者destory中断连接
    pipe_client_close_reason_disconnect = 4,        // 在connected状态时主动断开
    pipe_client_close_reason_error = 5,             // 在connected状态时连接断开
};

void PipeClient::uv_connect_cb(uv_connect_t* req, int status) {
    PipeClient* client = (PipeClient*)req->data;
    if(status < 0) {
        client->evConnectError(status);
    } else {
        client->evConnect();
    }
}

void PipeClient::uv_close_cb(uv_handle_t* req) {
    PipeClient* client = (PipeClient*)req->data;
    client->evClose();
}

void PipeClient::uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    PipeClient* client = (PipeClient*)handle->data;
    if(client->recvBuffer.Available() <= 0){
        buf->base = NULL;
        buf->len = 0;
    } else {
        buf->base = client->recvBuffer.Back();
        buf->len = client->recvBuffer.Available();
    }
}

void PipeClient::uv_read_cb(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf){
    /*
    nread is > 0 if there is data available or < 0 on error. 
    When we’ve reached EOF, nread will be set to UV_EOF. 
    When nread < 0, the buf parameter might not point to a valid buffer; in that case buf.len and buf.base are both set to 0.

    The callee is responsible for stopping/closing the stream when an error happens by calling uv_read_stop() or uv_close(). 
    Trying to read from the stream again is undefined.
    */
    PipeClient* client = (PipeClient*)handle->data;
    if (nread < 0) {
        client->evError(nread);
    } else {
        if(nread > 0){
            client->recvBuffer.PushBack(nread);
        }
        client->evData();
    }
}

void PipeClient::uv_shutdown_cb(uv_shutdown_t* req, int status) {  
    PipeClient* client = (PipeClient*)req->data;
    client->evShutdown();
} 

void PipeClient::uv_write_cb(uv_write_t* req, int status) {
    coord::net::WriteReq* req1 = (coord::net::WriteReq*)req->data;
    delete req1;
}

PipeClient::PipeClient(Coord* coord) : recvBuffer(0) {
    this->coord = coord;
    this->handler = nullptr;
    this->status = pipe_client_status_nil;
    this->closeReason = pipe_client_close_reason_nil;
    this->destoryDelay = false;
}

PipeClient::~PipeClient() {
}

void PipeClient::SetRecvBuffer(size_t size) {
    if (this->recvBuffer.Capacity() >= size){
        return;
    }
    this->recvBuffer.Reserve(size - (this->recvBuffer.Capacity() - this->recvBuffer.Available()));
}

void PipeClient::SetHandler(IPipeClientHandler* handler) {
    this->handler = handler;
}

bool PipeClient::IsClose() {
    return this->status == pipe_client_status_closed;
}

bool PipeClient::IsConnected() {
    return this->status == pipe_client_status_connected;
}

bool PipeClient::IsConnecting() {
    return this->status == pipe_client_status_connecting;
}


int PipeClient::Connect(const std::string& path, int ipc) {
    if (this->status != pipe_client_status_nil) {
        return ErrorInvalidStatus;
    }
    uv_pipe_init(&this->coord->loop, &this->handle, ipc);
    this->handle.data = this;
    this->connectReq.data = this;
    uv_pipe_connect(&this->connectReq, &this->handle, path.c_str(), PipeClient::uv_connect_cb);
    this->status = pipe_client_status_connecting;
    return 0;
}

void PipeClient::evShutdown() {
    this->coord->CoreLogDebug("[PipeClient] evShutdown");
    uv_close((uv_handle_t*)&this->handle, PipeClient::uv_close_cb);
}

void PipeClient::evError(int err) {
    this->coord->CoreLogDebug("[PipeClient] evError");
    if(this->handler != nullptr) {this->handler->EvError(err);}
    this->internalClose(pipe_client_close_reason_error);
}

void PipeClient::evConnectError(int err) {
    this->coord->CoreLogDebug("[PipeClient] evConnectError error='%s'", uv_strerror(err));
    if(this->handler != nullptr) {this->handler->EvConnectError(err);}
    // 当前只能是connecting 或者 closing
    if (this->status == pipe_client_status_connecting) {
        this->internalClose(pipe_client_close_reason_connect_error);
    } else if (this->status == pipe_client_status_closing) {
    } else {
        this->coord->CoreLogDebug("[PipeClient] evConnectError, status=%d, error='invalid status'", this->status);
    }
}

void PipeClient::evConnect() {
    this->coord->CoreLogDebug("[PipeClient] evConnect");
    // 当前只能是connecting 
    if (this->status == pipe_client_status_connecting) {
        int err = uv_read_start((uv_stream_t*) &this->handle, PipeClient::uv_alloc_cb, PipeClient::uv_read_cb);
        if (err < 0) {
            this->coord->CoreLogError("[PipeClient] evConnect uv_read_start failed, error='%s'", uv_strerror(err));
            if(this->handler != nullptr) {this->handler->EvConnectError(uv_strerror(err));}
            this->internalClose(pipe_client_close_reason_connect_error);
        } else {
            this->status = pipe_client_status_connected;
            if(this->handler != nullptr) {this->handler->EvConnect();}
        }
    } else {
        this->coord->CoreLogDebug("[PipeClient] evConnect, status=%d, error='invalid status'", this->status);
    }
}

void PipeClient::evData() {
    //this->coord->CoreLogDebug("[PipeClient] evData, len=%d", this->recvBuffer.Len());
    if (!this->handler){
        return;
    }
    while(this->recvBuffer.Len() > 0) {
        size_t byteRead = this->handler->EvData(this->recvBuffer.Front(), this->recvBuffer.Len());
        if (byteRead <= 0) {
            break;
        }
        this->recvBuffer.PopFront(byteRead);
    }
    this->recvBuffer.Truncate();
}

int PipeClient::Send(const char* data, size_t len) {
    return -1;
}

int PipeClient::Send(byte_slice& data) {
    this->coord->CoreLogDebug("[PipeClient] Send, len=%d", data.Len());
    if (this->status != pipe_client_status_connected) {
        return ErrorNotConnected;
    }
    uv_buf_t buf[] = {
        { .base = (char*)data.Data(), .len = data.Len()},
    };
    coord::net::WriteReq* req = new coord::net::WriteReq(data);
    int err = uv_write(&req->req, (uv_stream_t *)&this->handle, buf, 1, PipeClient::uv_write_cb);
    if (err < 0){
        this->coord->CoreLogError("[PipeClient] Send failed, error='%s'", uv_strerror(err));
        return err;
    }
    return 0;
}

void PipeClient::Destory() {
    if(this->status == pipe_client_status_closed) {
        delete this;
    } else if(this->status == pipe_client_status_nil) {
        delete this;
    } else if(this->status == pipe_client_status_closing) {
        //在回调中回收内存
        this->destoryDelay = true;
    } else if(this->status == pipe_client_status_connecting) {
        //在回调中回收内存
        this->destoryDelay = true;
        this->internalClose(pipe_client_close_reason_connect_cancel);
    } else if(this->status == pipe_client_status_connected) {
        //在回调中回收内存
        this->destoryDelay = true;
        this->internalClose(pipe_client_close_reason_disconnect);
    }
}

int PipeClient::Close() {
    if(uv_is_closing((uv_handle_t*)&this->handle)) {
        this->coord->CoreLogDebug("[PipeClient] Close fail2, error='is closing'");
        return ErrorIsClosing;
    }
    // 状态判断
    if(this->status == pipe_client_status_closing) {
        this->coord->CoreLogDebug("[PipeClient] Close fail, error='is closing'");
        return ErrorIsClosing;
    } else if(this->status == pipe_client_status_closed) {
        this->coord->CoreLogDebug("[PipeClient] Close fail, error='is closed'");
        return ErrorIsClosed;
    } else if(this->status == pipe_client_status_connecting) {
        return this->internalClose(pipe_client_close_reason_connect_cancel);
    } else if(this->status == pipe_client_status_connected) {
        return this->internalClose(pipe_client_close_reason_disconnect);
    } else if (this->status == pipe_client_status_nil) {
        return ErrorNotConnected;
    }
    return ErrorInvalidStatus;
}

int PipeClient::internalClose(int reason) {
    if(reason == pipe_client_close_reason_disconnect) {
        this->closeReason = reason;
        this->status = pipe_client_status_closing;
        uv_read_stop((uv_stream_t*) &this->handle);
        this->shutdownReq.data = this;
        //发送完缓冲区里的数据，再关闭
        uv_shutdown(&this->shutdownReq, (uv_stream_t*)&this->handle, PipeClient::uv_shutdown_cb);
        return 0;
    } else {
        this->closeReason = reason;
        this->status = pipe_client_status_closing;
        uv_close((uv_handle_t*)&this->handle, PipeClient::uv_close_cb);
        return 0;
    }
}

void PipeClient::evClose() {
    this->coord->CoreLogDebug("[PipeClient] evClose, reason=%d", this->closeReason);
    this->status = pipe_client_status_closed;
    if (this->handler)this->handler->EvClose();
    if (this->destoryDelay) {
        delete this;
    }
}


}
} 
