#pragma once 
#include "coord/builtin/type.h"
#include "coord/component/component.h"
#include "coord/redis/declare.h"
#include "coord/http/http_request.h"
#include <map>
#include <string>
#include <cstdint>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace coord {//tolua_export

class Coord;
class base_request;
class base_result;
class base_notify;
namespace http {
class HttpRequest;
class HttpResponse;
}
namespace websocket {
class Agent;
class Frame;
}

namespace gate {
class GateRequest;
class GateNotify;
class GateSession;
}
namespace cluster {
class Request;
class GateNotify;
class Result;
}

namespace worker {
class Request;
class Result;
class Notify;
}

namespace redis {
class AsyncClient;
class RedisResult;
}

namespace cache {
class AsyncClient;
class CacheResult;
}
namespace event {
class BaseEvent;
}
class ScriptComponent : public Component {  //tolua_export
CC_CLASS(ScriptComponent);
public:
    ScriptComponent(Coord* coord, const char* scriptName, int ref);
    virtual ~ScriptComponent(); 
public:
    const char* GetScriptName();
public:
    virtual void onAwake();
    virtual void onStart();
    virtual void onUpdate(uint64_t cur_tick);
    virtual void onReload();
    virtual void onDestory();

    void loadRef();
    void releaseRef();

    void recvRequest(base_request* request, const char* script, int ref);
    void recvResult(base_result* result, base_request* request, const char* script, int ref);
    void recvNotify(base_notify* notify, const char* script, int ref);

    void recvEvent(event::BaseEvent* args, const char* script, int ref);
    void recvPromise(const char* script, int ref);

    // for http begin
    void recvHttpRequest(const http::HttpRequestRef& request, int ref);
    // for http end

    // for websocket begin
    void recvWebSocket(websocket::Agent* agent, const char* script, int ref);
    void recvWebSocketFrame(websocket::Agent* agent, websocket::Frame* frame, const char* script, int ref);
    // for websocket end

    // for gate begin
   
    /*void recvGateSessionNew(gate::GateSession* session, const char* script);
    void recvGateSessionClose(gate::GateSession* session, const char* script);
    void recvGateUserLogin(gate::GateSession* session, const char* script);
    void recvGateUserLogout(gate::GateSession* session, const char* script);
    void recvGateUserInstead(gate::GateSession* session, const char* script);*/
    void recvGateSession(gate::GateSession* session, const char* script, int ref);
    void recvGatePromise(gate::GateSession* session, base_request* request, const char* script, int ref);
    void recvGateRequest(gate::GateSession* session, gate::GateRequest* request, const char* script, int ref);
    void recvGateNotify(gate::GateSession* session, gate::GateNotify* notify, const char* script, int ref);
    // for gate end
    //
    // for cluster begin
    void recvClusterRequest(cluster::Request* request, const char* script, int ref);
    void recvClusterNotify(cluster::GateNotify* notify, const char* script, int ref);
    void recvClusterResult(cluster::Result* result, const char* script, int ref);
    // for cluster end
    // for worker begin
    void recvWorkerRequest(worker::Request* request, const char* script, int ref);
    void recvWorkerNotify(worker::Notify* notify, const char* script, int ref);
    void recvWorkerResult(worker::Result* result, base_request* request, const char* script, int ref);
    //void recvWorkerResultRef(worker::Result* result, int ref);
    // for worker end
    //
    // for redis begin
    void recvRedisReply(redis::AsyncClient* client, const redis::RedisResultRef& result, const char* script, int ref);
    // for redis end

    // for redis begin
    void recvCacheReply(cache::AsyncClient* client, cache::CacheResult* result, const char* script, int ref);
    // for redis end

    // for timer begin
    uint64_t recvTimer(const char* script, int ref);
    void recvCron(const char* script, int ref);
    // for timer end

    virtual void AddHttpGet(const char* pattern, const char* callback);//tolua_export

    int SetTimeout(lua_State* L);   //tolua_export
    int SetInterval(lua_State* L);  //tolua_export
    void ClearInterval(int id);     //tolua_export
    int Log(lua_State* L);//tolua_export
    virtual void Log(const char* str) const;//tolua_export
    virtual void LogFatal(const char* str) const;//tolua_export
    virtual void LogError(const char* str) const;//tolua_export
    virtual void LogWarn(const char* str) const;//tolua_export
    virtual void LogInfo(const char* str) const;//tolua_export
    virtual void LogDebug(const char* str) const;//tolua_export
    virtual void LogMsg(const char* str) const;//tolua_export
public:
    char scriptName[64];//tolua_export
    int tableRef;
    int onAwakeRef;
    int onStartRef;
    int onUpdateRef;
    int onDestoryRef;
    int onReloadRef;
};//tolua_export

}//tolua_export
