#pragma once 

#include "coord/component/component.h"
#include "coord/net/tcp_listener.h"
#include "coord/net/tcp_agent.h"
#include "coord/websocket/websocket_server.h"
#include "coord/timer/timer.h"
#include "coord/builtin/slice.h"
#include "coord/gate/gate_config.h"
#include <uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export
namespace protobuf {
class Reflect;
}

namespace net {
class TcpListener;
class TcpAgent;
}
namespace websocket {
class Agent;
class Frame;
}
namespace redis {
class AsyncClient;
class Reply;
}

class Coord;
namespace gate {//tolua_export

class GateAgent;
class GateRouter;
class GateRequest;
class GateNotify;
class GateSession;
class gate_cluster;
class GateSession;
class GatePromise;

enum GateStatus {
    GateStatus_NIL = 0,
    GateStatus_RUNNING = 1,     //运行中
    GateStatus_CLOSED = 2,      //关闭
    GateStatus_MAINTAIN = 3,    //维护
    GateStatus_ERROR = 4,      //出错
};

class Gate : public net::ITcpHandler, public websocket::IWebSocketHandler {//tolua_export
CC_CLASS(Gate);
public:
    Gate(Coord* coord);
    virtual ~Gate();
public:
    GateConfig* DefaultConfig();//tolua_export
    //跟用户下线
    void Kick(uint64_t sessionId, const char* reason);//tolua_export
    //关闭网关
    void Close();
    //设置维护状态
    int Maintain(bool value);
    int GetOnlineNum();
    //登出
    int Logout(uint64_t userId);
public:
    //登录
    GatePromise* login(GateAgent* agent, uint64_t userId);
    int main();
    void onDestory();
    uint64_t heartbeatInterval();
    uint64_t agentRegisterInterval();
    void recvGateRequest(GateSession* session, GateRequest* request);
    void recvGateNotify(GateSession* session, GateNotify* notify);
    void recvGateSessionNew(GateSession* session);
    void recvGateSessionClose(GateSession* session);
    void recvAgentClose(GateAgent* agent);
    // implement net::ITcpHandler begin
    virtual void recvTcpNew(net::TcpListener* listener, net::TcpAgent* agent);
    // implement net::ITcpHandler end
    // implement websocket::IWebSocketHandler begin
    virtual void recvWebSocketNew(websocket::Agent* agent);
    // implement websocket::IWebSocketHandler end
    // gate cluster 通知
    void recvUserLoginSucc(uint64_t sessionId, uint64_t userId);
    void recvUserLoginErr(uint64_t sessionId, uint64_t userId);
    void recvUserLogoutSucc(uint64_t sessionId, uint64_t userId);
    void recvUserLogoutErr(uint64_t sessionId, uint64_t userId);
    void recvUserInstead(uint64_t userId);
    // gate cluster 通知 
public:
    Coord*                              coord;
    net::TcpListener*                   tcpListener;
    websocket::Server*         webSocketServer;
    GateConfig                          config;
    std::map<uint64_t, GateAgent*>      agentDict; // session id => agent
    std::map<uint64_t, GateAgent*>      userDict; // user id => agent
    std::map<uint64_t, uint64_t>        loginingUserDict; // 正在登录的用户, session id => user id 
    std::map<uint64_t, GatePromise*>    loginingPromiseDict; // 正在登录的用户, session id => promise
    std::string                         rsaPrivateKey;
    GateRouter*                         Router;//tolua_export
    int                                 status;
    gate_cluster*                       cluster;
    std::string                         address;
};//tolua_export

Gate* NewGate(Coord* coord);
}//tolua_export
}//tolua_export


