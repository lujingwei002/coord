#pragma once 

#include "coord/component/component.h"
#include "coord/net/tcp_agent.h"
#include "coord/coordx.h"
#include <uv.h>
#include <map>
namespace coord {//tolua_export

class Coord;

namespace net {//tolua_export

class TcpAgent;

class ITcpHandler {//tolua_export
public:
    virtual void recvTcpNew(TcpListener* listener, TcpAgent* agent) = 0;
};//tolua_export

class TcpListener : public coordx::RcObject {//tolua_export
CC_CLASS(TcpListener);
public:
    TcpListener(Coord* coord);
    virtual ~TcpListener();
    //开始侦听
    int Listen(const char* host, unsigned short port, int backlog = 1024);//tolua_export
    //关闭服务器
    void Close();//tolua_export
    //设置handler
    void SetHandler(ITcpHandler* handler);
public:
    void recvTcpNew(int status);
    void recvAgentClose(TcpAgent* agent);
public:
    ITcpHandler* handler;
    Coord* coord;
    uv_tcp_t server;
    int sessionId;
    std::map<int, TcpAgent*> agentDict;
};//tolua_export

TcpListener* NewTcpListener(Coord* coord);

}//tolua_export
}//tolua_export


