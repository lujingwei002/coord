#pragma once 

#include "coord/timer/timer.h"
#include "coord/script/script.h"
#include "coord/closure/closure_mgr.h"
#include <uv.h>
#include <vector>
#include <map>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

namespace coord { //tolua_export


class SceneMgr;
class Scene;
class Config;
class EventListener;
class Component;
class ScriptComponent;
class EventArgs;
class Destoryable;
class BaseRequest;
class RequestPipeline;
namespace http {
class HttpServer;
class HttpRequest;
}
namespace script {
class Script;
}
namespace web {
class WebServer;
}
namespace log {
class base_logger;
class core_logger;
class file_logger;
}
namespace protobuf {
class Protobuf;
class Reflect;
}
namespace gate {
class Gate;
class GateRequest;
class GateNotify;
}
namespace sql {
class SQLClient;
class sql_mgr;
}
namespace redis {
class RedisMgr;
class Client;
class AsyncClient;
}
namespace cache {
class Client;
class AsyncClient;
class CacheReader;
}
namespace cluster {
class Cluster;
}
namespace net {
class TcpClient;
}
namespace managed {
class Managed;
}
namespace worker {
class Worker;
class WorkerSlave;
}
namespace timer {
class TimerMgr;
}
namespace action {
class ActionMgr;
}
namespace closure {
class ClosureMgr;
class Closure;
}
class Environment;
namespace event {
class BaseEvent;
class EventMgr;
class Listener;
}
namespace login {
class LoginSvr;
}
namespace json {
class JsonMgr;
}
namespace log4cc {
class LoggerMgr;
class Category;
}
enum worker_role {
    worker_role_master = 1,
    worker_role_slave = 2,
};


class Coord { //tolua_export
public:
    Coord();
    ~Coord();
public:
    int master();
    int slave();
    int Local();
    int Client();
    //新建一个线程
    int asWorker(worker::Worker* master, const char *configFile, int index);
    int asCommand(const char *configFile, const char* command);
    int Fork(const char *configFile);
    int Main(const char *configFile);  
    int beforeTest(const char *configFile); 
    void loopTest();   
    int afterTest();  
    int Reload();
    void Destory(int code);//tolua_export
    Scene* CreateScene(const char* sceneName);//tolua_expor
    void Sleep(uint64_t msec);//tolua_export
    //@xx 日志接口
    void Log(const char* fmt, ...);
    void LogFatal(const char* fmt, ...);
    void LogError(const char* fmt, ...);
    void LogWarn(const char* fmt, ...);
    void LogInfo(const char* fmt, ...);
    void LogDebug(const char* fmt, ...);
    void LogMsg(const char* fmt, ...);
    int Log(lua_State* L);//tolua_export
    void Log(const char* str) const;//tolua_export
    void LogFatal(const char* str) const;//tolua_export
    void LogError(const char* str) const;//tolua_export
    void LogWarn(const char* str) const;//tolua_export
    void LogInfo(const char* str) const;//tolua_export
    void LogDebug(const char* str) const;//tolua_export
    void LogMsg(const char* str) const;//tolua_export
    void LogCloseLevel(int level);//tolua_export
    void LogOpenLevel(int level);//tolua_export
    void LogSetLevel(int level);//tolua_export
    //@xx 日志接口
    //@xx 组件接口
    //ScriptComponent* AddScript(const char* scriptName);//tolua_export
    int AddScript(lua_State* L);//tolua_export
    int AddComponent(Component* component);//tolua_export
    //@xx 组件接口
    //@xx 定时器接口
    int SetTimeout(uint64_t timeout, timer::TimeoutFunc func);
    int SetInterval(uint64_t repeat, timer::TimeoutFunc func);
    int SetTimeout(lua_State* L);//tolua_export
    int SetInterval(lua_State* L);//tolua_export
    int SetCron(const char* expression, timer::CronFunc func);
    int SetCron(lua_State* L);//tolua_export
    void ClearInterval(int id);
    void ClearTimeout(int id);
    void ClearCron(int id);
    uint64_t StopTimer();
    //@xx 定时器接口
    void Emit(const char* name, event::BaseEvent* args);//tolua_export
    void Destory(Destoryable* object);//tolua_export
    void Destory(net::TcpClient* object);//tolua_export
    void DontDestory(Destoryable* object);//tolua_export
    http::HttpServer* NewHttpServer();//tolua_export
    uint64_t Now();//tolua_export
    uint64_t Time();//tolua_export
    uint64_t NanoTime();//tolua_export
    sql::SQLClient* SQLConfig(const char* name = "DB");//tolua_export
    redis::Client* RedisConfig(const char* name = "REDIS");//tolua_export
    redis::AsyncClient* RedisAsyncConfig(const char* name = "REDIS");//tolua_export
    //int Cache(const char* name, const char* data, size_t expiret);//tolua_export
    //cache::CacheReader Cache(const char* name);//tolua_export
    template<class... T>
    closure::Closure* Function(T... args) {
        return this->Closure->Function(args...);
    }
public:
    //void pushRequestPipeline(BaseRequest* request);
    //void recoverRequestPipeline(RequestPipeline* request);
    //void popRequestPipeline();
    //RequestPipeline* refRequestPipeline(BaseRequest* request);
    void cacheTimeofday();
    void onDestory(int code);
    uint64_t onGC();        
    int onAwake(); 
    uint64_t onUpdate(); 
    int readConfig(const char *filePath);
    void recvSigInt();
    //@xx core日志接口
    void coreLogFatal(const char* fmt, ...);
    void coreLogError(const char* fmt, ...);
    void coreLogWarn(const char* fmt, ...);
    void coreLogInfo(const char* fmt, ...);
    void coreLogDebug(const char* fmt, ...);
    void coreLogMsg(const char* fmt, ...);
    void coreLogFatal(const char* str) const;           //tolua_export
    void coreLogError(const char* str) const;           //tolua_export
    void coreLogWarn(const char* str) const;            //tolua_export
    void coreLogInfo(const char* str) const;            //tolua_export
    void coreLogDebug(const char* str) const;           //tolua_export
    void coreLogMsg(const char* str) const;             //tolua_export
    void coreLogFatal(const char* fmt, va_list args); 
    void coreLogError(const char* fmt, va_list args);
    void coreLogWarn(const char* fmt, va_list args);
    void coreLogInfo(const char* fmt, va_list args);
    void coreLogDebug(const char* fmt, va_list args);
    void coreLogMsg(const char* fmt, va_list args);
    void coreLogCloseLevel(int level);                  //tolua_export
    void coreLogOpenLevel(int level);                   //tolua_export
    void coreLogSetLevel(int level);                    //tolua_export
    //@xx core日志接口
public:
    Config*                 config;         //tolua_export
    script::Script*         Script;         //tolua_export   
    gate::Gate*             Gate;           //tolua_export
    http::HttpServer*       HttpServer;     //tolua_export 
    event::EventMgr*        Event;
    protobuf::Protobuf*     Proto;          //tolua_export
    redis::RedisMgr*        RedisMgr;       //tolua_export
    cache::Client*          Cache;          //tolua_export
    cache::AsyncClient*     AsyncCache;
    cluster::Cluster*       Cluster;        //tolua_export
    std::string             ConfigFile;     //tolua_export
    managed::Managed*       Managed;        //tolua_export
    worker::WorkerSlave*    WorkerSlave;    //tolua_export
    worker::Worker*         Worker;         //tolua_export
    std::string             Name;           //tolua_export
    std::string             PidPath;        //tolua_export
    coord::Environment*     Environment;    //tolua_export
    action::ActionMgr*      Action;         
    closure::ClosureMgr*    Closure;        //tolua_export
    login::LoginSvr*        Login;          //tolua_export
    json::JsonMgr*          Json;           
    log4cc::LoggerMgr*      LoggerMgr;      //tolua_export
public:
    uint64_t            frame;
    sql::sql_mgr*       sqlMgr;         
    timer::TimerMgr*    Timer;
    SceneMgr*           sceneMgr;
    uv_loop_t           loop;
    log4cc::Category*   logger;
    log4cc::Category*   coreLogger;
    uv_signal_t         sigInt;
    uv_signal_t         sigUsr1;
    uv_signal_t         sigUsr2;
    worker_role         workerRole;
    uv_pid_t            pid;
    bool                isAwake;
    uint64_t            time;
    uint64_t            nowRecord;
private:
    
    int                 exitCode;
public:
    static std::map<uv_thread_t*, Coord*> coordDict; 
}; //tolua_export

Coord *NewCoord();
int Wait(); 
int Init();
void Destory();
int Main(int argc, const char** argv);

} //tolua_export

extern thread_local coord::Coord* coorda;
