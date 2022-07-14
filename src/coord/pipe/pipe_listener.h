#pragma once 

#include "coord/component/component.h"
#include "coord/pipe/pipe_agent.h"
#include "coord/builtin/slice.h"
#include <uv.h>
#include <map>
namespace coord {//tolua_export

class Coord;

namespace pipe {//tolua_export

class PipeAgent;

class IPipeHandler {//tolua_export
public:
    virtual void recvPipeNew(PipeListener* listener, PipeAgent* agent) = 0;
};//tolua_export

class PipeListener  {//tolua_export
CC_CLASS(PipeListener);
public:
    PipeListener(Coord* coord);
    virtual ~PipeListener();
    //开始侦听
    int Listen(const std::string& path, int ipc, int backlog = 1024);//tolua_export
    //关闭服务器
    void Close();//tolua_export
    //设置handler
    void SetHandler(IPipeHandler* handler);
public:
    void recvPipeNew(int status);
    void recvAgentClose(PipeAgent* agent);
public:
    IPipeHandler*               handler;
    Coord*                      coord;
    uv_pipe_t                   server;
    int                         sessionId;
    std::map<int, PipeAgent*>   agentDict;
    int                         ipc;
};//tolua_export

PipeListener* NewPipeListener(Coord* coord);

}//tolua_export
}//tolua_export


