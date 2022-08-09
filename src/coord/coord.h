#pragma once 


#include <uv.h>
#include <vector>
#include <map>
#include <string>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
#include "coord/builtin/declare.h"
#include "coord/closure/init.h"
#include "coord/component/declare.h"
#include "coord/object/declare.h"
#include "coord/scene/declare.h"
#include "coord/event/declare.h"
#include "coord/base/declare.h"
#include "coord/http/declare.h"
#include "coord/websocket/declare.h"
#include "coord/script/declare.h"
#include "coord/web/declare.h"
#include "coord/protobuf/declare.h"
#include "coord/gate/declare.h"
#include "coord/sql/declare.h"
#include "coord/redis/declare.h"
#include "coord/cache/declare.h"
#include "coord/cluster/declare.h"
#include "coord/net/declare.h"
#include "coord/pipe/declare.h"
#include "coord/managed/declare.h"
#include "coord/worker/declare.h"
#include "coord/timer/declare.h"
#include "coord/action/declare.h"
#include "coord/closure/declare.h"
#include "coord/run/declare.h"
#include "coord/login/declare.h"
#include "coord/json/declare.h"
#include "coord/log4cc/declare.h"
#include "coord/config/declare.h"

namespace coord { //tolua_export



enum worker_role {
    worker_role_master = 1,
    worker_role_slave = 2,
};


class Argv {
public:
    std::string Name;           /// 名字
    std::string ConfigPath;     /// 配置文件路径
};

class Coord { //tolua_export

friend class worker::Worker;
friend class Argument;
friend class coord::Config;
friend class coord::Environment;
friend class coord::run::Running;
friend class coord::BaseRequest;
friend class coord::BaseResponse;
friend class coord::Promise;
friend class coord::ref_manager;
friend class coord::log4cc::LoggerMgr;
friend class coord::SceneMgr;
friend class coord::Scene;
friend class coord::Component;
friend class coord::Object;
friend class coord::ScriptComponent;
friend class coord::script::Script;
friend class coord::net::TcpAgent;
friend class coord::net::TcpClient;
friend class coord::net::TcpListener; 
friend class coord::pipe::PipeListener;
friend class coord::pipe::PipeClient;
friend class coord::pipe::PipeAgent;
friend class coord::http::HttpAgent;
friend class coord::http::HttpServer;
friend class coord::http::HttpRequest;
friend class coord::http::HttpResponse;
friend class coord::websocket::Agent;
friend class coord::websocket::Server;
friend class coord::websocket::Frame;
friend class coord::websocket::Router;
friend class coord::http::HttpRouter;
friend class coord::gate::Gate;
friend class coord::gate::GateAgent;
friend class coord::gate::GateRequest;
friend class coord::gate::gate_cluster;
friend class coord::gate::GateRouter;
friend class coord::gate::GatePromise;
friend class coord::protobuf::Protobuf;
friend class coord::protobuf::Array;
friend class coord::protobuf::Reflect;
friend class coord::timer::timer;
friend class coord::timer::cron;
friend class coord::timer::TimerMgr;
friend class coord::sql::MySQLClient;
friend class coord::sql::mysql_rows;
friend class coord::sql::SQLClient;
friend class coord::sql::sql_mgr;
friend class coord::redis::AsyncClient;
friend class coord::redis::Client;
friend class coord::redis::RedisMgr;
friend class coord::cluster::Cluster;
friend class coord::cluster::cluster_agent;
friend class coord::cluster::cluster_client;
friend class coord::cluster::cluster_redis_config;
friend class coord::cluster::Request;
friend class coord::cluster::Promise;
friend class coord::cluster::ClusterRouter;
friend class coord::cluster::cluster_server;
friend class coord::cluster::Result;
friend class coord::managed::ManagedAgent;
friend class coord::managed::managed_server;
friend class coord::managed::Managed;
friend class coord::managed::ManagedRequest;
friend class coord::worker::Request;
friend class coord::worker::WorkerSlave;
friend class coord::worker::WorkerRouter;
friend class coord::worker::Promise;
friend class coord::worker::worker_packet;
friend class coord::worker::Notify;
friend class coord::worker::Response;
friend class coord::worker::Result;
friend class coord::worker::Worker;
friend class coord::action::Animation;
friend class coord::action::parallel_action;
friend class coord::login::LoginSvr;
friend class coord::login::account_controller;
friend class coord::login::login_cluster;
friend class coord::json::JsonMgr;
friend class coord::protobuf::my_multi_file_error_collector;
friend int coord::path::RealPath(const std::string& path, std::string& realPath);
friend int coord::path::MakeDir(const std::string& path, int mode);
friend int coord::path::RemoveDir(const std::string& path);
friend int coord::path::RemoveDirRecursive(const std::string& path);
friend int coord::path::Unlink(const std::string& path);
friend bool coord::path::Exists(const std::string& path);
friend uv_stat_t* coord::path::FileStat(const char* path);
friend void coord::log::LogFatal(const char *fmt, ...);
friend void coord::log::LogError(const char *fmt, ...);
friend void coord::log::LogWarn(const char *fmt, ...);
friend void coord::log::LogInfo(const char *fmt, ...);
friend void coord::log::LogMsg(const char *fmt, ...);
friend void coord::log::LogDebug(const char *fmt, ...);
friend void coord::log::SetPriority(int priority);
public:
    Coord();
    ~Coord();
public:
    /// 重载
    int Reload();
    /// 销毁并退出
    void Destory(int code);                             //tolua_export
    /// 创建场景
    Scene* CreateScene(const char* sceneName);          //tolua_expor


    /// 日志接口
    void Log(const char* fmt, ...);
    void LogFatal(const char* fmt, ...);
    void LogError(const char* fmt, ...);
    void LogWarn(const char* fmt, ...);
    void LogInfo(const char* fmt, ...);
    void LogDebug(const char* fmt, ...);
    void LogMsg(const char* fmt, ...);
    /// Info级别日志，类似lua的print, 支持可变参数
    int Log(lua_State* L);                      //tolua_export
    void Log(const char* str) const;            //tolua_export
    void LogFatal(const char* str) const;       //tolua_export
    void LogError(const char* str) const;       //tolua_export
    void LogWarn(const char* str) const;        //tolua_export
    void LogInfo(const char* str) const;        //tolua_export
    void LogDebug(const char* str) const;       //tolua_export
    void LogMsg(const char* str) const;         //tolua_export
    void LogSetPriority(int priority);          //tolua_export

    /// 日志接口
    void CoreLogFatal(const char* fmt, ...);
    void CoreLogError(const char* fmt, ...);
    void CoreLogWarn(const char* fmt, ...);
    void CoreLogInfo(const char* fmt, ...);
    void CoreLogDebug(const char* fmt, ...);
    void CoreLogMsg(const char* fmt, ...);
    void CoreLogFatal(const char* str) const;   //tolua_export        
    void CoreLogError(const char* str) const;   //tolua_export      
    void CoreLogWarn(const char* str) const;    //tolua_export       
    void CoreLogInfo(const char* str) const;    //tolua_export         
    void CoreLogDebug(const char* str) const;   //tolua_export       
    void CoreLogMsg(const char* str) const;     //tolua_export        
    void CoreLogFatal(const char* fmt, va_list args); 
    void CoreLogError(const char* fmt, va_list args);
    void CoreLogWarn(const char* fmt, va_list args);
    void CoreLogInfo(const char* fmt, va_list args);
    void CoreLogDebug(const char* fmt, va_list args);
    void CoreLogMsg(const char* fmt, va_list args);
    void CoreLogSetPriority(int priority);                                     

    /// ##组件接口
    //ScriptComponent* AddScript(const char* scriptName);//tolua_export
    /// 在默认场景中添加脚本组件
    int AddScript(lua_State* L);                //tolua_export
    /// 在默认场景中添加组件
    int AddComponent(Component* component);     //tolua_export
   
    /// 睡眠指定的毫秒数
    void Sleep(uint64_t msec);                                  //tolua_export
    /// 当前时间
    uint64_t Now();                                             //tolua_export
    /// 当前时间
    uint64_t Time();                                            //tolua_export
    /// 当前时间
    uint64_t NanoTime();                                        //tolua_export
    /// ##定时器接口
    /// 设置超时回调
    int SetTimeout(uint64_t timeout, timer::TimeoutFunc func);
    int SetTimeout(lua_State* L);                               //tolua_export
    void ClearTimeout(int id);

    /// 设置定时间隔回调
    int SetInterval(uint64_t repeat, timer::TimeoutFunc func);
    int SetInterval(lua_State* L);                              //tolua_export
    void ClearInterval(int id);

    /// 设置计划任务
    int SetCron(const char* expression, timer::CronFunc func);
    int SetCron(lua_State* L);//tolua_export
    void ClearCron(int id);

    uint64_t StopTimer();

    /// @定时器接口

    /// ##事件接口
    void Emit(const char* name, event::BaseEvent* args);//tolua_export
    
    /// ##内存管理接口
    void Destory(Destoryable* object);//tolua_export
    void Destory(net::TcpClient* object);//tolua_export
    void DontDestory(Destoryable* object);//tolua_export

    /// 创建httpserver
    http::HttpServer* NewHttpServer();//tolua_export
    /// 根据配置创建 sql client
    sql::SQLClient* SQLConfig(const char* name = "DB");//tolua_export
    redis::Client* NewRedisClient();//tolua_export
    /// 根据配置创建 redis client
    redis::Client* RedisConfig(const char* name = "REDIS");//tolua_export
    redis::AsyncClient* NewAsyncRedisClient();
    /// 根据配置创建 async redis client
    redis::AsyncClient* AsyncRedisConfig(const char* name = "REDIS");//tolua_export

    //int Cache(const char* name, const char* data, size_t expiret);//tolua_export
    //cache::CacheReader Cache(const char* name);//tolua_export
    template<class... T>
    closure::Closure* Function(T... args) {
        return this->Closure->Function(args...);
    }

    /// ##入口函数
    /// worker启动入口
    int Main(const Argv& argv);  
    int workerEntryPoint(worker::Worker* master, const std::string& configPath, int index);
    int asCommand(const char *configPath, const char* command);
    int ActionEnv(const Argv& argv);
    int ActionStart(const char *configPath);
    int ActionStop(const char *configPath);
    int ActionStatus(const char *configPath);
    int ActionRestart(const char *configPath);
    int beforeTest(const Argv& argv); 
    void loopTest();   
    int afterTest();  

private:
    int initLogger();
    int master();
    int slave();
    int Local();
    int Client();
    //void pushRequestPipeline(BaseRequest* request);
    //void recoverRequestPipeline(RequestPipeline* request);
    //void popRequestPipeline();
    //RequestPipeline* refRequestPipeline(BaseRequest* request);
    void cacheTimeofday();
    void onDestory(int code);
    uint64_t onGC();        
    int onAwake(); 
    uint64_t onUpdate(); 
public:
    coord::Config*          Config;         //tolua_export
    script::Script*         Script;         //tolua_export   
    gate::Gate*             Gate;           //tolua_export
    web::WebServer*         WebServer;      //tolua_export 
    event::EventMgr*        Event;
    protobuf::Protobuf*     Proto;          //tolua_export
    redis::RedisMgr*        RedisMgr;       //tolua_export
    cache::Client*          Cache;          //tolua_export
    cache::AsyncClient*     AsyncCache;
    cluster::Cluster*       Cluster;        //tolua_export
    std::string             ConfigPath;     //tolua_export
    managed::Managed*       Managed;        //tolua_export
    worker::WorkerSlave*    WorkerSlave;    //tolua_export
    worker::Worker*         Worker;         //tolua_export
    std::string             Name;           //tolua_export
    coord::Environment*     Environment;    //tolua_export
    coord::run::Running*    Running;        
    action::ActionMgr*      Action;         
    closure::ClosureMgr*    Closure;        //tolua_export
    login::LoginSvr*        Login;          //tolua_export
    json::JsonMgr*          Json;           
    log4cc::LoggerMgr*      LoggerMgr;   
    int                     ExitCode;   
    std::string             ProcDir;        
private:
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
    
public:
    static std::map<uv_thread_t*, Coord*> coordDict; 
}; //tolua_export




Coord *NewCoord();
int Wait(); 
int Init();
void Destory();
int Main(int argc, const char** argv);
int Fork(const char *configPath);

} //tolua_export

extern thread_local coord::Coord* coorda;
