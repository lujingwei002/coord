/*
** Lua binding: coord
** Generated automatically by tolua++-1.0.92 on Mon Jul 11 18:06:22 2022.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_coord_open (lua_State* tolua_S);

#include "coord/coord.h"
#include "coord/config/config.h"
#include "coord/script/script.h"
#include "coord/script/reflect.h"
#include "coord/builtin/type.h"
#include "coord/builtin/argument.h"
#include "coord/builtin/environment.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/base_request.h"
#include "coord/builtin/base_response.h"
#include "coord/builtin/base_result.h"
#include "coord/builtin/promise.h"
#include "coord/object/object.h"
#include "coord/scene/scene.h"
#include "coord/scene/scene_mgr.h"
#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/http/http_request.h"
#include "coord/http/http_response.h"
#include "coord/http/http_router.h"
#include "coord/http/http_agent.h"
#include "coord/web/web_config.h"
#include "coord/websocket/websocket_server.h"
#include "coord/websocket/websocket_router.h"
#include "coord/websocket/websocket_frame.h"
#include "coord/websocket/websocket_agent.h"
#include "coord/component/script_component.h"
#include "coord/display/transform.h"
#include "coord/display/vector3.h"
#include "coord/net/tcp_listener.h"
#include "coord/net/tcp_agent.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_config.h"
#include "coord/gate/gate_router.h"
#include "coord/gate/gate_request.h"
#include "coord/gate/gate_notify.h"
#include "coord/gate/gate_response.h"
#include "coord/gate/gate_session.h"
#include "coord/gate/gate_promise.h"
#include "coord/event/event.h"
#include "coord/event/event_mgr.h"
#include "coord/event/event_listener.h"
#include "coord/protobuf/protobuf.h"
#include "coord/protobuf/reflect.h"
#include "coord/protobuf/array.h"
#include "coord/timer/timer.h"
#include "coord/sql/sql_mgr.h"
#include "coord/sql/sql_client.h"
#include "coord/sql/sql_result.h"
#include "coord/sql/sql_rows.h"
#include "coord/sql/mysql/mysql_client.h"
#include "coord/sql/mysql/mysql_result.h"
#include "coord/sql/mysql/mysql_rows.h"
#include "coord/redis/redis_mgr.h"
#include "coord/redis/redis_config.h"
#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_client.h"
#include "coord/redis/redis_promise.h"
#include "coord/redis/redis_reply.h"
#include "coord/cache/cache.h"
#include "coord/cache/cache_config.h"
#include "coord/cache/cache_client.h"
#include "coord/cache/cache_reader.h"
#include "coord/cache/cache_async_client.h"
#include "coord/cluster/cluster.h"
#include "coord/cluster/cluster_config.h"
#include "coord/cluster/cluster_router.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_notify.h"
#include "coord/cluster/cluster_response.h"
#include "coord/cluster/cluster_promise.h"
#include "coord/cluster/cluster_result.h"
#include "coord/net/tcp_client.h"
#include "coord/managed/managed.h"
#include "coord/managed/managed_config.h"
#include "coord/managed/managed_server.h"
#include "coord/managed/managed_agent.h"
#include "coord/managed/managed_request.h"
#include "coord/worker/worker.h"
#include "coord/worker/worker_router.h"
#include "coord/worker/worker_slave.h"
#include "coord/worker/worker_request.h"
#include "coord/worker/worker_response.h"
#include "coord/worker/worker_result.h"
#include "coord/worker/worker_notify.h"
#include "coord/worker/worker_promise.h"
#include "coord/closure/closure_mgr.h"
#include "coord/login/login.h"
#include "coord/login/login_config.h"
#include "coord/json/reflect.h"
#include "util/os/os.h"
#include "util/os/path.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_coord__script__Reflect (lua_State* tolua_S)
{
 coord::script::Reflect* self = (coord::script::Reflect*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_coord__json__Reflect (lua_State* tolua_S)
{
 coord::json::Reflect* self = (coord::json::Reflect*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_coord__protobuf__Array (lua_State* tolua_S)
{
 coord::protobuf::Array* self = (coord::protobuf::Array*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_coord__redis__Reply (lua_State* tolua_S)
{
 coord::redis::Reply* self = (coord::redis::Reply*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_coord__protobuf__Reflect (lua_State* tolua_S)
{
 coord::protobuf::Reflect* self = (coord::protobuf::Reflect*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"coord::web::WebConfig");
 tolua_usertype(tolua_S,"coord::worker::Worker");
 tolua_usertype(tolua_S,"coord::cluster::Result");
 tolua_usertype(tolua_S,"coord::net::TcpAgent");
 tolua_usertype(tolua_S,"coord::cache::CacheConfig");
 tolua_usertype(tolua_S,"coord::worker::WorkerSlave");
 tolua_usertype(tolua_S,"coord::sql::sql_mgr");
 tolua_usertype(tolua_S,"coord::sql::SQLResult");
 tolua_usertype(tolua_S,"coord::managed::ManagedConfig");
 tolua_usertype(tolua_S,"coord::http::HttpAgent");
 tolua_usertype(tolua_S,"coord::websocket::WebSocketServerConfig");
 tolua_usertype(tolua_S,"coord::websocket::Agent");
 tolua_usertype(tolua_S,"coord::script::Script");
 tolua_usertype(tolua_S,"coord::net::TcpListener");
 tolua_usertype(tolua_S,"coord::cache::CacheReader");
 tolua_usertype(tolua_S,"coord::http::HttpResponse");
 tolua_usertype(tolua_S,"coord::net::ITcpHandler");
 tolua_usertype(tolua_S,"coord::worker::Promise");
 tolua_usertype(tolua_S,"coord::SceneMgr");
 tolua_usertype(tolua_S,"coord::Transform");
 tolua_usertype(tolua_S,"coord::redis::AsyncClient");
 tolua_usertype(tolua_S,"coord::login::LoginConfig");
 tolua_usertype(tolua_S,"coord::Object");
 tolua_usertype(tolua_S,"coord::websocket::Frame");
 tolua_usertype(tolua_S,"coord::Config");
 tolua_usertype(tolua_S,"coord::http::HttpRouter");
 tolua_usertype(tolua_S,"coord::Environment");
 tolua_usertype(tolua_S,"coord::websocket::IAgentHandler");
 tolua_usertype(tolua_S,"coord::websocket::Server");
 tolua_usertype(tolua_S,"coord::Scene");
 tolua_usertype(tolua_S,"coord::cluster::ClusterRouter");
 tolua_usertype(tolua_S,"coord::sql::SQLConfig");
 tolua_usertype(tolua_S,"coord::net::ITcpAgentHandler");
 tolua_usertype(tolua_S,"coord::json::Reflect");
 tolua_usertype(tolua_S,"coord::login::LoginSvr");
 tolua_usertype(tolua_S,"coord::cache::Client");
 tolua_usertype(tolua_S,"coord::Coord");
 tolua_usertype(tolua_S,"coord::closure::ClosureMgr");
 tolua_usertype(tolua_S,"coord::worker::Request");
 tolua_usertype(tolua_S,"coord::http::IHttpAgentHandler");
 tolua_usertype(tolua_S,"coord::worker::Notify");
 tolua_usertype(tolua_S,"coord::worker::Result");
 tolua_usertype(tolua_S,"coord::protobuf::Reflect");
 tolua_usertype(tolua_S,"coord::cluster::Response");
 tolua_usertype(tolua_S,"coord::managed::ManagedServer");
 tolua_usertype(tolua_S,"coord::sql::SQLClient");
 tolua_usertype(tolua_S,"coord::worker::WorkerRouter");
 tolua_usertype(tolua_S,"coord::Vector3");
 tolua_usertype(tolua_S,"coord::redis::Promise");
 tolua_usertype(tolua_S,"coord::worker::WorkerConfig");
 tolua_usertype(tolua_S,"coord::gate::GateResponse");
 tolua_usertype(tolua_S,"lua_Number");
 tolua_usertype(tolua_S,"coord::cluster::Notify");
 tolua_usertype(tolua_S,"coord::net::TcpClient");
 tolua_usertype(tolua_S,"coord::managed::ManagedAgent");
 tolua_usertype(tolua_S,"coord::http::HttpRequest");
 tolua_usertype(tolua_S,"coord::redis::Reply");
 tolua_usertype(tolua_S,"coord::worker::Response");
 tolua_usertype(tolua_S,"coord::managed::Managed");
 tolua_usertype(tolua_S,"coord::websocket::IWebSocketHandler");
 tolua_usertype(tolua_S,"coord::cluster::Cluster");
 tolua_usertype(tolua_S,"coord::BaseResponse");
 tolua_usertype(tolua_S,"coord::cluster::Promise");
 tolua_usertype(tolua_S,"coord::gate::GateRequest");
 tolua_usertype(tolua_S,"coord::http::IHttpHandler");
 tolua_usertype(tolua_S,"coord::event::BaseEvent");
 tolua_usertype(tolua_S,"coord::gate::Gate");
 tolua_usertype(tolua_S,"coord::http::HttpServer");
 tolua_usertype(tolua_S,"coord::cluster::ClusterConfig");
 tolua_usertype(tolua_S,"coord::gate::GateSession");
 tolua_usertype(tolua_S,"coord::net::ITcpClientHandler");
 tolua_usertype(tolua_S,"coord::Destoryable");
 tolua_usertype(tolua_S,"coord::BaseRequest");
 tolua_usertype(tolua_S,"coord::cache::AsyncClient");
 tolua_usertype(tolua_S,"coord::gate::GateConfig");
 tolua_usertype(tolua_S,"coord::redis::Client");
 tolua_usertype(tolua_S,"coord::ScriptComponent");
 tolua_usertype(tolua_S,"coord::event::Listener");
 tolua_usertype(tolua_S,"coord::redis::RedisMgr");
 tolua_usertype(tolua_S,"coord::sql::MySQLClient");
 tolua_usertype(tolua_S,"coord::sql::SQLRows");
 tolua_usertype(tolua_S,"coord::gate::GateNotify");
 tolua_usertype(tolua_S,"coord::Component");
 tolua_usertype(tolua_S,"coord::timer::TimerMgr");
 tolua_usertype(tolua_S,"coord::script::Reflect");
 tolua_usertype(tolua_S,"coord::protobuf::Protobuf");
 tolua_usertype(tolua_S,"coord::Promise");
 tolua_usertype(tolua_S,"coord::Argument");
 tolua_usertype(tolua_S,"coord::event::EventMgr");
 tolua_usertype(tolua_S,"coord::Type");
 tolua_usertype(tolua_S,"coord::redis::RedisConfig");
 tolua_usertype(tolua_S,"coord::BaseResult");
 tolua_usertype(tolua_S,"coord::gate::GatePromise");
 tolua_usertype(tolua_S,"coord::BasicConfig");
 tolua_usertype(tolua_S,"coord::protobuf::Array");
 tolua_usertype(tolua_S,"coord::managed::ManagedRequest");
 tolua_usertype(tolua_S,"coord::gate::GateRouter");
 tolua_usertype(tolua_S,"coord::http::HttpServerConfig");
 tolua_usertype(tolua_S,"coord::websocket::Router");
 tolua_usertype(tolua_S,"coord::cluster::Request");
}

/* method: Destory of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Destory00
static int tolua_coord_coord_Coord_Destory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  int code = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destory'",NULL);
#endif
  {
   self->Destory(code);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateScene of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CreateScene00
static int tolua_coord_coord_Coord_CreateScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* sceneName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateScene'",NULL);
#endif
  {
   coord::Scene* tolua_ret = (coord::Scene*)  self->CreateScene(sceneName);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Sleep of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Sleep00
static int tolua_coord_coord_Coord_Sleep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  uint64_t msec = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Sleep'",NULL);
#endif
  {
   self->Sleep(msec);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sleep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Log of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Log00
static int tolua_coord_coord_Coord_Log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Log'",NULL);
#endif
  {
return self->Log(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Log of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Log01
static int tolua_coord_coord_Coord_Log01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Log'",NULL);
#endif
  {
   self->Log(str);
  }
 }
 return 0;
tolua_lerror:
 return tolua_coord_coord_Coord_Log00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogFatal of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogFatal00
static int tolua_coord_coord_Coord_LogFatal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogFatal'",NULL);
#endif
  {
   self->LogFatal(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogFatal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogError of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogError00
static int tolua_coord_coord_Coord_LogError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogError'",NULL);
#endif
  {
   self->LogError(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogWarn of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogWarn00
static int tolua_coord_coord_Coord_LogWarn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogWarn'",NULL);
#endif
  {
   self->LogWarn(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogWarn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogInfo of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogInfo00
static int tolua_coord_coord_Coord_LogInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogInfo'",NULL);
#endif
  {
   self->LogInfo(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogDebug of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogDebug00
static int tolua_coord_coord_Coord_LogDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogDebug'",NULL);
#endif
  {
   self->LogDebug(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogMsg of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogMsg00
static int tolua_coord_coord_Coord_LogMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogMsg'",NULL);
#endif
  {
   self->LogMsg(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogCloseLevel of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogCloseLevel00
static int tolua_coord_coord_Coord_LogCloseLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogCloseLevel'",NULL);
#endif
  {
   self->LogCloseLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogCloseLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogOpenLevel of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogOpenLevel00
static int tolua_coord_coord_Coord_LogOpenLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogOpenLevel'",NULL);
#endif
  {
   self->LogOpenLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogOpenLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogSetLevel of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_LogSetLevel00
static int tolua_coord_coord_Coord_LogSetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogSetLevel'",NULL);
#endif
  {
   self->LogSetLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogSetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CoreLogFatal of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CoreLogFatal00
static int tolua_coord_coord_Coord_CoreLogFatal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CoreLogFatal'",NULL);
#endif
  {
   self->CoreLogFatal(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CoreLogFatal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CoreLogError of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CoreLogError00
static int tolua_coord_coord_Coord_CoreLogError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CoreLogError'",NULL);
#endif
  {
   self->CoreLogError(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CoreLogError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CoreLogWarn of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CoreLogWarn00
static int tolua_coord_coord_Coord_CoreLogWarn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CoreLogWarn'",NULL);
#endif
  {
   self->CoreLogWarn(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CoreLogWarn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CoreLogInfo of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CoreLogInfo00
static int tolua_coord_coord_Coord_CoreLogInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CoreLogInfo'",NULL);
#endif
  {
   self->CoreLogInfo(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CoreLogInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CoreLogDebug of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CoreLogDebug00
static int tolua_coord_coord_Coord_CoreLogDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CoreLogDebug'",NULL);
#endif
  {
   self->CoreLogDebug(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CoreLogDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CoreLogMsg of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CoreLogMsg00
static int tolua_coord_coord_Coord_CoreLogMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Coord* self = (const coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CoreLogMsg'",NULL);
#endif
  {
   self->CoreLogMsg(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CoreLogMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddScript of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_AddScript00
static int tolua_coord_coord_Coord_AddScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddScript'",NULL);
#endif
  {
return self->AddScript(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddComponent of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_AddComponent00
static int tolua_coord_coord_Coord_AddComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  coord::Component* component = ((coord::Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddComponent'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddComponent(component);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTimeout of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_SetTimeout00
static int tolua_coord_coord_Coord_SetTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeout'",NULL);
#endif
  {
return self->SetTimeout(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInterval of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_SetInterval00
static int tolua_coord_coord_Coord_SetInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInterval'",NULL);
#endif
  {
return self->SetInterval(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCron of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_SetCron00
static int tolua_coord_coord_Coord_SetCron00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCron'",NULL);
#endif
  {
return self->SetCron(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCron'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Emit of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Emit00
static int tolua_coord_coord_Coord_Emit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::event::BaseEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::event::BaseEvent* args = ((coord::event::BaseEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Emit'",NULL);
#endif
  {
   self->Emit(name,args);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Emit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destory of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Destory01
static int tolua_coord_coord_Coord_Destory01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Destoryable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  coord::Destoryable* object = ((coord::Destoryable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destory'",NULL);
#endif
  {
   self->Destory(object);
  }
 }
 return 0;
tolua_lerror:
 return tolua_coord_coord_Coord_Destory00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destory of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Destory02
static int tolua_coord_coord_Coord_Destory02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::net::TcpClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  coord::net::TcpClient* object = ((coord::net::TcpClient*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destory'",NULL);
#endif
  {
   self->Destory(object);
  }
 }
 return 0;
tolua_lerror:
 return tolua_coord_coord_Coord_Destory01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: DontDestory of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_DontDestory00
static int tolua_coord_coord_Coord_DontDestory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Destoryable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  coord::Destoryable* object = ((coord::Destoryable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DontDestory'",NULL);
#endif
  {
   self->DontDestory(object);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DontDestory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewHttpServer of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_NewHttpServer00
static int tolua_coord_coord_Coord_NewHttpServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewHttpServer'",NULL);
#endif
  {
   coord::http::HttpServer* tolua_ret = (coord::http::HttpServer*)  self->NewHttpServer();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::http::HttpServer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewHttpServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Now of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Now00
static int tolua_coord_coord_Coord_Now00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Now'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->Now();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Now'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Time of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Time00
static int tolua_coord_coord_Coord_Time00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Time'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->Time();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Time'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NanoTime of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_NanoTime00
static int tolua_coord_coord_Coord_NanoTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NanoTime'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->NanoTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NanoTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SQLConfig of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_SQLConfig00
static int tolua_coord_coord_Coord_SQLConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,"DB"));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SQLConfig'",NULL);
#endif
  {
   coord::sql::SQLClient* tolua_ret = (coord::sql::SQLClient*)  self->SQLConfig(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::sql::SQLClient");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SQLConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RedisConfig of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_RedisConfig00
static int tolua_coord_coord_Coord_RedisConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,"REDIS"));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RedisConfig'",NULL);
#endif
  {
   coord::redis::Client* tolua_ret = (coord::redis::Client*)  self->RedisConfig(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::Client");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RedisConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RedisAsyncConfig of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_RedisAsyncConfig00
static int tolua_coord_coord_Coord_RedisAsyncConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,"REDIS"));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RedisAsyncConfig'",NULL);
#endif
  {
   coord::redis::AsyncClient* tolua_ret = (coord::redis::AsyncClient*)  self->RedisAsyncConfig(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::AsyncClient");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RedisAsyncConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Config of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Config_ptr
static int tolua_get_coord__Coord_Config_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Config'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Config,"coord::Config");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Config of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Config_ptr
static int tolua_set_coord__Coord_Config_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Config'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Config",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Config = ((coord::Config*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Script of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Script_ptr
static int tolua_get_coord__Coord_Script_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Script'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Script,"coord::script::Script");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Script of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Script_ptr
static int tolua_set_coord__Coord_Script_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Script'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::script::Script",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Script = ((coord::script::Script*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Gate of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Gate_ptr
static int tolua_get_coord__Coord_Gate_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gate'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Gate,"coord::gate::Gate");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Gate of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Gate_ptr
static int tolua_set_coord__Coord_Gate_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gate'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::gate::Gate",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Gate = ((coord::gate::Gate*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HttpServer of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_HttpServer_ptr
static int tolua_get_coord__Coord_HttpServer_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HttpServer'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->HttpServer,"coord::http::HttpServer");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: HttpServer of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_HttpServer_ptr
static int tolua_set_coord__Coord_HttpServer_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HttpServer'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::http::HttpServer",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->HttpServer = ((coord::http::HttpServer*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Proto of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Proto_ptr
static int tolua_get_coord__Coord_Proto_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Proto'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Proto,"coord::protobuf::Protobuf");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Proto of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Proto_ptr
static int tolua_set_coord__Coord_Proto_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Proto'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::protobuf::Protobuf",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Proto = ((coord::protobuf::Protobuf*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RedisMgr of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_RedisMgr_ptr
static int tolua_get_coord__Coord_RedisMgr_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RedisMgr'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->RedisMgr,"coord::redis::RedisMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RedisMgr of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_RedisMgr_ptr
static int tolua_set_coord__Coord_RedisMgr_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RedisMgr'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::redis::RedisMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RedisMgr = ((coord::redis::RedisMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Cache of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Cache_ptr
static int tolua_get_coord__Coord_Cache_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cache'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Cache,"coord::cache::Client");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Cache of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Cache_ptr
static int tolua_set_coord__Coord_Cache_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cache'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::cache::Client",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Cache = ((coord::cache::Client*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Cluster of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Cluster_ptr
static int tolua_get_coord__Coord_Cluster_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Cluster,"coord::cluster::Cluster");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Cluster of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Cluster_ptr
static int tolua_set_coord__Coord_Cluster_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::cluster::Cluster",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Cluster = ((coord::cluster::Cluster*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ConfigPath of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_ConfigPath
static int tolua_get_coord__Coord_ConfigPath(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ConfigPath'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ConfigPath);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ConfigPath of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_ConfigPath
static int tolua_set_coord__Coord_ConfigPath(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ConfigPath'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ConfigPath = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Managed of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Managed_ptr
static int tolua_get_coord__Coord_Managed_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Managed'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Managed,"coord::managed::Managed");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Managed of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Managed_ptr
static int tolua_set_coord__Coord_Managed_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Managed'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::managed::Managed",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Managed = ((coord::managed::Managed*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WorkerSlave of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_WorkerSlave_ptr
static int tolua_get_coord__Coord_WorkerSlave_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorkerSlave'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->WorkerSlave,"coord::worker::WorkerSlave");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WorkerSlave of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_WorkerSlave_ptr
static int tolua_set_coord__Coord_WorkerSlave_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorkerSlave'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::worker::WorkerSlave",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WorkerSlave = ((coord::worker::WorkerSlave*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Worker of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Worker_ptr
static int tolua_get_coord__Coord_Worker_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Worker'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Worker,"coord::worker::Worker");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Worker of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Worker_ptr
static int tolua_set_coord__Coord_Worker_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Worker'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::worker::Worker",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Worker = ((coord::worker::Worker*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Name of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Name
static int tolua_get_coord__Coord_Name(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Name of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Name
static int tolua_set_coord__Coord_Name(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Environment of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Environment_ptr
static int tolua_get_coord__Coord_Environment_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Environment'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Environment,"coord::Environment");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Environment of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Environment_ptr
static int tolua_set_coord__Coord_Environment_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Environment'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Environment",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Environment = ((coord::Environment*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Closure of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Closure_ptr
static int tolua_get_coord__Coord_Closure_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Closure'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Closure,"coord::closure::ClosureMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Closure of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Closure_ptr
static int tolua_set_coord__Coord_Closure_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Closure'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::closure::ClosureMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Closure = ((coord::closure::ClosureMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Login of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_Login_ptr
static int tolua_get_coord__Coord_Login_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Login'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Login,"coord::login::LoginSvr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Login of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_Login_ptr
static int tolua_set_coord__Coord_Login_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Login'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::login::LoginSvr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Login = ((coord::login::LoginSvr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Env of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Env
static int tolua_get_coord__BasicConfig_Env(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Env'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Env);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Env of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Env
static int tolua_set_coord__BasicConfig_Env(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Env'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Env = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Main of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Main
static int tolua_get_coord__BasicConfig_Main(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Main'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Main);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Main of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Main
static int tolua_set_coord__BasicConfig_Main(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Main'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Main = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Scene of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Scene
static int tolua_get_coord__BasicConfig_Scene(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Scene'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Scene);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Scene of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Scene
static int tolua_set_coord__BasicConfig_Scene(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Scene'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Scene = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Registery of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Registery
static int tolua_get_coord__BasicConfig_Registery(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Registery'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Registery);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Registery of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Registery
static int tolua_set_coord__BasicConfig_Registery(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Registery'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Registery = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Package of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Package
static int tolua_get_coord__BasicConfig_Package(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Package'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Package);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Package of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Package
static int tolua_set_coord__BasicConfig_Package(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Package'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Package = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: GC of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_GC
static int tolua_get_coord__BasicConfig_GC(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GC'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->GC);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: GC of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_GC
static int tolua_set_coord__BasicConfig_GC(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'GC'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->GC = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Update of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Update
static int tolua_get_coord__BasicConfig_Update(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Update'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Update);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Update of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Update
static int tolua_set_coord__BasicConfig_Update(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Update'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Update = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Worker of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Worker
static int tolua_get_coord__BasicConfig_Worker(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Worker'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Worker);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Worker of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Worker
static int tolua_set_coord__BasicConfig_Worker(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Worker'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Worker = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WorkerNum of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_WorkerNum
static int tolua_get_coord__BasicConfig_WorkerNum(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorkerNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->WorkerNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WorkerNum of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_WorkerNum
static int tolua_set_coord__BasicConfig_WorkerNum(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorkerNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WorkerNum = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Proto of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Proto
static int tolua_get_coord__BasicConfig_Proto(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Proto'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Proto);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Proto of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Proto
static int tolua_set_coord__BasicConfig_Proto(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Proto'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Proto = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Name of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Name
static int tolua_get_coord__BasicConfig_Name(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Name of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Name
static int tolua_set_coord__BasicConfig_Name(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Version of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_Version
static int tolua_get_coord__BasicConfig_Version(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Version'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Version);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Version of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_Version
static int tolua_set_coord__BasicConfig_Version(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Version'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Version = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ShortVersion of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__BasicConfig_ShortVersion
static int tolua_get_coord__BasicConfig_ShortVersion(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ShortVersion'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ShortVersion);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ShortVersion of class  coord::BasicConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__BasicConfig_ShortVersion
static int tolua_set_coord__BasicConfig_ShortVersion(lua_State* tolua_S)
{
  coord::BasicConfig* self = (coord::BasicConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ShortVersion'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ShortVersion = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Basic of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_get_coord__Config_Basic
static int tolua_get_coord__Config_Basic(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Basic'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Basic,"coord::BasicConfig");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Basic of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_set_coord__Config_Basic
static int tolua_set_coord__Config_Basic(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Basic'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::BasicConfig",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Basic = *((coord::BasicConfig*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Web of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_get_coord__Config_Web
static int tolua_get_coord__Config_Web(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Web'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Web,"coord::web::WebConfig");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Web of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_set_coord__Config_Web
static int tolua_set_coord__Config_Web(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Web'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::web::WebConfig",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Web = *((coord::web::WebConfig*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Gate of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_get_coord__Config_Gate
static int tolua_get_coord__Config_Gate(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gate'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Gate,"coord::gate::GateConfig");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Gate of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_set_coord__Config_Gate
static int tolua_set_coord__Config_Gate(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Gate'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::gate::GateConfig",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Gate = *((coord::gate::GateConfig*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Cache of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_get_coord__Config_Cache
static int tolua_get_coord__Config_Cache(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cache'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Cache,"coord::cache::CacheConfig");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Cache of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_set_coord__Config_Cache
static int tolua_set_coord__Config_Cache(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cache'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::cache::CacheConfig",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Cache = *((coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Cluster of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_get_coord__Config_Cluster
static int tolua_get_coord__Config_Cluster(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Cluster,"coord::cluster::ClusterConfig");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Cluster of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_set_coord__Config_Cluster
static int tolua_set_coord__Config_Cluster(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::cluster::ClusterConfig",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Cluster = *((coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Managed of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_get_coord__Config_Managed
static int tolua_get_coord__Config_Managed(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Managed'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Managed,"coord::managed::ManagedConfig");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Managed of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_set_coord__Config_Managed
static int tolua_set_coord__Config_Managed(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Managed'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::managed::ManagedConfig",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Managed = *((coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Login of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_get_coord__Config_Login
static int tolua_get_coord__Config_Login(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Login'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->Login,"coord::login::LoginConfig");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Login of class  coord::Config */
#ifndef TOLUA_DISABLE_tolua_set_coord__Config_Login
static int tolua_set_coord__Config_Login(lua_State* tolua_S)
{
  coord::Config* self = (coord::Config*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Login'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::login::LoginConfig",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Login = *((coord::login::LoginConfig*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToString of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Script_ToString00
static int tolua_coord_coord_script_Script_ToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Script",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToString'",NULL);
#endif
  {
return self->ToString(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToShortString of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Script_ToShortString00
static int tolua_coord_coord_script_Script_ToShortString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Script",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToShortString'",NULL);
#endif
  {
return self->ToShortString(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToShortString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Encode of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Script_Encode00
static int tolua_coord_coord_script_Script_Encode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Script",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Encode'",NULL);
#endif
  {
return self->Encode(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Encode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Decode of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Script_Decode00
static int tolua_coord_coord_script_Script_Decode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Script",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Decode'",NULL);
#endif
  {
return self->Decode(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Decode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToJson of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Script_ToJson00
static int tolua_coord_coord_script_Script_ToJson00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Script",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToJson'",NULL);
#endif
  {
return self->ToJson(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToJson'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FromJson of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Script_FromJson00
static int tolua_coord_coord_script_Script_FromJson00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Script",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FromJson'",NULL);
#endif
  {
return self->FromJson(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FromJson'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Path of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_get_coord__script__Script_Path
static int tolua_get_coord__script__Script_Path(lua_State* tolua_S)
{
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Path'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->Path);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Path of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_set_coord__script__Script_Path
static int tolua_set_coord__script__Script_Path(lua_State* tolua_S)
{
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Path'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->Path,tolua_tostring(tolua_S,2,0),PACKAGE_MAX+1-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Main of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_get_coord__script__Script_Main
static int tolua_get_coord__script__Script_Main(lua_State* tolua_S)
{
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Main'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->Main);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Main of class  coord::script::Script */
#ifndef TOLUA_DISABLE_tolua_set_coord__script__Script_Main
static int tolua_set_coord__script__Script_Main(lua_State* tolua_S)
{
  coord::script::Script* self = (coord::script::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Main'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->Main,tolua_tostring(tolua_S,2,0),PACKAGE_MAX+1-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBool of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetBool00
static int tolua_coord_coord_script_Reflect_SetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBool'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetBool(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetString of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetString00
static int tolua_coord_coord_script_Reflect_SetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetString'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetString(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumber of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetNumber00
static int tolua_coord_coord_script_Reflect_SetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"lua_Number",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  lua_Number value = *((lua_Number*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumber'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetNumber(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTable of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetTable00
static int tolua_coord_coord_script_Reflect_SetTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTable'",NULL);
#endif
  {
   coord::script::Reflect tolua_ret = (coord::script::Reflect)  self->SetTable(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::script::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::script::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::script::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::script::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBool of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetBool01
static int tolua_coord_coord_script_Reflect_SetBool01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBool'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetBool(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_script_Reflect_SetBool00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetString of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetString01
static int tolua_coord_coord_script_Reflect_SetString01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetString'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetString(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_script_Reflect_SetString00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumber of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetNumber01
static int tolua_coord_coord_script_Reflect_SetNumber01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"lua_Number",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  lua_Number value = *((lua_Number*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumber'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetNumber(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_script_Reflect_SetNumber00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTable of class  coord::script::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_script_Reflect_SetTable01
static int tolua_coord_coord_script_Reflect_SetTable01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::script::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::script::Reflect* self = (coord::script::Reflect*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTable'",NULL);
#endif
  {
   coord::script::Reflect tolua_ret = (coord::script::Reflect)  self->SetTable(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::script::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::script::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::script::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::script::Reflect");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_script_Reflect_SetTable00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumber of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_GetNumber00
static int tolua_coord_coord_Argument_GetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumber'",NULL);
#endif
  {
   int64_t tolua_ret = (int64_t)  self->GetNumber(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBool of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_GetBool00
static int tolua_coord_coord_Argument_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBool(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetString of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_GetString00
static int tolua_coord_coord_Argument_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetString'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetString(index);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProto of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_GetProto00
static int tolua_coord_coord_Argument_GetProto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProto'",NULL);
#endif
  {
   coord::protobuf::Reflect& tolua_ret = (coord::protobuf::Reflect&)  self->GetProto(index);
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"coord::protobuf::Reflect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProto'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTable of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_GetTable00
static int tolua_coord_coord_Argument_GetTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTable'",NULL);
#endif
  {
   coord::script::Reflect& tolua_ret = (coord::script::Reflect&)  self->GetTable(index);
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"coord::script::Reflect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNone of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_IsNone00
static int tolua_coord_coord_Argument_IsNone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNone'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNone(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNil of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_IsNil00
static int tolua_coord_coord_Argument_IsNil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNil'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNil(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNil'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNumber of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_IsNumber00
static int tolua_coord_coord_Argument_IsNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNumber'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNumber(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsString of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_IsString00
static int tolua_coord_coord_Argument_IsString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsString'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsString(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsProto of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_IsProto00
static int tolua_coord_coord_Argument_IsProto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsProto'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsProto(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsProto'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBool of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_IsBool00
static int tolua_coord_coord_Argument_IsBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBool(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTable of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_IsTable00
static int tolua_coord_coord_Argument_IsTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTable'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsTable(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNumber of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_AddNumber00
static int tolua_coord_coord_Argument_AddNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  int64_t value = ((int64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNumber'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddNumber(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddString of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_AddString00
static int tolua_coord_coord_Argument_AddString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddString'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddString(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNil of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_AddNil00
static int tolua_coord_coord_Argument_AddNil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNil'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddNil();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNil'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddBool of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_AddBool00
static int tolua_coord_coord_Argument_AddBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddBool'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddBool(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Count of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_Count00
static int tolua_coord_coord_Argument_Count00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Count'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Count();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Count'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Trace of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_Trace00
static int tolua_coord_coord_Argument_Trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Trace'",NULL);
#endif
  {
   self->Trace();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Pack of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_Pack00
static int tolua_coord_coord_Argument_Pack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Pack'",NULL);
#endif
  {
return self->Pack(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Pack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Unpack of class  coord::Argument */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Argument_Unpack00
static int tolua_coord_coord_Argument_Unpack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Argument",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Argument* self = (coord::Argument*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Unpack'",NULL);
#endif
  {
return self->Unpack(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Unpack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Environment_Get00
static int tolua_coord_coord_Environment_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Environment",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
  {
return self->Get(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Version of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_Version
static int tolua_get_coord__Environment_Version(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Version'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Version);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Version of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_Version
static int tolua_set_coord__Environment_Version(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Version'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Version = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ExecPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_ExecPath
static int tolua_get_coord__Environment_ExecPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ExecPath'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ExecPath);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ExecPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_ExecPath
static int tolua_set_coord__Environment_ExecPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ExecPath'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ExecPath = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ExecDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_ExecDir
static int tolua_get_coord__Environment_ExecDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ExecDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ExecDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ExecDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_ExecDir
static int tolua_set_coord__Environment_ExecDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ExecDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ExecDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ProjectDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_ProjectDir
static int tolua_get_coord__Environment_ProjectDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ProjectDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ProjectDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ProjectDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_ProjectDir
static int tolua_set_coord__Environment_ProjectDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ProjectDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ProjectDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: WorkingDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_WorkingDir
static int tolua_get_coord__Environment_WorkingDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorkingDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->WorkingDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: WorkingDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_WorkingDir
static int tolua_set_coord__Environment_WorkingDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'WorkingDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->WorkingDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HomeDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_HomeDir
static int tolua_get_coord__Environment_HomeDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HomeDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->HomeDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: HomeDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_HomeDir
static int tolua_set_coord__Environment_HomeDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HomeDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->HomeDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: CoordDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_CoordDir
static int tolua_get_coord__Environment_CoordDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CoordDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->CoordDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: CoordDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_CoordDir
static int tolua_set_coord__Environment_CoordDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CoordDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->CoordDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ConfigPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_ConfigPath
static int tolua_get_coord__Environment_ConfigPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ConfigPath'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ConfigPath);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ConfigPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_ConfigPath
static int tolua_set_coord__Environment_ConfigPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ConfigPath'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ConfigPath = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ConfigDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_ConfigDir
static int tolua_get_coord__Environment_ConfigDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ConfigDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ConfigDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ConfigDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_ConfigDir
static int tolua_set_coord__Environment_ConfigDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ConfigDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ConfigDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Package of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_Package
static int tolua_get_coord__Environment_Package(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Package'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Package);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Package of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_Package
static int tolua_set_coord__Environment_Package(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Package'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Package = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ProcDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_ProcDir
static int tolua_get_coord__Environment_ProcDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ProcDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ProcDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ProcDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_ProcDir
static int tolua_set_coord__Environment_ProcDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ProcDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ProcDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RunDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_RunDir
static int tolua_get_coord__Environment_RunDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RunDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->RunDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RunDir of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_RunDir
static int tolua_set_coord__Environment_RunDir(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RunDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RunDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: PidPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_PidPath
static int tolua_get_coord__Environment_PidPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'PidPath'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->PidPath);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: PidPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_PidPath
static int tolua_set_coord__Environment_PidPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'PidPath'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->PidPath = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Name of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_Name
static int tolua_get_coord__Environment_Name(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Name of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_Name
static int tolua_set_coord__Environment_Name(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ManagedSockPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_get_coord__Environment_ManagedSockPath
static int tolua_get_coord__Environment_ManagedSockPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ManagedSockPath'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ManagedSockPath);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ManagedSockPath of class  coord::Environment */
#ifndef TOLUA_DISABLE_tolua_set_coord__Environment_ManagedSockPath
static int tolua_set_coord__Environment_ManagedSockPath(lua_State* tolua_S)
{
  coord::Environment* self = (coord::Environment*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ManagedSockPath'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ManagedSockPath = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_Proto00
static int tolua_coord_coord_BaseRequest_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::protobuf::Reflect& tolua_ret = (coord::protobuf::Reflect&)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"coord::protobuf::Reflect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Proto'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_String00
static int tolua_coord_coord_BaseRequest_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->String();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'String'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Len of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_Len00
static int tolua_coord_coord_BaseRequest_Len00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Len'",NULL);
#endif
  {
   size_t tolua_ret = (size_t)  self->Len();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Len'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Args of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_Args00
static int tolua_coord_coord_BaseRequest_Args00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Args'",NULL);
#endif
  {
   coord::Argument* tolua_ret = (coord::Argument*)  self->Args();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Argument");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Args'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_String01
static int tolua_coord_coord_BaseRequest_String01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
return self->String(L);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_BaseRequest_String00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Unpack of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_Unpack00
static int tolua_coord_coord_BaseRequest_Unpack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Unpack'",NULL);
#endif
  {
return self->Unpack(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Unpack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Table of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_Table00
static int tolua_coord_coord_BaseRequest_Table00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Table'",NULL);
#endif
  {
return self->Table(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Table'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Json of class  coord::BaseRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseRequest_Json00
static int tolua_coord_coord_BaseRequest_Json00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseRequest* self = (coord::BaseRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Json'",NULL);
#endif
  {
   coord::json::Reflect tolua_ret = (coord::json::Reflect)  self->Json();
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::json::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::json::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Json'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Proto00
static int tolua_coord_coord_BaseResponse_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::protobuf::Reflect& tolua_ret = (coord::protobuf::Reflect&)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"coord::protobuf::Reflect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Proto'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Proto01
static int tolua_coord_coord_BaseResponse_Proto01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
  coord::protobuf::Reflect* proto = ((coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Proto(*proto);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_BaseResponse_Proto00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Proto02
static int tolua_coord_coord_BaseResponse_Proto02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::protobuf::Reflect& tolua_ret = (coord::protobuf::Reflect&)  self->Proto();
   tolua_pushusertype(tolua_S,(void*)&tolua_ret,"coord::protobuf::Reflect");
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_BaseResponse_Proto01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_String00
static int tolua_coord_coord_BaseResponse_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   int tolua_ret = (int)  self->String(data);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'String'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Args of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Args00
static int tolua_coord_coord_BaseResponse_Args00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Args'",NULL);
#endif
  {
   coord::Argument* tolua_ret = (coord::Argument*)  self->Args();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Argument");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Args'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Pack of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Pack00
static int tolua_coord_coord_BaseResponse_Pack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Pack'",NULL);
#endif
  {
return self->Pack(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Pack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Table of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Table00
static int tolua_coord_coord_BaseResponse_Table00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Table'",NULL);
#endif
  {
return self->Table(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Table'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Resolve of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Resolve00
static int tolua_coord_coord_BaseResponse_Resolve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Resolve'",NULL);
#endif
  {
   self->Resolve();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Resolve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reject of class  coord::BaseResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_BaseResponse_Reject00
static int tolua_coord_coord_BaseResponse_Reject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::BaseResponse",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::BaseResponse* self = (coord::BaseResponse*)  tolua_tousertype(tolua_S,1,0);
  int code = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reject'",NULL);
#endif
  {
   self->Reject(code);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Code of class  coord::BaseResult */
#ifndef TOLUA_DISABLE_tolua_get_coord__BaseResult_Code
static int tolua_get_coord__BaseResult_Code(lua_State* tolua_S)
{
  coord::BaseResult* self = (coord::BaseResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Code'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Code);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Code of class  coord::BaseResult */
#ifndef TOLUA_DISABLE_tolua_set_coord__BaseResult_Code
static int tolua_set_coord__BaseResult_Code(lua_State* tolua_S)
{
  coord::BaseResult* self = (coord::BaseResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Code'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Code = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Then of class  coord::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Promise_Then00
static int tolua_coord_coord_Promise_Then00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Promise* self = (coord::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Then'",NULL);
#endif
  {
return self->Then(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Then'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Else of class  coord::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Promise_Else00
static int tolua_coord_coord_Promise_Else00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Promise* self = (coord::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Else'",NULL);
#endif
  {
return self->Else(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Else'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Create of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_Create00
static int tolua_coord_coord_Object_Create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Create'",NULL);
#endif
  {
   self->Create();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Save of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_Save00
static int tolua_coord_coord_Object_Save00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Save'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Save();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Save'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddComponent of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_AddComponent00
static int tolua_coord_coord_Object_AddComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  coord::Component* component = ((coord::Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddComponent'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddComponent(component);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddScript of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_AddScript00
static int tolua_coord_coord_Object_AddScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddScript'",NULL);
#endif
  {
return self->AddScript(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveComponent of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_RemoveComponent00
static int tolua_coord_coord_Object_RemoveComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  coord::Component* component = ((coord::Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveComponent'",NULL);
#endif
  {
   int tolua_ret = (int)  self->RemoveComponent(component);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetComponent of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_GetComponent00
static int tolua_coord_coord_Object_GetComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Type",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  coord::Type* type = ((coord::Type*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetComponent'",NULL);
#endif
  {
   coord::Component* tolua_ret = (coord::Component*)  self->GetComponent(type);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Component");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetComponent of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_GetComponent01
static int tolua_coord_coord_Object_GetComponent01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetComponent'",NULL);
#endif
  {
   coord::Component* tolua_ret = (coord::Component*)  self->GetComponent(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Component");
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_Object_GetComponent00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetComponent of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_GetComponent02
static int tolua_coord_coord_Object_GetComponent02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetComponent'",NULL);
#endif
  {
return self->GetComponent(L);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_Object_GetComponent01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScript of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_GetScript00
static int tolua_coord_coord_Object_GetScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  const char* classname = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScript'",NULL);
#endif
  {
   coord::ScriptComponent* tolua_ret = (coord::ScriptComponent*)  self->GetScript(classname);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::ScriptComponent");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_GetChild00
static int tolua_coord_coord_Object_GetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'",NULL);
#endif
  {
   coord::Object* tolua_ret = (coord::Object*)  self->GetChild(index);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Object");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_GetParent00
static int tolua_coord_coord_Object_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'",NULL);
#endif
  {
   coord::Object* tolua_ret = (coord::Object*)  self->GetParent();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Object");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddChild of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_AddChild00
static int tolua_coord_coord_Object_AddChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  coord::Object* obj = ((coord::Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddChild'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddChild(obj);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChildIndex of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_ChildIndex00
static int tolua_coord_coord_Object_ChildIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  coord::Object* obj = ((coord::Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChildIndex'",NULL);
#endif
  {
   int tolua_ret = (int)  self->ChildIndex(obj);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChildIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Trace of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_Trace00
static int tolua_coord_coord_Object_Trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  int deep = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Trace'",NULL);
#endif
  {
   self->Trace(deep);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_get_coord__Object_id
static int tolua_get_coord__Object_id(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: id of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_set_coord__Object_id
static int tolua_set_coord__Object_id(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->id = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: data of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_get_coord__Object_data
static int tolua_get_coord__Object_data(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
#endif
  tolua_pushuserdata(tolua_S,(void*)self->data);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: data of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_set_coord__Object_data
static int tolua_set_coord__Object_data(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'data'",NULL);
  if (!tolua_isuserdata(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->data = ((void*)  tolua_touserdata(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_get_coord__Object_name
static int tolua_get_coord__Object_name(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_set_coord__Object_name
static int tolua_set_coord__Object_name(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->name,tolua_tostring(tolua_S,2,0),64-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: transform of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_get_coord__Object_transform_ptr
static int tolua_get_coord__Object_transform_ptr(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transform'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->transform,"coord::Transform");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: transform of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_set_coord__Object_transform_ptr
static int tolua_set_coord__Object_transform_ptr(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transform'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Transform",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->transform = ((coord::Transform*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scene of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_get_coord__Object_scene_ptr
static int tolua_get_coord__Object_scene_ptr(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->scene,"coord::Scene");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scene of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_set_coord__Object_scene_ptr
static int tolua_set_coord__Object_scene_ptr(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Scene",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scene = ((coord::Scene*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: coord of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_get_coord__Object_coord_ptr
static int tolua_get_coord__Object_coord_ptr(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'coord'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->coord,"coord::Coord");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: coord of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_set_coord__Object_coord_ptr
static int tolua_set_coord__Object_coord_ptr(lua_State* tolua_S)
{
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'coord'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instantiate of class  coord::Scene */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Scene_Instantiate00
static int tolua_coord_coord_Scene_Instantiate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Scene",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Scene* self = (coord::Scene*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* filePath = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Instantiate'",NULL);
#endif
  {
   coord::Object* tolua_ret = (coord::Object*)  self->Instantiate(name,filePath);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Object");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instantiate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateObject of class  coord::Scene */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Scene_CreateObject00
static int tolua_coord_coord_Scene_CreateObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Scene",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Scene* self = (coord::Scene*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateObject'",NULL);
#endif
  {
   coord::Object* tolua_ret = (coord::Object*)  self->CreateObject(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Object");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  coord::Scene */
#ifndef TOLUA_DISABLE_tolua_get_coord__Scene_name
static int tolua_get_coord__Scene_name(lua_State* tolua_S)
{
  coord::Scene* self = (coord::Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  coord::Scene */
#ifndef TOLUA_DISABLE_tolua_set_coord__Scene_name
static int tolua_set_coord__Scene_name(lua_State* tolua_S)
{
  coord::Scene* self = (coord::Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->name,tolua_tostring(tolua_S,2,0),64-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetComponent of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_GetComponent00
static int tolua_coord_coord_Component_GetComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetComponent'",NULL);
#endif
  {
   coord::Component* tolua_ret = (coord::Component*)  self->GetComponent(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Component");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddHttpRouterGet of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_AddHttpRouterGet00
static int tolua_coord_coord_Component_AddHttpRouterGet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* pattern = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* callback = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddHttpRouterGet'",NULL);
#endif
  {
   self->AddHttpRouterGet(pattern,callback);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddHttpRouterGet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Log of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_Log00
static int tolua_coord_coord_Component_Log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Component* self = (const coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Log'",NULL);
#endif
  {
   self->Log(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogFatal of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_LogFatal00
static int tolua_coord_coord_Component_LogFatal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Component* self = (const coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogFatal'",NULL);
#endif
  {
   self->LogFatal(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogFatal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogError of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_LogError00
static int tolua_coord_coord_Component_LogError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Component* self = (const coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogError'",NULL);
#endif
  {
   self->LogError(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogWarn of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_LogWarn00
static int tolua_coord_coord_Component_LogWarn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Component* self = (const coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogWarn'",NULL);
#endif
  {
   self->LogWarn(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogWarn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogInfo of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_LogInfo00
static int tolua_coord_coord_Component_LogInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Component* self = (const coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogInfo'",NULL);
#endif
  {
   self->LogInfo(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogDebug of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_LogDebug00
static int tolua_coord_coord_Component_LogDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Component* self = (const coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogDebug'",NULL);
#endif
  {
   self->LogDebug(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogMsg of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_LogMsg00
static int tolua_coord_coord_Component_LogMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::Component",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::Component* self = (const coord::Component*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogMsg'",NULL);
#endif
  {
   self->LogMsg(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: object of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_get_coord__Component_object_ptr
static int tolua_get_coord__Component_object_ptr(lua_State* tolua_S)
{
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'object'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->object,"coord::Object");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: object of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_set_coord__Component_object_ptr
static int tolua_set_coord__Component_object_ptr(lua_State* tolua_S)
{
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'object'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Object",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->object = ((coord::Object*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scene of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_get_coord__Component_scene_ptr
static int tolua_get_coord__Component_scene_ptr(lua_State* tolua_S)
{
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->scene,"coord::Scene");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scene of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_set_coord__Component_scene_ptr
static int tolua_set_coord__Component_scene_ptr(lua_State* tolua_S)
{
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Scene",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scene = ((coord::Scene*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: coord of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_get_coord__Component_coord_ptr
static int tolua_get_coord__Component_coord_ptr(lua_State* tolua_S)
{
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'coord'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->coord,"coord::Coord");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: coord of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_set_coord__Component_coord_ptr
static int tolua_set_coord__Component_coord_ptr(lua_State* tolua_S)
{
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'coord'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_Host
static int tolua_get_coord__http__HttpServerConfig_Host(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_Host
static int tolua_set_coord__http__HttpServerConfig_Host(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_unsigned_Port
static int tolua_get_coord__http__HttpServerConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_unsigned_Port
static int tolua_set_coord__http__HttpServerConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Backlog of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_Backlog
static int tolua_get_coord__http__HttpServerConfig_Backlog(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Backlog);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Backlog of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_Backlog
static int tolua_set_coord__http__HttpServerConfig_Backlog(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Backlog = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLEncrypt of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_SSLEncrypt
static int tolua_get_coord__http__HttpServerConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->SSLEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLEncrypt of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_SSLEncrypt
static int tolua_set_coord__http__HttpServerConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLEncrypt = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLPemFile of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_SSLPemFile
static int tolua_get_coord__http__HttpServerConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLPemFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLPemFile of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_SSLPemFile
static int tolua_set_coord__http__HttpServerConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLPemFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLKeyFile of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_SSLKeyFile
static int tolua_get_coord__http__HttpServerConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLKeyFile of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_SSLKeyFile
static int tolua_set_coord__http__HttpServerConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLKeyFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RecvBufferSize of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_RecvBufferSize
static int tolua_get_coord__http__HttpServerConfig_RecvBufferSize(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBufferSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RecvBufferSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RecvBufferSize of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_RecvBufferSize
static int tolua_set_coord__http__HttpServerConfig_RecvBufferSize(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBufferSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RecvBufferSize = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: AssetDir of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_AssetDir
static int tolua_get_coord__http__HttpServerConfig_AssetDir(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AssetDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->AssetDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: AssetDir of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_AssetDir
static int tolua_set_coord__http__HttpServerConfig_AssetDir(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AssetDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->AssetDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UseEtag of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_UseEtag
static int tolua_get_coord__http__HttpServerConfig_UseEtag(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UseEtag'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->UseEtag);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UseEtag of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_UseEtag
static int tolua_set_coord__http__HttpServerConfig_UseEtag(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UseEtag'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UseEtag = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Start of class  coord::http::HttpServer */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpServer_Start00
static int tolua_coord_coord_http_HttpServer_Start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpServer* self = (coord::http::HttpServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Start'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Start();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefaultConfig of class  coord::http::HttpServer */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpServer_DefaultConfig00
static int tolua_coord_coord_http_HttpServer_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpServer* self = (coord::http::HttpServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::http::HttpServerConfig* tolua_ret = (coord::http::HttpServerConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::http::HttpServerConfig");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefaultConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Router of class  coord::http::HttpServer */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServer_Router_ptr
static int tolua_get_coord__http__HttpServer_Router_ptr(lua_State* tolua_S)
{
  coord::http::HttpServer* self = (coord::http::HttpServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Router,"coord::http::HttpRouter");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Router of class  coord::http::HttpServer */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServer_Router_ptr
static int tolua_set_coord__http__HttpServer_Router_ptr(lua_State* tolua_S)
{
  coord::http::HttpServer* self = (coord::http::HttpServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::http::HttpRouter",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Router = ((coord::http::HttpRouter*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __Destoryable__ of class  coord::http::HttpServer */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServer___Destoryable__
static int tolua_get_coord__http__HttpServer___Destoryable__(lua_State* tolua_S)
{
  coord::http::HttpServer* self = (coord::http::HttpServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__Destoryable__'",NULL);
#endif
#ifdef __cplusplus
  tolua_pushusertype(tolua_S,(void*)static_cast<coord::Destoryable*>(self), "coord::Destoryable");
#else
  tolua_pushusertype(tolua_S,(void*)((coord::Destoryable*)self), "coord::Destoryable");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeader of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRequest_GetHeader00
static int tolua_coord_coord_http_HttpRequest_GetHeader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* field = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeader'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetHeader(field);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasHeader of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRequest_HasHeader00
static int tolua_coord_coord_http_HttpRequest_HasHeader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* field = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasHeader'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasHeader(field,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasHeader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResponse of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRequest_GetResponse00
static int tolua_coord_coord_http_HttpRequest_GetResponse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResponse'",NULL);
#endif
  {
   coord::http::HttpResponse* tolua_ret = (coord::http::HttpResponse*)  self->GetResponse();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::http::HttpResponse");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResponse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Method of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_Method
static int tolua_get_coord__http__HttpRequest_Method(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Method'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Method);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Method of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_Method
static int tolua_set_coord__http__HttpRequest_Method(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Method'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Method = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Url of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_Url
static int tolua_get_coord__http__HttpRequest_Url(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Url'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Url);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Url of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_Url
static int tolua_set_coord__http__HttpRequest_Url(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Url'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Url = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Path of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_Path
static int tolua_get_coord__http__HttpRequest_Path(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Path'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Path);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Path of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_Path
static int tolua_set_coord__http__HttpRequest_Path(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Path'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Path = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Query of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_Query
static int tolua_get_coord__http__HttpRequest_Query(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Query'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Query);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Query of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_Query
static int tolua_set_coord__http__HttpRequest_Query(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Query'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Query = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Schema of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_Schema
static int tolua_get_coord__http__HttpRequest_Schema(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Schema'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Schema);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Schema of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_Schema
static int tolua_set_coord__http__HttpRequest_Schema(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Schema'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Schema = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_Host
static int tolua_get_coord__http__HttpRequest_Host(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_Host
static int tolua_set_coord__http__HttpRequest_Host(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RemoteAddr of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_RemoteAddr
static int tolua_get_coord__http__HttpRequest_RemoteAddr(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RemoteAddr'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->RemoteAddr);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RemoteAddr of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_RemoteAddr
static int tolua_set_coord__http__HttpRequest_RemoteAddr(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RemoteAddr'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RemoteAddr = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Text of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_Text00
static int tolua_coord_coord_http_HttpResponse_Text00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Text'",NULL);
#endif
  {
return self->Text(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Text'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Text of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_Text01
static int tolua_coord_coord_http_HttpResponse_Text01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* content = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Text'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Text(content);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_http_HttpResponse_Text00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Json of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_Json00
static int tolua_coord_coord_http_HttpResponse_Json00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
  coord::json::Reflect* json = ((coord::json::Reflect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Json'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Json(*json);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Json'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Upgrade of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_Upgrade00
static int tolua_coord_coord_http_HttpResponse_Upgrade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Upgrade'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Upgrade();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Upgrade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PageNotFound of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_PageNotFound00
static int tolua_coord_coord_http_HttpResponse_PageNotFound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PageNotFound'",NULL);
#endif
  {
   self->PageNotFound();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PageNotFound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Exception of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_Exception00
static int tolua_coord_coord_http_HttpResponse_Exception00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* msg = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exception'",NULL);
#endif
  {
   self->Exception(msg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Exception'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStatusCode of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_SetStatusCode00
static int tolua_coord_coord_http_HttpResponse_SetStatusCode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
  int code = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStatusCode'",NULL);
#endif
  {
   self->SetStatusCode(code);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStatusCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: File of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_File00
static int tolua_coord_coord_http_HttpResponse_File00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpResponse* self = (coord::http::HttpResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'File'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->File(path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'File'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  coord::http::HttpRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRouter_Get00
static int tolua_coord_coord_http_HttpRouter_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRouter* self = (coord::http::HttpRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
  {
return self->Get(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Post of class  coord::http::HttpRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRouter_Post00
static int tolua_coord_coord_http_HttpRouter_Post00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRouter* self = (coord::http::HttpRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Post'",NULL);
#endif
  {
return self->Post(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Post'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Static of class  coord::http::HttpRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRouter_Static00
static int tolua_coord_coord_http_HttpRouter_Static00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRouter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRouter* self = (coord::http::HttpRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* dir = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Static'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Static(url,dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Static'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StaticFile of class  coord::http::HttpRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRouter_StaticFile00
static int tolua_coord_coord_http_HttpRouter_StaticFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRouter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRouter* self = (coord::http::HttpRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* path = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StaticFile'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->StaticFile(url,path);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StaticFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Trace of class  coord::http::HttpRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRouter_Trace00
static int tolua_coord_coord_http_HttpRouter_Trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRouter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRouter* self = (coord::http::HttpRouter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Trace'",NULL);
#endif
  {
   self->Trace();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __net of class  coord::http::HttpAgent */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpAgent___net__ITcpAgentHandler__
static int tolua_get_coord__http__HttpAgent___net__ITcpAgentHandler__(lua_State* tolua_S)
{
  coord::http::HttpAgent* self = (coord::http::HttpAgent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__net'",NULL);
#endif
#ifdef __cplusplus
  tolua_pushusertype(tolua_S,(void*)static_cast<coord::net::ITcpAgentHandler*>(self), "coord::net::ITcpAgentHandler");
#else
  tolua_pushusertype(tolua_S,(void*)((coord::net::ITcpAgentHandler*)self), "coord::net::ITcpAgentHandler");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_Port
static int tolua_get_coord__web__WebConfig_Port(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_Port
static int tolua_set_coord__web__WebConfig_Port(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_Host
static int tolua_get_coord__web__WebConfig_Host(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_Host
static int tolua_set_coord__web__WebConfig_Host(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Backlog of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_Backlog
static int tolua_get_coord__web__WebConfig_Backlog(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Backlog);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Backlog of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_Backlog
static int tolua_set_coord__web__WebConfig_Backlog(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Backlog = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RecvBuffer of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_RecvBuffer
static int tolua_get_coord__web__WebConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBuffer'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RecvBuffer);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RecvBuffer of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_RecvBuffer
static int tolua_set_coord__web__WebConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBuffer'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RecvBuffer = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLEncrypt of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_SSLEncrypt
static int tolua_get_coord__web__WebConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->SSLEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLEncrypt of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_SSLEncrypt
static int tolua_set_coord__web__WebConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLEncrypt = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLPemFile of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_SSLPemFile
static int tolua_get_coord__web__WebConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLPemFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLPemFile of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_SSLPemFile
static int tolua_set_coord__web__WebConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLPemFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLKeyFile of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_SSLKeyFile
static int tolua_get_coord__web__WebConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLKeyFile of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_SSLKeyFile
static int tolua_set_coord__web__WebConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLKeyFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: AssetDir of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_AssetDir
static int tolua_get_coord__web__WebConfig_AssetDir(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AssetDir'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->AssetDir);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: AssetDir of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_AssetDir
static int tolua_set_coord__web__WebConfig_AssetDir(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'AssetDir'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->AssetDir = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UseEtag of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__web__WebConfig_UseEtag
static int tolua_get_coord__web__WebConfig_UseEtag(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UseEtag'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->UseEtag);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UseEtag of class  coord::web::WebConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__web__WebConfig_UseEtag
static int tolua_set_coord__web__WebConfig_UseEtag(lua_State* tolua_S)
{
  coord::web::WebConfig* self = (coord::web::WebConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UseEtag'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UseEtag = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_Host
static int tolua_get_coord__websocket__WebSocketServerConfig_Host(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_Host
static int tolua_set_coord__websocket__WebSocketServerConfig_Host(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_unsigned_Port
static int tolua_get_coord__websocket__WebSocketServerConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_unsigned_Port
static int tolua_set_coord__websocket__WebSocketServerConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Backlog of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_Backlog
static int tolua_get_coord__websocket__WebSocketServerConfig_Backlog(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Backlog);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Backlog of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_Backlog
static int tolua_set_coord__websocket__WebSocketServerConfig_Backlog(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Backlog = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLEncrypt of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_SSLEncrypt
static int tolua_get_coord__websocket__WebSocketServerConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->SSLEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLEncrypt of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_SSLEncrypt
static int tolua_set_coord__websocket__WebSocketServerConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLEncrypt = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLPemFile of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_SSLPemFile
static int tolua_get_coord__websocket__WebSocketServerConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLPemFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLPemFile of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_SSLPemFile
static int tolua_set_coord__websocket__WebSocketServerConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLPemFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLKeyFile of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_SSLKeyFile
static int tolua_get_coord__websocket__WebSocketServerConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLKeyFile of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_SSLKeyFile
static int tolua_set_coord__websocket__WebSocketServerConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLKeyFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RecvBufferSize of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_RecvBufferSize
static int tolua_get_coord__websocket__WebSocketServerConfig_RecvBufferSize(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBufferSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RecvBufferSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RecvBufferSize of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_RecvBufferSize
static int tolua_set_coord__websocket__WebSocketServerConfig_RecvBufferSize(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBufferSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RecvBufferSize = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Start of class  coord::websocket::Server */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_Server_Start00
static int tolua_coord_coord_websocket_Server_Start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::Server",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::Server* self = (coord::websocket::Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Start'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Start();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefaultConfig of class  coord::websocket::Server */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_Server_DefaultConfig00
static int tolua_coord_coord_websocket_Server_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::Server",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::Server* self = (coord::websocket::Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::websocket::WebSocketServerConfig* tolua_ret = (coord::websocket::WebSocketServerConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::websocket::WebSocketServerConfig");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefaultConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Router of class  coord::websocket::Server */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__Server_Router_ptr
static int tolua_get_coord__websocket__Server_Router_ptr(lua_State* tolua_S)
{
  coord::websocket::Server* self = (coord::websocket::Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Router,"coord::websocket::Router");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Router of class  coord::websocket::Server */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__Server_Router_ptr
static int tolua_set_coord__websocket__Server_Router_ptr(lua_State* tolua_S)
{
  coord::websocket::Server* self = (coord::websocket::Server*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::websocket::Router",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Router = ((coord::websocket::Router*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Message of class  coord::websocket::Router */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_Router_Message00
static int tolua_coord_coord_websocket_Router_Message00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::Router",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::Router* self = (coord::websocket::Router*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Message'",NULL);
#endif
  {
return self->Message(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Message'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendBinaryFrame of class  coord::websocket::Agent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_Agent_SendBinaryFrame00
static int tolua_coord_coord_websocket_Agent_SendBinaryFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::Agent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::Agent* self = (coord::websocket::Agent*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
  size_t len = ((size_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendBinaryFrame'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SendBinaryFrame(data,len);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendBinaryFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendStringFrame of class  coord::websocket::Agent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_Agent_SendStringFrame00
static int tolua_coord_coord_websocket_Agent_SendStringFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::Agent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::Agent* self = (coord::websocket::Agent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendStringFrame'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SendStringFrame(str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendStringFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __http of class  coord::websocket::Agent */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__Agent___http__IHttpAgentHandler__
static int tolua_get_coord__websocket__Agent___http__IHttpAgentHandler__(lua_State* tolua_S)
{
  coord::websocket::Agent* self = (coord::websocket::Agent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__http'",NULL);
#endif
#ifdef __cplusplus
  tolua_pushusertype(tolua_S,(void*)static_cast<coord::http::IHttpAgentHandler*>(self), "coord::http::IHttpAgentHandler");
#else
  tolua_pushusertype(tolua_S,(void*)((coord::http::IHttpAgentHandler*)self), "coord::http::IHttpAgentHandler");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddHttpGet of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_AddHttpGet00
static int tolua_coord_coord_ScriptComponent_AddHttpGet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* pattern = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* callback = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddHttpGet'",NULL);
#endif
  {
   self->AddHttpGet(pattern,callback);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddHttpGet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTimeout of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_SetTimeout00
static int tolua_coord_coord_ScriptComponent_SetTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::ScriptComponent",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeout'",NULL);
#endif
  {
return self->SetTimeout(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInterval of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_SetInterval00
static int tolua_coord_coord_ScriptComponent_SetInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::ScriptComponent",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInterval'",NULL);
#endif
  {
return self->SetInterval(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearInterval of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_ClearInterval00
static int tolua_coord_coord_ScriptComponent_ClearInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearInterval'",NULL);
#endif
  {
   self->ClearInterval(id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Log of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_Log00
static int tolua_coord_coord_ScriptComponent_Log00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::ScriptComponent",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Log'",NULL);
#endif
  {
return self->Log(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Log'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Log of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_Log01
static int tolua_coord_coord_ScriptComponent_Log01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const coord::ScriptComponent* self = (const coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Log'",NULL);
#endif
  {
   self->Log(str);
  }
 }
 return 0;
tolua_lerror:
 return tolua_coord_coord_ScriptComponent_Log00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogFatal of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_LogFatal00
static int tolua_coord_coord_ScriptComponent_LogFatal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::ScriptComponent* self = (const coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogFatal'",NULL);
#endif
  {
   self->LogFatal(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogFatal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogError of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_LogError00
static int tolua_coord_coord_ScriptComponent_LogError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::ScriptComponent* self = (const coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogError'",NULL);
#endif
  {
   self->LogError(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogWarn of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_LogWarn00
static int tolua_coord_coord_ScriptComponent_LogWarn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::ScriptComponent* self = (const coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogWarn'",NULL);
#endif
  {
   self->LogWarn(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogWarn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogInfo of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_LogInfo00
static int tolua_coord_coord_ScriptComponent_LogInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::ScriptComponent* self = (const coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogInfo'",NULL);
#endif
  {
   self->LogInfo(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogDebug of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_LogDebug00
static int tolua_coord_coord_ScriptComponent_LogDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::ScriptComponent* self = (const coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogDebug'",NULL);
#endif
  {
   self->LogDebug(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LogMsg of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_LogMsg00
static int tolua_coord_coord_ScriptComponent_LogMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const coord::ScriptComponent* self = (const coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LogMsg'",NULL);
#endif
  {
   self->LogMsg(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LogMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scriptName of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_get_coord__ScriptComponent_scriptName
static int tolua_get_coord__ScriptComponent_scriptName(lua_State* tolua_S)
{
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scriptName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->scriptName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scriptName of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_set_coord__ScriptComponent_scriptName
static int tolua_set_coord__ScriptComponent_scriptName(lua_State* tolua_S)
{
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scriptName'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->scriptName,tolua_tostring(tolua_S,2,0),64-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: position of class  coord::Transform */
#ifndef TOLUA_DISABLE_tolua_get_coord__Transform_position
static int tolua_get_coord__Transform_position(lua_State* tolua_S)
{
  coord::Transform* self = (coord::Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->position,"coord::Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: position of class  coord::Transform */
#ifndef TOLUA_DISABLE_tolua_set_coord__Transform_position
static int tolua_set_coord__Transform_position(lua_State* tolua_S)
{
  coord::Transform* self = (coord::Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Vector3",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->position = *((coord::Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scale of class  coord::Transform */
#ifndef TOLUA_DISABLE_tolua_get_coord__Transform_scale
static int tolua_get_coord__Transform_scale(lua_State* tolua_S)
{
  coord::Transform* self = (coord::Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->scale,"coord::Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scale of class  coord::Transform */
#ifndef TOLUA_DISABLE_tolua_set_coord__Transform_scale
static int tolua_set_coord__Transform_scale(lua_State* tolua_S)
{
  coord::Transform* self = (coord::Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Vector3",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scale = *((coord::Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rotation of class  coord::Transform */
#ifndef TOLUA_DISABLE_tolua_get_coord__Transform_rotation
static int tolua_get_coord__Transform_rotation(lua_State* tolua_S)
{
  coord::Transform* self = (coord::Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotation'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)&self->rotation,"coord::Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rotation of class  coord::Transform */
#ifndef TOLUA_DISABLE_tolua_set_coord__Transform_rotation
static int tolua_set_coord__Transform_rotation(lua_State* tolua_S)
{
  coord::Transform* self = (coord::Transform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotation'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Vector3",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rotation = *((coord::Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  coord::Vector3 */
#ifndef TOLUA_DISABLE_tolua_get_coord__Vector3_x
static int tolua_get_coord__Vector3_x(lua_State* tolua_S)
{
  coord::Vector3* self = (coord::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  coord::Vector3 */
#ifndef TOLUA_DISABLE_tolua_set_coord__Vector3_x
static int tolua_set_coord__Vector3_x(lua_State* tolua_S)
{
  coord::Vector3* self = (coord::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  coord::Vector3 */
#ifndef TOLUA_DISABLE_tolua_get_coord__Vector3_y
static int tolua_get_coord__Vector3_y(lua_State* tolua_S)
{
  coord::Vector3* self = (coord::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  coord::Vector3 */
#ifndef TOLUA_DISABLE_tolua_set_coord__Vector3_y
static int tolua_set_coord__Vector3_y(lua_State* tolua_S)
{
  coord::Vector3* self = (coord::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: z of class  coord::Vector3 */
#ifndef TOLUA_DISABLE_tolua_get_coord__Vector3_z
static int tolua_get_coord__Vector3_z(lua_State* tolua_S)
{
  coord::Vector3* self = (coord::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: z of class  coord::Vector3 */
#ifndef TOLUA_DISABLE_tolua_set_coord__Vector3_z
static int tolua_set_coord__Vector3_z(lua_State* tolua_S)
{
  coord::Vector3* self = (coord::Vector3*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Listen of class  coord::net::TcpListener */
#ifndef TOLUA_DISABLE_tolua_coord_coord_net_TcpListener_Listen00
static int tolua_coord_coord_net_TcpListener_Listen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::net::TcpListener",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::net::TcpListener* self = (coord::net::TcpListener*)  tolua_tousertype(tolua_S,1,0);
  const char* host = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  int backlog = ((int)  tolua_tonumber(tolua_S,4,1024));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Listen'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Listen(host,port,backlog);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Listen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  coord::net::TcpListener */
#ifndef TOLUA_DISABLE_tolua_coord_coord_net_TcpListener_Close00
static int tolua_coord_coord_net_TcpListener_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::net::TcpListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::net::TcpListener* self = (coord::net::TcpListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'",NULL);
#endif
  {
   self->Close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefaultConfig of class  coord::gate::Gate */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_Gate_DefaultConfig00
static int tolua_coord_coord_gate_Gate_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::Gate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::Gate* self = (coord::gate::Gate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::gate::GateConfig* tolua_ret = (coord::gate::GateConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::gate::GateConfig");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefaultConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Kick of class  coord::gate::Gate */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_Gate_Kick00
static int tolua_coord_coord_gate_Gate_Kick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::Gate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::Gate* self = (coord::gate::Gate*)  tolua_tousertype(tolua_S,1,0);
  uint64_t sessionId = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
  const char* reason = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Kick'",NULL);
#endif
  {
   self->Kick(sessionId,reason);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Kick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Router of class  coord::gate::Gate */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__Gate_Router_ptr
static int tolua_get_coord__gate__Gate_Router_ptr(lua_State* tolua_S)
{
  coord::gate::Gate* self = (coord::gate::Gate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Router,"coord::gate::GateRouter");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Router of class  coord::gate::Gate */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__Gate_Router_ptr
static int tolua_set_coord__gate__Gate_Router_ptr(lua_State* tolua_S)
{
  coord::gate::Gate* self = (coord::gate::Gate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::gate::GateRouter",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Router = ((coord::gate::GateRouter*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __websocket of class  coord::gate::Gate */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__Gate___websocket__IWebSocketHandler__
static int tolua_get_coord__gate__Gate___websocket__IWebSocketHandler__(lua_State* tolua_S)
{
  coord::gate::Gate* self = (coord::gate::Gate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__websocket'",NULL);
#endif
#ifdef __cplusplus
  tolua_pushusertype(tolua_S,(void*)static_cast<coord::websocket::IWebSocketHandler*>(self), "coord::websocket::IWebSocketHandler");
#else
  tolua_pushusertype(tolua_S,(void*)((coord::websocket::IWebSocketHandler*)self), "coord::websocket::IWebSocketHandler");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ServerName of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_ServerName
static int tolua_get_coord__gate__GateConfig_ServerName(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ServerName'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->ServerName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ServerName of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_ServerName
static int tolua_set_coord__gate__GateConfig_ServerName(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ServerName'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ServerName = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_Host
static int tolua_get_coord__gate__GateConfig_Host(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_Host
static int tolua_set_coord__gate__GateConfig_Host(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Network of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_Network
static int tolua_get_coord__gate__GateConfig_Network(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Network'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Network);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Network of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_Network
static int tolua_set_coord__gate__GateConfig_Network(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Network'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Network = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_unsigned_Port
static int tolua_get_coord__gate__GateConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_unsigned_Port
static int tolua_set_coord__gate__GateConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RsaEncrypt of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_RsaEncrypt
static int tolua_get_coord__gate__GateConfig_RsaEncrypt(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RsaEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->RsaEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RsaEncrypt of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_RsaEncrypt
static int tolua_set_coord__gate__GateConfig_RsaEncrypt(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RsaEncrypt'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RsaEncrypt = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RsaKeyFile of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_RsaKeyFile
static int tolua_get_coord__gate__GateConfig_RsaKeyFile(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RsaKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->RsaKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RsaKeyFile of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_RsaKeyFile
static int tolua_set_coord__gate__GateConfig_RsaKeyFile(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RsaKeyFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RsaKeyFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Heartbeat of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_Heartbeat
static int tolua_get_coord__gate__GateConfig_Heartbeat(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Heartbeat'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Heartbeat);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Heartbeat of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_Heartbeat
static int tolua_set_coord__gate__GateConfig_Heartbeat(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Heartbeat'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Heartbeat = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Backlog of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_Backlog
static int tolua_get_coord__gate__GateConfig_Backlog(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Backlog);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Backlog of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_Backlog
static int tolua_set_coord__gate__GateConfig_Backlog(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Backlog = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RecvBuffer of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_RecvBuffer
static int tolua_get_coord__gate__GateConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBuffer'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RecvBuffer);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RecvBuffer of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_RecvBuffer
static int tolua_set_coord__gate__GateConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBuffer'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RecvBuffer = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLEncrypt of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_SSLEncrypt
static int tolua_get_coord__gate__GateConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->SSLEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLEncrypt of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_SSLEncrypt
static int tolua_set_coord__gate__GateConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLEncrypt = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLPemFile of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_SSLPemFile
static int tolua_get_coord__gate__GateConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLPemFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLPemFile of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_SSLPemFile
static int tolua_set_coord__gate__GateConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLPemFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLKeyFile of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_SSLKeyFile
static int tolua_get_coord__gate__GateConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLKeyFile of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_SSLKeyFile
static int tolua_set_coord__gate__GateConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLKeyFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MaxUser of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_MaxUser
static int tolua_get_coord__gate__GateConfig_MaxUser(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxUser'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->MaxUser);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: MaxUser of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_MaxUser
static int tolua_set_coord__gate__GateConfig_MaxUser(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxUser'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MaxUser = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MaxConnection of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_MaxConnection
static int tolua_get_coord__gate__GateConfig_MaxConnection(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxConnection'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->MaxConnection);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: MaxConnection of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_MaxConnection
static int tolua_set_coord__gate__GateConfig_MaxConnection(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxConnection'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->MaxConnection = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Cluster of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_Cluster
static int tolua_get_coord__gate__GateConfig_Cluster(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Cluster);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Cluster of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_Cluster
static int tolua_set_coord__gate__GateConfig_Cluster(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Cluster = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UserRegisterExpire of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_UserRegisterExpire
static int tolua_get_coord__gate__GateConfig_UserRegisterExpire(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UserRegisterExpire'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->UserRegisterExpire);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UserRegisterExpire of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_UserRegisterExpire
static int tolua_set_coord__gate__GateConfig_UserRegisterExpire(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UserRegisterExpire'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UserRegisterExpire = ((uint32_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UserRegisterInterval of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_UserRegisterInterval
static int tolua_get_coord__gate__GateConfig_UserRegisterInterval(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UserRegisterInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->UserRegisterInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UserRegisterInterval of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_UserRegisterInterval
static int tolua_set_coord__gate__GateConfig_UserRegisterInterval(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UserRegisterInterval'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UserRegisterInterval = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RegisterExpire of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_RegisterExpire
static int tolua_get_coord__gate__GateConfig_RegisterExpire(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RegisterExpire'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RegisterExpire);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RegisterExpire of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_RegisterExpire
static int tolua_set_coord__gate__GateConfig_RegisterExpire(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RegisterExpire'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RegisterExpire = ((uint32_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RegisterInterval of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateConfig_RegisterInterval
static int tolua_get_coord__gate__GateConfig_RegisterInterval(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RegisterInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RegisterInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RegisterInterval of class  coord::gate::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateConfig_RegisterInterval
static int tolua_set_coord__gate__GateConfig_RegisterInterval(lua_State* tolua_S)
{
  coord::gate::GateConfig* self = (coord::gate::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RegisterInterval'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RegisterInterval = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Notify of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Notify00
static int tolua_coord_coord_gate_GateRouter_Notify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Notify'",NULL);
#endif
  {
return self->Notify(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Notify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Request of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Request00
static int tolua_coord_coord_gate_GateRouter_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
return self->Request(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Auth of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Auth00
static int tolua_coord_coord_gate_GateRouter_Auth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Auth'",NULL);
#endif
  {
return self->Auth(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Auth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SessionNew of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_SessionNew00
static int tolua_coord_coord_gate_GateRouter_SessionNew00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SessionNew'",NULL);
#endif
  {
return self->SessionNew(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SessionNew'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SessionClose of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_SessionClose00
static int tolua_coord_coord_gate_GateRouter_SessionClose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SessionClose'",NULL);
#endif
  {
return self->SessionClose(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SessionClose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Login of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Login00
static int tolua_coord_coord_gate_GateRouter_Login00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Login'",NULL);
#endif
  {
return self->Login(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Login'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Logout of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Logout00
static int tolua_coord_coord_gate_GateRouter_Logout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Logout'",NULL);
#endif
  {
return self->Logout(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Logout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instead of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Instead00
static int tolua_coord_coord_gate_GateRouter_Instead00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Instead'",NULL);
#endif
  {
return self->Instead(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instead'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Trace of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Trace00
static int tolua_coord_coord_gate_GateRouter_Trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Trace'",NULL);
#endif
  {
   self->Trace();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResponse of class  coord::gate::GateRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRequest_GetResponse00
static int tolua_coord_coord_gate_GateRequest_GetResponse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRequest* self = (coord::gate::GateRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResponse'",NULL);
#endif
  {
   coord::gate::GateResponse* tolua_ret = (coord::gate::GateResponse*)  self->GetResponse();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::gate::GateResponse");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResponse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Kick of class  coord::gate::GateRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRequest_Kick00
static int tolua_coord_coord_gate_GateRequest_Kick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRequest* self = (coord::gate::GateRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* reason = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Kick'",NULL);
#endif
  {
   self->Kick(reason);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Kick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSession of class  coord::gate::GateRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRequest_GetSession00
static int tolua_coord_coord_gate_GateRequest_GetSession00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRequest* self = (coord::gate::GateRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSession'",NULL);
#endif
  {
   coord::gate::GateSession* tolua_ret = (coord::gate::GateSession*)  self->GetSession();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::gate::GateSession");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSession'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sessionId of class  coord::gate::GateRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateRequest_sessionId
static int tolua_get_coord__gate__GateRequest_sessionId(lua_State* tolua_S)
{
  coord::gate::GateRequest* self = (coord::gate::GateRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sessionId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sessionId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sessionId of class  coord::gate::GateRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateRequest_sessionId
static int tolua_set_coord__gate__GateRequest_sessionId(lua_State* tolua_S)
{
  coord::gate::GateRequest* self = (coord::gate::GateRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sessionId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sessionId = ((uint64_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sessionId of class  coord::gate::GateNotify */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateNotify_sessionId
static int tolua_get_coord__gate__GateNotify_sessionId(lua_State* tolua_S)
{
  coord::gate::GateNotify* self = (coord::gate::GateNotify*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sessionId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sessionId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sessionId of class  coord::gate::GateNotify */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateNotify_sessionId
static int tolua_set_coord__gate__GateNotify_sessionId(lua_State* tolua_S)
{
  coord::gate::GateNotify* self = (coord::gate::GateNotify*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sessionId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sessionId = ((uint64_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Kick of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateSession_Kick00
static int tolua_coord_coord_gate_GateSession_Kick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateSession",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
  const char* reason = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Kick'",NULL);
#endif
  {
   self->Kick(reason);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Kick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Push of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateSession_Push00
static int tolua_coord_coord_gate_GateSession_Push00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateSession",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
  const char* route = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::protobuf::Reflect* proto = ((coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Push'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Push(route,proto);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Push'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Login of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateSession_Login00
static int tolua_coord_coord_gate_GateSession_Login00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateSession",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
  uint64_t userId = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Login'",NULL);
#endif
  {
   coord::gate::GatePromise* tolua_ret = (coord::gate::GatePromise*)  self->Login(userId);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::gate::GatePromise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Login'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAuth of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateSession_IsAuth00
static int tolua_coord_coord_gate_GateSession_IsAuth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateSession",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAuth'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAuth();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAuth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Id of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateSession_Id
static int tolua_get_coord__gate__GateSession_Id(lua_State* tolua_S)
{
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Id'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Id);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Id of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateSession_Id
static int tolua_set_coord__gate__GateSession_Id(lua_State* tolua_S)
{
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Id'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Id = ((uint64_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RemoteAddr of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateSession_RemoteAddr
static int tolua_get_coord__gate__GateSession_RemoteAddr(lua_State* tolua_S)
{
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RemoteAddr'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->RemoteAddr);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RemoteAddr of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateSession_RemoteAddr
static int tolua_set_coord__gate__GateSession_RemoteAddr(lua_State* tolua_S)
{
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RemoteAddr'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RemoteAddr = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: UserId of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_get_coord__gate__GateSession_UserId
static int tolua_get_coord__gate__GateSession_UserId(lua_State* tolua_S)
{
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UserId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->UserId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: UserId of class  coord::gate::GateSession */
#ifndef TOLUA_DISABLE_tolua_set_coord__gate__GateSession_UserId
static int tolua_set_coord__gate__GateSession_UserId(lua_State* tolua_S)
{
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'UserId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->UserId = ((uint64_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Then of class  coord::gate::GatePromise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GatePromise_Then00
static int tolua_coord_coord_gate_GatePromise_Then00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GatePromise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GatePromise* self = (coord::gate::GatePromise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Then'",NULL);
#endif
  {
return self->Then(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Then'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Else of class  coord::gate::GatePromise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GatePromise_Else00
static int tolua_coord_coord_gate_GatePromise_Else00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GatePromise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GatePromise* self = (coord::gate::GatePromise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Else'",NULL);
#endif
  {
return self->Else(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Else'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Using of class  coord::gate::GatePromise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GatePromise_Using00
static int tolua_coord_coord_gate_GatePromise_Using00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GatePromise",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::BaseRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GatePromise* self = (coord::gate::GatePromise*)  tolua_tousertype(tolua_S,1,0);
  coord::BaseRequest* request = ((coord::BaseRequest*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Using'",NULL);
#endif
  {
   coord::gate::GatePromise* tolua_ret = (coord::gate::GatePromise*)  self->Using(request);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::gate::GatePromise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Using'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name of class  coord::event::BaseEvent */
#ifndef TOLUA_DISABLE_tolua_get_coord__event__BaseEvent_name
static int tolua_get_coord__event__BaseEvent_name(lua_State* tolua_S)
{
  coord::event::BaseEvent* self = (coord::event::BaseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  coord::event::BaseEvent */
#ifndef TOLUA_DISABLE_tolua_set_coord__event__BaseEvent_name
static int tolua_set_coord__event__BaseEvent_name(lua_State* tolua_S)
{
  coord::event::BaseEvent* self = (coord::event::BaseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: arg of class  coord::event::BaseEvent */
#ifndef TOLUA_DISABLE_tolua_get_coord__event__BaseEvent_arg
static int tolua_get_coord__event__BaseEvent_arg(lua_State* tolua_S)
{
  coord::event::BaseEvent* self = (coord::event::BaseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arg'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->arg);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: arg of class  coord::event::BaseEvent */
#ifndef TOLUA_DISABLE_tolua_set_coord__event__BaseEvent_arg
static int tolua_set_coord__event__BaseEvent_arg(lua_State* tolua_S)
{
  coord::event::BaseEvent* self = (coord::event::BaseEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arg'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->arg = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddListener of class  coord::event::EventMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_event_EventMgr_AddListener00
static int tolua_coord_coord_event_EventMgr_AddListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::event::EventMgr",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::event::EventMgr* self = (coord::event::EventMgr*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddListener'",NULL);
#endif
  {
return self->AddListener(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasListener of class  coord::event::EventMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_event_EventMgr_HasListener00
static int tolua_coord_coord_event_EventMgr_HasListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::event::EventMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::event::EventMgr* self = (coord::event::EventMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasListener'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasListener(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Emit of class  coord::event::EventMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_event_EventMgr_Emit00
static int tolua_coord_coord_event_EventMgr_Emit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::event::EventMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::event::BaseEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::event::EventMgr* self = (coord::event::EventMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::event::BaseEvent* args = ((coord::event::BaseEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Emit'",NULL);
#endif
  {
   self->Emit(name,args);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Emit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Remove of class  coord::event::Listener */
#ifndef TOLUA_DISABLE_tolua_coord_coord_event_Listener_Remove00
static int tolua_coord_coord_event_Listener_Remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::event::Listener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::event::Listener* self = (coord::event::Listener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Remove'",NULL);
#endif
  {
   self->Remove();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MapPath of class  coord::protobuf::Protobuf */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Protobuf_MapPath00
static int tolua_coord_coord_protobuf_Protobuf_MapPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Protobuf",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Protobuf* self = (coord::protobuf::Protobuf*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* dir = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MapPath'",NULL);
#endif
  {
   int tolua_ret = (int)  self->MapPath(name,dir);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MapPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Import of class  coord::protobuf::Protobuf */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Protobuf_Import00
static int tolua_coord_coord_protobuf_Protobuf_Import00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Protobuf",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Protobuf* self = (coord::protobuf::Protobuf*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Import'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Import(fileName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Import'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ImportDir of class  coord::protobuf::Protobuf */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Protobuf_ImportDir00
static int tolua_coord_coord_protobuf_Protobuf_ImportDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Protobuf",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Protobuf* self = (coord::protobuf::Protobuf*)  tolua_tousertype(tolua_S,1,0);
  const char* dir = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ImportDir'",NULL);
#endif
  {
   int tolua_ret = (int)  self->ImportDir(dir);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ImportDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NewReflect of class  coord::protobuf::Protobuf */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Protobuf_NewReflect00
static int tolua_coord_coord_protobuf_Protobuf_NewReflect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Protobuf",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Protobuf* self = (coord::protobuf::Protobuf*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewReflect'",NULL);
#endif
  {
   coord::protobuf::Reflect tolua_ret = (coord::protobuf::Reflect)  self->NewReflect(name);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::protobuf::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::protobuf::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::protobuf::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::protobuf::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewReflect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_Get00
static int tolua_coord_coord_protobuf_Reflect_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
  {
return self->Get(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetString of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetString00
static int tolua_coord_coord_protobuf_Reflect_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetString'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetString(fieldName);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInt32 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetInt3200
static int tolua_coord_coord_protobuf_Reflect_GetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInt32'",NULL);
#endif
  {
   int32_t tolua_ret = (int32_t)  self->GetInt32(fieldName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInt64 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetInt6400
static int tolua_coord_coord_protobuf_Reflect_GetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInt64'",NULL);
#endif
  {
   int64_t tolua_ret = (int64_t)  self->GetInt64(fieldName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUInt32 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetUInt3200
static int tolua_coord_coord_protobuf_Reflect_GetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUInt32'",NULL);
#endif
  {
   uint32_t tolua_ret = (uint32_t)  self->GetUInt32(fieldName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUInt64 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetUInt6400
static int tolua_coord_coord_protobuf_Reflect_GetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUInt64'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->GetUInt64(fieldName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFloat of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetFloat00
static int tolua_coord_coord_protobuf_Reflect_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFloat'",NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFloat(fieldName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDouble of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetDouble00
static int tolua_coord_coord_protobuf_Reflect_GetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDouble'",NULL);
#endif
  {
   double tolua_ret = (double)  self->GetDouble(fieldName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBool of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_GetBool00
static int tolua_coord_coord_protobuf_Reflect_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBool(fieldName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_Set00
static int tolua_coord_coord_protobuf_Reflect_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
  {
return self->Set(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInt32 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetInt3200
static int tolua_coord_coord_protobuf_Reflect_SetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int32_t value = ((int32_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInt32'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetInt32(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInt64 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetInt6400
static int tolua_coord_coord_protobuf_Reflect_SetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int64_t value = ((int64_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInt64'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetInt64(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUInt32 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetUInt3200
static int tolua_coord_coord_protobuf_Reflect_SetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  uint32_t value = ((uint32_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUInt32'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetUInt32(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUInt64 of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetUInt6400
static int tolua_coord_coord_protobuf_Reflect_SetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  uint64_t value = ((uint64_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUInt64'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetUInt64(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFloat of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetFloat00
static int tolua_coord_coord_protobuf_Reflect_SetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFloat'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetFloat(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDouble of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetDouble00
static int tolua_coord_coord_protobuf_Reflect_SetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDouble'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetDouble(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBool of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetBool00
static int tolua_coord_coord_protobuf_Reflect_SetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetBool(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumber of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetNumber00
static int tolua_coord_coord_protobuf_Reflect_SetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* fieldName = ((const char*)  tolua_tostring(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumber'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetNumber(fieldName,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DebugString of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_DebugString00
static int tolua_coord_coord_protobuf_Reflect_DebugString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DebugString'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->DebugString();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DebugString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShortDebugString of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_ShortDebugString00
static int tolua_coord_coord_protobuf_Reflect_ShortDebugString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShortDebugString'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->ShortDebugString();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShortDebugString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CopyFrom of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_CopyFrom00
static int tolua_coord_coord_protobuf_Reflect_CopyFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  coord::protobuf::Reflect* other = ((coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CopyFrom'",NULL);
#endif
  {
   int tolua_ret = (int)  self->CopyFrom(*other);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CopyFrom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MergeFrom of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_MergeFrom00
static int tolua_coord_coord_protobuf_Reflect_MergeFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  coord::protobuf::Reflect* other = ((coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MergeFrom'",NULL);
#endif
  {
   int tolua_ret = (int)  self->MergeFrom(*other);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MergeFrom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ByteSize of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_ByteSize00
static int tolua_coord_coord_protobuf_Reflect_ByteSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ByteSize'",NULL);
#endif
  {
   int tolua_ret = (int)  self->ByteSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ByteSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDirty of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_IsDirty00
static int tolua_coord_coord_protobuf_Reflect_IsDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDirty'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDirty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDirty of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_SetDirty00
static int tolua_coord_coord_protobuf_Reflect_SetDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
  bool dirty = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDirty'",NULL);
#endif
  {
   self->SetDirty(dirty);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Name of class  coord::protobuf::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Reflect_Name00
static int tolua_coord_coord_protobuf_Reflect_Name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Name'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->Name();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Name'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_delete00
static int tolua_coord_coord_protobuf_Array_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
  delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_Clear00
static int tolua_coord_coord_protobuf_Array_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Clear();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MergeFrom of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_MergeFrom00
static int tolua_coord_coord_protobuf_Array_MergeFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  coord::protobuf::Array* other = ((coord::protobuf::Array*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MergeFrom'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->MergeFrom(*other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MergeFrom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveLast of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_RemoveLast00
static int tolua_coord_coord_protobuf_Array_RemoveLast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveLast'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveLast();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveLast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAt of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_RemoveAt00
static int tolua_coord_coord_protobuf_Array_RemoveAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAt'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveAt(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Remove of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_Remove00
static int tolua_coord_coord_protobuf_Array_Remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Remove'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Remove(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Count of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_Count00
static int tolua_coord_coord_protobuf_Array_Count00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Count'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Count();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Count'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDirty of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetDirty00
static int tolua_coord_coord_protobuf_Array_SetDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  bool dirty = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDirty'",NULL);
#endif
  {
   self->SetDirty(dirty);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_Set00
static int tolua_coord_coord_protobuf_Array_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
  {
return self->Set(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInt32 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetInt3200
static int tolua_coord_coord_protobuf_Array_SetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int32_t value = ((int32_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInt32'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetInt32(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInt64 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetInt6400
static int tolua_coord_coord_protobuf_Array_SetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  int64_t value = ((int64_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInt64'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetInt64(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUInt32 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetUInt3200
static int tolua_coord_coord_protobuf_Array_SetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  uint32_t value = ((uint32_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUInt32'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetUInt32(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUInt64 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetUInt6400
static int tolua_coord_coord_protobuf_Array_SetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  uint64_t value = ((uint64_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUInt64'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetUInt64(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFloat of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetFloat00
static int tolua_coord_coord_protobuf_Array_SetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFloat'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetFloat(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDouble of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetDouble00
static int tolua_coord_coord_protobuf_Array_SetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDouble'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetDouble(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBool of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetBool00
static int tolua_coord_coord_protobuf_Array_SetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetBool(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumber of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_SetNumber00
static int tolua_coord_coord_protobuf_Array_SetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumber'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetNumber(index,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_Get00
static int tolua_coord_coord_protobuf_Array_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
  {
return self->Get(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInt32 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetInt3200
static int tolua_coord_coord_protobuf_Array_GetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInt32'",NULL);
#endif
  {
   int32_t tolua_ret = (int32_t)  self->GetInt32(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInt64 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetInt6400
static int tolua_coord_coord_protobuf_Array_GetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInt64'",NULL);
#endif
  {
   int64_t tolua_ret = (int64_t)  self->GetInt64(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUInt32 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetUInt3200
static int tolua_coord_coord_protobuf_Array_GetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUInt32'",NULL);
#endif
  {
   uint32_t tolua_ret = (uint32_t)  self->GetUInt32(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUInt64 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetUInt6400
static int tolua_coord_coord_protobuf_Array_GetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUInt64'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->GetUInt64(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFloat of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetFloat00
static int tolua_coord_coord_protobuf_Array_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFloat'",NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFloat(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDouble of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetDouble00
static int tolua_coord_coord_protobuf_Array_GetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDouble'",NULL);
#endif
  {
   double tolua_ret = (double)  self->GetDouble(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBool of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetBool00
static int tolua_coord_coord_protobuf_Array_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBool(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumber of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_GetNumber00
static int tolua_coord_coord_protobuf_Array_GetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumber'",NULL);
#endif
  {
   double tolua_ret = (double)  self->GetNumber(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Add of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_Add00
static int tolua_coord_coord_protobuf_Array_Add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Add'",NULL);
#endif
  {
return self->Add(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddInt32 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddInt3200
static int tolua_coord_coord_protobuf_Array_AddInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int32_t value = ((int32_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddInt32'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddInt32(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddInt64 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddInt6400
static int tolua_coord_coord_protobuf_Array_AddInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  int64_t value = ((int64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddInt64'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddInt64(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddUInt32 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddUInt3200
static int tolua_coord_coord_protobuf_Array_AddUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  uint32_t value = ((uint32_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddUInt32'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddUInt32(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddUInt32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddUInt64 of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddUInt6400
static int tolua_coord_coord_protobuf_Array_AddUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  uint64_t value = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddUInt64'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddUInt64(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddUInt64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddFloat of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddFloat00
static int tolua_coord_coord_protobuf_Array_AddFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddFloat'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddFloat(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddDouble of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddDouble00
static int tolua_coord_coord_protobuf_Array_AddDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  double value = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddDouble'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddDouble(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDouble'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddBool of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddBool00
static int tolua_coord_coord_protobuf_Array_AddBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddBool(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNumber of class  coord::protobuf::Array */
#ifndef TOLUA_DISABLE_tolua_coord_coord_protobuf_Array_AddNumber00
static int tolua_coord_coord_protobuf_Array_AddNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::protobuf::Array",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::protobuf::Array* self = (coord::protobuf::Array*)  tolua_tousertype(tolua_S,1,0);
  double value = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNumber'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddNumber(value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTimeout of class  coord::timer::TimerMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_timer_TimerMgr_SetTimeout00
static int tolua_coord_coord_timer_TimerMgr_SetTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::timer::TimerMgr",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::timer::TimerMgr* self = (coord::timer::TimerMgr*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeout'",NULL);
#endif
  {
return self->SetTimeout(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTimeout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInterval of class  coord::timer::TimerMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_timer_TimerMgr_SetInterval00
static int tolua_coord_coord_timer_TimerMgr_SetInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::timer::TimerMgr",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::timer::TimerMgr* self = (coord::timer::TimerMgr*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInterval'",NULL);
#endif
  {
return self->SetInterval(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCron of class  coord::timer::TimerMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_timer_TimerMgr_SetCron00
static int tolua_coord_coord_timer_TimerMgr_SetCron00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::timer::TimerMgr",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::timer::TimerMgr* self = (coord::timer::TimerMgr*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCron'",NULL);
#endif
  {
return self->SetCron(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCron'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Driver of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__sql__SQLConfig_Driver
static int tolua_get_coord__sql__SQLConfig_Driver(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Driver'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Driver);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Driver of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__sql__SQLConfig_Driver
static int tolua_set_coord__sql__SQLConfig_Driver(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Driver'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Driver = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: User of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__sql__SQLConfig_User
static int tolua_get_coord__sql__SQLConfig_User(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->User);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: User of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__sql__SQLConfig_User
static int tolua_set_coord__sql__SQLConfig_User(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->User = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Password of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__sql__SQLConfig_Password
static int tolua_get_coord__sql__SQLConfig_Password(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__sql__SQLConfig_Password
static int tolua_set_coord__sql__SQLConfig_Password(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Password = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DB of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__sql__SQLConfig_DB
static int tolua_get_coord__sql__SQLConfig_DB(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DB'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->DB);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: DB of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__sql__SQLConfig_DB
static int tolua_set_coord__sql__SQLConfig_DB(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DB'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->DB = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: CharacterSet of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__sql__SQLConfig_CharacterSet
static int tolua_get_coord__sql__SQLConfig_CharacterSet(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CharacterSet'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->CharacterSet);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: CharacterSet of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__sql__SQLConfig_CharacterSet
static int tolua_set_coord__sql__SQLConfig_CharacterSet(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'CharacterSet'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->CharacterSet = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__sql__SQLConfig_Host
static int tolua_get_coord__sql__SQLConfig_Host(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__sql__SQLConfig_Host
static int tolua_set_coord__sql__SQLConfig_Host(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__sql__SQLConfig_Port
static int tolua_get_coord__sql__SQLConfig_Port(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::sql::SQLConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__sql__SQLConfig_Port
static int tolua_set_coord__sql__SQLConfig_Port(lua_State* tolua_S)
{
  coord::sql::SQLConfig* self = (coord::sql::SQLConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefaultConfig of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_DefaultConfig00
static int tolua_coord_coord_sql_SQLClient_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::sql::SQLConfig* tolua_ret = (coord::sql::SQLConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::sql::SQLConfig");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefaultConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Connect of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Connect00
static int tolua_coord_coord_sql_SQLClient_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connect'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Connect();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Ping of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Ping00
static int tolua_coord_coord_sql_SQLClient_Ping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ping'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Ping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Ping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Error of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Error00
static int tolua_coord_coord_sql_SQLClient_Error00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Error'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->Error();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Error'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Close00
static int tolua_coord_coord_sql_SQLClient_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'",NULL);
#endif
  {
   self->Close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RowsAffected of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_RowsAffected00
static int tolua_coord_coord_sql_SQLClient_RowsAffected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RowsAffected'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->RowsAffected();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RowsAffected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LastInsertId of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_LastInsertId00
static int tolua_coord_coord_sql_SQLClient_LastInsertId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LastInsertId'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->LastInsertId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LastInsertId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Query of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Query00
static int tolua_coord_coord_sql_SQLClient_Query00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Query'",NULL);
#endif
  {
return self->Query(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Query'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Get of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Get00
static int tolua_coord_coord_sql_SQLClient_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
  {
return self->Get(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Execute of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Execute00
static int tolua_coord_coord_sql_SQLClient_Execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Execute'",NULL);
#endif
  {
return self->Execute(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Execute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RowsAffected of class  coord::sql::SQLResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLResult_RowsAffected00
static int tolua_coord_coord_sql_SQLResult_RowsAffected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLResult* self = (coord::sql::SQLResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RowsAffected'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->RowsAffected();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RowsAffected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LastInsertId of class  coord::sql::SQLResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLResult_LastInsertId00
static int tolua_coord_coord_sql_SQLResult_LastInsertId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLResult* self = (coord::sql::SQLResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LastInsertId'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->LastInsertId();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LastInsertId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Next of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_Next00
static int tolua_coord_coord_sql_SQLRows_Next00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Next'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Next();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Next'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_Proto00
static int tolua_coord_coord_sql_SQLRows_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::protobuf::Reflect tolua_ret = (coord::protobuf::Reflect)  self->Proto(name);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::protobuf::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::protobuf::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::protobuf::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::protobuf::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Proto'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_Proto01
static int tolua_coord_coord_sql_SQLRows_Proto01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  coord::protobuf::Reflect* proto = ((coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Proto(*proto);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_sql_SQLRows_Proto00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Lua of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_Lua00
static int tolua_coord_coord_sql_SQLRows_Lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Lua'",NULL);
#endif
  {
return self->Lua(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Lua'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Column of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_Column00
static int tolua_coord_coord_sql_SQLRows_Column00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Column'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->Column(index);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Column'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ColumnCount of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_ColumnCount00
static int tolua_coord_coord_sql_SQLRows_ColumnCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ColumnCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->ColumnCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ColumnCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_String00
static int tolua_coord_coord_sql_SQLRows_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->String(index);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'String'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_String01
static int tolua_coord_coord_sql_SQLRows_String01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  const char* field = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->String(field);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_sql_SQLRows_String00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Number of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_Number00
static int tolua_coord_coord_sql_SQLRows_Number00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Number'",NULL);
#endif
  {
   double tolua_ret = (double)  self->Number(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Number'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Number of class  coord::sql::SQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLRows_Number01
static int tolua_coord_coord_sql_SQLRows_Number01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLRows",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::sql::SQLRows* self = (coord::sql::SQLRows*)  tolua_tousertype(tolua_S,1,0);
  const char* field = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Number'",NULL);
#endif
  {
   double tolua_ret = (double)  self->Number(field);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_sql_SQLRows_Number00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Password of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__redis__RedisConfig_Password
static int tolua_get_coord__redis__RedisConfig_Password(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__redis__RedisConfig_Password
static int tolua_set_coord__redis__RedisConfig_Password(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Password = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DB of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__redis__RedisConfig_DB
static int tolua_get_coord__redis__RedisConfig_DB(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DB'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->DB);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: DB of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__redis__RedisConfig_DB
static int tolua_set_coord__redis__RedisConfig_DB(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DB'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->DB = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__redis__RedisConfig_Host
static int tolua_get_coord__redis__RedisConfig_Host(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__redis__RedisConfig_Host
static int tolua_set_coord__redis__RedisConfig_Host(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__redis__RedisConfig_Port
static int tolua_get_coord__redis__RedisConfig_Port(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::redis::RedisConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__redis__RedisConfig_Port
static int tolua_set_coord__redis__RedisConfig_Port(lua_State* tolua_S)
{
  coord::redis::RedisConfig* self = (coord::redis::RedisConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Connect of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_Connect00
static int tolua_coord_coord_redis_AsyncClient_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connect'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->Connect();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefaultConfig of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_DefaultConfig00
static int tolua_coord_coord_redis_AsyncClient_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::redis::RedisConfig* tolua_ret = (coord::redis::RedisConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisConfig");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefaultConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_Close00
static int tolua_coord_coord_redis_AsyncClient_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'",NULL);
#endif
  {
   self->Close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SELECT of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_SELECT00
static int tolua_coord_coord_redis_AsyncClient_SELECT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* db = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SELECT'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->SELECT(db);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SELECT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AUTH of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_AUTH00
static int tolua_coord_coord_redis_AsyncClient_AUTH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* password = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AUTH'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->AUTH(password);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AUTH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DEL of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_DEL00
static int tolua_coord_coord_redis_AsyncClient_DEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DEL'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->DEL(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DEL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GET of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_GET00
static int tolua_coord_coord_redis_AsyncClient_GET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GET'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->GET(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SET of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_SET00
static int tolua_coord_coord_redis_AsyncClient_SET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SET'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->SET(key,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EXPIRE of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_EXPIRE00
static int tolua_coord_coord_redis_AsyncClient_EXPIRE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  uint64_t expire = ((uint64_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EXPIRE'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->EXPIRE(key,expire);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EXPIRE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HGETALL of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_HGETALL00
static int tolua_coord_coord_redis_AsyncClient_HGETALL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HGETALL'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->HGETALL(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HGETALL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HDEL of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_HDEL00
static int tolua_coord_coord_redis_AsyncClient_HDEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HDEL'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->HDEL(key,field);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HDEL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HMSET of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_HMSET00
static int tolua_coord_coord_redis_AsyncClient_HMSET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->HMSET(key,field,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HMSET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HMSET of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_HMSET01
static int tolua_coord_coord_redis_AsyncClient_HMSET01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  uint64_t value = ((uint64_t)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->HMSET(key,field,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_redis_AsyncClient_HMSET00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SCRIPT_LOAD of class  coord::redis::AsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_AsyncClient_SCRIPT_LOAD00
static int tolua_coord_coord_redis_AsyncClient_SCRIPT_LOAD00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::AsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::AsyncClient* self = (coord::redis::AsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SCRIPT_LOAD'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->SCRIPT_LOAD(str);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SCRIPT_LOAD'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Connect of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_Connect00
static int tolua_coord_coord_redis_Client_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connect'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Connect();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefaultConfig of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_DefaultConfig00
static int tolua_coord_coord_redis_Client_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::redis::RedisConfig* tolua_ret = (coord::redis::RedisConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisConfig");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefaultConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_Close00
static int tolua_coord_coord_redis_Client_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'",NULL);
#endif
  {
   self->Close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SELECT of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_SELECT00
static int tolua_coord_coord_redis_Client_SELECT00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* db = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SELECT'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->SELECT(db);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SELECT'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AUTH of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_AUTH00
static int tolua_coord_coord_redis_Client_AUTH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* password = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AUTH'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->AUTH(password);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AUTH'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TIME of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_TIME00
static int tolua_coord_coord_redis_Client_TIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TIME'",NULL);
#endif
  {
   uint64_t tolua_ret = (uint64_t)  self->TIME();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TIME'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DEL of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_DEL00
static int tolua_coord_coord_redis_Client_DEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DEL'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->DEL(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DEL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GET of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_GET00
static int tolua_coord_coord_redis_Client_GET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GET'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->GET(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SET of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_SET00
static int tolua_coord_coord_redis_Client_SET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SET'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->SET(key,value);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EXPIRE of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_EXPIRE00
static int tolua_coord_coord_redis_Client_EXPIRE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  uint64_t expire = ((uint64_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EXPIRE'",NULL);
#endif
  {
   int tolua_ret = (int)  self->EXPIRE(key,expire);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EXPIRE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HGETALL of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_HGETALL00
static int tolua_coord_coord_redis_Client_HGETALL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HGETALL'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->HGETALL(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HGETALL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HDEL of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_HDEL00
static int tolua_coord_coord_redis_Client_HDEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HDEL'",NULL);
#endif
  {
   int tolua_ret = (int)  self->HDEL(key,field);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HDEL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HMSET of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_HMSET00
static int tolua_coord_coord_redis_Client_HMSET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->HMSET(key,field,value);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HMSET'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HMSET of class  coord::redis::Client */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Client_HMSET01
static int tolua_coord_coord_redis_Client_HMSET01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Client",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::Client* self = (coord::redis::Client*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  uint64_t value = ((uint64_t)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::redis::Reply tolua_ret = (coord::redis::Reply)  self->HMSET(key,field,value);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::redis::Reply(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::redis::Reply));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::redis::Reply");
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_redis_Client_HMSET00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Then of class  coord::redis::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Promise_Then00
static int tolua_coord_coord_redis_Promise_Then00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Promise* self = (coord::redis::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Then'",NULL);
#endif
  {
return self->Then(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Then'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Else of class  coord::redis::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Promise_Else00
static int tolua_coord_coord_redis_Promise_Else00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Promise* self = (coord::redis::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Else'",NULL);
#endif
  {
return self->Else(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Else'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Error of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_Error00
static int tolua_coord_coord_redis_Reply_Error00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Error'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Error();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Error'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Array of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_Array00
static int tolua_coord_coord_redis_Reply_Array00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Array'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Array();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Array'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ArrayCount of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_ArrayCount00
static int tolua_coord_coord_redis_Reply_ArrayCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ArrayCount'",NULL);
#endif
  {
   int tolua_ret = (int)  self->ArrayCount();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ArrayCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Empty of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_Empty00
static int tolua_coord_coord_redis_Reply_Empty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Empty'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Empty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Empty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Empty of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_Empty01
static int tolua_coord_coord_redis_Reply_Empty01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Empty'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Empty(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_redis_Reply_Empty00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_String00
static int tolua_coord_coord_redis_Reply_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->String();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'String'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Integer of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_Integer00
static int tolua_coord_coord_redis_Reply_Integer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Integer'",NULL);
#endif
  {
   long long tolua_ret = (long long)  self->Integer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Integer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Integer of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_Integer01
static int tolua_coord_coord_redis_Reply_Integer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Integer'",NULL);
#endif
  {
   long long tolua_ret = (long long)  self->Integer(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_redis_Reply_Integer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::redis::Reply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_Reply_String01
static int tolua_coord_coord_redis_Reply_String01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::Reply",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::Reply* self = (coord::redis::Reply*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->String(index);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_redis_Reply_String00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Password of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cache__CacheConfig_Password
static int tolua_get_coord__cache__CacheConfig_Password(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cache__CacheConfig_Password
static int tolua_set_coord__cache__CacheConfig_Password(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Password = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DB of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cache__CacheConfig_DB
static int tolua_get_coord__cache__CacheConfig_DB(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DB'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->DB);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: DB of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cache__CacheConfig_DB
static int tolua_set_coord__cache__CacheConfig_DB(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'DB'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->DB = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cache__CacheConfig_Host
static int tolua_get_coord__cache__CacheConfig_Host(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cache__CacheConfig_Host
static int tolua_set_coord__cache__CacheConfig_Host(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cache__CacheConfig_Port
static int tolua_get_coord__cache__CacheConfig_Port(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cache__CacheConfig_Port
static int tolua_set_coord__cache__CacheConfig_Port(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((int16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ExpireTime of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cache__CacheConfig_ExpireTime
static int tolua_get_coord__cache__CacheConfig_ExpireTime(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ExpireTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ExpireTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ExpireTime of class  coord::cache::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cache__CacheConfig_ExpireTime
static int tolua_set_coord__cache__CacheConfig_ExpireTime(lua_State* tolua_S)
{
  coord::cache::CacheConfig* self = (coord::cache::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ExpireTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ExpireTime = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::cache::CacheReader */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_CacheReader_String00
static int tolua_coord_coord_cache_CacheReader_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::CacheReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::CacheReader* self = (coord::cache::CacheReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->String();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'String'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Empty of class  coord::cache::CacheReader */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_CacheReader_Empty00
static int tolua_coord_coord_cache_CacheReader_Empty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::CacheReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::CacheReader* self = (coord::cache::CacheReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Empty'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Empty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Empty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Error of class  coord::cache::CacheReader */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_CacheReader_Error00
static int tolua_coord_coord_cache_CacheReader_Error00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::CacheReader",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::CacheReader* self = (coord::cache::CacheReader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Error'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Error();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Error'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Notify of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_Cluster_Notify00
static int tolua_coord_coord_cluster_Cluster_Notify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::Cluster",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
  const char* node = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* route = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Notify'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Notify(node,route,data);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Notify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Request of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_Cluster_Request00
static int tolua_coord_coord_cluster_Cluster_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::Cluster",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
  const char* node = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* route = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->Request(node,route,data);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Request of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_Cluster_Request01
static int tolua_coord_coord_cluster_Cluster_Request01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::Cluster",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"coord::protobuf::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
  const char* node = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* route = ((const char*)  tolua_tostring(tolua_S,3,0));
  coord::protobuf::Reflect* proto = ((coord::protobuf::Reflect*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
   coord::Promise* tolua_ret = (coord::Promise*)  self->Request(node,route,*proto);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Promise");
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_cluster_Cluster_Request00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reload of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_Cluster_Reload00
static int tolua_coord_coord_cluster_Cluster_Reload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::Cluster",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reload'",NULL);
#endif
  {
   self->Reload();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reload'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Name of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__Cluster_Name
static int tolua_get_coord__cluster__Cluster_Name(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Name of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__Cluster_Name
static int tolua_set_coord__cluster__Cluster_Name(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FullName of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__Cluster_FullName
static int tolua_get_coord__cluster__Cluster_FullName(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FullName'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->FullName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: FullName of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__Cluster_FullName
static int tolua_set_coord__cluster__Cluster_FullName(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'FullName'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->FullName = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Version of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__Cluster_Version
static int tolua_get_coord__cluster__Cluster_Version(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Version'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Version);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Version of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__Cluster_Version
static int tolua_set_coord__cluster__Cluster_Version(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Version'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Version = ((uint64_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Router of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__Cluster_Router_ptr
static int tolua_get_coord__cluster__Cluster_Router_ptr(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Router,"coord::cluster::ClusterRouter");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Router of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__Cluster_Router_ptr
static int tolua_set_coord__cluster__Cluster_Router_ptr(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::cluster::ClusterRouter",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Router = ((coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Driver of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_Driver
static int tolua_get_coord__cluster__ClusterConfig_Driver(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Driver'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Driver);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Driver of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_Driver
static int tolua_set_coord__cluster__ClusterConfig_Driver(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Driver'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Driver = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_Host
static int tolua_get_coord__cluster__ClusterConfig_Host(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_Host
static int tolua_set_coord__cluster__ClusterConfig_Host(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_Port
static int tolua_get_coord__cluster__ClusterConfig_Port(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_Port
static int tolua_set_coord__cluster__ClusterConfig_Port(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Heartbeat of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_Heartbeat
static int tolua_get_coord__cluster__ClusterConfig_Heartbeat(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Heartbeat'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Heartbeat);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Heartbeat of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_Heartbeat
static int tolua_set_coord__cluster__ClusterConfig_Heartbeat(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Heartbeat'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Heartbeat = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Expire of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_Expire
static int tolua_get_coord__cluster__ClusterConfig_Expire(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Expire'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Expire);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Expire of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_Expire
static int tolua_set_coord__cluster__ClusterConfig_Expire(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Expire'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Expire = ((uint32_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Name of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_Name
static int tolua_get_coord__cluster__ClusterConfig_Name(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Name of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_Name
static int tolua_set_coord__cluster__ClusterConfig_Name(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Name = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RegisterInterval of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_RegisterInterval
static int tolua_get_coord__cluster__ClusterConfig_RegisterInterval(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RegisterInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RegisterInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RegisterInterval of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_RegisterInterval
static int tolua_set_coord__cluster__ClusterConfig_RegisterInterval(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RegisterInterval'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RegisterInterval = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ReloadInterval of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_ReloadInterval
static int tolua_get_coord__cluster__ClusterConfig_ReloadInterval(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ReloadInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ReloadInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ReloadInterval of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_ReloadInterval
static int tolua_set_coord__cluster__ClusterConfig_ReloadInterval(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ReloadInterval'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ReloadInterval = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: ReconnectInterval of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_ReconnectInterval
static int tolua_get_coord__cluster__ClusterConfig_ReconnectInterval(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ReconnectInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ReconnectInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ReconnectInterval of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_ReconnectInterval
static int tolua_set_coord__cluster__ClusterConfig_ReconnectInterval(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ReconnectInterval'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ReconnectInterval = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RecvBuffer of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterConfig_RecvBuffer
static int tolua_get_coord__cluster__ClusterConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBuffer'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RecvBuffer);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RecvBuffer of class  coord::cluster::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterConfig_RecvBuffer
static int tolua_set_coord__cluster__ClusterConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::cluster::ClusterConfig* self = (coord::cluster::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBuffer'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RecvBuffer = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Notify of class  coord::cluster::ClusterRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRouter_Notify00
static int tolua_coord_coord_cluster_ClusterRouter_Notify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRouter* self = (coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Notify'",NULL);
#endif
  {
return self->Notify(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Notify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Request of class  coord::cluster::ClusterRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRouter_Request00
static int tolua_coord_coord_cluster_ClusterRouter_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRouter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRouter* self = (coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* route = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  int ref = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Request(route,object,ref);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Request of class  coord::cluster::ClusterRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRouter_Request01
static int tolua_coord_coord_cluster_ClusterRouter_Request01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
 {
  coord::cluster::ClusterRouter* self = (coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
return self->Request(L);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_cluster_ClusterRouter_Request00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Trace of class  coord::cluster::ClusterRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRouter_Trace00
static int tolua_coord_coord_cluster_ClusterRouter_Trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRouter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRouter* self = (coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Trace'",NULL);
#endif
  {
   self->Trace();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResponse of class  coord::cluster::Request */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_Request_GetResponse00
static int tolua_coord_coord_cluster_Request_GetResponse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::Request",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::Request* self = (coord::cluster::Request*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResponse'",NULL);
#endif
  {
   coord::cluster::Response* tolua_ret = (coord::cluster::Response*)  self->GetResponse();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cluster::Response");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResponse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Then of class  coord::cluster::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_Promise_Then00
static int tolua_coord_coord_cluster_Promise_Then00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::Promise* self = (coord::cluster::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Then'",NULL);
#endif
  {
return self->Then(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Then'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Else of class  coord::cluster::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_Promise_Else00
static int tolua_coord_coord_cluster_Promise_Else00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::Promise* self = (coord::cluster::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Else'",NULL);
#endif
  {
return self->Else(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Else'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: coord::net::newTcpClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_net_newTcpClient00
static int tolua_coord_coord_net_newTcpClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,1,0));
  {
   coord::net::TcpClient* tolua_ret = (coord::net::TcpClient*)  coord::net::newTcpClient(coord);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::net::TcpClient");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'newTcpClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__managed__ManagedConfig_Host
static int tolua_get_coord__managed__ManagedConfig_Host(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__managed__ManagedConfig_Host
static int tolua_set_coord__managed__ManagedConfig_Host(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__managed__ManagedConfig_Port
static int tolua_get_coord__managed__ManagedConfig_Port(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__managed__ManagedConfig_Port
static int tolua_set_coord__managed__ManagedConfig_Port(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: User of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__managed__ManagedConfig_User
static int tolua_get_coord__managed__ManagedConfig_User(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->User);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: User of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__managed__ManagedConfig_User
static int tolua_set_coord__managed__ManagedConfig_User(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->User = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Password of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__managed__ManagedConfig_Password
static int tolua_get_coord__managed__ManagedConfig_Password(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  coord::managed::ManagedConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__managed__ManagedConfig_Password
static int tolua_set_coord__managed__ManagedConfig_Password(lua_State* tolua_S)
{
  coord::managed::ManagedConfig* self = (coord::managed::ManagedConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Password = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __net of class  coord::managed::ManagedAgent */
#ifndef TOLUA_DISABLE_tolua_get_coord__managed__ManagedAgent___net__ITcpAgentHandler__
static int tolua_get_coord__managed__ManagedAgent___net__ITcpAgentHandler__(lua_State* tolua_S)
{
  coord::managed::ManagedAgent* self = (coord::managed::ManagedAgent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__net'",NULL);
#endif
#ifdef __cplusplus
  tolua_pushusertype(tolua_S,(void*)static_cast<coord::net::ITcpAgentHandler*>(self), "coord::net::ITcpAgentHandler");
#else
  tolua_pushusertype(tolua_S,(void*)((coord::net::ITcpAgentHandler*)self), "coord::net::ITcpAgentHandler");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Request of class  coord::worker::Worker */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_Worker_Request00
static int tolua_coord_coord_worker_Worker_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::Worker",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::Worker* self = (coord::worker::Worker*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
return self->Request(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Notify of class  coord::worker::Worker */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_Worker_Notify00
static int tolua_coord_coord_worker_Worker_Notify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::Worker",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::Worker* self = (coord::worker::Worker*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Notify'",NULL);
#endif
  {
return self->Notify(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Notify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Request of class  coord::worker::WorkerRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_WorkerRouter_Request00
static int tolua_coord_coord_worker_WorkerRouter_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::WorkerRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::WorkerRouter* self = (coord::worker::WorkerRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
return self->Request(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Notify of class  coord::worker::WorkerRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_WorkerRouter_Notify00
static int tolua_coord_coord_worker_WorkerRouter_Notify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::WorkerRouter",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::WorkerRouter* self = (coord::worker::WorkerRouter*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Notify'",NULL);
#endif
  {
return self->Notify(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Notify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Trace of class  coord::worker::WorkerRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_WorkerRouter_Trace00
static int tolua_coord_coord_worker_WorkerRouter_Trace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::WorkerRouter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::WorkerRouter* self = (coord::worker::WorkerRouter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Trace'",NULL);
#endif
  {
   self->Trace();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Trace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Router of class  coord::worker::WorkerSlave */
#ifndef TOLUA_DISABLE_tolua_get_coord__worker__WorkerSlave_Router_ptr
static int tolua_get_coord__worker__WorkerSlave_Router_ptr(lua_State* tolua_S)
{
  coord::worker::WorkerSlave* self = (coord::worker::WorkerSlave*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Router,"coord::worker::WorkerRouter");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Router of class  coord::worker::WorkerSlave */
#ifndef TOLUA_DISABLE_tolua_set_coord__worker__WorkerSlave_Router_ptr
static int tolua_set_coord__worker__WorkerSlave_Router_ptr(lua_State* tolua_S)
{
  coord::worker::WorkerSlave* self = (coord::worker::WorkerSlave*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::worker::WorkerRouter",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Router = ((coord::worker::WorkerRouter*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResponse of class  coord::worker::Request */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_Request_GetResponse00
static int tolua_coord_coord_worker_Request_GetResponse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::Request",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::Request* self = (coord::worker::Request*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResponse'",NULL);
#endif
  {
   coord::worker::Response* tolua_ret = (coord::worker::Response*)  self->GetResponse();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::worker::Response");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResponse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Then of class  coord::worker::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_Promise_Then00
static int tolua_coord_coord_worker_Promise_Then00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::Promise* self = (coord::worker::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Then'",NULL);
#endif
  {
return self->Then(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Then'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Else of class  coord::worker::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_Promise_Else00
static int tolua_coord_coord_worker_Promise_Else00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::Promise",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::Promise* self = (coord::worker::Promise*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Else'",NULL);
#endif
  {
return self->Else(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Else'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Using of class  coord::worker::Promise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_worker_Promise_Using00
static int tolua_coord_coord_worker_Promise_Using00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::worker::Promise",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::BaseRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::worker::Promise* self = (coord::worker::Promise*)  tolua_tousertype(tolua_S,1,0);
  coord::BaseRequest* request = ((coord::BaseRequest*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Using'",NULL);
#endif
  {
   coord::worker::Promise* tolua_ret = (coord::worker::Promise*)  self->Using(request);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::worker::Promise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Using'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefaultConfig of class  coord::login::LoginSvr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_login_LoginSvr_DefaultConfig00
static int tolua_coord_coord_login_LoginSvr_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::login::LoginSvr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::login::LoginSvr* self = (coord::login::LoginSvr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::login::LoginConfig* tolua_ret = (coord::login::LoginConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::login::LoginConfig");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefaultConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Host of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_Host
static int tolua_get_coord__login__LoginConfig_Host(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_Host
static int tolua_set_coord__login__LoginConfig_Host(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_unsigned_Port
static int tolua_get_coord__login__LoginConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_unsigned_Port
static int tolua_set_coord__login__LoginConfig_unsigned_Port(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Port = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Backlog of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_Backlog
static int tolua_get_coord__login__LoginConfig_Backlog(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Backlog);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Backlog of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_Backlog
static int tolua_set_coord__login__LoginConfig_Backlog(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Backlog = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: RecvBufferSize of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_RecvBufferSize
static int tolua_get_coord__login__LoginConfig_RecvBufferSize(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBufferSize'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RecvBufferSize);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RecvBufferSize of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_RecvBufferSize
static int tolua_set_coord__login__LoginConfig_RecvBufferSize(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBufferSize'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->RecvBufferSize = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLEncrypt of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_SSLEncrypt
static int tolua_get_coord__login__LoginConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->SSLEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLEncrypt of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_SSLEncrypt
static int tolua_set_coord__login__LoginConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLEncrypt = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLPemFile of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_SSLPemFile
static int tolua_get_coord__login__LoginConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLPemFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLPemFile of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_SSLPemFile
static int tolua_set_coord__login__LoginConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLPemFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SSLKeyFile of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_SSLKeyFile
static int tolua_get_coord__login__LoginConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLKeyFile of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_SSLKeyFile
static int tolua_set_coord__login__LoginConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->SSLKeyFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Cluster of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__login__LoginConfig_Cluster
static int tolua_get_coord__login__LoginConfig_Cluster(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Cluster);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Cluster of class  coord::login::LoginConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__login__LoginConfig_Cluster
static int tolua_set_coord__login__LoginConfig_Cluster(lua_State* tolua_S)
{
  coord::login::LoginConfig* self = (coord::login::LoginConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Cluster'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Cluster = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetString of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_SetString00
static int tolua_coord_coord_json_Reflect_SetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetString'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetString(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumber of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_SetNumber00
static int tolua_coord_coord_json_Reflect_SetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  double value = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumber'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetNumber(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInteger of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_SetInteger00
static int tolua_coord_coord_json_Reflect_SetInteger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInteger'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetInteger(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInteger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBool of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_SetBool00
static int tolua_coord_coord_json_Reflect_SetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBool'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetBool(key,value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetObject of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_SetObject00
static int tolua_coord_coord_json_Reflect_SetObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetObject'",NULL);
#endif
  {
   coord::json::Reflect tolua_ret = (coord::json::Reflect)  self->SetObject(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::json::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::json::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetArray of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_SetArray00
static int tolua_coord_coord_json_Reflect_SetArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetArray'",NULL);
#endif
  {
   coord::json::Reflect tolua_ret = (coord::json::Reflect)  self->SetArray(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::json::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::json::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetString of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetString00
static int tolua_coord_coord_json_Reflect_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetString'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetString(key);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumber of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetNumber00
static int tolua_coord_coord_json_Reflect_GetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumber'",NULL);
#endif
  {
   double tolua_ret = (double)  self->GetNumber(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInteger of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetInteger00
static int tolua_coord_coord_json_Reflect_GetInteger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInteger'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetInteger(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInteger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBool of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetBool00
static int tolua_coord_coord_json_Reflect_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBool(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetObject of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetObject00
static int tolua_coord_coord_json_Reflect_GetObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetObject'",NULL);
#endif
  {
   coord::json::Reflect tolua_ret = (coord::json::Reflect)  self->GetObject(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::json::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::json::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetArray of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetArray00
static int tolua_coord_coord_json_Reflect_GetArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetArray'",NULL);
#endif
  {
   coord::json::Reflect tolua_ret = (coord::json::Reflect)  self->GetArray(key);
   {
#ifdef __cplusplus
    void* tolua_obj = new coord::json::Reflect(tolua_ret);
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(coord::json::Reflect));
    tolua_pushusertype_and_takeownership(tolua_S,tolua_obj,"coord::json::Reflect");
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsObject of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsObject00
static int tolua_coord_coord_json_Reflect_IsObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsObject'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsObject(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsArray of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsArray00
static int tolua_coord_coord_json_Reflect_IsArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsArray'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsArray(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsString of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsString00
static int tolua_coord_coord_json_Reflect_IsString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsString'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsString(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNumber of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsNumber00
static int tolua_coord_coord_json_Reflect_IsNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNumber'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNumber(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInteger of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsInteger00
static int tolua_coord_coord_json_Reflect_IsInteger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInteger'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInteger(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInteger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNull of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsNull00
static int tolua_coord_coord_json_Reflect_IsNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNull'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNull(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBool of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsBool00
static int tolua_coord_coord_json_Reflect_IsBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBool(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNumber of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_AddNumber00
static int tolua_coord_coord_json_Reflect_AddNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  double value = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNumber'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddNumber(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddInteger of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_AddInteger00
static int tolua_coord_coord_json_Reflect_AddInteger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddInteger'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddInteger(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddInteger'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddBool of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_AddBool00
static int tolua_coord_coord_json_Reflect_AddBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddBool'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddBool(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddString of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_AddString00
static int tolua_coord_coord_json_Reflect_AddString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddString'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddString(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumber of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetNumber01
static int tolua_coord_coord_json_Reflect_GetNumber01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumber'",NULL);
#endif
  {
   double tolua_ret = (double)  self->GetNumber(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_GetNumber00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInteger of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetInteger01
static int tolua_coord_coord_json_Reflect_GetInteger01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInteger'",NULL);
#endif
  {
   int tolua_ret = (int)  self->GetInteger(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_GetInteger00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBool of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_GetBool01
static int tolua_coord_coord_json_Reflect_GetBool01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBool(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_GetBool00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsObject of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsObject01
static int tolua_coord_coord_json_Reflect_IsObject01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsObject'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsObject(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_IsObject00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsArray of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsArray01
static int tolua_coord_coord_json_Reflect_IsArray01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsArray'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsArray(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_IsArray00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsString of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsString01
static int tolua_coord_coord_json_Reflect_IsString01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsString'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsString(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_IsString00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNumber of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsNumber01
static int tolua_coord_coord_json_Reflect_IsNumber01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNumber'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNumber(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_IsNumber00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInteger of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsInteger01
static int tolua_coord_coord_json_Reflect_IsInteger01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInteger'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInteger(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_IsInteger00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNull of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsNull01
static int tolua_coord_coord_json_Reflect_IsNull01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNull'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNull(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_IsNull00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBool of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_IsBool01
static int tolua_coord_coord_json_Reflect_IsBool01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
  size_t index = ((size_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBool(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_json_Reflect_IsBool00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: isObject of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_isObject00
static int tolua_coord_coord_json_Reflect_isObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isObject'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isObject();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isArray of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_isArray00
static int tolua_coord_coord_json_Reflect_isArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isArray'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isArray();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isString of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_isString00
static int tolua_coord_coord_json_Reflect_isString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isString'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isString();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isNumber of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_isNumber00
static int tolua_coord_coord_json_Reflect_isNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isNumber'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isNumber();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isNull of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_isNull00
static int tolua_coord_coord_json_Reflect_isNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isNull'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isNull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBool of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_isBool00
static int tolua_coord_coord_json_Reflect_isBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBool'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBool();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToString of class  coord::json::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_json_Reflect_ToString00
static int tolua_coord_coord_json_Reflect_ToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::json::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToString'",NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->ToString();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::GetCwd */
#ifndef TOLUA_DISABLE_tolua_coord_os_GetCwd00
static int tolua_coord_os_GetCwd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  {
return os::GetCwd(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCwd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::RealPath */
#ifndef TOLUA_DISABLE_tolua_coord_os_RealPath00
static int tolua_coord_os_RealPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  {
return os::RealPath(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RealPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::ListDir */
#ifndef TOLUA_DISABLE_tolua_coord_os_ListDir00
static int tolua_coord_os_ListDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  {
return os::ListDir(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ListDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::path::BaseName */
#ifndef TOLUA_DISABLE_tolua_coord_os_path_BaseName00
static int tolua_coord_os_path_BaseName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  lua_State* L =  tolua_S;
  {
return os::path::BaseName(L);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BaseName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::path::BaseName */
#ifndef TOLUA_DISABLE_tolua_coord_os_path_BaseName01
static int tolua_coord_os_path_BaseName01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  os::path::BaseName(path);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_os_path_BaseName00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::path::DirName */
#ifndef TOLUA_DISABLE_tolua_coord_os_path_DirName00
static int tolua_coord_os_path_DirName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* path = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   const char* tolua_ret = (const char*)  os::path::DirName(path);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DirName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::path::Exist */
#ifndef TOLUA_DISABLE_tolua_coord_os_path_Exist00
static int tolua_coord_os_path_Exist00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* dir = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  os::path::Exist(dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Exist'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: os::path::IsDir */
#ifndef TOLUA_DISABLE_tolua_coord_os_path_IsDir00
static int tolua_coord_os_path_IsDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* dir = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  os::path::IsDir(dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_coord_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Coord","coord::Coord","",NULL);
   tolua_beginmodule(tolua_S,"Coord");
    tolua_function(tolua_S,"Destory",tolua_coord_coord_Coord_Destory00);
    tolua_function(tolua_S,"CreateScene",tolua_coord_coord_Coord_CreateScene00);
    tolua_function(tolua_S,"Sleep",tolua_coord_coord_Coord_Sleep00);
    tolua_function(tolua_S,"Log",tolua_coord_coord_Coord_Log00);
    tolua_function(tolua_S,"Log",tolua_coord_coord_Coord_Log01);
    tolua_function(tolua_S,"LogFatal",tolua_coord_coord_Coord_LogFatal00);
    tolua_function(tolua_S,"LogError",tolua_coord_coord_Coord_LogError00);
    tolua_function(tolua_S,"LogWarn",tolua_coord_coord_Coord_LogWarn00);
    tolua_function(tolua_S,"LogInfo",tolua_coord_coord_Coord_LogInfo00);
    tolua_function(tolua_S,"LogDebug",tolua_coord_coord_Coord_LogDebug00);
    tolua_function(tolua_S,"LogMsg",tolua_coord_coord_Coord_LogMsg00);
    tolua_function(tolua_S,"LogCloseLevel",tolua_coord_coord_Coord_LogCloseLevel00);
    tolua_function(tolua_S,"LogOpenLevel",tolua_coord_coord_Coord_LogOpenLevel00);
    tolua_function(tolua_S,"LogSetLevel",tolua_coord_coord_Coord_LogSetLevel00);
    tolua_function(tolua_S,"CoreLogFatal",tolua_coord_coord_Coord_CoreLogFatal00);
    tolua_function(tolua_S,"CoreLogError",tolua_coord_coord_Coord_CoreLogError00);
    tolua_function(tolua_S,"CoreLogWarn",tolua_coord_coord_Coord_CoreLogWarn00);
    tolua_function(tolua_S,"CoreLogInfo",tolua_coord_coord_Coord_CoreLogInfo00);
    tolua_function(tolua_S,"CoreLogDebug",tolua_coord_coord_Coord_CoreLogDebug00);
    tolua_function(tolua_S,"CoreLogMsg",tolua_coord_coord_Coord_CoreLogMsg00);
    tolua_function(tolua_S,"AddScript",tolua_coord_coord_Coord_AddScript00);
    tolua_function(tolua_S,"AddComponent",tolua_coord_coord_Coord_AddComponent00);
    tolua_function(tolua_S,"SetTimeout",tolua_coord_coord_Coord_SetTimeout00);
    tolua_function(tolua_S,"SetInterval",tolua_coord_coord_Coord_SetInterval00);
    tolua_function(tolua_S,"SetCron",tolua_coord_coord_Coord_SetCron00);
    tolua_function(tolua_S,"Emit",tolua_coord_coord_Coord_Emit00);
    tolua_function(tolua_S,"Destory",tolua_coord_coord_Coord_Destory01);
    tolua_function(tolua_S,"Destory",tolua_coord_coord_Coord_Destory02);
    tolua_function(tolua_S,"DontDestory",tolua_coord_coord_Coord_DontDestory00);
    tolua_function(tolua_S,"NewHttpServer",tolua_coord_coord_Coord_NewHttpServer00);
    tolua_function(tolua_S,"Now",tolua_coord_coord_Coord_Now00);
    tolua_function(tolua_S,"Time",tolua_coord_coord_Coord_Time00);
    tolua_function(tolua_S,"NanoTime",tolua_coord_coord_Coord_NanoTime00);
    tolua_function(tolua_S,"SQLConfig",tolua_coord_coord_Coord_SQLConfig00);
    tolua_function(tolua_S,"RedisConfig",tolua_coord_coord_Coord_RedisConfig00);
    tolua_function(tolua_S,"RedisAsyncConfig",tolua_coord_coord_Coord_RedisAsyncConfig00);
    tolua_variable(tolua_S,"Config",tolua_get_coord__Coord_Config_ptr,tolua_set_coord__Coord_Config_ptr);
    tolua_variable(tolua_S,"Script",tolua_get_coord__Coord_Script_ptr,tolua_set_coord__Coord_Script_ptr);
    tolua_variable(tolua_S,"Gate",tolua_get_coord__Coord_Gate_ptr,tolua_set_coord__Coord_Gate_ptr);
    tolua_variable(tolua_S,"HttpServer",tolua_get_coord__Coord_HttpServer_ptr,tolua_set_coord__Coord_HttpServer_ptr);
    tolua_variable(tolua_S,"Proto",tolua_get_coord__Coord_Proto_ptr,tolua_set_coord__Coord_Proto_ptr);
    tolua_variable(tolua_S,"RedisMgr",tolua_get_coord__Coord_RedisMgr_ptr,tolua_set_coord__Coord_RedisMgr_ptr);
    tolua_variable(tolua_S,"Cache",tolua_get_coord__Coord_Cache_ptr,tolua_set_coord__Coord_Cache_ptr);
    tolua_variable(tolua_S,"Cluster",tolua_get_coord__Coord_Cluster_ptr,tolua_set_coord__Coord_Cluster_ptr);
    tolua_variable(tolua_S,"ConfigPath",tolua_get_coord__Coord_ConfigPath,tolua_set_coord__Coord_ConfigPath);
    tolua_variable(tolua_S,"Managed",tolua_get_coord__Coord_Managed_ptr,tolua_set_coord__Coord_Managed_ptr);
    tolua_variable(tolua_S,"WorkerSlave",tolua_get_coord__Coord_WorkerSlave_ptr,tolua_set_coord__Coord_WorkerSlave_ptr);
    tolua_variable(tolua_S,"Worker",tolua_get_coord__Coord_Worker_ptr,tolua_set_coord__Coord_Worker_ptr);
    tolua_variable(tolua_S,"Name",tolua_get_coord__Coord_Name,tolua_set_coord__Coord_Name);
    tolua_variable(tolua_S,"Environment",tolua_get_coord__Coord_Environment_ptr,tolua_set_coord__Coord_Environment_ptr);
    tolua_variable(tolua_S,"Closure",tolua_get_coord__Coord_Closure_ptr,tolua_set_coord__Coord_Closure_ptr);
    tolua_variable(tolua_S,"Login",tolua_get_coord__Coord_Login_ptr,tolua_set_coord__Coord_Login_ptr);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"BasicConfig","coord::BasicConfig","",NULL);
   tolua_beginmodule(tolua_S,"BasicConfig");
    tolua_variable(tolua_S,"Env",tolua_get_coord__BasicConfig_Env,tolua_set_coord__BasicConfig_Env);
    tolua_variable(tolua_S,"Main",tolua_get_coord__BasicConfig_Main,tolua_set_coord__BasicConfig_Main);
    tolua_variable(tolua_S,"Scene",tolua_get_coord__BasicConfig_Scene,tolua_set_coord__BasicConfig_Scene);
    tolua_variable(tolua_S,"Registery",tolua_get_coord__BasicConfig_Registery,tolua_set_coord__BasicConfig_Registery);
    tolua_variable(tolua_S,"Package",tolua_get_coord__BasicConfig_Package,tolua_set_coord__BasicConfig_Package);
    tolua_variable(tolua_S,"GC",tolua_get_coord__BasicConfig_GC,tolua_set_coord__BasicConfig_GC);
    tolua_variable(tolua_S,"Update",tolua_get_coord__BasicConfig_Update,tolua_set_coord__BasicConfig_Update);
    tolua_variable(tolua_S,"Worker",tolua_get_coord__BasicConfig_Worker,tolua_set_coord__BasicConfig_Worker);
    tolua_variable(tolua_S,"WorkerNum",tolua_get_coord__BasicConfig_WorkerNum,tolua_set_coord__BasicConfig_WorkerNum);
    tolua_variable(tolua_S,"Proto",tolua_get_coord__BasicConfig_Proto,tolua_set_coord__BasicConfig_Proto);
    tolua_variable(tolua_S,"Name",tolua_get_coord__BasicConfig_Name,tolua_set_coord__BasicConfig_Name);
    tolua_variable(tolua_S,"Version",tolua_get_coord__BasicConfig_Version,tolua_set_coord__BasicConfig_Version);
    tolua_variable(tolua_S,"ShortVersion",tolua_get_coord__BasicConfig_ShortVersion,tolua_set_coord__BasicConfig_ShortVersion);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Config","coord::Config","",NULL);
   tolua_beginmodule(tolua_S,"Config");
    tolua_variable(tolua_S,"Basic",tolua_get_coord__Config_Basic,tolua_set_coord__Config_Basic);
    tolua_variable(tolua_S,"Web",tolua_get_coord__Config_Web,tolua_set_coord__Config_Web);
    tolua_variable(tolua_S,"Gate",tolua_get_coord__Config_Gate,tolua_set_coord__Config_Gate);
    tolua_variable(tolua_S,"Cache",tolua_get_coord__Config_Cache,tolua_set_coord__Config_Cache);
    tolua_variable(tolua_S,"Cluster",tolua_get_coord__Config_Cluster,tolua_set_coord__Config_Cluster);
    tolua_variable(tolua_S,"Managed",tolua_get_coord__Config_Managed,tolua_set_coord__Config_Managed);
    tolua_variable(tolua_S,"Login",tolua_get_coord__Config_Login,tolua_set_coord__Config_Login);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"script",0);
   tolua_beginmodule(tolua_S,"script");
    tolua_cclass(tolua_S,"Script","coord::script::Script","",NULL);
    tolua_beginmodule(tolua_S,"Script");
     tolua_function(tolua_S,"ToString",tolua_coord_coord_script_Script_ToString00);
     tolua_function(tolua_S,"ToShortString",tolua_coord_coord_script_Script_ToShortString00);
     tolua_function(tolua_S,"Encode",tolua_coord_coord_script_Script_Encode00);
     tolua_function(tolua_S,"Decode",tolua_coord_coord_script_Script_Decode00);
     tolua_function(tolua_S,"ToJson",tolua_coord_coord_script_Script_ToJson00);
     tolua_function(tolua_S,"FromJson",tolua_coord_coord_script_Script_FromJson00);
     tolua_variable(tolua_S,"Path",tolua_get_coord__script__Script_Path,tolua_set_coord__script__Script_Path);
     tolua_variable(tolua_S,"Main",tolua_get_coord__script__Script_Main,tolua_set_coord__script__Script_Main);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"script",0);
   tolua_beginmodule(tolua_S,"script");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Reflect","coord::script::Reflect","",tolua_collect_coord__script__Reflect);
    #else
    tolua_cclass(tolua_S,"Reflect","coord::script::Reflect","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Reflect");
     tolua_function(tolua_S,"SetBool",tolua_coord_coord_script_Reflect_SetBool00);
     tolua_function(tolua_S,"SetString",tolua_coord_coord_script_Reflect_SetString00);
     tolua_function(tolua_S,"SetNumber",tolua_coord_coord_script_Reflect_SetNumber00);
     tolua_function(tolua_S,"SetTable",tolua_coord_coord_script_Reflect_SetTable00);
     tolua_function(tolua_S,"SetBool",tolua_coord_coord_script_Reflect_SetBool01);
     tolua_function(tolua_S,"SetString",tolua_coord_coord_script_Reflect_SetString01);
     tolua_function(tolua_S,"SetNumber",tolua_coord_coord_script_Reflect_SetNumber01);
     tolua_function(tolua_S,"SetTable",tolua_coord_coord_script_Reflect_SetTable01);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Type","coord::Type","",NULL);
   tolua_beginmodule(tolua_S,"Type");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Argument","coord::Argument","",NULL);
   tolua_beginmodule(tolua_S,"Argument");
    tolua_function(tolua_S,"GetNumber",tolua_coord_coord_Argument_GetNumber00);
    tolua_function(tolua_S,"GetBool",tolua_coord_coord_Argument_GetBool00);
    tolua_function(tolua_S,"GetString",tolua_coord_coord_Argument_GetString00);
    tolua_function(tolua_S,"GetProto",tolua_coord_coord_Argument_GetProto00);
    tolua_function(tolua_S,"GetTable",tolua_coord_coord_Argument_GetTable00);
    tolua_function(tolua_S,"IsNone",tolua_coord_coord_Argument_IsNone00);
    tolua_function(tolua_S,"IsNil",tolua_coord_coord_Argument_IsNil00);
    tolua_function(tolua_S,"IsNumber",tolua_coord_coord_Argument_IsNumber00);
    tolua_function(tolua_S,"IsString",tolua_coord_coord_Argument_IsString00);
    tolua_function(tolua_S,"IsProto",tolua_coord_coord_Argument_IsProto00);
    tolua_function(tolua_S,"IsBool",tolua_coord_coord_Argument_IsBool00);
    tolua_function(tolua_S,"IsTable",tolua_coord_coord_Argument_IsTable00);
    tolua_function(tolua_S,"AddNumber",tolua_coord_coord_Argument_AddNumber00);
    tolua_function(tolua_S,"AddString",tolua_coord_coord_Argument_AddString00);
    tolua_function(tolua_S,"AddNil",tolua_coord_coord_Argument_AddNil00);
    tolua_function(tolua_S,"AddBool",tolua_coord_coord_Argument_AddBool00);
    tolua_function(tolua_S,"Count",tolua_coord_coord_Argument_Count00);
    tolua_function(tolua_S,"Trace",tolua_coord_coord_Argument_Trace00);
    tolua_function(tolua_S,"Pack",tolua_coord_coord_Argument_Pack00);
    tolua_function(tolua_S,"Unpack",tolua_coord_coord_Argument_Unpack00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Environment","coord::Environment","",NULL);
   tolua_beginmodule(tolua_S,"Environment");
    tolua_function(tolua_S,"Get",tolua_coord_coord_Environment_Get00);
    tolua_variable(tolua_S,"Version",tolua_get_coord__Environment_Version,tolua_set_coord__Environment_Version);
    tolua_variable(tolua_S,"ExecPath",tolua_get_coord__Environment_ExecPath,tolua_set_coord__Environment_ExecPath);
    tolua_variable(tolua_S,"ExecDir",tolua_get_coord__Environment_ExecDir,tolua_set_coord__Environment_ExecDir);
    tolua_variable(tolua_S,"ProjectDir",tolua_get_coord__Environment_ProjectDir,tolua_set_coord__Environment_ProjectDir);
    tolua_variable(tolua_S,"WorkingDir",tolua_get_coord__Environment_WorkingDir,tolua_set_coord__Environment_WorkingDir);
    tolua_variable(tolua_S,"HomeDir",tolua_get_coord__Environment_HomeDir,tolua_set_coord__Environment_HomeDir);
    tolua_variable(tolua_S,"CoordDir",tolua_get_coord__Environment_CoordDir,tolua_set_coord__Environment_CoordDir);
    tolua_variable(tolua_S,"ConfigPath",tolua_get_coord__Environment_ConfigPath,tolua_set_coord__Environment_ConfigPath);
    tolua_variable(tolua_S,"ConfigDir",tolua_get_coord__Environment_ConfigDir,tolua_set_coord__Environment_ConfigDir);
    tolua_variable(tolua_S,"Package",tolua_get_coord__Environment_Package,tolua_set_coord__Environment_Package);
    tolua_variable(tolua_S,"ProcDir",tolua_get_coord__Environment_ProcDir,tolua_set_coord__Environment_ProcDir);
    tolua_variable(tolua_S,"RunDir",tolua_get_coord__Environment_RunDir,tolua_set_coord__Environment_RunDir);
    tolua_variable(tolua_S,"PidPath",tolua_get_coord__Environment_PidPath,tolua_set_coord__Environment_PidPath);
    tolua_variable(tolua_S,"Name",tolua_get_coord__Environment_Name,tolua_set_coord__Environment_Name);
    tolua_variable(tolua_S,"ManagedSockPath",tolua_get_coord__Environment_ManagedSockPath,tolua_set_coord__Environment_ManagedSockPath);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Destoryable","coord::Destoryable","",NULL);
   tolua_beginmodule(tolua_S,"Destoryable");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"BaseRequest","coord::BaseRequest","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"BaseRequest");
    tolua_function(tolua_S,"Proto",tolua_coord_coord_BaseRequest_Proto00);
    tolua_function(tolua_S,"String",tolua_coord_coord_BaseRequest_String00);
    tolua_function(tolua_S,"Len",tolua_coord_coord_BaseRequest_Len00);
    tolua_function(tolua_S,"Args",tolua_coord_coord_BaseRequest_Args00);
    tolua_function(tolua_S,"String",tolua_coord_coord_BaseRequest_String01);
    tolua_function(tolua_S,"Unpack",tolua_coord_coord_BaseRequest_Unpack00);
    tolua_function(tolua_S,"Table",tolua_coord_coord_BaseRequest_Table00);
    tolua_function(tolua_S,"Json",tolua_coord_coord_BaseRequest_Json00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"BaseResponse","coord::BaseResponse","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"BaseResponse");
    tolua_function(tolua_S,"Proto",tolua_coord_coord_BaseResponse_Proto00);
    tolua_function(tolua_S,"Proto",tolua_coord_coord_BaseResponse_Proto01);
    tolua_function(tolua_S,"Proto",tolua_coord_coord_BaseResponse_Proto02);
    tolua_function(tolua_S,"String",tolua_coord_coord_BaseResponse_String00);
    tolua_function(tolua_S,"Args",tolua_coord_coord_BaseResponse_Args00);
    tolua_function(tolua_S,"Pack",tolua_coord_coord_BaseResponse_Pack00);
    tolua_function(tolua_S,"Table",tolua_coord_coord_BaseResponse_Table00);
    tolua_function(tolua_S,"Resolve",tolua_coord_coord_BaseResponse_Resolve00);
    tolua_function(tolua_S,"Reject",tolua_coord_coord_BaseResponse_Reject00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"BaseResult","coord::BaseResult","coord::BaseRequest",NULL);
   tolua_beginmodule(tolua_S,"BaseResult");
    tolua_variable(tolua_S,"Code",tolua_get_coord__BaseResult_Code,tolua_set_coord__BaseResult_Code);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Promise","coord::Promise","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"Promise");
    tolua_function(tolua_S,"Then",tolua_coord_coord_Promise_Then00);
    tolua_function(tolua_S,"Else",tolua_coord_coord_Promise_Else00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Object","coord::Object","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"Object");
    tolua_function(tolua_S,"Create",tolua_coord_coord_Object_Create00);
    tolua_function(tolua_S,"Save",tolua_coord_coord_Object_Save00);
    tolua_function(tolua_S,"AddComponent",tolua_coord_coord_Object_AddComponent00);
    tolua_function(tolua_S,"AddScript",tolua_coord_coord_Object_AddScript00);
    tolua_function(tolua_S,"RemoveComponent",tolua_coord_coord_Object_RemoveComponent00);
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Object_GetComponent00);
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Object_GetComponent01);
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Object_GetComponent02);
    tolua_function(tolua_S,"GetScript",tolua_coord_coord_Object_GetScript00);
    tolua_function(tolua_S,"GetChild",tolua_coord_coord_Object_GetChild00);
    tolua_function(tolua_S,"GetParent",tolua_coord_coord_Object_GetParent00);
    tolua_function(tolua_S,"AddChild",tolua_coord_coord_Object_AddChild00);
    tolua_function(tolua_S,"ChildIndex",tolua_coord_coord_Object_ChildIndex00);
    tolua_function(tolua_S,"Trace",tolua_coord_coord_Object_Trace00);
    tolua_variable(tolua_S,"id",tolua_get_coord__Object_id,tolua_set_coord__Object_id);
    tolua_variable(tolua_S,"data",tolua_get_coord__Object_data,tolua_set_coord__Object_data);
    tolua_variable(tolua_S,"name",tolua_get_coord__Object_name,tolua_set_coord__Object_name);
    tolua_variable(tolua_S,"transform",tolua_get_coord__Object_transform_ptr,tolua_set_coord__Object_transform_ptr);
    tolua_variable(tolua_S,"scene",tolua_get_coord__Object_scene_ptr,tolua_set_coord__Object_scene_ptr);
    tolua_variable(tolua_S,"coord",tolua_get_coord__Object_coord_ptr,tolua_set_coord__Object_coord_ptr);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Scene","coord::Scene","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"Scene");
    tolua_function(tolua_S,"Instantiate",tolua_coord_coord_Scene_Instantiate00);
    tolua_function(tolua_S,"CreateObject",tolua_coord_coord_Scene_CreateObject00);
    tolua_variable(tolua_S,"name",tolua_get_coord__Scene_name,tolua_set_coord__Scene_name);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"SceneMgr","coord::SceneMgr","",NULL);
   tolua_beginmodule(tolua_S,"SceneMgr");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Component","coord::Component","",NULL);
   tolua_beginmodule(tolua_S,"Component");
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Component_GetComponent00);
    tolua_function(tolua_S,"AddHttpRouterGet",tolua_coord_coord_Component_AddHttpRouterGet00);
    tolua_function(tolua_S,"Log",tolua_coord_coord_Component_Log00);
    tolua_function(tolua_S,"LogFatal",tolua_coord_coord_Component_LogFatal00);
    tolua_function(tolua_S,"LogError",tolua_coord_coord_Component_LogError00);
    tolua_function(tolua_S,"LogWarn",tolua_coord_coord_Component_LogWarn00);
    tolua_function(tolua_S,"LogInfo",tolua_coord_coord_Component_LogInfo00);
    tolua_function(tolua_S,"LogDebug",tolua_coord_coord_Component_LogDebug00);
    tolua_function(tolua_S,"LogMsg",tolua_coord_coord_Component_LogMsg00);
    tolua_variable(tolua_S,"object",tolua_get_coord__Component_object_ptr,tolua_set_coord__Component_object_ptr);
    tolua_variable(tolua_S,"scene",tolua_get_coord__Component_scene_ptr,tolua_set_coord__Component_scene_ptr);
    tolua_variable(tolua_S,"coord",tolua_get_coord__Component_coord_ptr,tolua_set_coord__Component_coord_ptr);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"http",0);
   tolua_beginmodule(tolua_S,"http");
    tolua_cclass(tolua_S,"IHttpHandler","coord::http::IHttpHandler","",NULL);
    tolua_beginmodule(tolua_S,"IHttpHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"HttpServerConfig","coord::http::HttpServerConfig","",NULL);
    tolua_beginmodule(tolua_S,"HttpServerConfig");
     tolua_variable(tolua_S,"Host",tolua_get_coord__http__HttpServerConfig_Host,tolua_set_coord__http__HttpServerConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__http__HttpServerConfig_unsigned_Port,tolua_set_coord__http__HttpServerConfig_unsigned_Port);
     tolua_variable(tolua_S,"Backlog",tolua_get_coord__http__HttpServerConfig_Backlog,tolua_set_coord__http__HttpServerConfig_Backlog);
     tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__http__HttpServerConfig_SSLEncrypt,tolua_set_coord__http__HttpServerConfig_SSLEncrypt);
     tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__http__HttpServerConfig_SSLPemFile,tolua_set_coord__http__HttpServerConfig_SSLPemFile);
     tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__http__HttpServerConfig_SSLKeyFile,tolua_set_coord__http__HttpServerConfig_SSLKeyFile);
     tolua_variable(tolua_S,"RecvBufferSize",tolua_get_coord__http__HttpServerConfig_RecvBufferSize,tolua_set_coord__http__HttpServerConfig_RecvBufferSize);
     tolua_variable(tolua_S,"AssetDir",tolua_get_coord__http__HttpServerConfig_AssetDir,tolua_set_coord__http__HttpServerConfig_AssetDir);
     tolua_variable(tolua_S,"UseEtag",tolua_get_coord__http__HttpServerConfig_UseEtag,tolua_set_coord__http__HttpServerConfig_UseEtag);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"HttpServer","coord::http::HttpServer","coord::net::ITcpHandler",NULL);
    tolua_beginmodule(tolua_S,"HttpServer");
     tolua_function(tolua_S,"Start",tolua_coord_coord_http_HttpServer_Start00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_http_HttpServer_DefaultConfig00);
     tolua_variable(tolua_S,"Router",tolua_get_coord__http__HttpServer_Router_ptr,tolua_set_coord__http__HttpServer_Router_ptr);
     tolua_variable(tolua_S,"__Destoryable__",tolua_get_coord__http__HttpServer___Destoryable__,NULL);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"http",0);
   tolua_beginmodule(tolua_S,"http");
    tolua_cclass(tolua_S,"HttpRequest","coord::http::HttpRequest","coord::BaseRequest",NULL);
    tolua_beginmodule(tolua_S,"HttpRequest");
     tolua_function(tolua_S,"GetHeader",tolua_coord_coord_http_HttpRequest_GetHeader00);
     tolua_function(tolua_S,"HasHeader",tolua_coord_coord_http_HttpRequest_HasHeader00);
     tolua_function(tolua_S,"GetResponse",tolua_coord_coord_http_HttpRequest_GetResponse00);
     tolua_variable(tolua_S,"Method",tolua_get_coord__http__HttpRequest_Method,tolua_set_coord__http__HttpRequest_Method);
     tolua_variable(tolua_S,"Url",tolua_get_coord__http__HttpRequest_Url,tolua_set_coord__http__HttpRequest_Url);
     tolua_variable(tolua_S,"Path",tolua_get_coord__http__HttpRequest_Path,tolua_set_coord__http__HttpRequest_Path);
     tolua_variable(tolua_S,"Query",tolua_get_coord__http__HttpRequest_Query,tolua_set_coord__http__HttpRequest_Query);
     tolua_variable(tolua_S,"Schema",tolua_get_coord__http__HttpRequest_Schema,tolua_set_coord__http__HttpRequest_Schema);
     tolua_variable(tolua_S,"Host",tolua_get_coord__http__HttpRequest_Host,tolua_set_coord__http__HttpRequest_Host);
     tolua_variable(tolua_S,"RemoteAddr",tolua_get_coord__http__HttpRequest_RemoteAddr,tolua_set_coord__http__HttpRequest_RemoteAddr);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"http",0);
   tolua_beginmodule(tolua_S,"http");
    tolua_cclass(tolua_S,"HttpResponse","coord::http::HttpResponse","",NULL);
    tolua_beginmodule(tolua_S,"HttpResponse");
     tolua_function(tolua_S,"Text",tolua_coord_coord_http_HttpResponse_Text00);
     tolua_function(tolua_S,"Text",tolua_coord_coord_http_HttpResponse_Text01);
     tolua_function(tolua_S,"Json",tolua_coord_coord_http_HttpResponse_Json00);
     tolua_function(tolua_S,"Upgrade",tolua_coord_coord_http_HttpResponse_Upgrade00);
     tolua_function(tolua_S,"PageNotFound",tolua_coord_coord_http_HttpResponse_PageNotFound00);
     tolua_function(tolua_S,"Exception",tolua_coord_coord_http_HttpResponse_Exception00);
     tolua_function(tolua_S,"SetStatusCode",tolua_coord_coord_http_HttpResponse_SetStatusCode00);
     tolua_function(tolua_S,"File",tolua_coord_coord_http_HttpResponse_File00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"http",0);
   tolua_beginmodule(tolua_S,"http");
    tolua_cclass(tolua_S,"HttpRouter","coord::http::HttpRouter","",NULL);
    tolua_beginmodule(tolua_S,"HttpRouter");
     tolua_function(tolua_S,"Get",tolua_coord_coord_http_HttpRouter_Get00);
     tolua_function(tolua_S,"Post",tolua_coord_coord_http_HttpRouter_Post00);
     tolua_function(tolua_S,"Static",tolua_coord_coord_http_HttpRouter_Static00);
     tolua_function(tolua_S,"StaticFile",tolua_coord_coord_http_HttpRouter_StaticFile00);
     tolua_function(tolua_S,"Trace",tolua_coord_coord_http_HttpRouter_Trace00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"http",0);
   tolua_beginmodule(tolua_S,"http");
    tolua_cclass(tolua_S,"IHttpAgentHandler","coord::http::IHttpAgentHandler","",NULL);
    tolua_beginmodule(tolua_S,"IHttpAgentHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"HttpAgent","coord::http::HttpAgent","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"HttpAgent");
     tolua_variable(tolua_S,"__net__ITcpAgentHandler__",tolua_get_coord__http__HttpAgent___net__ITcpAgentHandler__,NULL);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"web",0);
   tolua_beginmodule(tolua_S,"web");
    tolua_cclass(tolua_S,"WebConfig","coord::web::WebConfig","",NULL);
    tolua_beginmodule(tolua_S,"WebConfig");
     tolua_variable(tolua_S,"Port",tolua_get_coord__web__WebConfig_Port,tolua_set_coord__web__WebConfig_Port);
     tolua_variable(tolua_S,"Host",tolua_get_coord__web__WebConfig_Host,tolua_set_coord__web__WebConfig_Host);
     tolua_variable(tolua_S,"Backlog",tolua_get_coord__web__WebConfig_Backlog,tolua_set_coord__web__WebConfig_Backlog);
     tolua_variable(tolua_S,"RecvBuffer",tolua_get_coord__web__WebConfig_RecvBuffer,tolua_set_coord__web__WebConfig_RecvBuffer);
     tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__web__WebConfig_SSLEncrypt,tolua_set_coord__web__WebConfig_SSLEncrypt);
     tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__web__WebConfig_SSLPemFile,tolua_set_coord__web__WebConfig_SSLPemFile);
     tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__web__WebConfig_SSLKeyFile,tolua_set_coord__web__WebConfig_SSLKeyFile);
     tolua_variable(tolua_S,"AssetDir",tolua_get_coord__web__WebConfig_AssetDir,tolua_set_coord__web__WebConfig_AssetDir);
     tolua_variable(tolua_S,"UseEtag",tolua_get_coord__web__WebConfig_UseEtag,tolua_set_coord__web__WebConfig_UseEtag);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"IWebSocketHandler","coord::websocket::IWebSocketHandler","",NULL);
    tolua_beginmodule(tolua_S,"IWebSocketHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"WebSocketServerConfig","coord::websocket::WebSocketServerConfig","",NULL);
    tolua_beginmodule(tolua_S,"WebSocketServerConfig");
     tolua_variable(tolua_S,"Host",tolua_get_coord__websocket__WebSocketServerConfig_Host,tolua_set_coord__websocket__WebSocketServerConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__websocket__WebSocketServerConfig_unsigned_Port,tolua_set_coord__websocket__WebSocketServerConfig_unsigned_Port);
     tolua_variable(tolua_S,"Backlog",tolua_get_coord__websocket__WebSocketServerConfig_Backlog,tolua_set_coord__websocket__WebSocketServerConfig_Backlog);
     tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__websocket__WebSocketServerConfig_SSLEncrypt,tolua_set_coord__websocket__WebSocketServerConfig_SSLEncrypt);
     tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__websocket__WebSocketServerConfig_SSLPemFile,tolua_set_coord__websocket__WebSocketServerConfig_SSLPemFile);
     tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__websocket__WebSocketServerConfig_SSLKeyFile,tolua_set_coord__websocket__WebSocketServerConfig_SSLKeyFile);
     tolua_variable(tolua_S,"RecvBufferSize",tolua_get_coord__websocket__WebSocketServerConfig_RecvBufferSize,tolua_set_coord__websocket__WebSocketServerConfig_RecvBufferSize);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"Server","coord::websocket::Server","coord::http::IHttpHandler",NULL);
    tolua_beginmodule(tolua_S,"Server");
     tolua_function(tolua_S,"Start",tolua_coord_coord_websocket_Server_Start00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_websocket_Server_DefaultConfig00);
     tolua_variable(tolua_S,"Router",tolua_get_coord__websocket__Server_Router_ptr,tolua_set_coord__websocket__Server_Router_ptr);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"Router","coord::websocket::Router","",NULL);
    tolua_beginmodule(tolua_S,"Router");
     tolua_function(tolua_S,"Message",tolua_coord_coord_websocket_Router_Message00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"Frame","coord::websocket::Frame","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"Frame");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"IAgentHandler","coord::websocket::IAgentHandler","",NULL);
    tolua_beginmodule(tolua_S,"IAgentHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"Agent","coord::websocket::Agent","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"Agent");
     tolua_function(tolua_S,"SendBinaryFrame",tolua_coord_coord_websocket_Agent_SendBinaryFrame00);
     tolua_function(tolua_S,"SendStringFrame",tolua_coord_coord_websocket_Agent_SendStringFrame00);
     tolua_variable(tolua_S,"__http__IHttpAgentHandler__",tolua_get_coord__websocket__Agent___http__IHttpAgentHandler__,NULL);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"ScriptComponent","coord::ScriptComponent","coord::Component",NULL);
   tolua_beginmodule(tolua_S,"ScriptComponent");
    tolua_function(tolua_S,"AddHttpGet",tolua_coord_coord_ScriptComponent_AddHttpGet00);
    tolua_function(tolua_S,"SetTimeout",tolua_coord_coord_ScriptComponent_SetTimeout00);
    tolua_function(tolua_S,"SetInterval",tolua_coord_coord_ScriptComponent_SetInterval00);
    tolua_function(tolua_S,"ClearInterval",tolua_coord_coord_ScriptComponent_ClearInterval00);
    tolua_function(tolua_S,"Log",tolua_coord_coord_ScriptComponent_Log00);
    tolua_function(tolua_S,"Log",tolua_coord_coord_ScriptComponent_Log01);
    tolua_function(tolua_S,"LogFatal",tolua_coord_coord_ScriptComponent_LogFatal00);
    tolua_function(tolua_S,"LogError",tolua_coord_coord_ScriptComponent_LogError00);
    tolua_function(tolua_S,"LogWarn",tolua_coord_coord_ScriptComponent_LogWarn00);
    tolua_function(tolua_S,"LogInfo",tolua_coord_coord_ScriptComponent_LogInfo00);
    tolua_function(tolua_S,"LogDebug",tolua_coord_coord_ScriptComponent_LogDebug00);
    tolua_function(tolua_S,"LogMsg",tolua_coord_coord_ScriptComponent_LogMsg00);
    tolua_variable(tolua_S,"scriptName",tolua_get_coord__ScriptComponent_scriptName,tolua_set_coord__ScriptComponent_scriptName);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Transform","coord::Transform","coord::Component",NULL);
   tolua_beginmodule(tolua_S,"Transform");
    tolua_variable(tolua_S,"position",tolua_get_coord__Transform_position,tolua_set_coord__Transform_position);
    tolua_variable(tolua_S,"scale",tolua_get_coord__Transform_scale,tolua_set_coord__Transform_scale);
    tolua_variable(tolua_S,"rotation",tolua_get_coord__Transform_rotation,tolua_set_coord__Transform_rotation);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Vector3","coord::Vector3","",NULL);
   tolua_beginmodule(tolua_S,"Vector3");
    tolua_variable(tolua_S,"x",tolua_get_coord__Vector3_x,tolua_set_coord__Vector3_x);
    tolua_variable(tolua_S,"y",tolua_get_coord__Vector3_y,tolua_set_coord__Vector3_y);
    tolua_variable(tolua_S,"z",tolua_get_coord__Vector3_z,tolua_set_coord__Vector3_z);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"net",0);
   tolua_beginmodule(tolua_S,"net");
    tolua_cclass(tolua_S,"ITcpHandler","coord::net::ITcpHandler","",NULL);
    tolua_beginmodule(tolua_S,"ITcpHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"TcpListener","coord::net::TcpListener","",NULL);
    tolua_beginmodule(tolua_S,"TcpListener");
     tolua_function(tolua_S,"Listen",tolua_coord_coord_net_TcpListener_Listen00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_net_TcpListener_Close00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"net",0);
   tolua_beginmodule(tolua_S,"net");
    tolua_cclass(tolua_S,"ITcpAgentHandler","coord::net::ITcpAgentHandler","",NULL);
    tolua_beginmodule(tolua_S,"ITcpAgentHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"TcpAgent","coord::net::TcpAgent","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"TcpAgent");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"Gate","coord::gate::Gate","coord::net::ITcpHandler",NULL);
    tolua_beginmodule(tolua_S,"Gate");
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_gate_Gate_DefaultConfig00);
     tolua_function(tolua_S,"Kick",tolua_coord_coord_gate_Gate_Kick00);
     tolua_variable(tolua_S,"Router",tolua_get_coord__gate__Gate_Router_ptr,tolua_set_coord__gate__Gate_Router_ptr);
     tolua_variable(tolua_S,"__websocket__IWebSocketHandler__",tolua_get_coord__gate__Gate___websocket__IWebSocketHandler__,NULL);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateConfig","coord::gate::GateConfig","",NULL);
    tolua_beginmodule(tolua_S,"GateConfig");
     tolua_variable(tolua_S,"ServerName",tolua_get_coord__gate__GateConfig_ServerName,tolua_set_coord__gate__GateConfig_ServerName);
     tolua_variable(tolua_S,"Host",tolua_get_coord__gate__GateConfig_Host,tolua_set_coord__gate__GateConfig_Host);
     tolua_variable(tolua_S,"Network",tolua_get_coord__gate__GateConfig_Network,tolua_set_coord__gate__GateConfig_Network);
     tolua_variable(tolua_S,"Port",tolua_get_coord__gate__GateConfig_unsigned_Port,tolua_set_coord__gate__GateConfig_unsigned_Port);
     tolua_variable(tolua_S,"RsaEncrypt",tolua_get_coord__gate__GateConfig_RsaEncrypt,tolua_set_coord__gate__GateConfig_RsaEncrypt);
     tolua_variable(tolua_S,"RsaKeyFile",tolua_get_coord__gate__GateConfig_RsaKeyFile,tolua_set_coord__gate__GateConfig_RsaKeyFile);
     tolua_variable(tolua_S,"Heartbeat",tolua_get_coord__gate__GateConfig_Heartbeat,tolua_set_coord__gate__GateConfig_Heartbeat);
     tolua_variable(tolua_S,"Backlog",tolua_get_coord__gate__GateConfig_Backlog,tolua_set_coord__gate__GateConfig_Backlog);
     tolua_variable(tolua_S,"RecvBuffer",tolua_get_coord__gate__GateConfig_RecvBuffer,tolua_set_coord__gate__GateConfig_RecvBuffer);
     tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__gate__GateConfig_SSLEncrypt,tolua_set_coord__gate__GateConfig_SSLEncrypt);
     tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__gate__GateConfig_SSLPemFile,tolua_set_coord__gate__GateConfig_SSLPemFile);
     tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__gate__GateConfig_SSLKeyFile,tolua_set_coord__gate__GateConfig_SSLKeyFile);
     tolua_variable(tolua_S,"MaxUser",tolua_get_coord__gate__GateConfig_MaxUser,tolua_set_coord__gate__GateConfig_MaxUser);
     tolua_variable(tolua_S,"MaxConnection",tolua_get_coord__gate__GateConfig_MaxConnection,tolua_set_coord__gate__GateConfig_MaxConnection);
     tolua_variable(tolua_S,"Cluster",tolua_get_coord__gate__GateConfig_Cluster,tolua_set_coord__gate__GateConfig_Cluster);
     tolua_variable(tolua_S,"UserRegisterExpire",tolua_get_coord__gate__GateConfig_UserRegisterExpire,tolua_set_coord__gate__GateConfig_UserRegisterExpire);
     tolua_variable(tolua_S,"UserRegisterInterval",tolua_get_coord__gate__GateConfig_UserRegisterInterval,tolua_set_coord__gate__GateConfig_UserRegisterInterval);
     tolua_variable(tolua_S,"RegisterExpire",tolua_get_coord__gate__GateConfig_RegisterExpire,tolua_set_coord__gate__GateConfig_RegisterExpire);
     tolua_variable(tolua_S,"RegisterInterval",tolua_get_coord__gate__GateConfig_RegisterInterval,tolua_set_coord__gate__GateConfig_RegisterInterval);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateRouter","coord::gate::GateRouter","",NULL);
    tolua_beginmodule(tolua_S,"GateRouter");
     tolua_function(tolua_S,"Notify",tolua_coord_coord_gate_GateRouter_Notify00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_gate_GateRouter_Request00);
     tolua_function(tolua_S,"Auth",tolua_coord_coord_gate_GateRouter_Auth00);
     tolua_function(tolua_S,"SessionNew",tolua_coord_coord_gate_GateRouter_SessionNew00);
     tolua_function(tolua_S,"SessionClose",tolua_coord_coord_gate_GateRouter_SessionClose00);
     tolua_function(tolua_S,"Login",tolua_coord_coord_gate_GateRouter_Login00);
     tolua_function(tolua_S,"Logout",tolua_coord_coord_gate_GateRouter_Logout00);
     tolua_function(tolua_S,"Instead",tolua_coord_coord_gate_GateRouter_Instead00);
     tolua_function(tolua_S,"Trace",tolua_coord_coord_gate_GateRouter_Trace00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateRequest","coord::gate::GateRequest","coord::BaseRequest",NULL);
    tolua_beginmodule(tolua_S,"GateRequest");
     tolua_function(tolua_S,"GetResponse",tolua_coord_coord_gate_GateRequest_GetResponse00);
     tolua_function(tolua_S,"Kick",tolua_coord_coord_gate_GateRequest_Kick00);
     tolua_function(tolua_S,"GetSession",tolua_coord_coord_gate_GateRequest_GetSession00);
     tolua_variable(tolua_S,"sessionId",tolua_get_coord__gate__GateRequest_sessionId,tolua_set_coord__gate__GateRequest_sessionId);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateNotify","coord::gate::GateNotify","coord::BaseRequest",NULL);
    tolua_beginmodule(tolua_S,"GateNotify");
     tolua_variable(tolua_S,"sessionId",tolua_get_coord__gate__GateNotify_sessionId,tolua_set_coord__gate__GateNotify_sessionId);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateResponse","coord::gate::GateResponse","coord::BaseResponse",NULL);
    tolua_beginmodule(tolua_S,"GateResponse");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateSession","coord::gate::GateSession","",NULL);
    tolua_beginmodule(tolua_S,"GateSession");
     tolua_function(tolua_S,"Kick",tolua_coord_coord_gate_GateSession_Kick00);
     tolua_function(tolua_S,"Push",tolua_coord_coord_gate_GateSession_Push00);
     tolua_function(tolua_S,"Login",tolua_coord_coord_gate_GateSession_Login00);
     tolua_function(tolua_S,"IsAuth",tolua_coord_coord_gate_GateSession_IsAuth00);
     tolua_variable(tolua_S,"Id",tolua_get_coord__gate__GateSession_Id,tolua_set_coord__gate__GateSession_Id);
     tolua_variable(tolua_S,"RemoteAddr",tolua_get_coord__gate__GateSession_RemoteAddr,tolua_set_coord__gate__GateSession_RemoteAddr);
     tolua_variable(tolua_S,"UserId",tolua_get_coord__gate__GateSession_UserId,tolua_set_coord__gate__GateSession_UserId);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GatePromise","coord::gate::GatePromise","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"GatePromise");
     tolua_function(tolua_S,"Then",tolua_coord_coord_gate_GatePromise_Then00);
     tolua_function(tolua_S,"Else",tolua_coord_coord_gate_GatePromise_Else00);
     tolua_function(tolua_S,"Using",tolua_coord_coord_gate_GatePromise_Using00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"event",0);
   tolua_beginmodule(tolua_S,"event");
    tolua_cclass(tolua_S,"BaseEvent","coord::event::BaseEvent","",NULL);
    tolua_beginmodule(tolua_S,"BaseEvent");
     tolua_variable(tolua_S,"name",tolua_get_coord__event__BaseEvent_name,tolua_set_coord__event__BaseEvent_name);
     tolua_variable(tolua_S,"arg",tolua_get_coord__event__BaseEvent_arg,tolua_set_coord__event__BaseEvent_arg);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"event",0);
   tolua_beginmodule(tolua_S,"event");
    tolua_cclass(tolua_S,"EventMgr","coord::event::EventMgr","",NULL);
    tolua_beginmodule(tolua_S,"EventMgr");
     tolua_function(tolua_S,"AddListener",tolua_coord_coord_event_EventMgr_AddListener00);
     tolua_function(tolua_S,"HasListener",tolua_coord_coord_event_EventMgr_HasListener00);
     tolua_function(tolua_S,"Emit",tolua_coord_coord_event_EventMgr_Emit00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"event",0);
   tolua_beginmodule(tolua_S,"event");
    tolua_cclass(tolua_S,"Listener","coord::event::Listener","",NULL);
    tolua_beginmodule(tolua_S,"Listener");
     tolua_function(tolua_S,"Remove",tolua_coord_coord_event_Listener_Remove00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"protobuf",0);
   tolua_beginmodule(tolua_S,"protobuf");
    tolua_cclass(tolua_S,"Protobuf","coord::protobuf::Protobuf","",NULL);
    tolua_beginmodule(tolua_S,"Protobuf");
     tolua_function(tolua_S,"MapPath",tolua_coord_coord_protobuf_Protobuf_MapPath00);
     tolua_function(tolua_S,"Import",tolua_coord_coord_protobuf_Protobuf_Import00);
     tolua_function(tolua_S,"ImportDir",tolua_coord_coord_protobuf_Protobuf_ImportDir00);
     tolua_function(tolua_S,"NewReflect",tolua_coord_coord_protobuf_Protobuf_NewReflect00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"protobuf",0);
   tolua_beginmodule(tolua_S,"protobuf");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Reflect","coord::protobuf::Reflect","",tolua_collect_coord__protobuf__Reflect);
    #else
    tolua_cclass(tolua_S,"Reflect","coord::protobuf::Reflect","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Reflect");
     tolua_function(tolua_S,"Get",tolua_coord_coord_protobuf_Reflect_Get00);
     tolua_function(tolua_S,"GetString",tolua_coord_coord_protobuf_Reflect_GetString00);
     tolua_function(tolua_S,"GetInt32",tolua_coord_coord_protobuf_Reflect_GetInt3200);
     tolua_function(tolua_S,"GetInt64",tolua_coord_coord_protobuf_Reflect_GetInt6400);
     tolua_function(tolua_S,"GetUInt32",tolua_coord_coord_protobuf_Reflect_GetUInt3200);
     tolua_function(tolua_S,"GetUInt64",tolua_coord_coord_protobuf_Reflect_GetUInt6400);
     tolua_function(tolua_S,"GetFloat",tolua_coord_coord_protobuf_Reflect_GetFloat00);
     tolua_function(tolua_S,"GetDouble",tolua_coord_coord_protobuf_Reflect_GetDouble00);
     tolua_function(tolua_S,"GetBool",tolua_coord_coord_protobuf_Reflect_GetBool00);
     tolua_function(tolua_S,"Set",tolua_coord_coord_protobuf_Reflect_Set00);
     tolua_function(tolua_S,"SetInt32",tolua_coord_coord_protobuf_Reflect_SetInt3200);
     tolua_function(tolua_S,"SetInt64",tolua_coord_coord_protobuf_Reflect_SetInt6400);
     tolua_function(tolua_S,"SetUInt32",tolua_coord_coord_protobuf_Reflect_SetUInt3200);
     tolua_function(tolua_S,"SetUInt64",tolua_coord_coord_protobuf_Reflect_SetUInt6400);
     tolua_function(tolua_S,"SetFloat",tolua_coord_coord_protobuf_Reflect_SetFloat00);
     tolua_function(tolua_S,"SetDouble",tolua_coord_coord_protobuf_Reflect_SetDouble00);
     tolua_function(tolua_S,"SetBool",tolua_coord_coord_protobuf_Reflect_SetBool00);
     tolua_function(tolua_S,"SetNumber",tolua_coord_coord_protobuf_Reflect_SetNumber00);
     tolua_function(tolua_S,"DebugString",tolua_coord_coord_protobuf_Reflect_DebugString00);
     tolua_function(tolua_S,"ShortDebugString",tolua_coord_coord_protobuf_Reflect_ShortDebugString00);
     tolua_function(tolua_S,"CopyFrom",tolua_coord_coord_protobuf_Reflect_CopyFrom00);
     tolua_function(tolua_S,"MergeFrom",tolua_coord_coord_protobuf_Reflect_MergeFrom00);
     tolua_function(tolua_S,"ByteSize",tolua_coord_coord_protobuf_Reflect_ByteSize00);
     tolua_function(tolua_S,"IsDirty",tolua_coord_coord_protobuf_Reflect_IsDirty00);
     tolua_function(tolua_S,"SetDirty",tolua_coord_coord_protobuf_Reflect_SetDirty00);
     tolua_function(tolua_S,"Name",tolua_coord_coord_protobuf_Reflect_Name00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"protobuf",0);
   tolua_beginmodule(tolua_S,"protobuf");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Array","coord::protobuf::Array","",tolua_collect_coord__protobuf__Array);
    #else
    tolua_cclass(tolua_S,"Array","coord::protobuf::Array","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Array");
     tolua_function(tolua_S,"delete",tolua_coord_coord_protobuf_Array_delete00);
     tolua_function(tolua_S,"Clear",tolua_coord_coord_protobuf_Array_Clear00);
     tolua_function(tolua_S,"MergeFrom",tolua_coord_coord_protobuf_Array_MergeFrom00);
     tolua_function(tolua_S,"RemoveLast",tolua_coord_coord_protobuf_Array_RemoveLast00);
     tolua_function(tolua_S,"RemoveAt",tolua_coord_coord_protobuf_Array_RemoveAt00);
     tolua_function(tolua_S,"Remove",tolua_coord_coord_protobuf_Array_Remove00);
     tolua_function(tolua_S,"Count",tolua_coord_coord_protobuf_Array_Count00);
     tolua_function(tolua_S,"SetDirty",tolua_coord_coord_protobuf_Array_SetDirty00);
     tolua_function(tolua_S,"Set",tolua_coord_coord_protobuf_Array_Set00);
     tolua_function(tolua_S,"SetInt32",tolua_coord_coord_protobuf_Array_SetInt3200);
     tolua_function(tolua_S,"SetInt64",tolua_coord_coord_protobuf_Array_SetInt6400);
     tolua_function(tolua_S,"SetUInt32",tolua_coord_coord_protobuf_Array_SetUInt3200);
     tolua_function(tolua_S,"SetUInt64",tolua_coord_coord_protobuf_Array_SetUInt6400);
     tolua_function(tolua_S,"SetFloat",tolua_coord_coord_protobuf_Array_SetFloat00);
     tolua_function(tolua_S,"SetDouble",tolua_coord_coord_protobuf_Array_SetDouble00);
     tolua_function(tolua_S,"SetBool",tolua_coord_coord_protobuf_Array_SetBool00);
     tolua_function(tolua_S,"SetNumber",tolua_coord_coord_protobuf_Array_SetNumber00);
     tolua_function(tolua_S,"Get",tolua_coord_coord_protobuf_Array_Get00);
     tolua_function(tolua_S,"GetInt32",tolua_coord_coord_protobuf_Array_GetInt3200);
     tolua_function(tolua_S,"GetInt64",tolua_coord_coord_protobuf_Array_GetInt6400);
     tolua_function(tolua_S,"GetUInt32",tolua_coord_coord_protobuf_Array_GetUInt3200);
     tolua_function(tolua_S,"GetUInt64",tolua_coord_coord_protobuf_Array_GetUInt6400);
     tolua_function(tolua_S,"GetFloat",tolua_coord_coord_protobuf_Array_GetFloat00);
     tolua_function(tolua_S,"GetDouble",tolua_coord_coord_protobuf_Array_GetDouble00);
     tolua_function(tolua_S,"GetBool",tolua_coord_coord_protobuf_Array_GetBool00);
     tolua_function(tolua_S,"GetNumber",tolua_coord_coord_protobuf_Array_GetNumber00);
     tolua_function(tolua_S,"Add",tolua_coord_coord_protobuf_Array_Add00);
     tolua_function(tolua_S,"AddInt32",tolua_coord_coord_protobuf_Array_AddInt3200);
     tolua_function(tolua_S,"AddInt64",tolua_coord_coord_protobuf_Array_AddInt6400);
     tolua_function(tolua_S,"AddUInt32",tolua_coord_coord_protobuf_Array_AddUInt3200);
     tolua_function(tolua_S,"AddUInt64",tolua_coord_coord_protobuf_Array_AddUInt6400);
     tolua_function(tolua_S,"AddFloat",tolua_coord_coord_protobuf_Array_AddFloat00);
     tolua_function(tolua_S,"AddDouble",tolua_coord_coord_protobuf_Array_AddDouble00);
     tolua_function(tolua_S,"AddBool",tolua_coord_coord_protobuf_Array_AddBool00);
     tolua_function(tolua_S,"AddNumber",tolua_coord_coord_protobuf_Array_AddNumber00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"timer",0);
   tolua_beginmodule(tolua_S,"timer");
    tolua_cclass(tolua_S,"TimerMgr","coord::timer::TimerMgr","",NULL);
    tolua_beginmodule(tolua_S,"TimerMgr");
     tolua_function(tolua_S,"SetTimeout",tolua_coord_coord_timer_TimerMgr_SetTimeout00);
     tolua_function(tolua_S,"SetInterval",tolua_coord_coord_timer_TimerMgr_SetInterval00);
     tolua_function(tolua_S,"SetCron",tolua_coord_coord_timer_TimerMgr_SetCron00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"sql_mgr","coord::sql::sql_mgr","",NULL);
    tolua_beginmodule(tolua_S,"sql_mgr");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"SQLConfig","coord::sql::SQLConfig","",NULL);
    tolua_beginmodule(tolua_S,"SQLConfig");
     tolua_variable(tolua_S,"Driver",tolua_get_coord__sql__SQLConfig_Driver,tolua_set_coord__sql__SQLConfig_Driver);
     tolua_variable(tolua_S,"User",tolua_get_coord__sql__SQLConfig_User,tolua_set_coord__sql__SQLConfig_User);
     tolua_variable(tolua_S,"Password",tolua_get_coord__sql__SQLConfig_Password,tolua_set_coord__sql__SQLConfig_Password);
     tolua_variable(tolua_S,"DB",tolua_get_coord__sql__SQLConfig_DB,tolua_set_coord__sql__SQLConfig_DB);
     tolua_variable(tolua_S,"CharacterSet",tolua_get_coord__sql__SQLConfig_CharacterSet,tolua_set_coord__sql__SQLConfig_CharacterSet);
     tolua_variable(tolua_S,"Host",tolua_get_coord__sql__SQLConfig_Host,tolua_set_coord__sql__SQLConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__sql__SQLConfig_Port,tolua_set_coord__sql__SQLConfig_Port);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"SQLClient","coord::sql::SQLClient","",NULL);
    tolua_beginmodule(tolua_S,"SQLClient");
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_sql_SQLClient_DefaultConfig00);
     tolua_function(tolua_S,"Connect",tolua_coord_coord_sql_SQLClient_Connect00);
     tolua_function(tolua_S,"Ping",tolua_coord_coord_sql_SQLClient_Ping00);
     tolua_function(tolua_S,"Error",tolua_coord_coord_sql_SQLClient_Error00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_sql_SQLClient_Close00);
     tolua_function(tolua_S,"RowsAffected",tolua_coord_coord_sql_SQLClient_RowsAffected00);
     tolua_function(tolua_S,"LastInsertId",tolua_coord_coord_sql_SQLClient_LastInsertId00);
     tolua_function(tolua_S,"Query",tolua_coord_coord_sql_SQLClient_Query00);
     tolua_function(tolua_S,"Get",tolua_coord_coord_sql_SQLClient_Get00);
     tolua_function(tolua_S,"Execute",tolua_coord_coord_sql_SQLClient_Execute00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"SQLResult","coord::sql::SQLResult","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"SQLResult");
     tolua_function(tolua_S,"RowsAffected",tolua_coord_coord_sql_SQLResult_RowsAffected00);
     tolua_function(tolua_S,"LastInsertId",tolua_coord_coord_sql_SQLResult_LastInsertId00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"SQLRows","coord::sql::SQLRows","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"SQLRows");
     tolua_function(tolua_S,"Next",tolua_coord_coord_sql_SQLRows_Next00);
     tolua_function(tolua_S,"Proto",tolua_coord_coord_sql_SQLRows_Proto00);
     tolua_function(tolua_S,"Proto",tolua_coord_coord_sql_SQLRows_Proto01);
     tolua_function(tolua_S,"Lua",tolua_coord_coord_sql_SQLRows_Lua00);
     tolua_function(tolua_S,"Column",tolua_coord_coord_sql_SQLRows_Column00);
     tolua_function(tolua_S,"ColumnCount",tolua_coord_coord_sql_SQLRows_ColumnCount00);
     tolua_function(tolua_S,"String",tolua_coord_coord_sql_SQLRows_String00);
     tolua_function(tolua_S,"String",tolua_coord_coord_sql_SQLRows_String01);
     tolua_function(tolua_S,"Number",tolua_coord_coord_sql_SQLRows_Number00);
     tolua_function(tolua_S,"Number",tolua_coord_coord_sql_SQLRows_Number01);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"MySQLClient","coord::sql::MySQLClient","coord::sql::SQLClient",NULL);
    tolua_beginmodule(tolua_S,"MySQLClient");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"RedisMgr","coord::redis::RedisMgr","",NULL);
    tolua_beginmodule(tolua_S,"RedisMgr");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"RedisConfig","coord::redis::RedisConfig","",NULL);
    tolua_beginmodule(tolua_S,"RedisConfig");
     tolua_variable(tolua_S,"Password",tolua_get_coord__redis__RedisConfig_Password,tolua_set_coord__redis__RedisConfig_Password);
     tolua_variable(tolua_S,"DB",tolua_get_coord__redis__RedisConfig_DB,tolua_set_coord__redis__RedisConfig_DB);
     tolua_variable(tolua_S,"Host",tolua_get_coord__redis__RedisConfig_Host,tolua_set_coord__redis__RedisConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__redis__RedisConfig_Port,tolua_set_coord__redis__RedisConfig_Port);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"AsyncClient","coord::redis::AsyncClient","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"AsyncClient");
     tolua_function(tolua_S,"Connect",tolua_coord_coord_redis_AsyncClient_Connect00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_redis_AsyncClient_DefaultConfig00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_redis_AsyncClient_Close00);
     tolua_function(tolua_S,"SELECT",tolua_coord_coord_redis_AsyncClient_SELECT00);
     tolua_function(tolua_S,"AUTH",tolua_coord_coord_redis_AsyncClient_AUTH00);
     tolua_function(tolua_S,"DEL",tolua_coord_coord_redis_AsyncClient_DEL00);
     tolua_function(tolua_S,"GET",tolua_coord_coord_redis_AsyncClient_GET00);
     tolua_function(tolua_S,"SET",tolua_coord_coord_redis_AsyncClient_SET00);
     tolua_function(tolua_S,"EXPIRE",tolua_coord_coord_redis_AsyncClient_EXPIRE00);
     tolua_function(tolua_S,"HGETALL",tolua_coord_coord_redis_AsyncClient_HGETALL00);
     tolua_function(tolua_S,"HDEL",tolua_coord_coord_redis_AsyncClient_HDEL00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_AsyncClient_HMSET00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_AsyncClient_HMSET01);
     tolua_function(tolua_S,"SCRIPT_LOAD",tolua_coord_coord_redis_AsyncClient_SCRIPT_LOAD00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"Client","coord::redis::Client","",NULL);
    tolua_beginmodule(tolua_S,"Client");
     tolua_function(tolua_S,"Connect",tolua_coord_coord_redis_Client_Connect00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_redis_Client_DefaultConfig00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_redis_Client_Close00);
     tolua_function(tolua_S,"SELECT",tolua_coord_coord_redis_Client_SELECT00);
     tolua_function(tolua_S,"AUTH",tolua_coord_coord_redis_Client_AUTH00);
     tolua_function(tolua_S,"TIME",tolua_coord_coord_redis_Client_TIME00);
     tolua_function(tolua_S,"DEL",tolua_coord_coord_redis_Client_DEL00);
     tolua_function(tolua_S,"GET",tolua_coord_coord_redis_Client_GET00);
     tolua_function(tolua_S,"SET",tolua_coord_coord_redis_Client_SET00);
     tolua_function(tolua_S,"EXPIRE",tolua_coord_coord_redis_Client_EXPIRE00);
     tolua_function(tolua_S,"HGETALL",tolua_coord_coord_redis_Client_HGETALL00);
     tolua_function(tolua_S,"HDEL",tolua_coord_coord_redis_Client_HDEL00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_Client_HMSET00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_Client_HMSET01);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"Promise","coord::redis::Promise","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"Promise");
     tolua_function(tolua_S,"Then",tolua_coord_coord_redis_Promise_Then00);
     tolua_function(tolua_S,"Else",tolua_coord_coord_redis_Promise_Else00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Reply","coord::redis::Reply","coord::Destoryable",tolua_collect_coord__redis__Reply);
    #else
    tolua_cclass(tolua_S,"Reply","coord::redis::Reply","coord::Destoryable",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Reply");
     tolua_function(tolua_S,"Error",tolua_coord_coord_redis_Reply_Error00);
     tolua_function(tolua_S,"Array",tolua_coord_coord_redis_Reply_Array00);
     tolua_function(tolua_S,"ArrayCount",tolua_coord_coord_redis_Reply_ArrayCount00);
     tolua_function(tolua_S,"Empty",tolua_coord_coord_redis_Reply_Empty00);
     tolua_function(tolua_S,"Empty",tolua_coord_coord_redis_Reply_Empty01);
     tolua_function(tolua_S,"String",tolua_coord_coord_redis_Reply_String00);
     tolua_function(tolua_S,"Integer",tolua_coord_coord_redis_Reply_Integer00);
     tolua_function(tolua_S,"Integer",tolua_coord_coord_redis_Reply_Integer01);
     tolua_function(tolua_S,"String",tolua_coord_coord_redis_Reply_String01);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cache",0);
   tolua_beginmodule(tolua_S,"cache");
    tolua_cclass(tolua_S,"CacheConfig","coord::cache::CacheConfig","",NULL);
    tolua_beginmodule(tolua_S,"CacheConfig");
     tolua_variable(tolua_S,"Password",tolua_get_coord__cache__CacheConfig_Password,tolua_set_coord__cache__CacheConfig_Password);
     tolua_variable(tolua_S,"DB",tolua_get_coord__cache__CacheConfig_DB,tolua_set_coord__cache__CacheConfig_DB);
     tolua_variable(tolua_S,"Host",tolua_get_coord__cache__CacheConfig_Host,tolua_set_coord__cache__CacheConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__cache__CacheConfig_Port,tolua_set_coord__cache__CacheConfig_Port);
     tolua_variable(tolua_S,"ExpireTime",tolua_get_coord__cache__CacheConfig_ExpireTime,tolua_set_coord__cache__CacheConfig_ExpireTime);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cache",0);
   tolua_beginmodule(tolua_S,"cache");
    tolua_cclass(tolua_S,"Client","coord::cache::Client","",NULL);
    tolua_beginmodule(tolua_S,"Client");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cache",0);
   tolua_beginmodule(tolua_S,"cache");
    tolua_cclass(tolua_S,"CacheReader","coord::cache::CacheReader","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"CacheReader");
     tolua_function(tolua_S,"String",tolua_coord_coord_cache_CacheReader_String00);
     tolua_function(tolua_S,"Empty",tolua_coord_coord_cache_CacheReader_Empty00);
     tolua_function(tolua_S,"Error",tolua_coord_coord_cache_CacheReader_Error00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cache",0);
   tolua_beginmodule(tolua_S,"cache");
    tolua_cclass(tolua_S,"AsyncClient","coord::cache::AsyncClient","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"AsyncClient");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"Cluster","coord::cluster::Cluster","",NULL);
    tolua_beginmodule(tolua_S,"Cluster");
     tolua_function(tolua_S,"Notify",tolua_coord_coord_cluster_Cluster_Notify00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_cluster_Cluster_Request00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_cluster_Cluster_Request01);
     tolua_function(tolua_S,"Reload",tolua_coord_coord_cluster_Cluster_Reload00);
     tolua_variable(tolua_S,"Name",tolua_get_coord__cluster__Cluster_Name,tolua_set_coord__cluster__Cluster_Name);
     tolua_variable(tolua_S,"FullName",tolua_get_coord__cluster__Cluster_FullName,tolua_set_coord__cluster__Cluster_FullName);
     tolua_variable(tolua_S,"Version",tolua_get_coord__cluster__Cluster_Version,tolua_set_coord__cluster__Cluster_Version);
     tolua_variable(tolua_S,"Router",tolua_get_coord__cluster__Cluster_Router_ptr,tolua_set_coord__cluster__Cluster_Router_ptr);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"ClusterConfig","coord::cluster::ClusterConfig","",NULL);
    tolua_beginmodule(tolua_S,"ClusterConfig");
     tolua_variable(tolua_S,"Driver",tolua_get_coord__cluster__ClusterConfig_Driver,tolua_set_coord__cluster__ClusterConfig_Driver);
     tolua_variable(tolua_S,"Host",tolua_get_coord__cluster__ClusterConfig_Host,tolua_set_coord__cluster__ClusterConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__cluster__ClusterConfig_Port,tolua_set_coord__cluster__ClusterConfig_Port);
     tolua_variable(tolua_S,"Heartbeat",tolua_get_coord__cluster__ClusterConfig_Heartbeat,tolua_set_coord__cluster__ClusterConfig_Heartbeat);
     tolua_variable(tolua_S,"Expire",tolua_get_coord__cluster__ClusterConfig_Expire,tolua_set_coord__cluster__ClusterConfig_Expire);
     tolua_variable(tolua_S,"Name",tolua_get_coord__cluster__ClusterConfig_Name,tolua_set_coord__cluster__ClusterConfig_Name);
     tolua_variable(tolua_S,"RegisterInterval",tolua_get_coord__cluster__ClusterConfig_RegisterInterval,tolua_set_coord__cluster__ClusterConfig_RegisterInterval);
     tolua_variable(tolua_S,"ReloadInterval",tolua_get_coord__cluster__ClusterConfig_ReloadInterval,tolua_set_coord__cluster__ClusterConfig_ReloadInterval);
     tolua_variable(tolua_S,"ReconnectInterval",tolua_get_coord__cluster__ClusterConfig_ReconnectInterval,tolua_set_coord__cluster__ClusterConfig_ReconnectInterval);
     tolua_variable(tolua_S,"RecvBuffer",tolua_get_coord__cluster__ClusterConfig_RecvBuffer,tolua_set_coord__cluster__ClusterConfig_RecvBuffer);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"ClusterRouter","coord::cluster::ClusterRouter","",NULL);
    tolua_beginmodule(tolua_S,"ClusterRouter");
     tolua_function(tolua_S,"Notify",tolua_coord_coord_cluster_ClusterRouter_Notify00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_cluster_ClusterRouter_Request00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_cluster_ClusterRouter_Request01);
     tolua_function(tolua_S,"Trace",tolua_coord_coord_cluster_ClusterRouter_Trace00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"Request","coord::cluster::Request","coord::BaseRequest",NULL);
    tolua_beginmodule(tolua_S,"Request");
     tolua_function(tolua_S,"GetResponse",tolua_coord_coord_cluster_Request_GetResponse00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"Notify","coord::cluster::Notify","coord::BaseRequest",NULL);
    tolua_beginmodule(tolua_S,"Notify");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"Response","coord::cluster::Response","coord::BaseResponse",NULL);
    tolua_beginmodule(tolua_S,"Response");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"Promise","coord::cluster::Promise","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"Promise");
     tolua_function(tolua_S,"Then",tolua_coord_coord_cluster_Promise_Then00);
     tolua_function(tolua_S,"Else",tolua_coord_coord_cluster_Promise_Else00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"Result","coord::cluster::Result","coord::BaseResult",NULL);
    tolua_beginmodule(tolua_S,"Result");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"net",0);
   tolua_beginmodule(tolua_S,"net");
    tolua_cclass(tolua_S,"ITcpClientHandler","coord::net::ITcpClientHandler","",NULL);
    tolua_beginmodule(tolua_S,"ITcpClientHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"TcpClient","coord::net::TcpClient","",NULL);
    tolua_beginmodule(tolua_S,"TcpClient");
    tolua_endmodule(tolua_S);
    tolua_function(tolua_S,"newTcpClient",tolua_coord_coord_net_newTcpClient00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"managed",0);
   tolua_beginmodule(tolua_S,"managed");
    tolua_cclass(tolua_S,"Managed","coord::managed::Managed","",NULL);
    tolua_beginmodule(tolua_S,"Managed");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"managed",0);
   tolua_beginmodule(tolua_S,"managed");
    tolua_cclass(tolua_S,"ManagedConfig","coord::managed::ManagedConfig","",NULL);
    tolua_beginmodule(tolua_S,"ManagedConfig");
     tolua_variable(tolua_S,"Host",tolua_get_coord__managed__ManagedConfig_Host,tolua_set_coord__managed__ManagedConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__managed__ManagedConfig_Port,tolua_set_coord__managed__ManagedConfig_Port);
     tolua_variable(tolua_S,"User",tolua_get_coord__managed__ManagedConfig_User,tolua_set_coord__managed__ManagedConfig_User);
     tolua_variable(tolua_S,"Password",tolua_get_coord__managed__ManagedConfig_Password,tolua_set_coord__managed__ManagedConfig_Password);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"managed",0);
   tolua_beginmodule(tolua_S,"managed");
    tolua_cclass(tolua_S,"ManagedServer","coord::managed::ManagedServer","coord::net::ITcpHandler",NULL);
    tolua_beginmodule(tolua_S,"ManagedServer");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"managed",0);
   tolua_beginmodule(tolua_S,"managed");
    tolua_cclass(tolua_S,"ManagedAgent","coord::managed::ManagedAgent","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"ManagedAgent");
     tolua_variable(tolua_S,"__net__ITcpAgentHandler__",tolua_get_coord__managed__ManagedAgent___net__ITcpAgentHandler__,NULL);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"managed",0);
   tolua_beginmodule(tolua_S,"managed");
    tolua_cclass(tolua_S,"ManagedRequest","coord::managed::ManagedRequest","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"ManagedRequest");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"WorkerConfig","coord::worker::WorkerConfig","",NULL);
    tolua_beginmodule(tolua_S,"WorkerConfig");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"Worker","coord::worker::Worker","",NULL);
    tolua_beginmodule(tolua_S,"Worker");
     tolua_function(tolua_S,"Request",tolua_coord_coord_worker_Worker_Request00);
     tolua_function(tolua_S,"Notify",tolua_coord_coord_worker_Worker_Notify00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"WorkerRouter","coord::worker::WorkerRouter","",NULL);
    tolua_beginmodule(tolua_S,"WorkerRouter");
     tolua_function(tolua_S,"Request",tolua_coord_coord_worker_WorkerRouter_Request00);
     tolua_function(tolua_S,"Notify",tolua_coord_coord_worker_WorkerRouter_Notify00);
     tolua_function(tolua_S,"Trace",tolua_coord_coord_worker_WorkerRouter_Trace00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"WorkerSlave","coord::worker::WorkerSlave","",NULL);
    tolua_beginmodule(tolua_S,"WorkerSlave");
     tolua_variable(tolua_S,"Router",tolua_get_coord__worker__WorkerSlave_Router_ptr,tolua_set_coord__worker__WorkerSlave_Router_ptr);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"Request","coord::worker::Request","coord::BaseRequest",NULL);
    tolua_beginmodule(tolua_S,"Request");
     tolua_function(tolua_S,"GetResponse",tolua_coord_coord_worker_Request_GetResponse00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"Response","coord::worker::Response","coord::BaseResponse",NULL);
    tolua_beginmodule(tolua_S,"Response");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"Result","coord::worker::Result","coord::BaseResult",NULL);
    tolua_beginmodule(tolua_S,"Result");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"Notify","coord::worker::Notify","coord::BaseRequest",NULL);
    tolua_beginmodule(tolua_S,"Notify");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"worker",0);
   tolua_beginmodule(tolua_S,"worker");
    tolua_cclass(tolua_S,"Promise","coord::worker::Promise","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"Promise");
     tolua_function(tolua_S,"Then",tolua_coord_coord_worker_Promise_Then00);
     tolua_function(tolua_S,"Else",tolua_coord_coord_worker_Promise_Else00);
     tolua_function(tolua_S,"Using",tolua_coord_coord_worker_Promise_Using00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"closure",0);
   tolua_beginmodule(tolua_S,"closure");
    tolua_cclass(tolua_S,"ClosureMgr","coord::closure::ClosureMgr","",NULL);
    tolua_beginmodule(tolua_S,"ClosureMgr");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"login",0);
   tolua_beginmodule(tolua_S,"login");
    tolua_cclass(tolua_S,"LoginSvr","coord::login::LoginSvr","",NULL);
    tolua_beginmodule(tolua_S,"LoginSvr");
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_login_LoginSvr_DefaultConfig00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"login",0);
   tolua_beginmodule(tolua_S,"login");
    tolua_cclass(tolua_S,"LoginConfig","coord::login::LoginConfig","",NULL);
    tolua_beginmodule(tolua_S,"LoginConfig");
     tolua_variable(tolua_S,"Host",tolua_get_coord__login__LoginConfig_Host,tolua_set_coord__login__LoginConfig_Host);
     tolua_variable(tolua_S,"Port",tolua_get_coord__login__LoginConfig_unsigned_Port,tolua_set_coord__login__LoginConfig_unsigned_Port);
     tolua_variable(tolua_S,"Backlog",tolua_get_coord__login__LoginConfig_Backlog,tolua_set_coord__login__LoginConfig_Backlog);
     tolua_variable(tolua_S,"RecvBufferSize",tolua_get_coord__login__LoginConfig_RecvBufferSize,tolua_set_coord__login__LoginConfig_RecvBufferSize);
     tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__login__LoginConfig_SSLEncrypt,tolua_set_coord__login__LoginConfig_SSLEncrypt);
     tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__login__LoginConfig_SSLPemFile,tolua_set_coord__login__LoginConfig_SSLPemFile);
     tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__login__LoginConfig_SSLKeyFile,tolua_set_coord__login__LoginConfig_SSLKeyFile);
     tolua_variable(tolua_S,"Cluster",tolua_get_coord__login__LoginConfig_Cluster,tolua_set_coord__login__LoginConfig_Cluster);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"json",0);
   tolua_beginmodule(tolua_S,"json");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Reflect","coord::json::Reflect","",tolua_collect_coord__json__Reflect);
    #else
    tolua_cclass(tolua_S,"Reflect","coord::json::Reflect","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Reflect");
     tolua_function(tolua_S,"SetString",tolua_coord_coord_json_Reflect_SetString00);
     tolua_function(tolua_S,"SetNumber",tolua_coord_coord_json_Reflect_SetNumber00);
     tolua_function(tolua_S,"SetInteger",tolua_coord_coord_json_Reflect_SetInteger00);
     tolua_function(tolua_S,"SetBool",tolua_coord_coord_json_Reflect_SetBool00);
     tolua_function(tolua_S,"SetObject",tolua_coord_coord_json_Reflect_SetObject00);
     tolua_function(tolua_S,"SetArray",tolua_coord_coord_json_Reflect_SetArray00);
     tolua_function(tolua_S,"GetString",tolua_coord_coord_json_Reflect_GetString00);
     tolua_function(tolua_S,"GetNumber",tolua_coord_coord_json_Reflect_GetNumber00);
     tolua_function(tolua_S,"GetInteger",tolua_coord_coord_json_Reflect_GetInteger00);
     tolua_function(tolua_S,"GetBool",tolua_coord_coord_json_Reflect_GetBool00);
     tolua_function(tolua_S,"GetObject",tolua_coord_coord_json_Reflect_GetObject00);
     tolua_function(tolua_S,"GetArray",tolua_coord_coord_json_Reflect_GetArray00);
     tolua_function(tolua_S,"IsObject",tolua_coord_coord_json_Reflect_IsObject00);
     tolua_function(tolua_S,"IsArray",tolua_coord_coord_json_Reflect_IsArray00);
     tolua_function(tolua_S,"IsString",tolua_coord_coord_json_Reflect_IsString00);
     tolua_function(tolua_S,"IsNumber",tolua_coord_coord_json_Reflect_IsNumber00);
     tolua_function(tolua_S,"IsInteger",tolua_coord_coord_json_Reflect_IsInteger00);
     tolua_function(tolua_S,"IsNull",tolua_coord_coord_json_Reflect_IsNull00);
     tolua_function(tolua_S,"IsBool",tolua_coord_coord_json_Reflect_IsBool00);
     tolua_function(tolua_S,"AddNumber",tolua_coord_coord_json_Reflect_AddNumber00);
     tolua_function(tolua_S,"AddInteger",tolua_coord_coord_json_Reflect_AddInteger00);
     tolua_function(tolua_S,"AddBool",tolua_coord_coord_json_Reflect_AddBool00);
     tolua_function(tolua_S,"AddString",tolua_coord_coord_json_Reflect_AddString00);
     tolua_function(tolua_S,"GetNumber",tolua_coord_coord_json_Reflect_GetNumber01);
     tolua_function(tolua_S,"GetInteger",tolua_coord_coord_json_Reflect_GetInteger01);
     tolua_function(tolua_S,"GetBool",tolua_coord_coord_json_Reflect_GetBool01);
     tolua_function(tolua_S,"IsObject",tolua_coord_coord_json_Reflect_IsObject01);
     tolua_function(tolua_S,"IsArray",tolua_coord_coord_json_Reflect_IsArray01);
     tolua_function(tolua_S,"IsString",tolua_coord_coord_json_Reflect_IsString01);
     tolua_function(tolua_S,"IsNumber",tolua_coord_coord_json_Reflect_IsNumber01);
     tolua_function(tolua_S,"IsInteger",tolua_coord_coord_json_Reflect_IsInteger01);
     tolua_function(tolua_S,"IsNull",tolua_coord_coord_json_Reflect_IsNull01);
     tolua_function(tolua_S,"IsBool",tolua_coord_coord_json_Reflect_IsBool01);
     tolua_function(tolua_S,"isObject",tolua_coord_coord_json_Reflect_isObject00);
     tolua_function(tolua_S,"isArray",tolua_coord_coord_json_Reflect_isArray00);
     tolua_function(tolua_S,"isString",tolua_coord_coord_json_Reflect_isString00);
     tolua_function(tolua_S,"isNumber",tolua_coord_coord_json_Reflect_isNumber00);
     tolua_function(tolua_S,"isNull",tolua_coord_coord_json_Reflect_isNull00);
     tolua_function(tolua_S,"isBool",tolua_coord_coord_json_Reflect_isBool00);
     tolua_function(tolua_S,"ToString",tolua_coord_coord_json_Reflect_ToString00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"os",0);
  tolua_beginmodule(tolua_S,"os");
   tolua_function(tolua_S,"GetCwd",tolua_coord_os_GetCwd00);
   tolua_function(tolua_S,"RealPath",tolua_coord_os_RealPath00);
   tolua_function(tolua_S,"ListDir",tolua_coord_os_ListDir00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"os",0);
  tolua_beginmodule(tolua_S,"os");
   tolua_module(tolua_S,"path",0);
   tolua_beginmodule(tolua_S,"path");
    tolua_function(tolua_S,"BaseName",tolua_coord_os_path_BaseName00);
    tolua_function(tolua_S,"BaseName",tolua_coord_os_path_BaseName01);
    tolua_function(tolua_S,"DirName",tolua_coord_os_path_DirName00);
    tolua_function(tolua_S,"Exist",tolua_coord_os_path_Exist00);
    tolua_function(tolua_S,"IsDir",tolua_coord_os_path_IsDir00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);

  { /* begin embedded lua code */
   int top = lua_gettop(tolua_S);
   static unsigned char B[] = {
    10, 95, 95, 67, 79, 77, 80, 79, 78, 69, 78, 84, 83, 32, 61,
     32, 49, 10, 95, 95, 67, 72, 73, 76, 68, 82, 69, 78, 32, 61,
     32, 50, 10,102,117,110, 99,116,105,111,110, 32,105,110,115,
    116, 97,110,116,105, 97,116,101, 40, 99,111,110,102, 41, 10,
    108,111, 99, 97,108, 32,111, 98,106,101, 99,116, 32, 61, 32,
     71, 97,109,101, 79, 98,106,101, 99,116, 58,110,101,119, 40,
     41, 10,102,111,114, 32,107, 44, 32,118, 32,105,110, 32,112,
     97,105,114,115, 40, 99,111,110,102, 41, 32,100,111, 10,105,
    102, 32,107, 32, 61, 61, 32, 95, 95, 67, 79, 77, 80, 79, 78,
     69, 78, 84, 83, 32,116,104,101,110, 10,102,111,114, 32, 99,
    108, 97,115,115, 44, 32, 99,111,109,112,111,110,101,110,116,
     95, 99,111,110,102, 32,105,110, 32,112, 97,105,114,115, 40,
    118, 41, 32,100,111, 10,105,102, 32, 99,111,109,112,111,110,
    101,110,116, 95, 99,111,110,102, 46, 95, 95,115, 99,114,105,
    112,116, 32,116,104,101,110, 10,108,111, 99, 97,108, 32, 99,
    111,109,112,111,110,101,110,116, 32, 61, 32,111, 98,106,101,
     99,116, 58, 97,100,100, 95,115, 99,114,105,112,116, 40, 99,
    111,109,112,111,110,101,110,116, 95, 99,111,110,102, 46, 95,
     95,115, 99,114,105,112,116, 41, 10,102,111,114, 32,118, 97,
    114,110, 97,109,101, 44, 32,118, 97,108,117,101, 32,105,110,
     32,112, 97,105,114,115, 40, 99,111,109,112,111,110,101,110,
    116, 95, 99,111,110,102, 41, 32,100,111, 10, 99,111,109,112,
    111,110,101,110,116, 91,118, 97,114,110, 97,109,101, 93, 32,
     61, 32,118, 97,108,117,101, 10,101,110,100, 10,101,108,115,
    101, 10,108,111, 99, 97,108, 32, 99,111,109,112,111,110,101,
    110,116, 95, 99,108, 97,115,115, 32, 61, 32, 95, 71, 91, 99,
    108, 97,115,115, 93, 10,105,102, 32,110,111,116, 32, 99,111,
    109,112,111,110,101,110,116, 95, 99,108, 97,115,115, 32,116,
    104,101,110, 10,112,114,105,110,116, 40,115,116,114,105,110,
    103, 46,102,111,114,109, 97,116, 40, 39, 37,115, 32,110,111,
    116, 32,102,111,117,110,100, 39, 44, 32, 99,108, 97,115,115,
     41, 41, 10,101,110,100, 10,108,111, 99, 97,108, 32, 99,111,
    109,112,111,110,101,110,116, 32, 61, 32, 99,111,109,112,111,
    110,101,110,116, 95, 99,108, 97,115,115, 58,110,101,119, 40,
     41, 10,111, 98,106,101, 99,116, 58, 97,100,100, 95, 99,111,
    109,112,111,110,101,110,116, 40, 99,111,109,112,111,110,101,
    110,116, 41, 10,102,111,114, 32,118, 97,114,110, 97,109,101,
     44, 32,118, 97,108,117,101, 32,105,110, 32,112, 97,105,114,
    115, 40, 99,111,109,112,111,110,101,110,116, 95, 99,111,110,
    102, 41, 32,100,111, 10, 99,111,109,112,111,110,101,110,116,
     91,118, 97,114,110, 97,109,101, 93, 32, 61, 32,118, 97,108,
    117,101, 10,101,110,100, 10,101,110,100, 10,101,110,100, 10,
    101,108,115,101,105,102, 32,107, 32, 61, 61, 32, 95, 95, 67,
     72, 73, 76, 68, 82, 69, 78, 32,116,104,101,110, 10,102,111,
    114, 32,107, 50, 44, 32,118, 50, 32,105,110, 32,112, 97,105,
    114,115, 40,118, 41, 32,100,111, 10,108,111, 99, 97,108, 32,
     99,104,105,108,100, 32, 61, 32,105,110,115,116, 97,110,116,
    105, 97,116,101, 40,118, 50, 41, 10, 99,104,105,108,100, 46,
    110, 97,109,101, 32, 61, 32,107, 50, 10,111, 98,106,101, 99,
    116, 58, 97,100,100, 95, 99,104,105,108,100, 40, 99,104,105,
    108,100, 41, 10,101,110,100, 10,101,108,115,101, 10,111, 98,
    106,101, 99,116, 91,107, 93, 32, 61, 32,118, 10,101,110,100,
     10,101,110,100, 10,114,101,116,117,114,110, 32,111, 98,106,
    101, 99,116, 10,101,110,100, 10, 78, 69, 87, 95, 80, 79, 83,
     84, 32, 61, 32,102,117,110, 99,116,105,111,110, 40,115,114,
    118,105,100, 41, 10,108,111, 99, 97,108, 32,115,114,118,105,
    100, 32, 61, 32,115,114,118,105,100, 10,108,111, 99, 97,108,
     32,109,111,100,110, 97,109,101, 32, 61, 32,110,105,108, 10,
    108,111, 99, 97,108, 32,102,117,110,110, 97,109,101, 32, 61,
     32,110,105,108, 10,108,111, 99, 97,108, 32,109,116, 32, 61,
     32,123, 10, 95, 95,105,110,100,101,120, 32, 61, 32,102,117,
    110, 99,116,105,111,110, 40,115,101,108,102, 44, 32,107, 41,
     10,105,102, 32,110,111,116, 32,109,111,100,110, 97,109,101,
     32,116,104,101,110, 10,109,111,100,110, 97,109,101, 32, 61,
     32,107, 10,101,108,115,101, 10,102,117,110, 99,110, 97,109,
    101, 32, 61, 32,107, 10,101,110,100, 10,114,101,116,117,114,
    110, 32,115,101,108,102, 10,101,110,100, 44, 10, 95, 95, 99,
     97,108,108, 32, 61, 32,102,117,110, 99,116,105,111,110, 40,
    115,101,108,102, 44, 32, 46, 46, 46, 41, 10,109,111,100,110,
     97,109,101, 32, 61, 32,110,105,108, 10,102,117,110, 99,110,
     97,109,101, 32, 61, 32,110,105,108, 10,109,121,110,111,100,
    101, 58,112,111,115,116, 40,115,114,118,105,100, 44, 32,109,
    111,100,110, 97,109,101, 44, 32,102,117,110, 99,110, 97,109,
    101, 44, 32, 46, 46, 46, 41, 10,101,110,100, 10,125, 10,108,
    111, 99, 97,108, 32,115,116,117, 98, 32, 61, 32,123,125, 10,
    115,101,116,109,101,116, 97,116, 97, 98,108,101, 40,115,116,
    117, 98, 44, 32,109,116, 41, 10,114,101,116,117,114,110, 32,
    115,116,117, 98, 10,101,110,100, 10, 80, 79, 83, 84, 32, 61,
     32,102,117,110, 99,116,105,111,110, 40, 46, 46, 46, 41, 10,
    109,121,110,111,100,101, 58,112,111,115,116, 40, 46, 46, 46,
     41, 10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,
    105,109,112,111,114,116, 95,112,114,111,116,111, 40,100,105,
    114, 41, 10, 80, 98,108,117, 97, 46,109, 97,112,112, 97,116,
    104, 40, 39, 39, 44, 32,100,105,114, 41, 10,108,111, 99, 97,
    108, 32,102,105,108,101,115, 32, 61, 32, 70,105,108,101, 46,
    108,105,115,116,100,105,114, 40,100,105,114, 41, 10,102,111,
    114, 32, 95, 44, 32,102,105,108,101, 32,105,110, 32,112, 97,
    105,114,115, 40,102,105,108,101,115, 41, 32,100,111, 10,105,
    102, 32,102,105,108,101, 46,116,121,112,101, 32, 61, 61, 32,
     70,105,108,101, 46, 84, 89, 80, 69, 95, 70, 73, 76, 69, 32,
     97,110,100, 32,115,116,114,105,110,103, 46,102,105,110,100,
     40,102,105,108,101, 46,110, 97,109,101, 44, 32, 39, 46,112,
    114,111,116,111, 36, 39, 41, 32,116,104,101,110, 10,108,111,
    103,100,101, 98,117,103, 40,115,116,114,105,110,103, 46,102,
    111,114,109, 97,116, 40, 39,108,111, 97,100, 32,112,114,111,
    116,111, 40, 37,115, 41, 39, 44, 32,102,105,108,101, 46,110,
     97,109,101, 41, 41, 10, 80, 98,108,117, 97, 46,105,109,112,
    111,114,116, 40,102,105,108,101, 46,110, 97,109,101, 41, 10,
    101,110,100, 10,101,110,100, 10,101,110,100, 10,102,117,110,
     99,116,105,111,110, 32, 95,112, 97, 99,107, 97,103,101, 95,
     40,110, 97,109,101, 41, 10,101,110,100, 10,108,111, 99, 97,
    108, 32,102,117,110, 99,116,105,111,110, 32, 76,111,103, 40,
    115,116,114, 41, 10,108,111, 99, 97,108, 32,101,110,118, 32,
     61, 32,103,101,116,102,101,110,118, 40, 50, 41, 10, 99,111,
    111,114,100, 97, 58, 76,111,103, 40,115,116,114,105,110,103,
     46,102,111,114,109, 97,116, 40, 39, 91, 37,115, 93, 32, 37,
    115, 39, 44, 32,101,110,118, 46, 95, 95, 80, 65, 67, 75, 65,
     71, 69, 32,111,114, 32, 39, 97, 97, 39, 44, 32,115,116,114,
     32,111,114, 32, 39, 39, 41, 41, 10,101,110,100, 10,108,111,
     99, 97,108, 32,102,117,110, 99,116,105,111,110, 32, 76,111,
    103, 70, 97,116, 97,108, 40,115,116,114, 41, 10,108,111, 99,
     97,108, 32,101,110,118, 32, 61, 32,103,101,116,102,101,110,
    118, 40, 50, 41, 10, 99,111,111,114,100, 97, 58, 76,111,103,
     70, 97,116, 97,108, 40,115,116,114,105,110,103, 46,102,111,
    114,109, 97,116, 40, 39, 91, 37,115, 93, 32, 37,115, 39, 44,
     32,101,110,118, 46, 95, 95, 80, 65, 67, 75, 65, 71, 69, 44,
     32,115,116,114, 32,111,114, 32, 39, 39, 41, 41, 10,101,110,
    100, 10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,
    110, 32, 76,111,103, 69,114,114,111,114, 40,115,116,114, 41,
     10,108,111, 99, 97,108, 32,101,110,118, 32, 61, 32,103,101,
    116,102,101,110,118, 40, 50, 41, 10, 99,111,111,114,100, 97,
     58, 76,111,103, 69,114,114,111,114, 40,115,116,114,105,110,
    103, 46,102,111,114,109, 97,116, 40, 39, 91, 37,115, 93, 32,
     37,115, 39, 44, 32,101,110,118, 46, 95, 95, 80, 65, 67, 75,
     65, 71, 69, 44, 32,115,116,114, 32,111,114, 32, 39, 39, 41,
     41, 10,101,110,100, 10,108,111, 99, 97,108, 32,102,117,110,
     99,116,105,111,110, 32, 76,111,103, 87, 97,114,110, 40,115,
    116,114, 41, 10,108,111, 99, 97,108, 32,101,110,118, 32, 61,
     32,103,101,116,102,101,110,118, 40, 50, 41, 10, 99,111,111,
    114,100, 97, 58, 76,111,103, 87, 97,114,110, 40,115,116,114,
    105,110,103, 46,102,111,114,109, 97,116, 40, 39, 91, 37,115,
     93, 32, 37,115, 39, 44, 32,101,110,118, 46, 95, 95, 80, 65,
     67, 75, 65, 71, 69, 44, 32,115,116,114, 32,111,114, 32, 39,
     39, 41, 41, 10,101,110,100, 10,108,111, 99, 97,108, 32,102,
    117,110, 99,116,105,111,110, 32, 76,111,103, 73,110,102,111,
     40,115,116,114, 41, 10,108,111, 99, 97,108, 32,101,110,118,
     32, 61, 32,103,101,116,102,101,110,118, 40, 50, 41, 10, 99,
    111,111,114,100, 97, 58, 76,111,103, 73,110,102,111, 40,115,
    116,114,105,110,103, 46,102,111,114,109, 97,116, 40, 39, 91,
     37,115, 93, 32, 37,115, 39, 44, 32,101,110,118, 46, 95, 95,
     80, 65, 67, 75, 65, 71, 69, 44, 32,115,116,114, 32,111,114,
     32, 39, 39, 41, 41, 10,101,110,100, 10,108,111, 99, 97,108,
     32,102,117,110, 99,116,105,111,110, 32, 76,111,103, 68,101,
     98,117,103, 40,115,116,114, 41, 10,108,111, 99, 97,108, 32,
    101,110,118, 32, 61, 32,103,101,116,102,101,110,118, 40, 50,
     41, 10, 99,111,111,114,100, 97, 58, 76,111,103, 68,101, 98,
    117,103, 40,115,116,114,105,110,103, 46,102,111,114,109, 97,
    116, 40, 39, 91, 37,115, 93, 32, 37,115, 39, 44, 32,101,110,
    118, 46, 95, 95, 80, 65, 67, 75, 65, 71, 69, 44, 32,115,116,
    114, 32,111,114, 32, 39, 39, 41, 41, 10,101,110,100, 10,108,
    111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32, 76,
    111,103, 77,115,103, 40,115,116,114, 41, 10,108,111, 99, 97,
    108, 32,101,110,118, 32, 61, 32,103,101,116,102,101,110,118,
     40, 50, 41, 10, 99,111,111,114,100, 97, 58, 76,111,103, 77,
    115,103, 40,115,116,114,105,110,103, 46,102,111,114,109, 97,
    116, 40, 39, 91, 37,115, 93, 32, 37,115, 39, 44, 32,101,110,
    118, 46, 95, 95, 80, 65, 67, 75, 65, 71, 69, 44, 32,115,116,
    114, 32,111,114, 32, 39, 39, 41, 41, 10,101,110,100, 10,108,
    111, 99, 97,108, 32,115, 99,114,105,112,116, 32, 61, 32,123,
    125, 10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,
    110, 32, 95,105,109,112,111,114,116, 95, 40,115,101, 97,114,
     99,104, 68,105,114, 44, 32,112, 97, 99,107, 97,103,101, 80,
     97,116,104, 44, 32,101,120,112,111,114,116, 78, 97,109,101,
     41, 10,108,111, 99, 97,108, 32,102,117,108,108, 68,105,114,
     32, 61, 32,115,101, 97,114, 99,104, 68,105,114, 46, 46, 39,
     47, 39, 46, 46,112, 97, 99,107, 97,103,101, 80, 97,116,104,
     10,105,102, 32,110,111,116, 32,111,115, 46,112, 97,116,104,
     46, 73,115, 68,105,114, 40,102,117,108,108, 68,105,114, 41,
     32,116,104,101,110, 10,114,101,116,117,114,110, 32,102, 97,
    108,115,101, 10,101,110,100, 10,108,111, 99, 97,108, 32,112,
     97, 99,107, 97,103,101, 78, 97,109,101, 32, 61, 32,111,115,
     46,112, 97,116,104, 46, 66, 97,115,101, 78, 97,109,101, 40,
    112, 97, 99,107, 97,103,101, 80, 97,116,104, 41, 10,108,111,
     99, 97,108, 32,101,110,118, 32, 61, 32,115, 99,114,105,112,
    116, 46,112, 97, 99,107, 97,103,101, 91,112, 97, 99,107, 97,
    103,101, 80, 97,116,104, 93, 10,105,102, 32,110,111,116, 32,
    101,110,118, 32,116,104,101,110, 10,101,110,118, 32, 61, 32,
    123, 95, 95, 78, 65, 77, 69, 32, 61, 32,101,120,112,111,114,
    116, 78, 97,109,101, 44, 32, 95, 95, 80, 65, 67, 75, 65, 71,
     69, 32, 61, 32,112, 97, 99,107, 97,103,101, 80, 97,116,104,
     44, 32, 95, 95, 80, 65, 84, 72, 32, 61, 32,102,117,108,108,
     68,105,114, 44, 32, 76,111,103, 32, 61, 32, 76,111,103, 44,
     32, 76,111,103, 70, 97,116, 97,108, 32, 61, 32, 76,111,103,
     70, 97,116, 97,108, 44, 32, 76,111,103, 69,114,114,111,114,
     32, 61, 32, 76,111,103, 69,114,114,111,114, 44, 32, 76,111,
    103, 87, 97,114,110, 32, 61, 32, 76,111,103, 87, 97,114,110,
     44, 32, 76,111,103, 73,110,102,111, 32, 61, 32, 76,111,103,
     73,110,102,111, 44, 32, 76,111,103, 68,101, 98,117,103, 32,
     61, 32, 76,111,103, 68,101, 98,117,103, 44, 32, 76,111,103,
     77,115,103, 32, 61, 32, 76,111,103, 77,115,103,125, 10,101,
    110,118, 46,112, 97, 99,107, 97,103,101, 32, 61, 32,101,110,
    118, 10,115,101,116,109,101,116, 97,116, 97, 98,108,101, 40,
    101,110,118, 44, 32,123, 95, 95,105,110,100,101,120, 32, 61,
     32, 95, 71,125, 41, 10,101,110,100, 10,108,111, 99, 97,108,
     32,102,105,108,101, 65,114,114, 44, 32,100,105,114, 65,114,
    114, 32, 61, 32,111,115, 46, 76,105,115,116, 68,105,114, 40,
    102,117,108,108, 68,105,114, 41, 10,102,111,114, 32, 95, 44,
     32,102,105,108,101, 78, 97,109,101, 32,105,110, 32,112, 97,
    105,114,115, 40,102,105,108,101, 65,114,114, 41, 32,100,111,
     10,105,102, 32,115,116,114,105,110,103, 46,102,105,110,100,
     40,102,105,108,101, 78, 97,109,101, 44, 32, 39, 46,108,117,
     97, 36, 39, 41, 32,116,104,101,110, 10,108,111, 99, 97,108,
     32,102,117,108,108, 80, 97,116,104, 32, 61, 32,102,117,108,
    108, 68,105,114, 46, 46, 39, 47, 39, 46, 46,102,105,108,101,
     78, 97,109,101, 10,108,111, 99, 97,108, 32,112, 97, 99,107,
     97,103,101, 78, 97,109,101, 82,101, 97,108, 32, 61, 32,110,
    105,108, 10,102,111,114, 32,108,105,110,101, 32,105,110, 32,
    105,111, 46,108,105,110,101,115, 40,102,117,108,108, 80, 97,
    116,104, 41, 32,100,111, 10,102,111,114, 32,107, 44, 32, 95,
     32,105,110, 32,115,116,114,105,110,103, 46,103,109, 97,116,
     99,104, 40,108,105,110,101, 44, 32, 34, 95,112, 97, 99,107,
     97,103,101, 95, 37, 40, 91, 92, 34, 92, 39, 93, 40, 91, 37,
    119, 92, 46, 35, 92, 47, 45, 93, 43, 41, 91, 92, 34, 92, 39,
     93, 34, 41, 32,100,111, 10,112, 97, 99,107, 97,103,101, 78,
     97,109,101, 82,101, 97,108, 32, 61, 32,107, 10, 98,114,101,
     97,107, 10,101,110,100, 10,105,102, 32,112, 97, 99,107, 97,
    103,101, 78, 97,109,101, 82,101, 97,108, 32,116,104,101,110,
     10, 98,114,101, 97,107, 10,101,110,100, 10,101,110,100, 10,
    105,102, 32,112, 97, 99,107, 97,103,101, 78, 97,109,101, 82,
    101, 97,108, 32, 61, 61, 32,112, 97, 99,107, 97,103,101, 78,
     97,109,101, 32,111,114, 32,112, 97, 99,107, 97,103,101, 78,
     97,109,101, 82,101, 97,108, 32, 61, 61, 32, 39,109, 97,105,
    110, 39, 32,116,104,101,110, 10,108,111, 99, 97,108, 32,102,
     44, 32,101,114,114, 32, 61, 32,108,111, 97,100,102,105,108,
    101, 40,102,117,108,108, 80, 97,116,104, 41, 10,105,102, 32,
    110,111,116, 32,102, 32,116,104,101,110, 10,101,114,114,111,
    114, 40,101,114,114, 41, 10,101,110,100, 10,115,101,116,102,
    101,110,118, 40,102, 44, 32,101,110,118, 41, 10,102, 40, 41,
     10,101,108,115,101, 10,112,114,105,110,116, 40, 39,105,103,
    110,111,114,101, 39, 44, 32,102,117,108,108, 80, 97,116,104,
     44, 32, 39, 97, 39, 44, 32,112, 97, 99,107, 97,103,101, 78,
     97,109,101, 82,101, 97,108, 44, 32, 39, 98, 39, 44, 32,112,
     97, 99,107, 97,103,101, 78, 97,109,101, 41, 10,101,110,100,
     10,101,110,100, 10,101,110,100, 10,115, 99,114,105,112,116,
     46,112, 97, 99,107, 97,103,101, 91,112, 97, 99,107, 97,103,
    101, 80, 97,116,104, 93, 32, 61, 32,101,110,118, 10,115, 99,
    114,105,112,116, 46,101,120,112,111,114,116, 91,101,120,112,
    111,114,116, 78, 97,109,101, 93, 32, 61, 32,101,110,118, 10,
    105,102, 32,115, 99,114,105,112,116, 46,114,101,108,111, 97,
    100,105,110,103, 32,116,104,101,110, 10,115, 99,114,105,112,
    116, 46,114,101,108,111, 97,100, 91,112, 97, 99,107, 97,103,
    101, 80, 97,116,104, 93, 32, 61, 32,101,110,118, 10,105,102,
     32,116,121,112,101, 40,101,110,118, 46,111,110, 82,101,108,
    111, 97,100, 41, 32, 61, 61, 32, 39,102,117,110, 99,116,105,
    111,110, 39, 32,116,104,101,110, 10,101,110,118, 46,111,110,
     82,101,108,111, 97,100, 40, 41, 10,101,110,100, 10,101,108,
    115,101, 10,105,102, 32,116,121,112,101, 40,101,110,118, 46,
    111,110, 65,119, 97,107,101, 41, 32, 61, 61, 32, 39,102,117,
    110, 99,116,105,111,110, 39, 32,116,104,101,110, 10,101,110,
    118, 46,111,110, 65,119, 97,107,101, 40, 41, 10,101,110,100,
     10,101,110,100, 10,114,101,116,117,114,110, 32,101,110,118,
     10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32,105,
    109,112,111,114,116, 40,112, 97, 99,107, 97,103,101, 80, 97,
    116,104, 44, 32,101,120,112,111,114,116, 78, 97,109,101, 41,
     10,105,102, 32,110,111,116, 32,101,120,112,111,114,116, 78,
     97,109,101, 32,116,104,101,110, 10,101,120,112,111,114,116,
     78, 97,109,101, 32, 61, 32,111,115, 46,112, 97,116,104, 46,
     66, 97,115,101, 78, 97,109,101, 40,112, 97, 99,107, 97,103,
    101, 80, 97,116,104, 41, 10,101,110,100, 10,108,111, 99, 97,
    108, 32,112, 97, 99,107, 97,103,101, 32, 61, 32,115, 99,114,
    105,112,116, 46,101,120,112,111,114,116, 91,101,120,112,111,
    114,116, 78, 97,109,101, 93, 10,105,102, 32,112, 97, 99,107,
     97,103,101, 32, 97,110,100, 32,112, 97, 99,107, 97,103,101,
     46, 95, 95, 80, 65, 67, 75, 65, 71, 69, 32,126, 61, 32,112,
     97, 99,107, 97,103,101, 80, 97,116,104, 32,116,104,101,110,
     10,101,114,114,111,114, 40,115,116,114,105,110,103, 46,102,
    111,114,109, 97,116, 40, 34,112, 97, 99,107, 97,103,101, 32,
     37,115, 32, 99,111,110,102,108,105, 99,116, 32,119,105,116,
    104, 32, 37,115, 34, 44, 32,112, 97, 99,107, 97,103,101, 80,
     97,116,104, 44, 32,112, 97, 99,107, 97,103,101, 46, 95, 95,
     80, 65, 67, 75, 65, 71, 69, 41, 41, 10,101,110,100, 10,108,
    111, 99, 97,108, 32,112, 97, 99,107, 97,103,101, 32, 61, 32,
    115, 99,114,105,112,116, 46,112, 97, 99,107, 97,103,101, 91,
    112, 97, 99,107, 97,103,101, 80, 97,116,104, 93, 10,105,102,
     32,112, 97, 99,107, 97,103,101, 32,116,104,101,110, 10,105,
    102, 32,110,111,116, 32,115, 99,114,105,112,116, 46,114,101,
    108,111, 97,100,105,110,103, 32,116,104,101,110, 10,114,101,
    116,117,114,110, 32,112, 97, 99,107, 97,103,101, 10,101,108,
    115,101,105,102, 32,115, 99,114,105,112,116, 46,114,101,108,
    111, 97,100, 91,112, 97, 99,107, 97,103,101, 80, 97,116,104,
     93, 32,116,104,101,110, 10,114,101,116,117,114,110, 32,112,
     97, 99,107, 97,103,101, 10,101,110,100, 10,101,110,100, 10,
    102,111,114, 32,115,101, 97,114, 99,104, 68,105,114, 44, 32,
     95, 32,105,110, 32,115,116,114,105,110,103, 46,103,109, 97,
    116, 99,104, 40, 99,111,111,114,100, 97, 46, 83, 99,114,105,
    112,116, 46, 80, 97,116,104, 44, 32, 34, 91, 94, 59, 93, 43,
     34, 41, 32,100,111, 10,108,111, 99, 97,108, 32,112, 97, 99,
    107, 97,103,101, 32, 61, 32, 95,105,109,112,111,114,116, 95,
     40,115,101, 97,114, 99,104, 68,105,114, 44, 32,112, 97, 99,
    107, 97,103,101, 80, 97,116,104, 44, 32,101,120,112,111,114,
    116, 78, 97,109,101, 41, 10,105,102, 32,112, 97, 99,107, 97,
    103,101, 32,116,104,101,110, 10,114,101,116,117,114,110, 32,
    112, 97, 99,107, 97,103,101, 10,101,110,100, 10,101,110,100,
     10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32, 99,
    111,109,112,111,110,101,110,116, 40,110, 97,109,101, 41, 10,
    108,111, 99, 97,108, 32,112, 97, 99,107, 97,103,101, 32, 61,
     32,103,101,116,102,101,110,118, 40, 50, 41, 10,108,111, 99,
     97,108, 32,101,110,118, 32, 61, 32,112, 97, 99,107, 97,103,
    101, 91,110, 97,109,101, 93, 10,105,102, 32,110,111,116, 32,
    101,110,118, 32,116,104,101,110, 10,101,110,118, 32, 61, 32,
    123, 95, 95, 67, 79, 77, 80, 79, 78, 69, 78, 84, 32, 61, 32,
    112, 97, 99,107, 97,103,101, 46, 95, 95, 80, 65, 67, 75, 65,
     71, 69, 46, 46, 39, 46, 39, 46, 46,110, 97,109,101, 44, 32,
    112, 97, 99,107, 97,103,101, 32, 61, 32,112, 97, 99,107, 97,
    103,101, 44, 32, 95, 95, 73, 78, 84, 69, 82, 70, 65, 67, 69,
     32, 61, 32,123,125,125, 10,115,101,116,109,101,116, 97,116,
     97, 98,108,101, 40,101,110,118, 44, 32,123, 95, 95,105,110,
    100,101,120, 32, 61, 32, 95, 71,125, 41, 10,112, 97, 99,107,
     97,103,101, 91,110, 97,109,101, 93, 32, 61, 32,101,110,118,
     10,101,110,100, 10,115,101,116,102,101,110,118, 40, 50, 44,
     32,101,110,118, 41, 10,101,110,100, 10,102,117,110, 99,116,
    105,111,110, 32,105,109,112,108,101,109,101,110,116, 40,110,
     97,109,101, 41, 10,108,111, 99, 97,108, 32,101,110,118, 32,
     61, 32,103,101,116,102,101,110,118, 40, 50, 41, 10,116, 97,
     98,108,101, 46,105,110,115,101,114,116, 40,101,110,118, 46,
     95, 95, 73, 78, 84, 69, 82, 70, 65, 67, 69, 44, 32,110, 97,
    109,101, 41, 10,101,110,100, 10,108,111, 99, 97,108, 32,102,
    117,110, 99,116,105,111,110, 32,116,114, 97, 99,101, 71, 40,
     41, 10,102,111,114, 32,107, 44, 32,118, 32,105,110, 32,112,
     97,105,114,115, 40, 95, 71, 41, 32,100,111, 10,112,114,105,
    110,116, 40,107, 41, 10,101,110,100, 10,101,110,100, 10,108,
    111, 99, 97,108, 32,108, 97,115,116, 80,114,105,110,116, 32,
     61, 32,112,114,105,110,116, 10,102,117,110, 99,116,105,111,
    110, 32,112,114,105,110,116, 40, 46, 46, 46, 41, 10, 99,111,
    111,114,100, 97, 58, 76,111,103, 40, 46, 46, 46, 41, 10,101,
    110,100, 10,102,117,110, 99,116,105,111,110, 32, 95,109, 97,
    105,110, 95, 40, 41, 10,115, 99,114,105,112,116, 46,112, 97,
     99,107, 97,103,101, 32, 61, 32,123,125, 10,115, 99,114,105,
    112,116, 46,101,120,112,111,114,116, 32, 61, 32,123,125, 10,
    101,110,100, 10,102,117,110, 99,116,105,111,110, 32, 95,111,
    110, 65,119, 97,107,101, 95, 40, 41, 10,108,111, 99, 97,108,
     32,112, 97, 99,107, 97,103,101, 32, 61, 32,105,109,112,111,
    114,116, 40, 99,111,111,114,100, 97, 46, 83, 99,114,105,112,
    116, 46, 77, 97,105,110, 44, 32, 39,109, 97,105,110, 39, 41,
     10,105,102, 32,110,111,116, 32,112, 97, 99,107, 97,103,101,
     32,116,104,101,110, 10,101,114,114,111,114, 40, 34,105,109,
    112,111,114,116, 32,109, 97,105,110, 32,112, 97, 99,107, 97,
    103,101, 32,102, 97,105,108,101,100, 34, 41, 10,101,110,100,
     10,101,110,100, 10,102,117,110, 99,116,105,111,110, 32, 95,
    111,110, 68,101,115,116,111,114,121, 95, 40, 41, 10,105,102,
     32,110,111,116, 32, 99,111,111,114,100, 97, 32,116,104,101,
    110, 10,114,101,116,117,114,110, 10,101,110,100, 10,105,102,
     32,110,111,116, 32,115, 99,114,105,112,116, 46,101,120,112,
    111,114,116, 46,109, 97,105,110, 32,116,104,101,110, 10,114,
    101,116,117,114,110, 10,101,110,100, 10,115, 99,114,105,112,
    116, 46,101,120,112,111,114,116, 46,109, 97,105,110, 46,111,
    110, 68,101,115,116,111,114,121, 40, 41, 10,101,110,100, 10,
    102,117,110, 99,116,105,111,110, 32, 95,111,110, 82,101,108,
    111, 97,100, 95, 40, 41, 10,115, 99,114,105,112,116, 46,114,
    101,108,111, 97,100,105,110,103, 32, 61, 32,116,114,117,101,
     10,115, 99,114,105,112,116, 46,114,101,108,111, 97,100, 32,
     61, 32,123,125, 10,108,111, 99, 97,108, 32,112, 97, 99,107,
     97,103,101, 32, 61, 32,105,109,112,111,114,116, 40, 99,111,
    111,114,100, 97, 46, 83, 99,114,105,112,116, 46, 77, 97,105,
    110, 44, 32, 39,109, 97,105,110, 39, 41, 10,115, 99,114,105,
    112,116, 46,114,101,108,111, 97,100,105,110,103, 32, 61, 32,
    102, 97,108,115,101, 10,115, 99,114,105,112,116, 46,114,101,
    108,111, 97,100, 32, 61, 32,123,125, 10,105,102, 32,110,111,
    116, 32,112, 97, 99,107, 97,103,101, 32,116,104,101,110, 10,
    101,114,114,111,114, 40, 34,105,109,112,111,114,116, 32,109,
     97,105,110, 32,112, 97, 99,107, 97,103,101, 32,102, 97,105,
    108,101,100, 34, 41, 10,101,110,100, 10,101,110,100, 10,102,
    117,110, 99,116,105,111,110, 32,114,101,108,111, 97,100, 40,
    112, 97, 99,107, 97,103,101, 80, 97,116,104, 44, 32,101,120,
    112,111,114,116, 78, 97,109,101, 41, 10,115, 99,114,105,112,
    116, 46,114,101,108,111, 97,100,105,110,103, 32, 61, 32,116,
    114,117,101, 10,115, 99,114,105,112,116, 46,114,101,108,111,
     97,100, 32, 61, 32,123,125, 10,108,111, 99, 97,108, 32,112,
     97, 99,107, 97,103,101, 32, 61, 32,105,109,112,111,114,116,
     40,112, 97, 99,107, 97,103,101, 80, 97,116,104, 44, 32,101,
    120,112,111,114,116, 78, 97,109,101, 41, 10,115, 99,114,105,
    112,116, 46,114,101,108,111, 97,100,105,110,103, 32, 61, 32,
    102, 97,108,115,101, 10,115, 99,114,105,112,116, 46,114,101,
    108,111, 97,100, 32, 61, 32,123,125, 10,114,101,116,117,114,
    110, 32,112, 97, 99,107, 97,103,101, 10,101,110,100, 10,102,
    117,110, 99,116,105,111,110, 32, 95, 82, 69, 81, 85, 69, 83,
     84, 40,115,101,108,102, 44, 32, 97,114,103,115, 41, 10,112,
    114,105,110,116, 40,115,101,108,102, 41, 10,112,114,105,110,
    116, 40, 34,103,103,103,103,103,103, 34, 44, 32, 97,114,103,
    115, 41, 10,101,110,100,32
   };
   tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: ../lualib/lib.lua");
   lua_settop(tolua_S, top);
  } /* end of embedded lua code */

 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 extern "C"{
 TOLUA_API int luaopen_coord (lua_State* tolua_S) {
 return tolua_coord_open(tolua_S);
};
}
#endif

