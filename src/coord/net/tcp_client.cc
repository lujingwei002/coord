#include "coord/net/tcp_client.h"
#include "coord/net/write_req.h"
#include "coord/coord.h"

namespace coord {
namespace net {

RC_IMPLEMENT(TcpClient, "coord::net::TcpClient")


static void uv_connect_cb(uv_connect_t* req, int status) {
    TcpClient* client = (TcpClient*)req->data;
    //free(req);
    if(status < 0) {
        client->recvTcpConnectError(status);
    } else {
        client->recvTcpConnect();
    }
}

static void uv_close_cb(uv_handle_t* req) {
    //printf("uv_close_cb\n");
    TcpClient* client = (TcpClient*)req->data;
    client->recvTcpClose();
    if (client->isDestory) {
        delete client;
    }
}

static void uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    TcpClient* client = (TcpClient*)handle->data;
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
    TcpClient* client = (TcpClient*)handle->data;
    //printf("uv_read_cb %ld\n", nread);
    if (nread < 0) {
        client->recvTcpError(nread);
    } else {
        if(nread > 0){
            client->recvBuffer.PushBack(nread);
        }
        client->recvTcpData();
    }
}

static void uv_shutdown_cb(uv_shutdown_t* req, int status) {  
    //printf("uv_shutdown_cb\n");
    TcpClient* client = (TcpClient*)req->data;
    uv_close((uv_handle_t*)&client->handle, uv_close_cb);
} 

static void uv_write_cb(uv_write_t* req, int status) {
   // printf("uv_write_cb %d\n", status);
    WriteReq* req1 = (WriteReq*)req->data;
    delete req1;
}

TcpClient* newTcpClient(Coord* coord) {
    TcpClient* client = new TcpClient(coord);
    return client;
}

TcpClient::TcpClient(Coord* coord) : recvBuffer(0) {
    this->coord = coord;
    this->handler = NULL;
    this->status = TcpClientStatus_NIL;
    this->isDestory = false;
}

TcpClient::~TcpClient() {
    //printf("~TcpClient\n");
}

void TcpClient::SetRecvBuffer(size_t size) {
    if (this->recvBuffer.Capacity() >= size){
        return;
    }
    this->recvBuffer.Reserve(size - (this->recvBuffer.Capacity() - this->recvBuffer.Available()));
}

void TcpClient::SetHandler(ITcpClientHandler* handler) {
    this->handler = handler;
}

int TcpClient::Connect(const char* host, int16_t port) {
    //uv_connect_t* req = (uv_connect_t*)malloc(sizeof(uv_connect_t));
    uv_tcp_init(&this->coord->loop, &this->handle);
    this->handle.data = this;
    struct sockaddr_in remoteAddr;
    int err = uv_ip4_addr(host, port, &remoteAddr);
    if (err != 0) {
        this->coord->CoreLogError("[TcpClient] Connect.uv_ip4_addr failed, error=%s", uv_strerror(err));
        return -1;
    }
    this->connectReq.data = this;
    err = uv_tcp_connect(&this->connectReq, &this->handle, (const struct sockaddr*)&remoteAddr, uv_connect_cb);
    if (err != 0) {
        this->coord->CoreLogError("[TcpClient] Connect.uv_tcp_connect failed, error=%s", uv_strerror(err));
        return -1;
    }
    this->status = TcpClientStatus_CONNECTING;
    return 0;
}

bool TcpClient::IsClose() {
    return this->status == TcpClientStatus_CLOSED;
}

void TcpClient::onDestory() {
    if(this->status == TcpClientStatus_CLOSED || this->status == TcpClientStatus_NIL) {
        delete this;
    } else {
        //在回调中回收内存
        this->isDestory = true;
        //this->handler = NULL;
        if(!this->IsClose())this->Close();
    }
}

int TcpClient::Reconnect(const char* host, int16_t port) {
    if(this->status != TcpClientStatus_CLOSED) {
        return -1;
    }
    this->recvBuffer.Reset();
    uv_connect_t* req = (uv_connect_t*)malloc(sizeof(uv_connect_t));
    uv_tcp_init(&this->coord->loop, &this->handle);
    this->handle.data = this;
    struct sockaddr_in remoteAddr;
    int err = uv_ip4_addr(host, port, &remoteAddr);
    if (err != 0) {
        this->coord->CoreLogError("[TcpClient] Connect.uv_ip4_addr failed, error=%s", uv_strerror(err));
        return -1;
    }
    req->data = this;
    err = uv_tcp_connect(req, &this->handle, (const struct sockaddr*)&remoteAddr, uv_connect_cb);
    if (err != 0) {
        this->coord->CoreLogError("[TcpClient] Connect.uv_tcp_connect failed, error=%s", uv_strerror(err));
        return -1;
    }
    this->status = TcpClientStatus_CONNECTING;
    return 0;
}

int TcpClient::GetStatus() {
    return this->status;
}

void TcpClient::Close() {
    if(this->status == TcpClientStatus_CLOSING || this->status == TcpClientStatus_CLOSED) {
        this->coord->CoreLogDebug("[TcpClient] close failed1 %d", this->status);
        return;
    }
    if(uv_is_closing((uv_handle_t*)&this->handle)) {
        this->coord->CoreLogDebug("[TcpClient] close failed2");
        return;
    }
    if(this->status == TcpClientStatus_CONNECTED) {
        uv_read_stop((uv_stream_t*) &this->handle);
        this->shutdownReq.data = this;
        this->status = TcpClientStatus_CLOSING;
        //发送完缓冲区里的数据，再关闭
        uv_shutdown(&this->shutdownReq, (uv_stream_t*)&this->handle, uv_shutdown_cb);
    }  else {
        uv_close((uv_handle_t*)&this->handle, uv_close_cb);
    }
}

void TcpClient::recvTcpError(int err) {
    this->coord->CoreLogDebug("[TcpClient] recvTcpError");
    this->status = TcpClientStatus_ERROR;
    if(this->handler != NULL) {this->handler->recvTcpError(err);}
    this->Close();
}

void TcpClient::recvTcpClose() {
    this->coord->CoreLogDebug("[TcpClient] recvTcpClose");
    this->status = TcpClientStatus_CLOSED;
    if(this->handler != NULL) {this->handler->recvTcpClose();}
}

void TcpClient::recvTcpConnectError(int err) {
    this->coord->CoreLogDebug("[TcpClient] recvTcpConnectError error='%s'", uv_strerror(err));
    this->status = TcpClientStatus_ERROR;
    if(this->handler != NULL) {this->handler->recvTcpConnectError(uv_strerror(err));}
    this->Close();
}

void TcpClient::recvTcpConnect() {
    this->coord->CoreLogDebug("[TcpClient] recvTcpConnect");
    int err = uv_read_start((uv_stream_t*) &this->handle, uv_alloc_cb, uv_read_cb);
    if (err < 0) {
        this->coord->CoreLogError("[TcpClient] recvTcpConnect.uv_read_start failed, error='%s'", uv_strerror(err));
        if(this->handler != NULL) {this->handler->recvTcpConnectError(uv_strerror(err));}
        this->Close();
        return;
    }
    this->status = TcpClientStatus_CONNECTED;
    if(this->handler != NULL) {this->handler->recvTcpConnect();}
}

void TcpClient::recvTcpData() {
    //this->coord->CoreLogDebug("[TcpClient] recvTcpData, len=%d", this->recvBuffer.Len());
    if (!this->handler){
        return;
    }
    while(this->recvBuffer.Len() > 0) {
        size_t byteRead = this->handler->recvTcpData(this->recvBuffer.Front(), this->recvBuffer.Len());
        if (byteRead <= 0) {
            break;
        }
        this->recvBuffer.PopFront(byteRead);
    }
    this->recvBuffer.Truncate();
}

int TcpClient::Send(const char* data, size_t len) {
    return -1;
}

int TcpClient::Send(byte_slice& data) {
    this->coord->CoreLogDebug("[TcpClient] Send, len=%d", data.Len());
    uv_buf_t buf[] = {
        { .base = (char*)data.Data(), .len = data.Len()},
    };
    WriteReq* req = new WriteReq(data);
    int err = uv_write(&req->req, (uv_stream_t *)&this->handle, buf, 1, uv_write_cb);
    if (err < 0){
        this->coord->CoreLogError("[TcpClient] Send failed, error='%s'", uv_strerror(err));
        return err;
    }
    return 0;
}

}
}  
