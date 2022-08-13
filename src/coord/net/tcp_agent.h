#pragma once 


#include "coord/builtin/type.h"

#include "coord/net/recv_buffer.h"
#include "coord/builtin/slice.h"
#include <uv.h>
#include <string>
namespace coord {//tolua_export

class Coord;

namespace net {//tolua_export
class TcpListener;
class TcpAgent;

enum TcpAgentStatus {
    TcpAgentStatus_CONNECTED = 0,
    TcpAgentStatus_ERROR = 1,
    TcpAgentStatus_CLOSING = 2,
    TcpAgentStatus_CLOSED = 3,
};

class ITcpAgentHandler {//tolua_export
public:
    virtual void recvTcpClose(TcpAgent* agent) = 0;
    virtual void recvTcpError(TcpAgent* agent) = 0;
    virtual int recvTcpData(TcpAgent* agent, char* data, size_t len) = 0;
};//tolua_export

class TcpAgent : public RcObject  {//tolua_export
CC_CLASS(TcpAgent);
public:
    TcpAgent(Coord* coord, TcpListener* listen);
    virtual ~TcpAgent();
    //发送数据
    int Send(const void* data, size_t len);
    //发送数据
    int Send(byte_slice& data);
    //设置handler
    void SetHandler(ITcpAgentHandler* handler);
    //设置接收缓冲区
    void SetRecvBuffer(size_t size);
    //关闭链接
    void Close();
public:
    void recvTcpNew();
    void recvTcpError(int status);
    void recvTcpData();
    void recvTcpClose();
public:
    Coord*              coord;
    ITcpAgentHandler*   handler;
    TcpListener*        listener;
    uv_tcp_t            handle;
    int                 sockfd;
    int                 sessionId;
    std::string         remoteAddr;
    RecvBuffer          recvBuffer;  
    int                 status;      
};//tolua_export

TcpAgent* newTcpAgent(Coord* coord, TcpListener* listen);

}//tolua_export
}//tolua_export


