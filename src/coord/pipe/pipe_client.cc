#include "coord/pipe/pipe_client.h"
#include "coord/net/write_req.h"
#include "coord/coord.h"

namespace coord {
namespace pipe {

CC_IMPLEMENT(PipeClient, "coord::pipe::PipeClient")


static void uv_connect_cb(uv_connect_t* req, int status) {
    PipeClient* client = (PipeClient*)req->data;
    //free(req);
    if(status < 0) {
        client->recvConnectError(status);
    } else {
        client->recvPipeConnect();
    }
}

static void uv_close_cb(uv_handle_t* req) {
    //printf("uv_close_cb\n");
    PipeClient* client = (PipeClient*)req->data;
    client->recvPipeClose();
    if (client->isDestory) {
        delete client;
    }
}

static void uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    PipeClient* client = (PipeClient*)handle->data;
    //printf("uv_alloc_cb %ld\n", client->recvBuffer.Available());
    if(client->recvBuffer.Available() <= 0){
        buf->base = NULL;
        buf->len = 0;
    } else {
        buf->base = client->recvBuffer.Back();
        buf->len = client->recvBuffer.Available();
    }
}

static void uv_read_cb(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf){
    PipeClient* client = (PipeClient*)handle->data;
    //printf("uv_read_cb %ld\n", nread);
    if (nread < 0) {
        client->recvPipeError(nread);
    } else {
        if(nread > 0){
            client->recvBuffer.PushBack(nread);
        }
        client->recvPipeData();
    }
}

static void uv_shutdown_cb(uv_shutdown_t* req, int status) {  
    //printf("uv_shutdown_cb\n");
    PipeClient* client = (PipeClient*)req->data;
    uv_close((uv_handle_t*)&client->handle, uv_close_cb);
} 

static void uv_write_cb(uv_write_t* req, int status) {
   // printf("uv_write_cb %d\n", status);
    coord::net::WriteReq* req1 = (coord::net::WriteReq*)req->data;
    delete req1;
}

PipeClient* newPipeClient(Coord* coord) {
    PipeClient* client = new PipeClient(coord);
    return client;
}

PipeClient::PipeClient(Coord* coord) : recvBuffer(0) {
    this->coord = coord;
    this->handler = NULL;
    this->status = PipeClientStatus_NIL;
    this->isDestory = false;
}

PipeClient::~PipeClient() {
    //printf("~PipeClient\n");
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

int PipeClient::Connect(const std::string& path, int ipc) {
    //uv_connect_t* req = (uv_connect_t*)malloc(sizeof(uv_connect_t));
    uv_pipe_init(&this->coord->loop, &this->handle, ipc);
    this->handle.data = this;
    this->connectReq.data = this;
    uv_pipe_connect(&this->connectReq, &this->handle, path.c_str(), uv_connect_cb);
    this->status = PipeClientStatus_CONNECTING;
    return 0;
}

bool PipeClient::IsClose() {
    return this->status == PipeClientStatus_CLOSED;
}

void PipeClient::onDestory() {
    if(this->status == PipeClientStatus_CLOSED || this->status == PipeClientStatus_NIL) {
        delete this;
    } else {
        //在回调中回收内存
        this->isDestory = true;
        //this->handler = NULL;
        if(!this->IsClose())this->Close();
    }
}

int PipeClient::Reconnect(const std::string& path, int ipc) {
    if(this->status != PipeClientStatus_CLOSED) {
        return -1;
    }
    this->recvBuffer.Reset();
    uv_connect_t* req = (uv_connect_t*)malloc(sizeof(uv_connect_t));
    uv_pipe_init(&this->coord->loop, &this->handle, ipc);
    this->handle.data = this;
    req->data = this;
    uv_pipe_connect(req, &this->handle, path.c_str(), uv_connect_cb);
    this->status = PipeClientStatus_CONNECTING;
    return 0;
}

int PipeClient::GetStatus() {
    return this->status;
}

void PipeClient::Close() {
    if(this->status == PipeClientStatus_CLOSING || this->status == PipeClientStatus_CLOSED) {
        this->coord->CoreLogDebug("[PipeClient] close failed1 %d", this->status);
        return;
    }
    if(uv_is_closing((uv_handle_t*)&this->handle)) {
        this->coord->CoreLogDebug("[PipeClient] close failed2");
        return;
    }
    if(this->status == PipeClientStatus_CONNECTED) {
        uv_read_stop((uv_stream_t*) &this->handle);
        this->shutdownReq.data = this;
        this->status = PipeClientStatus_CLOSING;
        //发送完缓冲区里的数据，再关闭
        uv_shutdown(&this->shutdownReq, (uv_stream_t*)&this->handle, uv_shutdown_cb);
    }  else {
        uv_close((uv_handle_t*)&this->handle, uv_close_cb);
    }
}

void PipeClient::recvPipeError(int err) {
    this->coord->CoreLogDebug("[PipeClient] recvPipeError");
    this->status = PipeClientStatus_ERROR;
    if(this->handler != NULL) {this->handler->recvPipeError(err);}
    this->Close();
}

void PipeClient::recvPipeClose() {
    this->coord->CoreLogDebug("[PipeClient] recvPipeClose");
    this->status = PipeClientStatus_CLOSED;
    if(this->handler != NULL) {this->handler->recvPipeClose();}
}

void PipeClient::recvConnectError(int err) {
    this->coord->CoreLogDebug("[PipeClient] recvConnectError error='%s'", uv_strerror(err));
    this->status = PipeClientStatus_ERROR;
    if(this->handler != NULL) {this->handler->recvConnectError(uv_strerror(err));}
    this->Close();
}

void PipeClient::recvPipeConnect() {
    this->coord->CoreLogDebug("[PipeClient] recvPipeConnect");
    int err = uv_read_start((uv_stream_t*) &this->handle, uv_alloc_cb, uv_read_cb);
    if (err < 0) {
        this->coord->CoreLogError("[PipeClient] recvPipeConnect.uv_read_start failed, error='%s'", uv_strerror(err));
        if(this->handler != NULL) {this->handler->recvConnectError(uv_strerror(err));}
        this->Close();
        return;
    }
    this->status = PipeClientStatus_CONNECTED;
    if(this->handler != NULL) {this->handler->recvPipeConnect();}
}

void PipeClient::recvPipeData() {
    //this->coord->CoreLogDebug("[PipeClient] recvPipeData, len=%d", this->recvBuffer.Len());
    if (!this->handler){
        return;
    }
    while(this->recvBuffer.Len() > 0) {
        size_t byteRead = this->handler->recvPipeData(this->recvBuffer.Front(), this->recvBuffer.Len());
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
    uv_buf_t buf[] = {
        { .base = (char*)data.Data(), .len = data.Len()},
    };
    coord::net::WriteReq* req = new coord::net::WriteReq(data);
    int err = uv_write(&req->req, (uv_stream_t *)&this->handle, buf, 1, uv_write_cb);
    if (err < 0){
        this->coord->CoreLogError("[PipeClient] Send failed, error='%s'", uv_strerror(err));
        return err;
    }
    return 0;
}

}
} 
