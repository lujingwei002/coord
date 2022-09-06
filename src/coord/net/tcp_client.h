#pragma once 


#include "coord/coordx.h"
#include "coord/memory/type.h"
#include "coord/net/recv_buffer.h"
#include <uv.h>
#include <string>
namespace coord {//tolua_export
class Coord;
namespace net {//tolua_export

class ITcpClientHandler {//tolua_export
public:
    virtual void recvTcpClose() = 0;
    virtual void recvTcpConnect() = 0;
    virtual void recvTcpError(int err) = 0;
    virtual int recvTcpData(char* data, size_t len) = 0;
    virtual void recvTcpConnectError(const char* err) = 0;
};//tolua_export

enum TcpClientStatus {
    TcpClientStatus_NIL = 0,
    TcpClientStatus_CONNECTING = 1,
    TcpClientStatus_CONNECTED = 2,
    TcpClientStatus_ERROR = 3,
    TcpClientStatus_CLOSING = 4,
    TcpClientStatus_CLOSED = 5,
};

class TcpClient {//tolua_export
RC_CLASS(TcpClient);
public:
    TcpClient(Coord* coord);
    virtual ~TcpClient();
public:
    int Connect(const char* host, int16_t port);
    int Reconnect(const char* host, int16_t port);
    void SetRecvBuffer(size_t size);
    void SetHandler(ITcpClientHandler* handler);
    void Close();
    bool IsClose();
    int GetStatus();
    void onDestory();
    int Send(const char* data, size_t len);
    int Send(byte_slice& data);
public:
    void recvTcpError(int err);
    void recvTcpClose();
    void recvTcpData();
    void recvTcpConnectError(int err);
    void recvTcpConnect();
public:
    Coord*              coord;
    uv_tcp_t            handle;    
    uv_shutdown_t       shutdownReq;
    uv_connect_t        connectReq;
    RecvBuffer          recvBuffer;  
    ITcpClientHandler*  handler;     
    TcpClientStatus     status;
    bool                isDestory;
};//tolua_export

TcpClient* newTcpClient(Coord* coord);//tolua_export

}//tolua_export
}//tolua_export


