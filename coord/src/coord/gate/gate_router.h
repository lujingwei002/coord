#pragma once 

#include "coord/component/component.h"
#include "coord/gate/gate.h"
#include "coord/builtin/slice.h"

#include <map>
#include <string>
#include <functional>
namespace coord {//tolua_export

class Coord;

class ScriptComponent;

namespace gate {//tolua_export

class GateRequest;
class GateNotify;
class GateSession;

typedef std::function<void (GateSession* session, GateRequest* request)> GateRouter_RecvGateRequest; 
typedef std::function<void (GateSession* session, GateNotify* notify)> GateRouter_RecvGateNotify; 
typedef std::function<void (GateSession* session)> GateRouter_RecvGateSession; 

class gate_router_handler {
public:
    //gate_router_handler(){}
    gate_router_handler(Coord* coord, GateRouter_RecvGateRequest recvGateRequest, int ref = LUA_NOREF): 
        coord(coord), recvGateRequestFunc(recvGateRequest), ref(ref) {
        this->init();
    }
    gate_router_handler(Coord* coord, GateRouter_RecvGateNotify recvGateNotify, int ref = LUA_NOREF): 
        coord(coord), recvGateNotifyFunc(recvGateNotify), ref(ref) {
        this->init();
    }
    gate_router_handler(Coord* coord, GateRouter_RecvGateSession recvGateSession, int ref = LUA_NOREF): 
        coord(coord), recvGateSessionFunc(recvGateSession), ref(ref) {
        this->init();
    }
    ~gate_router_handler();
public:
    void recvGateAuth(GateSession* session, GateRequest* request);
    void recvGateRequest(GateSession* session, GateRequest* request);
    void recvGateNotify(GateSession* session, GateNotify* notify);
    void recvGateSessionNew(GateSession* session);
    void recvGateSessionClose(GateSession* session);
    void recvGateUserLogin(GateSession* session);
    void recvGateUserLogout(GateSession* session);
    void recvGateUserInstead(GateSession* session);
    void init() {
        this->times = 0;
        this->consumeTime = 0;
    }
public:
    Coord*                      coord;
    GateRouter_RecvGateRequest  recvGateRequestFunc;
    GateRouter_RecvGateNotify   recvGateNotifyFunc;
    GateRouter_RecvGateSession  recvGateSessionFunc;
    int                         ref;
    int                         times;              //处理次数
    int                         consumeTime;        //耗时
};

class gate_router_tree {
public:
    gate_router_tree() {
    }
    ~gate_router_tree() {
    }
public:
    std::map<std::string, gate_router_handler*> handlerDict;
};

class GateRouter {//tolua_export
CC_CLASS(GateRouter);
public:
    GateRouter(Coord* coord);
    virtual ~GateRouter();
public:
    //侦听'通知'事件
    bool Notify(const char* path, GateRouter_RecvGateNotify func);
    //侦听'请求'事件
    bool Request(const char* path, GateRouter_RecvGateRequest func);
    //侦听'会话开始'事件
    bool SessionNew(GateRouter_RecvGateSession func);
    //侦听'会话关闭'事件
    bool SessionClose(GateRouter_RecvGateSession func);
    //侦听'认证请求'事件
    bool Auth(const char* path, GateRouter_RecvGateRequest func);
    //侦听'登录'事件
    bool Login(GateRouter_RecvGateSession func);
    //侦听'登出'事件
    bool Logout(GateRouter_RecvGateSession func);
    //侦听'被顶下线'事件
    bool Instead(GateRouter_RecvGateSession func);
    
    int Notify(lua_State* L);//tolua_export
    /*
    *example:
    *local Gate = {}
    *function Gate.roundresult = function(self, session, request) end
    *function Gate.roundresult = function(self, session, request) end
    *router:Request("daxigua.roundresult", self, GATE.RoundResult)
    *router:Request("daxigua", self, GATE)
    *参数4是函数或者table
    */
    int Request(lua_State* L);//tolua_export
    int Auth(lua_State* L);//tolua_export
    int SessionNew(lua_State* L);//tolua_export
    int SessionClose(lua_State* L);//tolua_export
    int Login(lua_State* L);//tolua_export
    int Logout(lua_State* L);//tolua_export
    int Instead(lua_State* L);//tolua_export

    bool Notify(const char* path, ScriptComponent* object, int ref);
    bool Request(const char* path, ScriptComponent* object, int ref);
    bool Auth(const char* path, ScriptComponent* object, int ref);
    bool SessionNew(ScriptComponent* object, int ref);
    bool SessionClose(ScriptComponent* object, int ref);
    bool Login(ScriptComponent* object, int ref);
    bool Logout(ScriptComponent* object, int ref);
    bool Instead(ScriptComponent* object, int ref);

    void Trace();//tolua_export
public: 
    void recvGateAuth(GateSession* session, GateRequest* request);
    void recvGateRequest(GateSession* session, GateRequest* request);
    void recvGateNotify(GateSession* session, GateNotify* notify);
    void recvGateSessionNew(GateSession* session);
    void recvGateSessionClose(GateSession* session);
    void recvGateUserLogin(GateSession* session);
    void recvGateUserLogout(GateSession* session);
    void recvGateUserInstead(GateSession* session);
private:
    gate_router_handler* searchHandler(const char* event, const char* path);
    bool addRoute(const char* event, const char* path, gate_router_handler* handler);
    gate_router_tree* getTree(const char* event);
public:
    Coord* coord;
    std::map<std::string, gate_router_tree*> trees;
};//tolua_export

GateRouter* newGateRouter(Coord* coord);

}//tolua_export
}//tolua_export
 
