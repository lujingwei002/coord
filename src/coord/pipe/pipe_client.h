#pragma once 


#include "coord/builtin/type.h"
#include "coord/builtin/slice.h"
#include "coord/net/recv_buffer.h"
#include <uv.h>
#include <string>
namespace coord {//tolua_export
class Coord;
namespace pipe {//tolua_export

class IPipeClientHandler {//tolua_export
public:
    virtual void recvPipeClose() = 0;
    virtual void recvPipeConnect() = 0;
    virtual void recvPipeError(int err) = 0;
    virtual int recvPipeData(char* data, size_t len) = 0;
    virtual void recvConnectError(const char* err) = 0;
};//tolua_export

enum PipeClientStatus {
    PipeClientStatus_NIL = 0,
    PipeClientStatus_CONNECTING = 1,
    PipeClientStatus_CONNECTED = 2,
    PipeClientStatus_ERROR = 3,
    PipeClientStatus_CLOSING = 4,
    PipeClientStatus_CLOSED = 5,
};

class PipeClient {//tolua_export
CC_CLASS(PipeClient);
public:
    PipeClient(Coord* coord);
    virtual ~PipeClient();
public:
    int Connect(const std::string& path, int ipc);
    int Reconnect(const std::string& path, int ipc);
    void SetRecvBuffer(size_t size);
    void SetHandler(IPipeClientHandler* handler);
    void Close();
    bool IsClose();
    int GetStatus();
    int Send(const char* data, size_t len);
    int Send(byte_slice& data);
public:
    void recvPipeError(int err);
    void recvPipeClose();
    void recvPipeData();
    void recvConnectError(int err);
    void recvPipeConnect();
    void onDestory();
public:
    Coord*                  coord;
    uv_pipe_t               handle;    
    uv_shutdown_t           shutdownReq;
    uv_connect_t            connectReq;
    coord::net::RecvBuffer  recvBuffer;  
    IPipeClientHandler*     handler;     
    PipeClientStatus        status;
    bool                    isDestory;
};//tolua_export

PipeClient* newPipeClient(Coord* coord);//tolua_export

}//tolua_export
}//tolua_export


