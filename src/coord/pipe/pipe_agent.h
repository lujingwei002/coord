#pragma once 


#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/net/recv_buffer.h"
#include "coord/builtin/slice.h"
#include <uv.h>
#include <string>
namespace coord {//tolua_export

class Coord;

namespace pipe {//tolua_export
class PipeListener;
class PipeAgent;

enum PipeAgentStatus {
    PipeAgentStatus_CONNECTED = 0,
    PipeAgentStatus_ERROR = 1,
    PipeAgentStatus_CLOSING = 2,
    PipeAgentStatus_CLOSED = 3,
};

class IPipeAgentHandler {//tolua_export
public:
    virtual void recvPipeClose(PipeAgent* agent) = 0;
    virtual void recvPipeError(PipeAgent* agent) = 0;
    virtual int recvPipeData(PipeAgent* agent, char* data, size_t len) = 0;
};//tolua_export

class PipeAgent : public Destoryable  {//tolua_export
CC_CLASS(PipeAgent);
public:
    PipeAgent(Coord* coord, PipeListener* listen);
    virtual ~PipeAgent();
    //发送数据
    int Send(const void* data, size_t len);
    //发送数据
    int Send(byte_slice& data);
    //设置handler
    void SetHandler(IPipeAgentHandler* handler);
    //设置接收缓冲区
    void SetRecvBuffer(size_t size);
    //关闭链接
    void Close();
public:
    void recvPipeNew();
    void recvPipeError(int status);
    void recvPipeData();
    void recvPipeClose();
public:
    Coord*              coord;
    IPipeAgentHandler*  handler;
    PipeListener*       listener;
    uv_pipe_t           handle;
    int                 sockfd;
    int                 sessionId;
    std::string         remoteAddr;
    net::RecvBuffer     recvBuffer;  
    int                 status;      
};//tolua_export

PipeAgent* newPipeAgent(Coord* coord, PipeListener* listen);

}//tolua_export
}//tolua_export


