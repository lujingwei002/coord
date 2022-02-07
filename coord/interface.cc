/*
** Lua binding: coord
** Generated automatically by tolua++-1.0.92 on Wed Sep  8 15:30:17 2021.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_coord_open (lua_State* tolua_S);

#include "src/coord/coord.h"
#include "src/coord/config/config.h"
#include "src/coord/script/script.h"
#include "src/coord/base/type.h"
#include "src/coord/base/destoryable.h"
#include "src/coord/object/object.h"
#include "src/coord/scene/scene.h"
#include "src/coord/scene/scene_mgr.h"
#include "src/coord/component/component.h"
#include "src/coord/http/http_server.h"
#include "src/coord/http/http_request.h"
#include "src/coord/http/http_response.h"
#include "src/coord/http/http_router.h"
#include "src/coord/http/http_agent.h"
#include "src/coord/websocket/websocket_server.h"
#include "src/coord/websocket/websocket_router.h"
#include "src/coord/websocket/websocket_frame.h"
#include "src/coord/websocket/websocket_agent.h"
#include "src/coord/component/script_component.h"
#include "src/coord/display/transform.h"
#include "src/coord/display/vector3.h"
#include "src/coord/net/tcp_listener.h"
#include "src/coord/net/tcp_agent.h"
#include "src/coord/gate/gate.h"
#include "src/coord/gate/gate_router.h"
#include "src/coord/gate/gate_request.h"
#include "src/coord/gate/gate_notify.h"
#include "src/coord/gate/gate_response.h"
#include "src/coord/gate/gate_session.h"
#include "src/coord/event/event_args.h"
#include "src/coord/proto/proto_mgr.h"
#include "src/coord/proto/reflect.h"
#include "src/coord/proto/repeated.h"
#include "src/coord/timer/timer.h"
#include "src/coord/sql/sql_mgr.h"
#include "src/coord/sql/sql_client.h"
#include "src/coord/sql/sql_result.h"
#include "src/coord/sql/sql_rows.h"
#include "src/coord/sql/mysql/mysql_client.h"
#include "src/coord/sql/mysql/mysql_result.h"
#include "src/coord/sql/mysql/mysql_rows.h"
#include "src/coord/redis/redis_mgr.h"
#include "src/coord/redis/redis_config.h"
#include "src/coord/redis/redis_async_client.h"
#include "src/coord/redis/redis_client.h"
#include "src/coord/redis/redis_promise.h"
#include "src/coord/redis/redis_reply.h"
#include "src/coord/cache/cache.h"
#include "src/coord/cache/cache_reader.h"
#include "src/coord/cluster/cluster.h"
#include "src/coord/cluster/cluster_router.h"
#include "src/coord/cluster/cluster_request.h"
#include "src/coord/cluster/cluster_notify.h"
#include "src/coord/cluster/cluster_response.h"
#include "src/coord/cluster/cluster_promise.h"
#include "src/coord/cluster/cluster_result.h"
#include "src/coord/net/tcp_client.h"
#include "src/util/os/os.h"
#include "src/util/os/path.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_coord__proto__Repeated (lua_State* tolua_S)
{
 coord::proto::Repeated* self = (coord::proto::Repeated*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}

static int tolua_collect_coord__proto__Reflect (lua_State* tolua_S)
{
 coord::proto::Reflect* self = (coord::proto::Reflect*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"coord::cluster::ClusterRequest");
 tolua_usertype(tolua_S,"coord::ClusterConfig");
 tolua_usertype(tolua_S,"coord::net::TcpAgent");
 tolua_usertype(tolua_S,"coord::cache::CacheConfig");
 tolua_usertype(tolua_S,"coord::sql::SQLRows");
 tolua_usertype(tolua_S,"coord::http::HttpAgent");
 tolua_usertype(tolua_S,"coord::websocket::WebSocketServerConfig");
 tolua_usertype(tolua_S,"coord::websocket::WebSocketServer");
 tolua_usertype(tolua_S,"coord::gate::GateResponse");
 tolua_usertype(tolua_S,"coord::net::TcpListener");
 tolua_usertype(tolua_S,"coord::cache::CacheReader");
 tolua_usertype(tolua_S,"coord::TimerMgr");
 tolua_usertype(tolua_S,"coord::http::HttpResponse");
 tolua_usertype(tolua_S,"coord::net::ITcpHandler");
 tolua_usertype(tolua_S,"coord::cluster::ClusterResponse");
 tolua_usertype(tolua_S,"coord::SceneMgr");
 tolua_usertype(tolua_S,"coord::cluster::ClusterResult");
 tolua_usertype(tolua_S,"coord::WebConfig");
 tolua_usertype(tolua_S,"coord::Transform");
 tolua_usertype(tolua_S,"coord::Script");
 tolua_usertype(tolua_S,"coord::Object");
 tolua_usertype(tolua_S,"coord::Config");
 tolua_usertype(tolua_S,"coord::ScriptComponent");
 tolua_usertype(tolua_S,"coord::sql::MySQLRows");
 tolua_usertype(tolua_S,"coord::GateConfig");
 tolua_usertype(tolua_S,"coord::sql::MySQLResult");
 tolua_usertype(tolua_S,"coord::Scene");
 tolua_usertype(tolua_S,"coord::proto::Reflect");
 tolua_usertype(tolua_S,"coord::sql::SQLConfig");
 tolua_usertype(tolua_S,"coord::net::ITcpAgentHandler");
 tolua_usertype(tolua_S,"coord::cluster::ClusterPromise");
 tolua_usertype(tolua_S,"coord::Coord");
 tolua_usertype(tolua_S,"coord::proto::ProtoMgr");
 tolua_usertype(tolua_S,"coord::http::IHttpAgentHandler");
 tolua_usertype(tolua_S,"coord::EventArgs");
 tolua_usertype(tolua_S,"coord::sql::SQLClient");
 tolua_usertype(tolua_S,"coord::websocket::IWebSocketAgentHandler");
 tolua_usertype(tolua_S,"coord::Vector3");
 tolua_usertype(tolua_S,"coord::net::TcpClient");
 tolua_usertype(tolua_S,"coord::http::HttpRequest");
 tolua_usertype(tolua_S,"coord::websocket::IWebSocketHandler");
 tolua_usertype(tolua_S,"coord::http::IHttpHandler");
 tolua_usertype(tolua_S,"coord::gate::Gate");
 tolua_usertype(tolua_S,"coord::http::HttpServer");
 tolua_usertype(tolua_S,"coord::gate::GateSession");
 tolua_usertype(tolua_S,"coord::net::ITcpClientHandler");
 tolua_usertype(tolua_S,"coord::Destoryable");
 tolua_usertype(tolua_S,"coord::cluster::ClusterNotify");
 tolua_usertype(tolua_S,"coord::redis::RedisAsyncClient");
 tolua_usertype(tolua_S,"coord::gate::GateConfig");
 tolua_usertype(tolua_S,"coord::cluster::ClusterRouter");
 tolua_usertype(tolua_S,"coord::cluster::Cluster");
 tolua_usertype(tolua_S,"coord::sql::SQLResult");
 tolua_usertype(tolua_S,"coord::websocket::WebSocketFrame");
 tolua_usertype(tolua_S,"coord::cache::Cache");
 tolua_usertype(tolua_S,"coord::redis::RedisReply");
 tolua_usertype(tolua_S,"coord::gate::GateNotify");
 tolua_usertype(tolua_S,"coord::redis::RedisPromise");
 tolua_usertype(tolua_S,"coord::Component");
 tolua_usertype(tolua_S,"coord::redis::RedisClient");
 tolua_usertype(tolua_S,"coord::proto::Repeated");
 tolua_usertype(tolua_S,"coord::cluster::ClusterConfig");
 tolua_usertype(tolua_S,"IEventHandler");
 tolua_usertype(tolua_S,"coord::redis::RedisMgr");
 tolua_usertype(tolua_S,"coord::websocket::WebSocketRouter");
 tolua_usertype(tolua_S,"coord::redis::RedisConfig");
 tolua_usertype(tolua_S,"coord::sql::MySQLClient");
 tolua_usertype(tolua_S,"coord::Type");
 tolua_usertype(tolua_S,"coord::sql::SQLMgr");
 tolua_usertype(tolua_S,"coord::CacheConfig");
 tolua_usertype(tolua_S,"coord::http::HttpRouter");
 tolua_usertype(tolua_S,"coord::gate::GateRouter");
 tolua_usertype(tolua_S,"coord::http::HttpServerConfig");
 tolua_usertype(tolua_S,"coord::gate::GateRequest");
 tolua_usertype(tolua_S,"coord::websocket::WebSocketAgent");
}

/* method: Exit of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Exit00
static int tolua_coord_coord_Coord_Exit00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exit'",NULL);
#endif
  {
   self->Exit(code);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Exit'.",&tolua_err);
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

/* method: CloseAllLog of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_CloseAllLog00
static int tolua_coord_coord_Coord_CloseAllLog00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CloseAllLog'",NULL);
#endif
  {
   self->CloseAllLog();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CloseAllLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenLog of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_OpenLog00
static int tolua_coord_coord_Coord_OpenLog00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OpenLog'",NULL);
#endif
  {
   self->OpenLog(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenLog'.",&tolua_err);
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

/* method: AddScript of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_AddScript00
static int tolua_coord_coord_Coord_AddScript00(lua_State* tolua_S)
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
  const char* scriptName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddScript'",NULL);
#endif
  {
   coord::ScriptComponent* tolua_ret = (coord::ScriptComponent*)  self->AddScript(scriptName);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::ScriptComponent");
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

/* method: Emit of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Emit00
static int tolua_coord_coord_Coord_Emit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::EventArgs",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::EventArgs* args = ((coord::EventArgs*)  tolua_tousertype(tolua_S,3,0));
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
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Destory00
static int tolua_coord_coord_Coord_Destory00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destory'",NULL);
#endif
  {
   self->Destory(object);
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

/* method: Destory of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Destory01
static int tolua_coord_coord_Coord_Destory01(lua_State* tolua_S)
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
 return tolua_coord_coord_Coord_Destory00(tolua_S);
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

/* method: SetTimeout of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_SetTimeout00
static int tolua_coord_coord_Coord_SetTimeout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* script = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  uint64_t timeout = ((uint64_t)  tolua_tonumber(tolua_S,3,0));
  const char* func = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeout'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetTimeout(script,timeout,func);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* script = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  uint64_t repeat = ((uint64_t)  tolua_tonumber(tolua_S,3,0));
  const char* func = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInterval'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetInterval(script,repeat,func);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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
   coord::redis::RedisClient* tolua_ret = (coord::redis::RedisClient*)  self->RedisConfig(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisClient");
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
   coord::redis::RedisAsyncClient* tolua_ret = (coord::redis::RedisAsyncClient*)  self->RedisAsyncConfig(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisAsyncClient");
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

/* method: Cache of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Cache00
static int tolua_coord_coord_Coord_Cache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,3,0));
  size_t expiret = ((size_t)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cache'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Cache(name,data,expiret);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Cache of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Coord_Cache01
static int tolua_coord_coord_Coord_Cache01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Coord",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cache'",NULL);
#endif
  {
   coord::cache::CacheReader* tolua_ret = (coord::cache::CacheReader*)  self->Cache(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cache::CacheReader");
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_Coord_Cache00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: config of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_config_ptr
static int tolua_get_coord__Coord_config_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'config'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->config,"coord::Config");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: config of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_config_ptr
static int tolua_set_coord__Coord_config_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'config'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Config",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->config = ((coord::Config*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: script of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_script_ptr
static int tolua_get_coord__Coord_script_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'script'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->script,"coord::Script");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: script of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_script_ptr
static int tolua_set_coord__Coord_script_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'script'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::Script",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->script = ((coord::Script*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gate of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_gate_ptr
static int tolua_get_coord__Coord_gate_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gate'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->gate,"coord::gate::Gate");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gate of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_gate_ptr
static int tolua_set_coord__Coord_gate_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gate'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::gate::Gate",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->gate = ((coord::gate::Gate*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: httpServer of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_httpServer_ptr
static int tolua_get_coord__Coord_httpServer_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'httpServer'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->httpServer,"coord::http::HttpServer");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: httpServer of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_httpServer_ptr
static int tolua_set_coord__Coord_httpServer_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'httpServer'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::http::HttpServer",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->httpServer = ((coord::http::HttpServer*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: proto of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_proto_ptr
static int tolua_get_coord__Coord_proto_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'proto'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->proto,"coord::proto::ProtoMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: proto of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_proto_ptr
static int tolua_set_coord__Coord_proto_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'proto'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::proto::ProtoMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->proto = ((coord::proto::ProtoMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sqlMgr of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_sqlMgr_ptr
static int tolua_get_coord__Coord_sqlMgr_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sqlMgr'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->sqlMgr,"coord::sql::SQLMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sqlMgr of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_sqlMgr_ptr
static int tolua_set_coord__Coord_sqlMgr_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sqlMgr'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::sql::SQLMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sqlMgr = ((coord::sql::SQLMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: redisMgr of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_redisMgr_ptr
static int tolua_get_coord__Coord_redisMgr_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'redisMgr'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->redisMgr,"coord::redis::RedisMgr");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: redisMgr of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_redisMgr_ptr
static int tolua_set_coord__Coord_redisMgr_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'redisMgr'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::redis::RedisMgr",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->redisMgr = ((coord::redis::RedisMgr*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cluster of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_cluster_ptr
static int tolua_get_coord__Coord_cluster_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cluster'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->cluster,"coord::cluster::Cluster");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cluster of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_cluster_ptr
static int tolua_set_coord__Coord_cluster_ptr(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cluster'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::cluster::Cluster",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cluster = ((coord::cluster::Cluster*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: configFile of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_get_coord__Coord_configFile
static int tolua_get_coord__Coord_configFile(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'configFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->configFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: configFile of class  coord::Coord */
#ifndef TOLUA_DISABLE_tolua_set_coord__Coord_configFile
static int tolua_set_coord__Coord_configFile(lua_State* tolua_S)
{
  coord::Coord* self = (coord::Coord*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'configFile'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->configFile = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Port of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_Port
static int tolua_get_coord__GateConfig_Port(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_Port
static int tolua_set_coord__GateConfig_Port(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Host of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_Host
static int tolua_get_coord__GateConfig_Host(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_Host
static int tolua_set_coord__GateConfig_Host(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Network of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_Network
static int tolua_get_coord__GateConfig_Network(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Network'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Network);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Network of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_Network
static int tolua_set_coord__GateConfig_Network(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: RsaEncrypt of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_RsaEncrypt
static int tolua_get_coord__GateConfig_RsaEncrypt(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RsaEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->RsaEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RsaEncrypt of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_RsaEncrypt
static int tolua_set_coord__GateConfig_RsaEncrypt(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: RsaKeyFile of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_RsaKeyFile
static int tolua_get_coord__GateConfig_RsaKeyFile(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RsaKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->RsaKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RsaKeyFile of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_RsaKeyFile
static int tolua_set_coord__GateConfig_RsaKeyFile(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Heartbeat of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_Heartbeat
static int tolua_get_coord__GateConfig_Heartbeat(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Heartbeat'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Heartbeat);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Heartbeat of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_Heartbeat
static int tolua_set_coord__GateConfig_Heartbeat(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Backlog of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_Backlog
static int tolua_get_coord__GateConfig_Backlog(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Backlog'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Backlog);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Backlog of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_Backlog
static int tolua_set_coord__GateConfig_Backlog(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: RecvBuffer of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_RecvBuffer
static int tolua_get_coord__GateConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RecvBuffer'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RecvBuffer);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RecvBuffer of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_RecvBuffer
static int tolua_set_coord__GateConfig_RecvBuffer(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: SSLEncrypt of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_SSLEncrypt
static int tolua_get_coord__GateConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLEncrypt'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->SSLEncrypt);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLEncrypt of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_SSLEncrypt
static int tolua_set_coord__GateConfig_SSLEncrypt(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: SSLPemFile of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_SSLPemFile
static int tolua_get_coord__GateConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLPemFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLPemFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLPemFile of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_SSLPemFile
static int tolua_set_coord__GateConfig_SSLPemFile(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: SSLKeyFile of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_SSLKeyFile
static int tolua_get_coord__GateConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'SSLKeyFile'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->SSLKeyFile);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: SSLKeyFile of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_SSLKeyFile
static int tolua_set_coord__GateConfig_SSLKeyFile(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: MaxUser of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_MaxUser
static int tolua_get_coord__GateConfig_MaxUser(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxUser'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->MaxUser);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: MaxUser of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_MaxUser
static int tolua_set_coord__GateConfig_MaxUser(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: MaxConnection of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__GateConfig_MaxConnection
static int tolua_get_coord__GateConfig_MaxConnection(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'MaxConnection'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->MaxConnection);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: MaxConnection of class  coord::GateConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__GateConfig_MaxConnection
static int tolua_set_coord__GateConfig_MaxConnection(lua_State* tolua_S)
{
  coord::GateConfig* self = (coord::GateConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: password of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__CacheConfig_password
static int tolua_get_coord__CacheConfig_password(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: password of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__CacheConfig_password
static int tolua_set_coord__CacheConfig_password(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'password'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->password = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: db of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__CacheConfig_db
static int tolua_get_coord__CacheConfig_db(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'db'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->db);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: db of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__CacheConfig_db
static int tolua_set_coord__CacheConfig_db(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'db'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->db = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: host of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__CacheConfig_host
static int tolua_get_coord__CacheConfig_host(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: host of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__CacheConfig_host
static int tolua_set_coord__CacheConfig_host(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: port of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__CacheConfig_port
static int tolua_get_coord__CacheConfig_port(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: port of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__CacheConfig_port
static int tolua_set_coord__CacheConfig_port(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->port = ((uint16_t)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: expireTime of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__CacheConfig_expireTime
static int tolua_get_coord__CacheConfig_expireTime(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'expireTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->expireTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: expireTime of class  coord::CacheConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__CacheConfig_expireTime
static int tolua_set_coord__CacheConfig_expireTime(lua_State* tolua_S)
{
  coord::CacheConfig* self = (coord::CacheConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'expireTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->expireTime = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: Driver of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_Driver
static int tolua_get_coord__ClusterConfig_Driver(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Driver'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Driver);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Driver of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_Driver
static int tolua_set_coord__ClusterConfig_Driver(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Host of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_Host
static int tolua_get_coord__ClusterConfig_Host(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_Host
static int tolua_set_coord__ClusterConfig_Host(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Port of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_Port
static int tolua_get_coord__ClusterConfig_Port(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_Port
static int tolua_set_coord__ClusterConfig_Port(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Heartbeat of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_Heartbeat
static int tolua_get_coord__ClusterConfig_Heartbeat(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Heartbeat'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Heartbeat);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Heartbeat of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_Heartbeat
static int tolua_set_coord__ClusterConfig_Heartbeat(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Expire of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_Expire
static int tolua_get_coord__ClusterConfig_Expire(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Expire'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Expire);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Expire of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_Expire
static int tolua_set_coord__ClusterConfig_Expire(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Name of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_Name
static int tolua_get_coord__ClusterConfig_Name(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Name of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_Name
static int tolua_set_coord__ClusterConfig_Name(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: RegisterInterval of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_RegisterInterval
static int tolua_get_coord__ClusterConfig_RegisterInterval(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'RegisterInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->RegisterInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: RegisterInterval of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_RegisterInterval
static int tolua_set_coord__ClusterConfig_RegisterInterval(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: ReloadInterval of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_ReloadInterval
static int tolua_get_coord__ClusterConfig_ReloadInterval(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ReloadInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ReloadInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ReloadInterval of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_ReloadInterval
static int tolua_set_coord__ClusterConfig_ReloadInterval(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: ReconnectInterval of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__ClusterConfig_ReconnectInterval
static int tolua_get_coord__ClusterConfig_ReconnectInterval(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ReconnectInterval'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->ReconnectInterval);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: ReconnectInterval of class  coord::ClusterConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__ClusterConfig_ReconnectInterval
static int tolua_set_coord__ClusterConfig_ReconnectInterval(lua_State* tolua_S)
{
  coord::ClusterConfig* self = (coord::ClusterConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: path of class  coord::Script */
#ifndef TOLUA_DISABLE_tolua_get_coord__Script_path
static int tolua_get_coord__Script_path(lua_State* tolua_S)
{
  coord::Script* self = (coord::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'path'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->path);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: path of class  coord::Script */
#ifndef TOLUA_DISABLE_tolua_set_coord__Script_path
static int tolua_set_coord__Script_path(lua_State* tolua_S)
{
  coord::Script* self = (coord::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'path'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->path,tolua_tostring(tolua_S,2,0),PACKAGE_MAX-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: main of class  coord::Script */
#ifndef TOLUA_DISABLE_tolua_get_coord__Script_main
static int tolua_get_coord__Script_main(lua_State* tolua_S)
{
  coord::Script* self = (coord::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'main'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->main);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: main of class  coord::Script */
#ifndef TOLUA_DISABLE_tolua_set_coord__Script_main
static int tolua_set_coord__Script_main(lua_State* tolua_S)
{
  coord::Script* self = (coord::Script*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'main'",NULL);
  if (!tolua_isstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy(self->main,tolua_tostring(tolua_S,2,0),PACKAGE_MAX-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Test of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_Test00
static int tolua_coord_coord_Object_Test00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Test'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Test();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Test'.",&tolua_err);
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

/* method: Update of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_Update00
static int tolua_coord_coord_Object_Update00(lua_State* tolua_S)
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
  uint64_t cur_tick = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'",NULL);
#endif
  {
   self->Update(cur_tick);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Awake of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_Awake00
static int tolua_coord_coord_Object_Awake00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Awake'",NULL);
#endif
  {
   self->Awake();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Awake'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destory of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_Destory00
static int tolua_coord_coord_Object_Destory00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destory'",NULL);
#endif
  {
   self->Destory();
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
   coord::Component* tolua_ret = (coord::Component*)  self->AddComponent(component);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::Component");
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
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  const char* scriptName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddScript'",NULL);
#endif
  {
   coord::ScriptComponent* tolua_ret = (coord::ScriptComponent*)  self->AddScript(scriptName);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::ScriptComponent");
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

/* method: RemoveChild of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_RemoveChild00
static int tolua_coord_coord_Object_RemoveChild00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChild'",NULL);
#endif
  {
   int tolua_ret = (int)  self->RemoveChild(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveChild of class  coord::Object */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Object_RemoveChild01
static int tolua_coord_coord_Object_RemoveChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Object",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::Object* self = (coord::Object*)  tolua_tousertype(tolua_S,1,0);
  coord::Object* obj = ((coord::Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChild'",NULL);
#endif
  {
   int tolua_ret = (int)  self->RemoveChild(obj);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_Object_RemoveChild00(tolua_S);
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

/* method: AddObject of class  coord::Scene */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Scene_AddObject00
static int tolua_coord_coord_Scene_AddObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Object",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Scene* self = (coord::Scene*)  tolua_tousertype(tolua_S,1,0);
  coord::Object* object = ((coord::Object*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddObject'",NULL);
#endif
  {
   int tolua_ret = (int)  self->AddObject(object);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddObject'.",&tolua_err);
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

/* method: Update of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_Update00
static int tolua_coord_coord_Component_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::Component",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Component* self = (coord::Component*)  tolua_tousertype(tolua_S,1,0);
  uint64_t cur_tick = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'",NULL);
#endif
  {
   self->Update(cur_tick);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
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

/* method: AddEventListener of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_AddEventListener00
static int tolua_coord_coord_Component_AddEventListener00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddEventListener'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddEventListener(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddEventListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveEventListener of class  coord::Component */
#ifndef TOLUA_DISABLE_tolua_coord_coord_Component_RemoveEventListener00
static int tolua_coord_coord_Component_RemoveEventListener00(lua_State* tolua_S)
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
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveEventListener'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->RemoveEventListener(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveEventListener'.",&tolua_err);
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

/* get function: host of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_host
static int tolua_get_coord__http__HttpServerConfig_host(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: host of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_host
static int tolua_set_coord__http__HttpServerConfig_host(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: port of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpServerConfig_unsigned_port
static int tolua_get_coord__http__HttpServerConfig_unsigned_port(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: port of class  coord::http::HttpServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpServerConfig_unsigned_port
static int tolua_set_coord__http__HttpServerConfig_unsigned_port(lua_State* tolua_S)
{
  coord::http::HttpServerConfig* self = (coord::http::HttpServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->port = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
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

/* method: Listen of class  coord::http::HttpServer */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpServer_Listen00
static int tolua_coord_coord_http_HttpServer_Listen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpServer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpServer* self = (coord::http::HttpServer*)  tolua_tousertype(tolua_S,1,0);
  const char* host = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  int backlog = ((int)  tolua_tonumber(tolua_S,4,0));
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

/* get function: Body of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_get_coord__http__HttpRequest_Body
static int tolua_get_coord__http__HttpRequest_Body(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Body'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Body);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Body of class  coord::http::HttpRequest */
#ifndef TOLUA_DISABLE_tolua_set_coord__http__HttpRequest_Body
static int tolua_set_coord__http__HttpRequest_Body(lua_State* tolua_S)
{
  coord::http::HttpRequest* self = (coord::http::HttpRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Body'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Body = ((std::string)  tolua_tocppstring(tolua_S,2,0))
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

/* method: JSON of class  coord::http::HttpResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpResponse_JSON00
static int tolua_coord_coord_http_HttpResponse_JSON00(lua_State* tolua_S)
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
  const char* content = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'JSON'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->JSON(content);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'JSON'.",&tolua_err);
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

/* method: GET of class  coord::http::HttpRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRouter_GET00
static int tolua_coord_coord_http_HttpRouter_GET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRouter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRouter* self = (coord::http::HttpRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* handler = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  const char* method = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GET'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GET(path,handler,method);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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

/* method: POST of class  coord::http::HttpRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_http_HttpRouter_POST00
static int tolua_coord_coord_http_HttpRouter_POST00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::http::HttpRouter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::http::HttpRouter* self = (coord::http::HttpRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* handler = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  const char* method = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'POST'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->POST(path,handler,method);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'POST'.",&tolua_err);
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

/* get function: host of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_host
static int tolua_get_coord__websocket__WebSocketServerConfig_host(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: host of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_host
static int tolua_set_coord__websocket__WebSocketServerConfig_host(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'host'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->host = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: port of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServerConfig_unsigned_port
static int tolua_get_coord__websocket__WebSocketServerConfig_unsigned_port(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: port of class  coord::websocket::WebSocketServerConfig */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServerConfig_unsigned_port
static int tolua_set_coord__websocket__WebSocketServerConfig_unsigned_port(lua_State* tolua_S)
{
  coord::websocket::WebSocketServerConfig* self = (coord::websocket::WebSocketServerConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'port'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->port = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
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

/* method: Listen of class  coord::websocket::WebSocketServer */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_WebSocketServer_Listen00
static int tolua_coord_coord_websocket_WebSocketServer_Listen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::WebSocketServer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::WebSocketServer* self = (coord::websocket::WebSocketServer*)  tolua_tousertype(tolua_S,1,0);
  const char* host = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  int backlog = ((int)  tolua_tonumber(tolua_S,4,0));
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

/* method: DefaultConfig of class  coord::websocket::WebSocketServer */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_WebSocketServer_DefaultConfig00
static int tolua_coord_coord_websocket_WebSocketServer_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::WebSocketServer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::WebSocketServer* self = (coord::websocket::WebSocketServer*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Router of class  coord::websocket::WebSocketServer */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketServer_Router_ptr
static int tolua_get_coord__websocket__WebSocketServer_Router_ptr(lua_State* tolua_S)
{
  coord::websocket::WebSocketServer* self = (coord::websocket::WebSocketServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->Router,"coord::websocket::WebSocketRouter");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Router of class  coord::websocket::WebSocketServer */
#ifndef TOLUA_DISABLE_tolua_set_coord__websocket__WebSocketServer_Router_ptr
static int tolua_set_coord__websocket__WebSocketServer_Router_ptr(lua_State* tolua_S)
{
  coord::websocket::WebSocketServer* self = (coord::websocket::WebSocketServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Router'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::websocket::WebSocketRouter",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->Router = ((coord::websocket::WebSocketRouter*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: MESSAGE of class  coord::websocket::WebSocketRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_WebSocketRouter_MESSAGE00
static int tolua_coord_coord_websocket_WebSocketRouter_MESSAGE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::WebSocketRouter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::WebSocketRouter* self = (coord::websocket::WebSocketRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* handler = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  const char* method = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MESSAGE'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->MESSAGE(path,handler,method);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MESSAGE'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendBinaryFrame of class  coord::websocket::WebSocketAgent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_WebSocketAgent_SendBinaryFrame00
static int tolua_coord_coord_websocket_WebSocketAgent_SendBinaryFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::WebSocketAgent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::WebSocketAgent* self = (coord::websocket::WebSocketAgent*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SendStringFrame of class  coord::websocket::WebSocketAgent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_websocket_WebSocketAgent_SendStringFrame00
static int tolua_coord_coord_websocket_WebSocketAgent_SendStringFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::websocket::WebSocketAgent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::websocket::WebSocketAgent* self = (coord::websocket::WebSocketAgent*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: __http of class  coord::websocket::WebSocketAgent */
#ifndef TOLUA_DISABLE_tolua_get_coord__websocket__WebSocketAgent___http__IHttpAgentHandler__
static int tolua_get_coord__websocket__WebSocketAgent___http__IHttpAgentHandler__(lua_State* tolua_S)
{
  coord::websocket::WebSocketAgent* self = (coord::websocket::WebSocketAgent*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Awake of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_Awake00
static int tolua_coord_coord_ScriptComponent_Awake00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Awake'",NULL);
#endif
  {
   self->Awake();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Awake'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  coord::ScriptComponent */
#ifndef TOLUA_DISABLE_tolua_coord_coord_ScriptComponent_Update00
static int tolua_coord_coord_ScriptComponent_Update00(lua_State* tolua_S)
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
  uint64_t cur_tick = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'",NULL);
#endif
  {
   self->Update(cur_tick);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
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
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  uint64_t timeout = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
  const char* func = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeout'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetTimeout(timeout,func);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::ScriptComponent* self = (coord::ScriptComponent*)  tolua_tousertype(tolua_S,1,0);
  uint64_t repeat = ((uint64_t)  tolua_tonumber(tolua_S,2,0));
  const char* func = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInterval'",NULL);
#endif
  {
   int tolua_ret = (int)  self->SetInterval(repeat,func);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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
  int sessionId = ((int)  tolua_tonumber(tolua_S,2,0));
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

/* method: Notify of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_Notify00
static int tolua_coord_coord_gate_GateRouter_Notify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Notify'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Notify(path,object,script);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Request(path,object,script);
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

/* method: SessionNew of class  coord::gate::GateRouter */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRouter_SessionNew00
static int tolua_coord_coord_gate_GateRouter_SessionNew00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateRouter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SessionNew'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SessionNew(object,script);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SessionClose'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SessionClose(object,script);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Login'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Login(object,script);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Logout'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Logout(object,script);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateRouter* self = (coord::gate::GateRouter*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Instead'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Instead(object,script);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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

/* method: Proto of class  coord::gate::GateRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateRequest_Proto00
static int tolua_coord_coord_gate_GateRequest_Proto00(lua_State* tolua_S)
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
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::proto::Reflect* tolua_ret = (coord::proto::Reflect*)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::proto::Reflect");
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
  self->sessionId = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::gate::GateNotify */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateNotify_Proto00
static int tolua_coord_coord_gate_GateNotify_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateNotify",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateNotify* self = (coord::gate::GateNotify*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::proto::Reflect* tolua_ret = (coord::proto::Reflect*)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::proto::Reflect");
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
  self->sessionId = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::gate::GateResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateResponse_Proto00
static int tolua_coord_coord_gate_GateResponse_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateResponse* self = (coord::gate::GateResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::proto::Reflect* tolua_ret = (coord::proto::Reflect*)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::proto::Reflect");
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

/* method: String of class  coord::gate::GateResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_gate_GateResponse_String00
static int tolua_coord_coord_gate_GateResponse_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::gate::GateResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateResponse* self = (coord::gate::GateResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   self->String(data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'String'.",&tolua_err);
 return 0;
#endif
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
     !tolua_isusertype(tolua_S,3,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::gate::GateSession* self = (coord::gate::GateSession*)  tolua_tousertype(tolua_S,1,0);
  const char* route = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::proto::Reflect* proto = ((coord::proto::Reflect*)  tolua_tousertype(tolua_S,3,0));
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
  self->Id = ((int)  tolua_tonumber(tolua_S,2,0))
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

/* get function: name of class  coord::EventArgs */
#ifndef TOLUA_DISABLE_tolua_get_coord__EventArgs_name
static int tolua_get_coord__EventArgs_name(lua_State* tolua_S)
{
  coord::EventArgs* self = (coord::EventArgs*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name of class  coord::EventArgs */
#ifndef TOLUA_DISABLE_tolua_set_coord__EventArgs_name
static int tolua_set_coord__EventArgs_name(lua_State* tolua_S)
{
  coord::EventArgs* self = (coord::EventArgs*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: arg of class  coord::EventArgs */
#ifndef TOLUA_DISABLE_tolua_get_coord__EventArgs_arg
static int tolua_get_coord__EventArgs_arg(lua_State* tolua_S)
{
  coord::EventArgs* self = (coord::EventArgs*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arg'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->arg);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: arg of class  coord::EventArgs */
#ifndef TOLUA_DISABLE_tolua_set_coord__EventArgs_arg
static int tolua_set_coord__EventArgs_arg(lua_State* tolua_S)
{
  coord::EventArgs* self = (coord::EventArgs*)  tolua_tousertype(tolua_S,1,0);
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

/* method: MapPath of class  coord::proto::ProtoMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_ProtoMgr_MapPath00
static int tolua_coord_coord_proto_ProtoMgr_MapPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::ProtoMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::ProtoMgr* self = (coord::proto::ProtoMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* dir = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MapPath'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->MapPath(name,dir);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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

/* method: Import of class  coord::proto::ProtoMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_ProtoMgr_Import00
static int tolua_coord_coord_proto_ProtoMgr_Import00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::ProtoMgr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::ProtoMgr* self = (coord::proto::ProtoMgr*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Import'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Import(fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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

/* method: NewReflect of class  coord::proto::ProtoMgr */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_ProtoMgr_NewReflect00
static int tolua_coord_coord_proto_ProtoMgr_NewReflect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::ProtoMgr",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::ProtoMgr* self = (coord::proto::ProtoMgr*)  tolua_tousertype(tolua_S,1,0);
  lua_State* L =  tolua_S;
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NewReflect'",NULL);
#endif
  {
return self->NewReflect(L);
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

/* method: delete of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_delete00
static int tolua_coord_coord_proto_Reflect_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Get of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_Get00
static int tolua_coord_coord_proto_Reflect_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetString of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetString00
static int tolua_coord_coord_proto_Reflect_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetInt32 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetInt3200
static int tolua_coord_coord_proto_Reflect_GetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetInt64 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetInt6400
static int tolua_coord_coord_proto_Reflect_GetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetUInt32 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetUInt3200
static int tolua_coord_coord_proto_Reflect_GetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetUInt64 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetUInt6400
static int tolua_coord_coord_proto_Reflect_GetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetFloat of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetFloat00
static int tolua_coord_coord_proto_Reflect_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetDouble of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetDouble00
static int tolua_coord_coord_proto_Reflect_GetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetBool of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_GetBool00
static int tolua_coord_coord_proto_Reflect_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Set of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_Set00
static int tolua_coord_coord_proto_Reflect_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetInt32 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetInt3200
static int tolua_coord_coord_proto_Reflect_SetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetInt64 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetInt6400
static int tolua_coord_coord_proto_Reflect_SetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetUInt32 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetUInt3200
static int tolua_coord_coord_proto_Reflect_SetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetUInt64 of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetUInt6400
static int tolua_coord_coord_proto_Reflect_SetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetFloat of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetFloat00
static int tolua_coord_coord_proto_Reflect_SetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetDouble of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetDouble00
static int tolua_coord_coord_proto_Reflect_SetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetBool of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetBool00
static int tolua_coord_coord_proto_Reflect_SetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: DebugString of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_DebugString00
static int tolua_coord_coord_proto_Reflect_DebugString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: CopyFrom of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_CopyFrom00
static int tolua_coord_coord_proto_Reflect_CopyFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
  coord::proto::Reflect* other = ((coord::proto::Reflect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CopyFrom'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CopyFrom(other);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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

/* method: MergeFrom of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_MergeFrom00
static int tolua_coord_coord_proto_Reflect_MergeFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
  coord::proto::Reflect* other = ((coord::proto::Reflect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MergeFrom'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->MergeFrom(other);
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

/* method: ByteSize of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_ByteSize00
static int tolua_coord_coord_proto_Reflect_ByteSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsDirty of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_IsDirty00
static int tolua_coord_coord_proto_Reflect_IsDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetDirty of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_SetDirty00
static int tolua_coord_coord_proto_Reflect_SetDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Name of class  coord::proto::Reflect */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Reflect_Name00
static int tolua_coord_coord_proto_Reflect_Name00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Reflect* self = (coord::proto::Reflect*)  tolua_tousertype(tolua_S,1,0);
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

/* method: delete of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_delete00
static int tolua_coord_coord_proto_Repeated_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Clear of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_Clear00
static int tolua_coord_coord_proto_Repeated_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: MergeFrom of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_MergeFrom00
static int tolua_coord_coord_proto_Repeated_MergeFrom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
  coord::proto::Repeated* other = ((coord::proto::Repeated*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MergeFrom'",NULL);
#endif
  {
   int tolua_ret = (int)  self->MergeFrom(other);
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

/* method: RemoveLast of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_RemoveLast00
static int tolua_coord_coord_proto_Repeated_RemoveLast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: RemoveAt of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_RemoveAt00
static int tolua_coord_coord_proto_Repeated_RemoveAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Remove of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_Remove00
static int tolua_coord_coord_proto_Repeated_Remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Count of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_Count00
static int tolua_coord_coord_proto_Repeated_Count00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetDirty of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetDirty00
static int tolua_coord_coord_proto_Repeated_SetDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Set of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_Set00
static int tolua_coord_coord_proto_Repeated_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetInt32 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetInt3200
static int tolua_coord_coord_proto_Repeated_SetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetInt64 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetInt6400
static int tolua_coord_coord_proto_Repeated_SetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetUInt32 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetUInt3200
static int tolua_coord_coord_proto_Repeated_SetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetUInt64 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetUInt6400
static int tolua_coord_coord_proto_Repeated_SetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetFloat of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetFloat00
static int tolua_coord_coord_proto_Repeated_SetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetDouble of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetDouble00
static int tolua_coord_coord_proto_Repeated_SetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetBool of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetBool00
static int tolua_coord_coord_proto_Repeated_SetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetNumber of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_SetNumber00
static int tolua_coord_coord_proto_Repeated_SetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Get of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_Get00
static int tolua_coord_coord_proto_Repeated_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetInt32 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetInt3200
static int tolua_coord_coord_proto_Repeated_GetInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetInt64 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetInt6400
static int tolua_coord_coord_proto_Repeated_GetInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetUInt32 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetUInt3200
static int tolua_coord_coord_proto_Repeated_GetUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetUInt64 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetUInt6400
static int tolua_coord_coord_proto_Repeated_GetUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetFloat of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetFloat00
static int tolua_coord_coord_proto_Repeated_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetDouble of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetDouble00
static int tolua_coord_coord_proto_Repeated_GetDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetBool of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetBool00
static int tolua_coord_coord_proto_Repeated_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNumber of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_GetNumber00
static int tolua_coord_coord_proto_Repeated_GetNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Add of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_Add00
static int tolua_coord_coord_proto_Repeated_Add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddInt32 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddInt3200
static int tolua_coord_coord_proto_Repeated_AddInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddInt64 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddInt6400
static int tolua_coord_coord_proto_Repeated_AddInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddUInt32 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddUInt3200
static int tolua_coord_coord_proto_Repeated_AddUInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddUInt64 of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddUInt6400
static int tolua_coord_coord_proto_Repeated_AddUInt6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddFloat of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddFloat00
static int tolua_coord_coord_proto_Repeated_AddFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddDouble of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddDouble00
static int tolua_coord_coord_proto_Repeated_AddDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddBool of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddBool00
static int tolua_coord_coord_proto_Repeated_AddBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AddNumber of class  coord::proto::Repeated */
#ifndef TOLUA_DISABLE_tolua_coord_coord_proto_Repeated_AddNumber00
static int tolua_coord_coord_proto_Repeated_AddNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::proto::Repeated",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::proto::Repeated* self = (coord::proto::Repeated*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Query of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Query00
static int tolua_coord_coord_sql_SQLClient_Query00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
  const char* statement = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Query'",NULL);
#endif
  {
   coord::sql::SQLRows* tolua_ret = (coord::sql::SQLRows*)  self->Query(statement);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::sql::SQLRows");
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

/* method: Execute of class  coord::sql::SQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_SQLClient_Execute00
static int tolua_coord_coord_sql_SQLClient_Execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::SQLClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::SQLClient* self = (coord::sql::SQLClient*)  tolua_tousertype(tolua_S,1,0);
  const char* statement = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Execute'",NULL);
#endif
  {
   coord::sql::SQLResult* tolua_ret = (coord::sql::SQLResult*)  self->Execute(statement);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::sql::SQLResult");
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

/* method: Connect of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_Connect00
static int tolua_coord_coord_sql_MySQLClient_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Query of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_Query00
static int tolua_coord_coord_sql_MySQLClient_Query00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
  const char* statement = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Query'",NULL);
#endif
  {
   coord::sql::SQLRows* tolua_ret = (coord::sql::SQLRows*)  self->Query(statement);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::sql::SQLRows");
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

/* method: Execute of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_Execute00
static int tolua_coord_coord_sql_MySQLClient_Execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
  const char* statement = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Execute'",NULL);
#endif
  {
   coord::sql::SQLResult* tolua_ret = (coord::sql::SQLResult*)  self->Execute(statement);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::sql::SQLResult");
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

/* method: Ping of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_Ping00
static int tolua_coord_coord_sql_MySQLClient_Ping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Error of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_Error00
static int tolua_coord_coord_sql_MySQLClient_Error00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Close of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_Close00
static int tolua_coord_coord_sql_MySQLClient_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: RowsAffected of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_RowsAffected00
static int tolua_coord_coord_sql_MySQLClient_RowsAffected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: LastInsertId of class  coord::sql::MySQLClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLClient_LastInsertId00
static int tolua_coord_coord_sql_MySQLClient_LastInsertId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLClient* self = (coord::sql::MySQLClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: RowsAffected of class  coord::sql::MySQLResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLResult_RowsAffected00
static int tolua_coord_coord_sql_MySQLResult_RowsAffected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLResult* self = (coord::sql::MySQLResult*)  tolua_tousertype(tolua_S,1,0);
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

/* method: LastInsertId of class  coord::sql::MySQLResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLResult_LastInsertId00
static int tolua_coord_coord_sql_MySQLResult_LastInsertId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLResult* self = (coord::sql::MySQLResult*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Next of class  coord::sql::MySQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLRows_Next00
static int tolua_coord_coord_sql_MySQLRows_Next00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLRows",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLRows* self = (coord::sql::MySQLRows*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Lua of class  coord::sql::MySQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLRows_Lua00
static int tolua_coord_coord_sql_MySQLRows_Lua00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLRows",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLRows* self = (coord::sql::MySQLRows*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Column of class  coord::sql::MySQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLRows_Column00
static int tolua_coord_coord_sql_MySQLRows_Column00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLRows",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLRows* self = (coord::sql::MySQLRows*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ColumnCount of class  coord::sql::MySQLRows */
#ifndef TOLUA_DISABLE_tolua_coord_coord_sql_MySQLRows_ColumnCount00
static int tolua_coord_coord_sql_MySQLRows_ColumnCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::sql::MySQLRows",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::sql::MySQLRows* self = (coord::sql::MySQLRows*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Connect of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_Connect00
static int tolua_coord_coord_redis_RedisAsyncClient_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connect'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->Connect();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: DefaultConfig of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_DefaultConfig00
static int tolua_coord_coord_redis_RedisAsyncClient_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Close of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_Close00
static int tolua_coord_coord_redis_RedisAsyncClient_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AUTH of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_AUTH00
static int tolua_coord_coord_redis_RedisAsyncClient_AUTH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* password = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AUTH'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->AUTH(password);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: DEL of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_DEL00
static int tolua_coord_coord_redis_RedisAsyncClient_DEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DEL'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->DEL(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: GET of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_GET00
static int tolua_coord_coord_redis_RedisAsyncClient_GET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GET'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->GET(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: SET of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_SET00
static int tolua_coord_coord_redis_RedisAsyncClient_SET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SET'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->SET(key,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: EXPIRE of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_EXPIRE00
static int tolua_coord_coord_redis_RedisAsyncClient_EXPIRE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  uint64_t expire = ((uint64_t)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EXPIRE'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->EXPIRE(key,expire);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: HGETALL of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_HGETALL00
static int tolua_coord_coord_redis_RedisAsyncClient_HGETALL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HGETALL'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->HGETALL(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: HDEL of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_HDEL00
static int tolua_coord_coord_redis_RedisAsyncClient_HDEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HDEL'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->HDEL(key,field);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: HMSET of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_HMSET00
static int tolua_coord_coord_redis_RedisAsyncClient_HMSET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->HMSET(key,field,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: HMSET of class  coord::redis::RedisAsyncClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisAsyncClient_HMSET01
static int tolua_coord_coord_redis_RedisAsyncClient_HMSET01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisAsyncClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::RedisAsyncClient* self = (coord::redis::RedisAsyncClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  uint64_t value = ((uint64_t)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->HMSET(key,field,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_redis_RedisAsyncClient_HMSET00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Connect of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_Connect00
static int tolua_coord_coord_redis_RedisClient_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: DefaultConfig of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_DefaultConfig00
static int tolua_coord_coord_redis_RedisClient_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Close of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_Close00
static int tolua_coord_coord_redis_RedisClient_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: AUTH of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_AUTH00
static int tolua_coord_coord_redis_RedisClient_AUTH00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
  const char* password = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AUTH'",NULL);
#endif
  {
   coord::redis::RedisReply* tolua_ret = (coord::redis::RedisReply*)  self->AUTH(password);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisReply");
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

/* method: TIME of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_TIME00
static int tolua_coord_coord_redis_RedisClient_TIME00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: DEL of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_DEL00
static int tolua_coord_coord_redis_RedisClient_DEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DEL'",NULL);
#endif
  {
   coord::redis::RedisReply* tolua_ret = (coord::redis::RedisReply*)  self->DEL(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisReply");
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

/* method: GET of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_GET00
static int tolua_coord_coord_redis_RedisClient_GET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GET'",NULL);
#endif
  {
   coord::redis::RedisReply* tolua_ret = (coord::redis::RedisReply*)  self->GET(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisReply");
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

/* method: SET of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_SET00
static int tolua_coord_coord_redis_RedisClient_SET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SET'",NULL);
#endif
  {
   coord::redis::RedisReply* tolua_ret = (coord::redis::RedisReply*)  self->SET(key,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisReply");
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

/* method: EXPIRE of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_EXPIRE00
static int tolua_coord_coord_redis_RedisClient_EXPIRE00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: HGETALL of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_HGETALL00
static int tolua_coord_coord_redis_RedisClient_HGETALL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HGETALL'",NULL);
#endif
  {
   coord::redis::RedisReply* tolua_ret = (coord::redis::RedisReply*)  self->HGETALL(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisReply");
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

/* method: HDEL of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_HDEL00
static int tolua_coord_coord_redis_RedisClient_HDEL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
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

/* method: HMSET of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_HMSET00
static int tolua_coord_coord_redis_RedisClient_HMSET00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::redis::RedisReply* tolua_ret = (coord::redis::RedisReply*)  self->HMSET(key,field,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisReply");
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

/* method: HMSET of class  coord::redis::RedisClient */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisClient_HMSET01
static int tolua_coord_coord_redis_RedisClient_HMSET01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisClient",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::RedisClient* self = (coord::redis::RedisClient*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* field = ((const char*)  tolua_tostring(tolua_S,3,0));
  uint64_t value = ((uint64_t)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HMSET'",NULL);
#endif
  {
   coord::redis::RedisReply* tolua_ret = (coord::redis::RedisReply*)  self->HMSET(key,field,value);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisReply");
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_redis_RedisClient_HMSET00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Then of class  coord::redis::RedisPromise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisPromise_Then00
static int tolua_coord_coord_redis_RedisPromise_Then00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisPromise",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisPromise* self = (coord::redis::RedisPromise*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Then'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->Then(object,script);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
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

/* method: Catch of class  coord::redis::RedisPromise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisPromise_Catch00
static int tolua_coord_coord_redis_RedisPromise_Catch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisPromise",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisPromise* self = (coord::redis::RedisPromise*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Catch'",NULL);
#endif
  {
   coord::redis::RedisPromise* tolua_ret = (coord::redis::RedisPromise*)  self->Catch(object,script);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::redis::RedisPromise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Catch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Error of class  coord::redis::RedisReply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisReply_Error00
static int tolua_coord_coord_redis_RedisReply_Error00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisReply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisReply* self = (coord::redis::RedisReply*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Array of class  coord::redis::RedisReply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisReply_Array00
static int tolua_coord_coord_redis_RedisReply_Array00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisReply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisReply* self = (coord::redis::RedisReply*)  tolua_tousertype(tolua_S,1,0);
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

/* method: ArrayCount of class  coord::redis::RedisReply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisReply_ArrayCount00
static int tolua_coord_coord_redis_RedisReply_ArrayCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisReply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisReply* self = (coord::redis::RedisReply*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Empty of class  coord::redis::RedisReply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisReply_Empty00
static int tolua_coord_coord_redis_RedisReply_Empty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisReply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisReply* self = (coord::redis::RedisReply*)  tolua_tousertype(tolua_S,1,0);
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

/* method: String of class  coord::redis::RedisReply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisReply_String00
static int tolua_coord_coord_redis_RedisReply_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisReply",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::redis::RedisReply* self = (coord::redis::RedisReply*)  tolua_tousertype(tolua_S,1,0);
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

/* method: String of class  coord::redis::RedisReply */
#ifndef TOLUA_DISABLE_tolua_coord_coord_redis_RedisReply_String01
static int tolua_coord_coord_redis_RedisReply_String01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::redis::RedisReply",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::redis::RedisReply* self = (coord::redis::RedisReply*)  tolua_tousertype(tolua_S,1,0);
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
 return tolua_coord_coord_redis_RedisReply_String00(tolua_S);
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

/* method: Connect of class  coord::cache::Cache */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_Cache_Connect00
static int tolua_coord_coord_cache_Cache_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::Cache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::Cache* self = (coord::cache::Cache*)  tolua_tousertype(tolua_S,1,0);
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

/* method: DefaultConfig of class  coord::cache::Cache */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_Cache_DefaultConfig00
static int tolua_coord_coord_cache_Cache_DefaultConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::Cache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::Cache* self = (coord::cache::Cache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefaultConfig'",NULL);
#endif
  {
   coord::cache::CacheConfig* tolua_ret = (coord::cache::CacheConfig*)  self->DefaultConfig();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cache::CacheConfig");
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

/* method: Close of class  coord::cache::Cache */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_Cache_Close00
static int tolua_coord_coord_cache_Cache_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::Cache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::Cache* self = (coord::cache::Cache*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Get of class  coord::cache::Cache */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_Cache_Get00
static int tolua_coord_coord_cache_Cache_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::Cache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::Cache* self = (coord::cache::Cache*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
  {
   coord::cache::CacheReader* tolua_ret = (coord::cache::CacheReader*)  self->Get(key);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cache::CacheReader");
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

/* method: Set of class  coord::cache::Cache */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_Cache_Set00
static int tolua_coord_coord_cache_Cache_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::Cache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::Cache* self = (coord::cache::Cache*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,3,0));
  size_t expire = ((size_t)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Set(key,data,expire);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: Set of class  coord::cache::Cache */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_Cache_Set01
static int tolua_coord_coord_cache_Cache_Set01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::Cache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::cache::Cache* self = (coord::cache::Cache*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,3,0));
  size_t len = ((size_t)  tolua_tonumber(tolua_S,4,0));
  size_t expire = ((size_t)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Set(key,data,len,expire);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_coord_coord_cache_Cache_Set00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Delete of class  coord::cache::Cache */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cache_Cache_Delete00
static int tolua_coord_coord_cache_Cache_Delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cache::Cache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cache::Cache* self = (coord::cache::Cache*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Delete'",NULL);
#endif
  {
   int tolua_ret = (int)  self->Delete(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Delete'.",&tolua_err);
 return 0;
#endif
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
   coord::cluster::ClusterPromise* tolua_ret = (coord::cluster::ClusterPromise*)  self->Request(node,route,data);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cluster::ClusterPromise");
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
     !tolua_isusertype(tolua_S,4,"coord::proto::Reflect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
  const char* node = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* route = ((const char*)  tolua_tostring(tolua_S,3,0));
  coord::proto::Reflect* proto = ((coord::proto::Reflect*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
   coord::cluster::ClusterPromise* tolua_ret = (coord::cluster::ClusterPromise*)  self->Request(node,route,*proto);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cluster::ClusterPromise");
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

/* get function: router of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__Cluster_router_ptr
static int tolua_get_coord__cluster__Cluster_router_ptr(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'router'",NULL);
#endif
  tolua_pushusertype(tolua_S,(void*)self->router,"coord::cluster::ClusterRouter");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: router of class  coord::cluster::Cluster */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__Cluster_router_ptr
static int tolua_set_coord__cluster__Cluster_router_ptr(lua_State* tolua_S)
{
  coord::cluster::Cluster* self = (coord::cluster::Cluster*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'router'",NULL);
  if (!tolua_isusertype(tolua_S,2,"coord::cluster::ClusterRouter",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->router = ((coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,2,0))
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
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRouter* self = (coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Notify'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Notify(path,object,script);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
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
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRouter* self = (coord::cluster::ClusterRouter*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,3,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Request'",NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Request(path,object,script);
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

/* method: Proto of class  coord::cluster::ClusterRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRequest_Proto00
static int tolua_coord_coord_cluster_ClusterRequest_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRequest",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRequest* self = (coord::cluster::ClusterRequest*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::proto::Reflect* tolua_ret = (coord::proto::Reflect*)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::proto::Reflect");
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

/* method: GetResponse of class  coord::cluster::ClusterRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRequest_GetResponse00
static int tolua_coord_coord_cluster_ClusterRequest_GetResponse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRequest* self = (coord::cluster::ClusterRequest*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResponse'",NULL);
#endif
  {
   coord::cluster::ClusterResponse* tolua_ret = (coord::cluster::ClusterResponse*)  self->GetResponse();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cluster::ClusterResponse");
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

/* method: String of class  coord::cluster::ClusterRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRequest_String00
static int tolua_coord_coord_cluster_ClusterRequest_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRequest* self = (coord::cluster::ClusterRequest*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Len of class  coord::cluster::ClusterRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRequest_Len00
static int tolua_coord_coord_cluster_ClusterRequest_Len00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRequest",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterRequest* self = (coord::cluster::ClusterRequest*)  tolua_tousertype(tolua_S,1,0);
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

/* method: String of class  coord::cluster::ClusterRequest */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterRequest_String01
static int tolua_coord_coord_cluster_ClusterRequest_String01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterRequest",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
 {
  coord::cluster::ClusterRequest* self = (coord::cluster::ClusterRequest*)  tolua_tousertype(tolua_S,1,0);
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
 return tolua_coord_coord_cluster_ClusterRequest_String00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::cluster::ClusterNotify */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterNotify_String00
static int tolua_coord_coord_cluster_ClusterNotify_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterNotify",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterNotify* self = (coord::cluster::ClusterNotify*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Len of class  coord::cluster::ClusterNotify */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterNotify_Len00
static int tolua_coord_coord_cluster_ClusterNotify_Len00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterNotify",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterNotify* self = (coord::cluster::ClusterNotify*)  tolua_tousertype(tolua_S,1,0);
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

/* method: String of class  coord::cluster::ClusterNotify */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterNotify_String01
static int tolua_coord_coord_cluster_ClusterNotify_String01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterNotify",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
 {
  coord::cluster::ClusterNotify* self = (coord::cluster::ClusterNotify*)  tolua_tousertype(tolua_S,1,0);
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
 return tolua_coord_coord_cluster_ClusterNotify_String00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::cluster::ClusterNotify */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterNotify_Proto00
static int tolua_coord_coord_cluster_ClusterNotify_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterNotify",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterNotify* self = (coord::cluster::ClusterNotify*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::proto::Reflect* tolua_ret = (coord::proto::Reflect*)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::proto::Reflect");
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

/* method: Proto of class  coord::cluster::ClusterResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResponse_Proto00
static int tolua_coord_coord_cluster_ClusterResponse_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterResponse* self = (coord::cluster::ClusterResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::proto::Reflect* tolua_ret = (coord::proto::Reflect*)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::proto::Reflect");
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

/* method: String of class  coord::cluster::ClusterResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResponse_String00
static int tolua_coord_coord_cluster_ClusterResponse_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResponse",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterResponse* self = (coord::cluster::ClusterResponse*)  tolua_tousertype(tolua_S,1,0);
  const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'String'",NULL);
#endif
  {
   self->String(data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'String'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Resolve of class  coord::cluster::ClusterResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResponse_Resolve00
static int tolua_coord_coord_cluster_ClusterResponse_Resolve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResponse",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterResponse* self = (coord::cluster::ClusterResponse*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Reject of class  coord::cluster::ClusterResponse */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResponse_Reject00
static int tolua_coord_coord_cluster_ClusterResponse_Reject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResponse",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterResponse* self = (coord::cluster::ClusterResponse*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Then of class  coord::cluster::ClusterPromise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterPromise_Then00
static int tolua_coord_coord_cluster_ClusterPromise_Then00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterPromise",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterPromise* self = (coord::cluster::ClusterPromise*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Then'",NULL);
#endif
  {
   coord::cluster::ClusterPromise* tolua_ret = (coord::cluster::ClusterPromise*)  self->Then(object,script);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cluster::ClusterPromise");
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

/* method: Catch of class  coord::cluster::ClusterPromise */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterPromise_Catch00
static int tolua_coord_coord_cluster_ClusterPromise_Catch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterPromise",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::ScriptComponent",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterPromise* self = (coord::cluster::ClusterPromise*)  tolua_tousertype(tolua_S,1,0);
  coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(tolua_S,2,0));
  const char* script = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Catch'",NULL);
#endif
  {
   coord::cluster::ClusterPromise* tolua_ret = (coord::cluster::ClusterPromise*)  self->Catch(object,script);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::cluster::ClusterPromise");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Catch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: String of class  coord::cluster::ClusterResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResult_String00
static int tolua_coord_coord_cluster_ClusterResult_String00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterResult* self = (coord::cluster::ClusterResult*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Len of class  coord::cluster::ClusterResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResult_Len00
static int tolua_coord_coord_cluster_ClusterResult_Len00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterResult* self = (coord::cluster::ClusterResult*)  tolua_tousertype(tolua_S,1,0);
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

/* method: String of class  coord::cluster::ClusterResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResult_String01
static int tolua_coord_coord_cluster_ClusterResult_String01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResult",0,&tolua_err) ||
     false
 )
  goto tolua_lerror;
 else
 {
  coord::cluster::ClusterResult* self = (coord::cluster::ClusterResult*)  tolua_tousertype(tolua_S,1,0);
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
 return tolua_coord_coord_cluster_ClusterResult_String00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Proto of class  coord::cluster::ClusterResult */
#ifndef TOLUA_DISABLE_tolua_coord_coord_cluster_ClusterResult_Proto00
static int tolua_coord_coord_cluster_ClusterResult_Proto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"coord::cluster::ClusterResult",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::cluster::ClusterResult* self = (coord::cluster::ClusterResult*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Proto'",NULL);
#endif
  {
   coord::proto::Reflect* tolua_ret = (coord::proto::Reflect*)  self->Proto(name);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"coord::proto::Reflect");
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

/* get function: Code of class  coord::cluster::ClusterResult */
#ifndef TOLUA_DISABLE_tolua_get_coord__cluster__ClusterResult_Code
static int tolua_get_coord__cluster__ClusterResult_Code(lua_State* tolua_S)
{
  coord::cluster::ClusterResult* self = (coord::cluster::ClusterResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Code'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Code);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Code of class  coord::cluster::ClusterResult */
#ifndef TOLUA_DISABLE_tolua_set_coord__cluster__ClusterResult_Code
static int tolua_set_coord__cluster__ClusterResult_Code(lua_State* tolua_S)
{
  coord::cluster::ClusterResult* self = (coord::cluster::ClusterResult*)  tolua_tousertype(tolua_S,1,0);
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
    tolua_function(tolua_S,"Exit",tolua_coord_coord_Coord_Exit00);
    tolua_function(tolua_S,"CreateScene",tolua_coord_coord_Coord_CreateScene00);
    tolua_function(tolua_S,"LogFatal",tolua_coord_coord_Coord_LogFatal00);
    tolua_function(tolua_S,"LogError",tolua_coord_coord_Coord_LogError00);
    tolua_function(tolua_S,"LogWarn",tolua_coord_coord_Coord_LogWarn00);
    tolua_function(tolua_S,"LogInfo",tolua_coord_coord_Coord_LogInfo00);
    tolua_function(tolua_S,"LogDebug",tolua_coord_coord_Coord_LogDebug00);
    tolua_function(tolua_S,"LogMsg",tolua_coord_coord_Coord_LogMsg00);
    tolua_function(tolua_S,"CloseAllLog",tolua_coord_coord_Coord_CloseAllLog00);
    tolua_function(tolua_S,"OpenLog",tolua_coord_coord_Coord_OpenLog00);
    tolua_function(tolua_S,"NewHttpServer",tolua_coord_coord_Coord_NewHttpServer00);
    tolua_function(tolua_S,"AddScript",tolua_coord_coord_Coord_AddScript00);
    tolua_function(tolua_S,"Emit",tolua_coord_coord_Coord_Emit00);
    tolua_function(tolua_S,"Destory",tolua_coord_coord_Coord_Destory00);
    tolua_function(tolua_S,"Destory",tolua_coord_coord_Coord_Destory01);
    tolua_function(tolua_S,"DontDestory",tolua_coord_coord_Coord_DontDestory00);
    tolua_function(tolua_S,"SetTimeout",tolua_coord_coord_Coord_SetTimeout00);
    tolua_function(tolua_S,"SetInterval",tolua_coord_coord_Coord_SetInterval00);
    tolua_function(tolua_S,"SQLConfig",tolua_coord_coord_Coord_SQLConfig00);
    tolua_function(tolua_S,"RedisConfig",tolua_coord_coord_Coord_RedisConfig00);
    tolua_function(tolua_S,"RedisAsyncConfig",tolua_coord_coord_Coord_RedisAsyncConfig00);
    tolua_function(tolua_S,"Cache",tolua_coord_coord_Coord_Cache00);
    tolua_function(tolua_S,"Cache",tolua_coord_coord_Coord_Cache01);
    tolua_variable(tolua_S,"config",tolua_get_coord__Coord_config_ptr,tolua_set_coord__Coord_config_ptr);
    tolua_variable(tolua_S,"script",tolua_get_coord__Coord_script_ptr,tolua_set_coord__Coord_script_ptr);
    tolua_variable(tolua_S,"gate",tolua_get_coord__Coord_gate_ptr,tolua_set_coord__Coord_gate_ptr);
    tolua_variable(tolua_S,"httpServer",tolua_get_coord__Coord_httpServer_ptr,tolua_set_coord__Coord_httpServer_ptr);
    tolua_variable(tolua_S,"proto",tolua_get_coord__Coord_proto_ptr,tolua_set_coord__Coord_proto_ptr);
    tolua_variable(tolua_S,"sqlMgr",tolua_get_coord__Coord_sqlMgr_ptr,tolua_set_coord__Coord_sqlMgr_ptr);
    tolua_variable(tolua_S,"redisMgr",tolua_get_coord__Coord_redisMgr_ptr,tolua_set_coord__Coord_redisMgr_ptr);
    tolua_variable(tolua_S,"cluster",tolua_get_coord__Coord_cluster_ptr,tolua_set_coord__Coord_cluster_ptr);
    tolua_variable(tolua_S,"configFile",tolua_get_coord__Coord_configFile,tolua_set_coord__Coord_configFile);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"WebConfig","coord::WebConfig","",NULL);
   tolua_beginmodule(tolua_S,"WebConfig");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"GateConfig","coord::GateConfig","",NULL);
   tolua_beginmodule(tolua_S,"GateConfig");
    tolua_variable(tolua_S,"Port",tolua_get_coord__GateConfig_Port,tolua_set_coord__GateConfig_Port);
    tolua_variable(tolua_S,"Host",tolua_get_coord__GateConfig_Host,tolua_set_coord__GateConfig_Host);
    tolua_variable(tolua_S,"Network",tolua_get_coord__GateConfig_Network,tolua_set_coord__GateConfig_Network);
    tolua_variable(tolua_S,"RsaEncrypt",tolua_get_coord__GateConfig_RsaEncrypt,tolua_set_coord__GateConfig_RsaEncrypt);
    tolua_variable(tolua_S,"RsaKeyFile",tolua_get_coord__GateConfig_RsaKeyFile,tolua_set_coord__GateConfig_RsaKeyFile);
    tolua_variable(tolua_S,"Heartbeat",tolua_get_coord__GateConfig_Heartbeat,tolua_set_coord__GateConfig_Heartbeat);
    tolua_variable(tolua_S,"Backlog",tolua_get_coord__GateConfig_Backlog,tolua_set_coord__GateConfig_Backlog);
    tolua_variable(tolua_S,"RecvBuffer",tolua_get_coord__GateConfig_RecvBuffer,tolua_set_coord__GateConfig_RecvBuffer);
    tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__GateConfig_SSLEncrypt,tolua_set_coord__GateConfig_SSLEncrypt);
    tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__GateConfig_SSLPemFile,tolua_set_coord__GateConfig_SSLPemFile);
    tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__GateConfig_SSLKeyFile,tolua_set_coord__GateConfig_SSLKeyFile);
    tolua_variable(tolua_S,"MaxUser",tolua_get_coord__GateConfig_MaxUser,tolua_set_coord__GateConfig_MaxUser);
    tolua_variable(tolua_S,"MaxConnection",tolua_get_coord__GateConfig_MaxConnection,tolua_set_coord__GateConfig_MaxConnection);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CacheConfig","coord::CacheConfig","",NULL);
   tolua_beginmodule(tolua_S,"CacheConfig");
    tolua_variable(tolua_S,"password",tolua_get_coord__CacheConfig_password,tolua_set_coord__CacheConfig_password);
    tolua_variable(tolua_S,"db",tolua_get_coord__CacheConfig_db,tolua_set_coord__CacheConfig_db);
    tolua_variable(tolua_S,"host",tolua_get_coord__CacheConfig_host,tolua_set_coord__CacheConfig_host);
    tolua_variable(tolua_S,"port",tolua_get_coord__CacheConfig_port,tolua_set_coord__CacheConfig_port);
    tolua_variable(tolua_S,"expireTime",tolua_get_coord__CacheConfig_expireTime,tolua_set_coord__CacheConfig_expireTime);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ClusterConfig","coord::ClusterConfig","",NULL);
   tolua_beginmodule(tolua_S,"ClusterConfig");
    tolua_variable(tolua_S,"Driver",tolua_get_coord__ClusterConfig_Driver,tolua_set_coord__ClusterConfig_Driver);
    tolua_variable(tolua_S,"Host",tolua_get_coord__ClusterConfig_Host,tolua_set_coord__ClusterConfig_Host);
    tolua_variable(tolua_S,"Port",tolua_get_coord__ClusterConfig_Port,tolua_set_coord__ClusterConfig_Port);
    tolua_variable(tolua_S,"Heartbeat",tolua_get_coord__ClusterConfig_Heartbeat,tolua_set_coord__ClusterConfig_Heartbeat);
    tolua_variable(tolua_S,"Expire",tolua_get_coord__ClusterConfig_Expire,tolua_set_coord__ClusterConfig_Expire);
    tolua_variable(tolua_S,"Name",tolua_get_coord__ClusterConfig_Name,tolua_set_coord__ClusterConfig_Name);
    tolua_variable(tolua_S,"RegisterInterval",tolua_get_coord__ClusterConfig_RegisterInterval,tolua_set_coord__ClusterConfig_RegisterInterval);
    tolua_variable(tolua_S,"ReloadInterval",tolua_get_coord__ClusterConfig_ReloadInterval,tolua_set_coord__ClusterConfig_ReloadInterval);
    tolua_variable(tolua_S,"ReconnectInterval",tolua_get_coord__ClusterConfig_ReconnectInterval,tolua_set_coord__ClusterConfig_ReconnectInterval);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Config","coord::Config","",NULL);
   tolua_beginmodule(tolua_S,"Config");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Script","coord::Script","",NULL);
   tolua_beginmodule(tolua_S,"Script");
    tolua_variable(tolua_S,"path",tolua_get_coord__Script_path,tolua_set_coord__Script_path);
    tolua_variable(tolua_S,"main",tolua_get_coord__Script_main,tolua_set_coord__Script_main);
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
   tolua_cclass(tolua_S,"Destoryable","coord::Destoryable","",NULL);
   tolua_beginmodule(tolua_S,"Destoryable");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"Object","coord::Object","",NULL);
   tolua_beginmodule(tolua_S,"Object");
    tolua_function(tolua_S,"Test",tolua_coord_coord_Object_Test00);
    tolua_function(tolua_S,"Create",tolua_coord_coord_Object_Create00);
    tolua_function(tolua_S,"Save",tolua_coord_coord_Object_Save00);
    tolua_function(tolua_S,"Update",tolua_coord_coord_Object_Update00);
    tolua_function(tolua_S,"Awake",tolua_coord_coord_Object_Awake00);
    tolua_function(tolua_S,"Destory",tolua_coord_coord_Object_Destory00);
    tolua_function(tolua_S,"AddComponent",tolua_coord_coord_Object_AddComponent00);
    tolua_function(tolua_S,"AddScript",tolua_coord_coord_Object_AddScript00);
    tolua_function(tolua_S,"RemoveComponent",tolua_coord_coord_Object_RemoveComponent00);
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Object_GetComponent00);
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Object_GetComponent01);
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Object_GetComponent02);
    tolua_function(tolua_S,"GetScript",tolua_coord_coord_Object_GetScript00);
    tolua_function(tolua_S,"GetChild",tolua_coord_coord_Object_GetChild00);
    tolua_function(tolua_S,"AddChild",tolua_coord_coord_Object_AddChild00);
    tolua_function(tolua_S,"RemoveChild",tolua_coord_coord_Object_RemoveChild00);
    tolua_function(tolua_S,"RemoveChild",tolua_coord_coord_Object_RemoveChild01);
    tolua_function(tolua_S,"ChildIndex",tolua_coord_coord_Object_ChildIndex00);
    tolua_function(tolua_S,"GetParent",tolua_coord_coord_Object_GetParent00);
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
   tolua_cclass(tolua_S,"Scene","coord::Scene","",NULL);
   tolua_beginmodule(tolua_S,"Scene");
    tolua_function(tolua_S,"Instantiate",tolua_coord_coord_Scene_Instantiate00);
    tolua_function(tolua_S,"CreateObject",tolua_coord_coord_Scene_CreateObject00);
    tolua_function(tolua_S,"AddObject",tolua_coord_coord_Scene_AddObject00);
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
   tolua_cclass(tolua_S,"Component","coord::Component","IEventHandler",NULL);
   tolua_beginmodule(tolua_S,"Component");
    tolua_function(tolua_S,"Update",tolua_coord_coord_Component_Update00);
    tolua_function(tolua_S,"GetComponent",tolua_coord_coord_Component_GetComponent00);
    tolua_function(tolua_S,"AddEventListener",tolua_coord_coord_Component_AddEventListener00);
    tolua_function(tolua_S,"RemoveEventListener",tolua_coord_coord_Component_RemoveEventListener00);
    tolua_function(tolua_S,"AddHttpRouterGet",tolua_coord_coord_Component_AddHttpRouterGet00);
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
     tolua_variable(tolua_S,"host",tolua_get_coord__http__HttpServerConfig_host,tolua_set_coord__http__HttpServerConfig_host);
     tolua_variable(tolua_S,"port",tolua_get_coord__http__HttpServerConfig_unsigned_port,tolua_set_coord__http__HttpServerConfig_unsigned_port);
     tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__http__HttpServerConfig_SSLEncrypt,tolua_set_coord__http__HttpServerConfig_SSLEncrypt);
     tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__http__HttpServerConfig_SSLPemFile,tolua_set_coord__http__HttpServerConfig_SSLPemFile);
     tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__http__HttpServerConfig_SSLKeyFile,tolua_set_coord__http__HttpServerConfig_SSLKeyFile);
     tolua_variable(tolua_S,"RecvBufferSize",tolua_get_coord__http__HttpServerConfig_RecvBufferSize,tolua_set_coord__http__HttpServerConfig_RecvBufferSize);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"HttpServer","coord::http::HttpServer","coord::net::ITcpHandler",NULL);
    tolua_beginmodule(tolua_S,"HttpServer");
     tolua_function(tolua_S,"Listen",tolua_coord_coord_http_HttpServer_Listen00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_http_HttpServer_DefaultConfig00);
     tolua_variable(tolua_S,"Router",tolua_get_coord__http__HttpServer_Router_ptr,tolua_set_coord__http__HttpServer_Router_ptr);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"http",0);
   tolua_beginmodule(tolua_S,"http");
    tolua_cclass(tolua_S,"HttpRequest","coord::http::HttpRequest","coord::Destoryable",NULL);
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
     tolua_variable(tolua_S,"Body",tolua_get_coord__http__HttpRequest_Body,tolua_set_coord__http__HttpRequest_Body);
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
     tolua_function(tolua_S,"JSON",tolua_coord_coord_http_HttpResponse_JSON00);
     tolua_function(tolua_S,"Upgrade",tolua_coord_coord_http_HttpResponse_Upgrade00);
     tolua_function(tolua_S,"PageNotFound",tolua_coord_coord_http_HttpResponse_PageNotFound00);
     tolua_function(tolua_S,"Exception",tolua_coord_coord_http_HttpResponse_Exception00);
     tolua_function(tolua_S,"SetStatusCode",tolua_coord_coord_http_HttpResponse_SetStatusCode00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"http",0);
   tolua_beginmodule(tolua_S,"http");
    tolua_cclass(tolua_S,"HttpRouter","coord::http::HttpRouter","",NULL);
    tolua_beginmodule(tolua_S,"HttpRouter");
     tolua_function(tolua_S,"GET",tolua_coord_coord_http_HttpRouter_GET00);
     tolua_function(tolua_S,"POST",tolua_coord_coord_http_HttpRouter_POST00);
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
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"IWebSocketHandler","coord::websocket::IWebSocketHandler","",NULL);
    tolua_beginmodule(tolua_S,"IWebSocketHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"WebSocketServerConfig","coord::websocket::WebSocketServerConfig","",NULL);
    tolua_beginmodule(tolua_S,"WebSocketServerConfig");
     tolua_variable(tolua_S,"host",tolua_get_coord__websocket__WebSocketServerConfig_host,tolua_set_coord__websocket__WebSocketServerConfig_host);
     tolua_variable(tolua_S,"port",tolua_get_coord__websocket__WebSocketServerConfig_unsigned_port,tolua_set_coord__websocket__WebSocketServerConfig_unsigned_port);
     tolua_variable(tolua_S,"SSLEncrypt",tolua_get_coord__websocket__WebSocketServerConfig_SSLEncrypt,tolua_set_coord__websocket__WebSocketServerConfig_SSLEncrypt);
     tolua_variable(tolua_S,"SSLPemFile",tolua_get_coord__websocket__WebSocketServerConfig_SSLPemFile,tolua_set_coord__websocket__WebSocketServerConfig_SSLPemFile);
     tolua_variable(tolua_S,"SSLKeyFile",tolua_get_coord__websocket__WebSocketServerConfig_SSLKeyFile,tolua_set_coord__websocket__WebSocketServerConfig_SSLKeyFile);
     tolua_variable(tolua_S,"RecvBufferSize",tolua_get_coord__websocket__WebSocketServerConfig_RecvBufferSize,tolua_set_coord__websocket__WebSocketServerConfig_RecvBufferSize);
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"WebSocketServer","coord::websocket::WebSocketServer","coord::http::IHttpHandler",NULL);
    tolua_beginmodule(tolua_S,"WebSocketServer");
     tolua_function(tolua_S,"Listen",tolua_coord_coord_websocket_WebSocketServer_Listen00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_websocket_WebSocketServer_DefaultConfig00);
     tolua_variable(tolua_S,"Router",tolua_get_coord__websocket__WebSocketServer_Router_ptr,tolua_set_coord__websocket__WebSocketServer_Router_ptr);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"WebSocketRouter","coord::websocket::WebSocketRouter","",NULL);
    tolua_beginmodule(tolua_S,"WebSocketRouter");
     tolua_function(tolua_S,"MESSAGE",tolua_coord_coord_websocket_WebSocketRouter_MESSAGE00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"WebSocketFrame","coord::websocket::WebSocketFrame","",NULL);
    tolua_beginmodule(tolua_S,"WebSocketFrame");
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"websocket",0);
   tolua_beginmodule(tolua_S,"websocket");
    tolua_cclass(tolua_S,"IWebSocketAgentHandler","coord::websocket::IWebSocketAgentHandler","",NULL);
    tolua_beginmodule(tolua_S,"IWebSocketAgentHandler");
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"WebSocketAgent","coord::websocket::WebSocketAgent","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"WebSocketAgent");
     tolua_function(tolua_S,"SendBinaryFrame",tolua_coord_coord_websocket_WebSocketAgent_SendBinaryFrame00);
     tolua_function(tolua_S,"SendStringFrame",tolua_coord_coord_websocket_WebSocketAgent_SendStringFrame00);
     tolua_variable(tolua_S,"__http__IHttpAgentHandler__",tolua_get_coord__websocket__WebSocketAgent___http__IHttpAgentHandler__,NULL);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"ScriptComponent","coord::ScriptComponent","coord::Component",NULL);
   tolua_beginmodule(tolua_S,"ScriptComponent");
    tolua_function(tolua_S,"Awake",tolua_coord_coord_ScriptComponent_Awake00);
    tolua_function(tolua_S,"Update",tolua_coord_coord_ScriptComponent_Update00);
    tolua_function(tolua_S,"AddHttpGet",tolua_coord_coord_ScriptComponent_AddHttpGet00);
    tolua_function(tolua_S,"SetTimeout",tolua_coord_coord_ScriptComponent_SetTimeout00);
    tolua_function(tolua_S,"SetInterval",tolua_coord_coord_ScriptComponent_SetInterval00);
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
    tolua_cclass(tolua_S,"GateConfig","coord::gate::GateConfig","",NULL);
    tolua_beginmodule(tolua_S,"GateConfig");
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
    tolua_endmodule(tolua_S);
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
    tolua_cclass(tolua_S,"GateRouter","coord::gate::GateRouter","",NULL);
    tolua_beginmodule(tolua_S,"GateRouter");
     tolua_function(tolua_S,"Notify",tolua_coord_coord_gate_GateRouter_Notify00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_gate_GateRouter_Request00);
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
    tolua_cclass(tolua_S,"GateRequest","coord::gate::GateRequest","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"GateRequest");
     tolua_function(tolua_S,"Proto",tolua_coord_coord_gate_GateRequest_Proto00);
     tolua_function(tolua_S,"GetResponse",tolua_coord_coord_gate_GateRequest_GetResponse00);
     tolua_function(tolua_S,"Kick",tolua_coord_coord_gate_GateRequest_Kick00);
     tolua_variable(tolua_S,"sessionId",tolua_get_coord__gate__GateRequest_sessionId,tolua_set_coord__gate__GateRequest_sessionId);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateNotify","coord::gate::GateNotify","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"GateNotify");
     tolua_function(tolua_S,"Proto",tolua_coord_coord_gate_GateNotify_Proto00);
     tolua_variable(tolua_S,"sessionId",tolua_get_coord__gate__GateNotify_sessionId,tolua_set_coord__gate__GateNotify_sessionId);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"gate",0);
   tolua_beginmodule(tolua_S,"gate");
    tolua_cclass(tolua_S,"GateResponse","coord::gate::GateResponse","",NULL);
    tolua_beginmodule(tolua_S,"GateResponse");
     tolua_function(tolua_S,"Proto",tolua_coord_coord_gate_GateResponse_Proto00);
     tolua_function(tolua_S,"String",tolua_coord_coord_gate_GateResponse_String00);
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
     tolua_variable(tolua_S,"Id",tolua_get_coord__gate__GateSession_Id,tolua_set_coord__gate__GateSession_Id);
     tolua_variable(tolua_S,"RemoteAddr",tolua_get_coord__gate__GateSession_RemoteAddr,tolua_set_coord__gate__GateSession_RemoteAddr);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"EventArgs","coord::EventArgs","",NULL);
   tolua_beginmodule(tolua_S,"EventArgs");
    tolua_variable(tolua_S,"name",tolua_get_coord__EventArgs_name,tolua_set_coord__EventArgs_name);
    tolua_variable(tolua_S,"arg",tolua_get_coord__EventArgs_arg,tolua_set_coord__EventArgs_arg);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"proto",0);
   tolua_beginmodule(tolua_S,"proto");
    tolua_cclass(tolua_S,"ProtoMgr","coord::proto::ProtoMgr","",NULL);
    tolua_beginmodule(tolua_S,"ProtoMgr");
     tolua_function(tolua_S,"MapPath",tolua_coord_coord_proto_ProtoMgr_MapPath00);
     tolua_function(tolua_S,"Import",tolua_coord_coord_proto_ProtoMgr_Import00);
     tolua_function(tolua_S,"NewReflect",tolua_coord_coord_proto_ProtoMgr_NewReflect00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"proto",0);
   tolua_beginmodule(tolua_S,"proto");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Reflect","coord::proto::Reflect","",tolua_collect_coord__proto__Reflect);
    #else
    tolua_cclass(tolua_S,"Reflect","coord::proto::Reflect","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Reflect");
     tolua_function(tolua_S,"delete",tolua_coord_coord_proto_Reflect_delete00);
     tolua_function(tolua_S,"Get",tolua_coord_coord_proto_Reflect_Get00);
     tolua_function(tolua_S,"GetString",tolua_coord_coord_proto_Reflect_GetString00);
     tolua_function(tolua_S,"GetInt32",tolua_coord_coord_proto_Reflect_GetInt3200);
     tolua_function(tolua_S,"GetInt64",tolua_coord_coord_proto_Reflect_GetInt6400);
     tolua_function(tolua_S,"GetUInt32",tolua_coord_coord_proto_Reflect_GetUInt3200);
     tolua_function(tolua_S,"GetUInt64",tolua_coord_coord_proto_Reflect_GetUInt6400);
     tolua_function(tolua_S,"GetFloat",tolua_coord_coord_proto_Reflect_GetFloat00);
     tolua_function(tolua_S,"GetDouble",tolua_coord_coord_proto_Reflect_GetDouble00);
     tolua_function(tolua_S,"GetBool",tolua_coord_coord_proto_Reflect_GetBool00);
     tolua_function(tolua_S,"Set",tolua_coord_coord_proto_Reflect_Set00);
     tolua_function(tolua_S,"SetInt32",tolua_coord_coord_proto_Reflect_SetInt3200);
     tolua_function(tolua_S,"SetInt64",tolua_coord_coord_proto_Reflect_SetInt6400);
     tolua_function(tolua_S,"SetUInt32",tolua_coord_coord_proto_Reflect_SetUInt3200);
     tolua_function(tolua_S,"SetUInt64",tolua_coord_coord_proto_Reflect_SetUInt6400);
     tolua_function(tolua_S,"SetFloat",tolua_coord_coord_proto_Reflect_SetFloat00);
     tolua_function(tolua_S,"SetDouble",tolua_coord_coord_proto_Reflect_SetDouble00);
     tolua_function(tolua_S,"SetBool",tolua_coord_coord_proto_Reflect_SetBool00);
     tolua_function(tolua_S,"DebugString",tolua_coord_coord_proto_Reflect_DebugString00);
     tolua_function(tolua_S,"CopyFrom",tolua_coord_coord_proto_Reflect_CopyFrom00);
     tolua_function(tolua_S,"MergeFrom",tolua_coord_coord_proto_Reflect_MergeFrom00);
     tolua_function(tolua_S,"ByteSize",tolua_coord_coord_proto_Reflect_ByteSize00);
     tolua_function(tolua_S,"IsDirty",tolua_coord_coord_proto_Reflect_IsDirty00);
     tolua_function(tolua_S,"SetDirty",tolua_coord_coord_proto_Reflect_SetDirty00);
     tolua_function(tolua_S,"Name",tolua_coord_coord_proto_Reflect_Name00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"proto",0);
   tolua_beginmodule(tolua_S,"proto");
    #ifdef __cplusplus
    tolua_cclass(tolua_S,"Repeated","coord::proto::Repeated","",tolua_collect_coord__proto__Repeated);
    #else
    tolua_cclass(tolua_S,"Repeated","coord::proto::Repeated","",NULL);
    #endif
    tolua_beginmodule(tolua_S,"Repeated");
     tolua_function(tolua_S,"delete",tolua_coord_coord_proto_Repeated_delete00);
     tolua_function(tolua_S,"Clear",tolua_coord_coord_proto_Repeated_Clear00);
     tolua_function(tolua_S,"MergeFrom",tolua_coord_coord_proto_Repeated_MergeFrom00);
     tolua_function(tolua_S,"RemoveLast",tolua_coord_coord_proto_Repeated_RemoveLast00);
     tolua_function(tolua_S,"RemoveAt",tolua_coord_coord_proto_Repeated_RemoveAt00);
     tolua_function(tolua_S,"Remove",tolua_coord_coord_proto_Repeated_Remove00);
     tolua_function(tolua_S,"Count",tolua_coord_coord_proto_Repeated_Count00);
     tolua_function(tolua_S,"SetDirty",tolua_coord_coord_proto_Repeated_SetDirty00);
     tolua_function(tolua_S,"Set",tolua_coord_coord_proto_Repeated_Set00);
     tolua_function(tolua_S,"SetInt32",tolua_coord_coord_proto_Repeated_SetInt3200);
     tolua_function(tolua_S,"SetInt64",tolua_coord_coord_proto_Repeated_SetInt6400);
     tolua_function(tolua_S,"SetUInt32",tolua_coord_coord_proto_Repeated_SetUInt3200);
     tolua_function(tolua_S,"SetUInt64",tolua_coord_coord_proto_Repeated_SetUInt6400);
     tolua_function(tolua_S,"SetFloat",tolua_coord_coord_proto_Repeated_SetFloat00);
     tolua_function(tolua_S,"SetDouble",tolua_coord_coord_proto_Repeated_SetDouble00);
     tolua_function(tolua_S,"SetBool",tolua_coord_coord_proto_Repeated_SetBool00);
     tolua_function(tolua_S,"SetNumber",tolua_coord_coord_proto_Repeated_SetNumber00);
     tolua_function(tolua_S,"Get",tolua_coord_coord_proto_Repeated_Get00);
     tolua_function(tolua_S,"GetInt32",tolua_coord_coord_proto_Repeated_GetInt3200);
     tolua_function(tolua_S,"GetInt64",tolua_coord_coord_proto_Repeated_GetInt6400);
     tolua_function(tolua_S,"GetUInt32",tolua_coord_coord_proto_Repeated_GetUInt3200);
     tolua_function(tolua_S,"GetUInt64",tolua_coord_coord_proto_Repeated_GetUInt6400);
     tolua_function(tolua_S,"GetFloat",tolua_coord_coord_proto_Repeated_GetFloat00);
     tolua_function(tolua_S,"GetDouble",tolua_coord_coord_proto_Repeated_GetDouble00);
     tolua_function(tolua_S,"GetBool",tolua_coord_coord_proto_Repeated_GetBool00);
     tolua_function(tolua_S,"GetNumber",tolua_coord_coord_proto_Repeated_GetNumber00);
     tolua_function(tolua_S,"Add",tolua_coord_coord_proto_Repeated_Add00);
     tolua_function(tolua_S,"AddInt32",tolua_coord_coord_proto_Repeated_AddInt3200);
     tolua_function(tolua_S,"AddInt64",tolua_coord_coord_proto_Repeated_AddInt6400);
     tolua_function(tolua_S,"AddUInt32",tolua_coord_coord_proto_Repeated_AddUInt3200);
     tolua_function(tolua_S,"AddUInt64",tolua_coord_coord_proto_Repeated_AddUInt6400);
     tolua_function(tolua_S,"AddFloat",tolua_coord_coord_proto_Repeated_AddFloat00);
     tolua_function(tolua_S,"AddDouble",tolua_coord_coord_proto_Repeated_AddDouble00);
     tolua_function(tolua_S,"AddBool",tolua_coord_coord_proto_Repeated_AddBool00);
     tolua_function(tolua_S,"AddNumber",tolua_coord_coord_proto_Repeated_AddNumber00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_cclass(tolua_S,"TimerMgr","coord::TimerMgr","",NULL);
   tolua_beginmodule(tolua_S,"TimerMgr");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"SQLMgr","coord::sql::SQLMgr","",NULL);
    tolua_beginmodule(tolua_S,"SQLMgr");
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
     tolua_function(tolua_S,"Connect",tolua_coord_coord_sql_SQLClient_Connect00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_sql_SQLClient_DefaultConfig00);
     tolua_function(tolua_S,"Query",tolua_coord_coord_sql_SQLClient_Query00);
     tolua_function(tolua_S,"Execute",tolua_coord_coord_sql_SQLClient_Execute00);
     tolua_function(tolua_S,"Ping",tolua_coord_coord_sql_SQLClient_Ping00);
     tolua_function(tolua_S,"Error",tolua_coord_coord_sql_SQLClient_Error00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_sql_SQLClient_Close00);
     tolua_function(tolua_S,"RowsAffected",tolua_coord_coord_sql_SQLClient_RowsAffected00);
     tolua_function(tolua_S,"LastInsertId",tolua_coord_coord_sql_SQLClient_LastInsertId00);
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
     tolua_function(tolua_S,"Lua",tolua_coord_coord_sql_SQLRows_Lua00);
     tolua_function(tolua_S,"Column",tolua_coord_coord_sql_SQLRows_Column00);
     tolua_function(tolua_S,"ColumnCount",tolua_coord_coord_sql_SQLRows_ColumnCount00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"MySQLClient","coord::sql::MySQLClient","coord::sql::SQLClient",NULL);
    tolua_beginmodule(tolua_S,"MySQLClient");
     tolua_function(tolua_S,"Connect",tolua_coord_coord_sql_MySQLClient_Connect00);
     tolua_function(tolua_S,"Query",tolua_coord_coord_sql_MySQLClient_Query00);
     tolua_function(tolua_S,"Execute",tolua_coord_coord_sql_MySQLClient_Execute00);
     tolua_function(tolua_S,"Ping",tolua_coord_coord_sql_MySQLClient_Ping00);
     tolua_function(tolua_S,"Error",tolua_coord_coord_sql_MySQLClient_Error00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_sql_MySQLClient_Close00);
     tolua_function(tolua_S,"RowsAffected",tolua_coord_coord_sql_MySQLClient_RowsAffected00);
     tolua_function(tolua_S,"LastInsertId",tolua_coord_coord_sql_MySQLClient_LastInsertId00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"MySQLResult","coord::sql::MySQLResult","coord::sql::SQLResult",NULL);
    tolua_beginmodule(tolua_S,"MySQLResult");
     tolua_function(tolua_S,"RowsAffected",tolua_coord_coord_sql_MySQLResult_RowsAffected00);
     tolua_function(tolua_S,"LastInsertId",tolua_coord_coord_sql_MySQLResult_LastInsertId00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"sql",0);
   tolua_beginmodule(tolua_S,"sql");
    tolua_cclass(tolua_S,"MySQLRows","coord::sql::MySQLRows","coord::sql::SQLRows",NULL);
    tolua_beginmodule(tolua_S,"MySQLRows");
     tolua_function(tolua_S,"Next",tolua_coord_coord_sql_MySQLRows_Next00);
     tolua_function(tolua_S,"Lua",tolua_coord_coord_sql_MySQLRows_Lua00);
     tolua_function(tolua_S,"Column",tolua_coord_coord_sql_MySQLRows_Column00);
     tolua_function(tolua_S,"ColumnCount",tolua_coord_coord_sql_MySQLRows_ColumnCount00);
    tolua_endmodule(tolua_S);
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
    tolua_cclass(tolua_S,"RedisAsyncClient","coord::redis::RedisAsyncClient","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"RedisAsyncClient");
     tolua_function(tolua_S,"Connect",tolua_coord_coord_redis_RedisAsyncClient_Connect00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_redis_RedisAsyncClient_DefaultConfig00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_redis_RedisAsyncClient_Close00);
     tolua_function(tolua_S,"AUTH",tolua_coord_coord_redis_RedisAsyncClient_AUTH00);
     tolua_function(tolua_S,"DEL",tolua_coord_coord_redis_RedisAsyncClient_DEL00);
     tolua_function(tolua_S,"GET",tolua_coord_coord_redis_RedisAsyncClient_GET00);
     tolua_function(tolua_S,"SET",tolua_coord_coord_redis_RedisAsyncClient_SET00);
     tolua_function(tolua_S,"EXPIRE",tolua_coord_coord_redis_RedisAsyncClient_EXPIRE00);
     tolua_function(tolua_S,"HGETALL",tolua_coord_coord_redis_RedisAsyncClient_HGETALL00);
     tolua_function(tolua_S,"HDEL",tolua_coord_coord_redis_RedisAsyncClient_HDEL00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_RedisAsyncClient_HMSET00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_RedisAsyncClient_HMSET01);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"RedisClient","coord::redis::RedisClient","",NULL);
    tolua_beginmodule(tolua_S,"RedisClient");
     tolua_function(tolua_S,"Connect",tolua_coord_coord_redis_RedisClient_Connect00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_redis_RedisClient_DefaultConfig00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_redis_RedisClient_Close00);
     tolua_function(tolua_S,"AUTH",tolua_coord_coord_redis_RedisClient_AUTH00);
     tolua_function(tolua_S,"TIME",tolua_coord_coord_redis_RedisClient_TIME00);
     tolua_function(tolua_S,"DEL",tolua_coord_coord_redis_RedisClient_DEL00);
     tolua_function(tolua_S,"GET",tolua_coord_coord_redis_RedisClient_GET00);
     tolua_function(tolua_S,"SET",tolua_coord_coord_redis_RedisClient_SET00);
     tolua_function(tolua_S,"EXPIRE",tolua_coord_coord_redis_RedisClient_EXPIRE00);
     tolua_function(tolua_S,"HGETALL",tolua_coord_coord_redis_RedisClient_HGETALL00);
     tolua_function(tolua_S,"HDEL",tolua_coord_coord_redis_RedisClient_HDEL00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_RedisClient_HMSET00);
     tolua_function(tolua_S,"HMSET",tolua_coord_coord_redis_RedisClient_HMSET01);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"RedisPromise","coord::redis::RedisPromise","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"RedisPromise");
     tolua_function(tolua_S,"Then",tolua_coord_coord_redis_RedisPromise_Then00);
     tolua_function(tolua_S,"Catch",tolua_coord_coord_redis_RedisPromise_Catch00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"redis",0);
   tolua_beginmodule(tolua_S,"redis");
    tolua_cclass(tolua_S,"RedisReply","coord::redis::RedisReply","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"RedisReply");
     tolua_function(tolua_S,"Error",tolua_coord_coord_redis_RedisReply_Error00);
     tolua_function(tolua_S,"Array",tolua_coord_coord_redis_RedisReply_Array00);
     tolua_function(tolua_S,"ArrayCount",tolua_coord_coord_redis_RedisReply_ArrayCount00);
     tolua_function(tolua_S,"Empty",tolua_coord_coord_redis_RedisReply_Empty00);
     tolua_function(tolua_S,"String",tolua_coord_coord_redis_RedisReply_String00);
     tolua_function(tolua_S,"String",tolua_coord_coord_redis_RedisReply_String01);
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
    tolua_cclass(tolua_S,"Cache","coord::cache::Cache","",NULL);
    tolua_beginmodule(tolua_S,"Cache");
     tolua_function(tolua_S,"Connect",tolua_coord_coord_cache_Cache_Connect00);
     tolua_function(tolua_S,"DefaultConfig",tolua_coord_coord_cache_Cache_DefaultConfig00);
     tolua_function(tolua_S,"Close",tolua_coord_coord_cache_Cache_Close00);
     tolua_function(tolua_S,"Get",tolua_coord_coord_cache_Cache_Get00);
     tolua_function(tolua_S,"Set",tolua_coord_coord_cache_Cache_Set00);
     tolua_function(tolua_S,"Set",tolua_coord_coord_cache_Cache_Set01);
     tolua_function(tolua_S,"Delete",tolua_coord_coord_cache_Cache_Delete00);
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
    tolua_endmodule(tolua_S);
    tolua_cclass(tolua_S,"Cluster","coord::cluster::Cluster","",NULL);
    tolua_beginmodule(tolua_S,"Cluster");
     tolua_function(tolua_S,"Notify",tolua_coord_coord_cluster_Cluster_Notify00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_cluster_Cluster_Request00);
     tolua_function(tolua_S,"Request",tolua_coord_coord_cluster_Cluster_Request01);
     tolua_function(tolua_S,"Reload",tolua_coord_coord_cluster_Cluster_Reload00);
     tolua_variable(tolua_S,"Name",tolua_get_coord__cluster__Cluster_Name,tolua_set_coord__cluster__Cluster_Name);
     tolua_variable(tolua_S,"FullName",tolua_get_coord__cluster__Cluster_FullName,tolua_set_coord__cluster__Cluster_FullName);
     tolua_variable(tolua_S,"Version",tolua_get_coord__cluster__Cluster_Version,tolua_set_coord__cluster__Cluster_Version);
     tolua_variable(tolua_S,"router",tolua_get_coord__cluster__Cluster_router_ptr,tolua_set_coord__cluster__Cluster_router_ptr);
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
     tolua_function(tolua_S,"Trace",tolua_coord_coord_cluster_ClusterRouter_Trace00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"ClusterRequest","coord::cluster::ClusterRequest","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"ClusterRequest");
     tolua_function(tolua_S,"Proto",tolua_coord_coord_cluster_ClusterRequest_Proto00);
     tolua_function(tolua_S,"GetResponse",tolua_coord_coord_cluster_ClusterRequest_GetResponse00);
     tolua_function(tolua_S,"String",tolua_coord_coord_cluster_ClusterRequest_String00);
     tolua_function(tolua_S,"Len",tolua_coord_coord_cluster_ClusterRequest_Len00);
     tolua_function(tolua_S,"String",tolua_coord_coord_cluster_ClusterRequest_String01);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"ClusterNotify","coord::cluster::ClusterNotify","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"ClusterNotify");
     tolua_function(tolua_S,"String",tolua_coord_coord_cluster_ClusterNotify_String00);
     tolua_function(tolua_S,"Len",tolua_coord_coord_cluster_ClusterNotify_Len00);
     tolua_function(tolua_S,"String",tolua_coord_coord_cluster_ClusterNotify_String01);
     tolua_function(tolua_S,"Proto",tolua_coord_coord_cluster_ClusterNotify_Proto00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"ClusterResponse","coord::cluster::ClusterResponse","",NULL);
    tolua_beginmodule(tolua_S,"ClusterResponse");
     tolua_function(tolua_S,"Proto",tolua_coord_coord_cluster_ClusterResponse_Proto00);
     tolua_function(tolua_S,"String",tolua_coord_coord_cluster_ClusterResponse_String00);
     tolua_function(tolua_S,"Resolve",tolua_coord_coord_cluster_ClusterResponse_Resolve00);
     tolua_function(tolua_S,"Reject",tolua_coord_coord_cluster_ClusterResponse_Reject00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"ClusterPromise","coord::cluster::ClusterPromise","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"ClusterPromise");
     tolua_function(tolua_S,"Then",tolua_coord_coord_cluster_ClusterPromise_Then00);
     tolua_function(tolua_S,"Catch",tolua_coord_coord_cluster_ClusterPromise_Catch00);
    tolua_endmodule(tolua_S);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"coord",0);
  tolua_beginmodule(tolua_S,"coord");
   tolua_module(tolua_S,"cluster",0);
   tolua_beginmodule(tolua_S,"cluster");
    tolua_cclass(tolua_S,"ClusterResult","coord::cluster::ClusterResult","coord::Destoryable",NULL);
    tolua_beginmodule(tolua_S,"ClusterResult");
     tolua_function(tolua_S,"String",tolua_coord_coord_cluster_ClusterResult_String00);
     tolua_function(tolua_S,"Len",tolua_coord_coord_cluster_ClusterResult_Len00);
     tolua_function(tolua_S,"String",tolua_coord_coord_cluster_ClusterResult_String01);
     tolua_function(tolua_S,"Proto",tolua_coord_coord_cluster_ClusterResult_Proto00);
     tolua_variable(tolua_S,"Code",tolua_get_coord__cluster__ClusterResult_Code,tolua_set_coord__cluster__ClusterResult_Code);
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
    108, 32,102,117,110, 99,116,105,111,110, 32, 76,111,103, 70,
     97,116, 97,108, 40,115,101,108,102, 44, 32,115,116,114, 41,
     10, 99,111,111,114,100, 97, 58, 76,111,103, 77,115,103, 40,
    115,116,114,105,110,103, 46,102,111,114,109, 97,116, 40, 39,
     91, 37,115, 93, 37,115, 39, 44, 32,115,101,108,102, 46, 95,
     95, 78, 65, 77, 69, 44, 32,115,116,114, 32,111,114, 32, 39,
     39, 41, 41, 10,101,110,100, 10,108,111, 99, 97,108, 32,102,
    117,110, 99,116,105,111,110, 32, 76,111,103, 69,114,114,111,
    114, 40,115,101,108,102, 44, 32,115,116,114, 41, 10, 99,111,
    111,114,100, 97, 58, 76,111,103, 77,115,103, 40,115,116,114,
    105,110,103, 46,102,111,114,109, 97,116, 40, 39, 91, 37,115,
     93, 37,115, 39, 44, 32,115,101,108,102, 46, 95, 95, 78, 65,
     77, 69, 44, 32,115,116,114, 32,111,114, 32, 39, 39, 41, 41,
     10,101,110,100, 10,108,111, 99, 97,108, 32,102,117,110, 99,
    116,105,111,110, 32, 76,111,103, 87, 97,114,110, 40,115,101,
    108,102, 44, 32,115,116,114, 41, 10, 99,111,111,114,100, 97,
     58, 76,111,103, 77,115,103, 40,115,116,114,105,110,103, 46,
    102,111,114,109, 97,116, 40, 39, 91, 37,115, 93, 37,115, 39,
     44, 32,115,101,108,102, 46, 95, 95, 78, 65, 77, 69, 44, 32,
    115,116,114, 32,111,114, 32, 39, 39, 41, 41, 10,101,110,100,
     10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,110,
     32, 76,111,103, 73,110,102,111, 40,115,101,108,102, 44, 32,
    115,116,114, 41, 10, 99,111,111,114,100, 97, 58, 76,111,103,
     77,115,103, 40,115,116,114,105,110,103, 46,102,111,114,109,
     97,116, 40, 39, 91, 37,115, 93, 37,115, 39, 44, 32,115,101,
    108,102, 46, 95, 95, 78, 65, 77, 69, 44, 32,115,116,114, 32,
    111,114, 32, 39, 39, 41, 41, 10,101,110,100, 10,108,111, 99,
     97,108, 32,102,117,110, 99,116,105,111,110, 32, 76,111,103,
     68,101, 98,117,103, 40,115,101,108,102, 44, 32,115,116,114,
     41, 10, 99,111,111,114,100, 97, 58, 76,111,103, 77,115,103,
     40,115,116,114,105,110,103, 46,102,111,114,109, 97,116, 40,
     39, 91, 37,115, 93, 37,115, 39, 44, 32,115,101,108,102, 46,
     95, 95, 78, 65, 77, 69, 44, 32,115,116,114, 32,111,114, 32,
     39, 39, 41, 41, 10,101,110,100, 10,108,111, 99, 97,108, 32,
    102,117,110, 99,116,105,111,110, 32, 76,111,103, 77,115,103,
     40,115,101,108,102, 44, 32,115,116,114, 41, 10, 99,111,111,
    114,100, 97, 58, 76,111,103, 77,115,103, 40,115,116,114,105,
    110,103, 46,102,111,114,109, 97,116, 40, 39, 91, 37,115, 93,
     37,115, 39, 44, 32,115,101,108,102, 46, 95, 95, 78, 65, 77,
     69, 44, 32,115,116,114, 32,111,114, 32, 39, 39, 41, 41, 10,
    101,110,100, 10,108,111, 99, 97,108, 32,115, 99,114,105,112,
    116, 32, 61, 32,123,125, 10,108,111, 99, 97,108, 32,102,117,
    110, 99,116,105,111,110, 32, 95,105,109,112,111,114,116, 95,
     40,115,101, 97,114, 99,104, 68,105,114, 44, 32,112, 97, 99,
    107, 97,103,101, 80, 97,116,104, 44, 32,101,120,112,111,114,
    116, 78, 97,109,101, 44, 32,114,101,108,111, 97,100, 41, 10,
    108,111, 99, 97,108, 32,102,117,108,108, 68,105,114, 32, 61,
     32,115,101, 97,114, 99,104, 68,105,114, 46, 46, 39, 47, 39,
     46, 46,112, 97, 99,107, 97,103,101, 80, 97,116,104, 10,105,
    102, 32,110,111,116, 32,111,115, 46,112, 97,116,104, 46, 73,
    115, 68,105,114, 40,102,117,108,108, 68,105,114, 41, 32,116,
    104,101,110, 10,114,101,116,117,114,110, 32,102, 97,108,115,
    101, 10,101,110,100, 10,108,111, 99, 97,108, 32,102,105,108,
    101, 65,114,114, 44, 32,100,105,114, 65,114,114, 32, 61, 32,
    111,115, 46, 76,105,115,116, 68,105,114, 40,102,117,108,108,
     68,105,114, 41, 10,108,111, 99, 97,108, 32,112, 97, 99,107,
     97,103,101, 78, 97,109,101, 32, 61, 32,111,115, 46,112, 97,
    116,104, 46, 66, 97,115,101, 78, 97,109,101, 40,112, 97, 99,
    107, 97,103,101, 80, 97,116,104, 41, 10,102,111,114, 32, 95,
     44, 32,102,105,108,101, 78, 97,109,101, 32,105,110, 32,112,
     97,105,114,115, 40,102,105,108,101, 65,114,114, 41, 32,100,
    111, 10,105,102, 32,115,116,114,105,110,103, 46,102,105,110,
    100, 40,102,105,108,101, 78, 97,109,101, 44, 32, 39, 46,108,
    117, 97, 36, 39, 41, 32,116,104,101,110, 10,108,111, 99, 97,
    108, 32,102,117,108,108, 80, 97,116,104, 32, 61, 32,102,117,
    108,108, 68,105,114, 46, 46, 39, 47, 39, 46, 46,102,105,108,
    101, 78, 97,109,101, 10,108,111, 99, 97,108, 32,109,111,100,
    117,108,101, 78, 97,109,101, 32, 61, 32,110,105,108, 10,102,
    111,114, 32,108,105,110,101, 32,105,110, 32,105,111, 46,108,
    105,110,101,115, 40,102,117,108,108, 80, 97,116,104, 41, 32,
    100,111, 10,102,111,114, 32,107, 44, 32, 95, 32,105,110, 32,
    115,116,114,105,110,103, 46,103,109, 97,116, 99,104, 40,108,
    105,110,101, 44, 32, 34, 95,112, 97, 99,107, 97,103,101, 95,
     37, 40, 91, 92, 34, 92, 39, 93, 40, 91, 37,119, 92, 46, 35,
     92, 47, 45, 93, 43, 41, 91, 92, 34, 92, 39, 93, 34, 41, 32,
    100,111, 10,109,111,100,117,108,101, 78, 97,109,101, 32, 61,
     32,107, 10, 98,114,101, 97,107, 10,101,110,100, 10,105,102,
     32,109,111,100,117,108,101, 78, 97,109,101, 32,116,104,101,
    110, 10, 98,114,101, 97,107, 10,101,110,100, 10,101,110,100,
     10,105,102, 32,109,111,100,117,108,101, 78, 97,109,101, 32,
     61, 61, 32,112, 97, 99,107, 97,103,101, 78, 97,109,101, 32,
    116,104,101,110, 10,105,102, 32,114,101,108,111, 97,100, 32,
     97,110,100, 32,115, 99,114,105,112,116, 46,108,111, 97,100,
    101,100, 91,102,117,108,108, 80, 97,116,104, 93, 32,116,104,
    101,110, 10,108,111, 99, 97,108, 32,101,110,118, 32, 61, 32,
    115, 99,114,105,112,116, 46,108,111, 97,100,101,100, 91,102,
    117,108,108, 80, 97,116,104, 93, 10,108,111, 99, 97,108, 32,
    102, 44, 32,101,114,114, 32, 61, 32,108,111, 97,100,102,105,
    108,101, 40,102,117,108,108, 80, 97,116,104, 41, 10,105,102,
     32,110,111,116, 32,102, 32,116,104,101,110, 10,101,114,114,
    111,114, 40,101,114,114, 41, 10,101,110,100, 10,115,101,116,
    102,101,110,118, 40,102, 44, 32,101,110,118, 41, 10,102, 40,
     41, 10,101,108,115,101,105,102, 32,115, 99,114,105,112,116,
     46,108,111, 97,100,101,100, 91,102,117,108,108, 80, 97,116,
    104, 93, 32,116,104,101,110, 10,101,108,115,101, 10,112,114,
    105,110,116, 40, 39,114,101,113,117,105,114,101, 39, 44, 32,
    102,117,108,108, 80, 97,116,104, 41, 10,108,111, 99, 97,108,
     32,102, 44, 32,101,114,114, 32, 61, 32,108,111, 97,100,102,
    105,108,101, 40,102,117,108,108, 80, 97,116,104, 41, 10,105,
    102, 32,110,111,116, 32,102, 32,116,104,101,110, 10,101,114,
    114,111,114, 40,101,114,114, 41, 10,101,110,100, 10,108,111,
     99, 97,108, 32,101,110,118, 32, 61, 32, 95, 71, 91,101,120,
    112,111,114,116, 78, 97,109,101, 93, 10,105,102, 32,110,111,
    116, 32,101,110,118, 32,116,104,101,110, 10,101,110,118, 32,
     61, 32,123, 95, 95, 78, 65, 77, 69, 32, 61, 32,101,120,112,
    111,114,116, 78, 97,109,101, 44, 32, 95, 95, 80, 65, 67, 75,
     65, 71, 69, 32, 61, 32,112, 97, 99,107, 97,103,101, 80, 97,
    116,104, 44, 32, 95, 95, 80, 65, 84, 72, 32, 61, 32,102,117,
    108,108, 68,105,114, 44, 32, 76,111,103, 77,115,103, 32, 61,
     32, 76,111,103, 77,115,103,125, 10,101,110,118, 46,115,116,
     97,116,105, 99, 32, 61, 32,101,110,118, 10,115,101,116,109,
    101,116, 97,116, 97, 98,108,101, 40,101,110,118, 44, 32,123,
     95, 95,105,110,100,101,120, 32, 61, 32, 95, 71,125, 41, 10,
     95, 71, 91,101,120,112,111,114,116, 78, 97,109,101, 93, 32,
     61, 32,101,110,118, 10,101,110,100, 10,115,101,116,102,101,
    110,118, 40,102, 44, 32,101,110,118, 41, 10,115, 99,114,105,
    112,116, 46,108,111, 97,100,101,100, 91,102,117,108,108, 80,
     97,116,104, 93, 32, 61, 32,101,110,118, 10,115, 99,114,105,
    112,116, 46,112, 97, 99,107, 97,103,101, 91,101,120,112,111,
    114,116, 78, 97,109,101, 93, 32, 61, 32,101,110,118, 10,102,
     40, 41, 10,101,110,100, 10,101,108,115,101, 10,101,110,100,
     10,101,110,100, 10,101,110,100, 10,105,102, 32,114,101,108,
    111, 97,100, 32,116,104,101,110, 10,105,102, 32, 95, 71, 91,
    101,120,112,111,114,116, 78, 97,109,101, 93, 32, 97,110,100,
     32, 95, 71, 91,101,120,112,111,114,116, 78, 97,109,101, 93,
     46,114,101,108,111, 97,100, 32,116,104,101,110, 10, 95, 71,
     91,101,120,112,111,114,116, 78, 97,109,101, 93, 46,114,101,
    108,111, 97,100, 40, 41, 10,101,110,100, 10,101,108,115,101,
     10,105,102, 32, 95, 71, 91,101,120,112,111,114,116, 78, 97,
    109,101, 93, 32, 97,110,100, 32, 95, 71, 91,101,120,112,111,
    114,116, 78, 97,109,101, 93, 46,109, 97,105,110, 32,116,104,
    101,110, 10, 95, 71, 91,101,120,112,111,114,116, 78, 97,109,
    101, 93, 46,109, 97,105,110, 40, 41, 10,101,110,100, 10,101,
    110,100, 10,114,101,116,117,114,110, 32,116,114,117,101, 10,
    101,110,100, 10,102,117,110, 99,116,105,111,110, 32,105,109,
    112,111,114,116, 40,112, 97, 99,107, 97,103,101, 80, 97,116,
    104, 44, 32,101,120,112,111,114,116, 78, 97,109,101, 44, 32,
    114,101,108,111, 97,100, 41, 10,105,102, 32,110,111,116, 32,
    101,120,112,111,114,116, 78, 97,109,101, 32,116,104,101,110,
     10,101,120,112,111,114,116, 78, 97,109,101, 32, 61, 32,111,
    115, 46,112, 97,116,104, 46, 66, 97,115,101, 78, 97,109,101,
     40,112, 97, 99,107, 97,103,101, 80, 97,116,104, 41, 10,101,
    110,100, 10,105,102, 32, 95, 71, 91,101,120,112,111,114,116,
     78, 97,109,101, 93, 32, 97,110,100, 32,110,111,116, 32,115,
     99,114,105,112,116, 46,112, 97, 99,107, 97,103,101, 91,101,
    120,112,111,114,116, 78, 97,109,101, 93, 32,116,104,101,110,
     10,101,114,114,111,114, 40,115,116,114,105,110,103, 46,102,
    111,114,109, 97,116, 40, 34,101,110,118,105,114,111,110,109,
    101,110,116, 32, 37,115, 32, 99,111,110,102,108,105, 99,116,
     34, 44, 32,101,120,112,111,114,116, 78, 97,109,101, 41, 41,
     10,114,101,116,117,114,110, 10,101,110,100, 10,105,102, 32,
    110,111,116, 32,114,101,108,111, 97,100, 32, 97,110,100, 32,
    115, 99,114,105,112,116, 46,112, 97, 99,107, 97,103,101, 91,
    101,120,112,111,114,116, 78, 97,109,101, 93, 32,116,104,101,
    110, 10,101,114,114,111,114, 40,115,116,114,105,110,103, 46,
    102,111,114,109, 97,116, 40, 34,112, 97, 99,107, 97,103,101,
     32, 37,115, 32, 99,111,110,102,108,105, 99,116, 34, 44, 32,
    101,120,112,111,114,116, 78, 97,109,101, 41, 41, 10,114,101,
    116,117,114,110, 10,101,110,100, 10,102,111,114, 32,115,101,
     97,114, 99,104, 68,105,114, 44, 32, 95, 32,105,110, 32,115,
    116,114,105,110,103, 46,103,109, 97,116, 99,104, 40, 99,111,
    111,114,100, 97, 46,115, 99,114,105,112,116, 46,112, 97,116,
    104, 44, 32, 34, 91, 37,119, 47, 92, 46, 92, 63, 93, 43, 34,
     41, 32,100,111, 10,108,111, 99, 97,108, 32,109,111,100, 32,
     61, 32, 95,105,109,112,111,114,116, 95, 40,115,101, 97,114,
     99,104, 68,105,114, 44, 32,112, 97, 99,107, 97,103,101, 80,
     97,116,104, 44, 32,101,120,112,111,114,116, 78, 97,109,101,
     44, 32,114,101,108,111, 97,100, 41, 10,105,102, 32,109,111,
    100, 32,116,104,101,110, 10,114,101,116,117,114,110, 32,109,
    111,100, 10,101,110,100, 10,101,110,100, 10,101,110,100, 10,
    102,117,110, 99,116,105,111,110, 32, 99,111,109,112,111,110,
    101,110,116, 40,110, 97,109,101, 41, 10,108,111, 99, 97,108,
     32,112, 97, 99,107, 97,103,101, 32, 61, 32,103,101,116,102,
    101,110,118, 40, 50, 41, 10,108,111, 99, 97,108, 32,101,110,
    118, 32, 61, 32,123, 95, 95, 67, 79, 77, 80, 79, 78, 69, 78,
     84, 32, 61, 32,112, 97, 99,107, 97,103,101, 46, 95, 95, 78,
     65, 77, 69, 46, 46, 39, 46, 39, 46, 46,110, 97,109,101, 44,
     32, 95, 95, 73, 78, 84, 69, 82, 70, 65, 67, 69, 32, 61, 32,
    123,125,125, 10,115,101,116,109,101,116, 97,116, 97, 98,108,
    101, 40,101,110,118, 44, 32,123, 95, 95,105,110,100,101,120,
     32, 61, 32, 95, 71,125, 41, 10,112, 97, 99,107, 97,103,101,
     91,110, 97,109,101, 93, 32, 61, 32,101,110,118, 10,115,101,
    116,102,101,110,118, 40, 50, 44, 32,101,110,118, 41, 10,101,
    110,100, 10,102,117,110, 99,116,105,111,110, 32,105,109,112,
    108,101,109,101,110,116, 40,110, 97,109,101, 41, 10,108,111,
     99, 97,108, 32,101,110,118, 32, 61, 32,103,101,116,102,101,
    110,118, 40, 50, 41, 10,116, 97, 98,108,101, 46,105,110,115,
    101,114,116, 40,101,110,118, 46, 95, 95, 73, 78, 84, 69, 82,
     70, 65, 67, 69, 44, 32,110, 97,109,101, 41, 10,101,110,100,
     10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,110,
     32,116,114, 97, 99,101, 71, 40, 41, 10,102,111,114, 32,107,
     44, 32,118, 32,105,110, 32,112, 97,105,114,115, 40, 95, 71,
     41, 32,100,111, 10,112,114,105,110,116, 40,107, 41, 10,101,
    110,100, 10,101,110,100, 10,102,117,110, 99,116,105,111,110,
     32, 95,109, 97,105,110, 95, 40, 41, 10,108,111, 99, 97,108,
     32,115,101, 97,114, 99,104, 68,105,114, 65,114,114, 32, 61,
     32,111,115, 46, 71,101,116, 67,119,100, 40, 41, 10,102,111,
    114, 32,107, 44, 32,118, 32,105,110, 32,115,116,114,105,110,
    103, 46,103,109, 97,116, 99,104, 40, 99,111,111,114,100, 97,
     46,115, 99,114,105,112,116, 46,112, 97,116,104, 44, 32, 34,
     91, 37,119, 47, 92, 46, 92, 63, 93, 43, 34, 41, 32,100,111,
     10,108,111, 99, 97,108, 32,114,101, 97,108, 80, 97,116,104,
     32, 61, 32,111,115, 46, 82,101, 97,108, 80, 97,116,104, 40,
    107, 41, 10,105,102, 32,114,101, 97,108, 80, 97,116,104, 32,
     61, 61, 32,110,105,108, 32,116,104,101,110, 10,112,114,105,
    110,116, 40, 39,115, 99,114,105,112,116, 32,112, 97,116,104,
     32,110,111,116, 32,102,111,117,110,100, 58, 39, 46, 46,107,
     41, 10,111,115, 46,101,120,105,116, 40, 49, 41, 10,101,110,
    100, 10,115,101, 97,114, 99,104, 68,105,114, 65,114,114, 32,
     61, 32,115,101, 97,114, 99,104, 68,105,114, 65,114,114, 46,
     46, 39, 59, 39, 46, 46,114,101, 97,108, 80, 97,116,104, 10,
    101,110,100, 10, 99,111,111,114,100, 97, 46,115, 99,114,105,
    112,116, 46,112, 97,116,104, 32, 61, 32,115,101, 97,114, 99,
    104, 68,105,114, 65,114,114, 10, 99,111,111,114,100, 97, 58,
     76,111,103, 77,115,103, 40, 99,111,111,114,100, 97, 46,115,
     99,114,105,112,116, 46,112, 97,116,104, 41, 10,115, 99,114,
    105,112,116, 46,108,111, 97,100,101,100, 32, 61, 32,123,125,
     10,115, 99,114,105,112,116, 46,112, 97, 99,107, 97,103,101,
     32, 61, 32,123,125, 10,108,111, 99, 97,108, 32,101,120,112,
    111,114,116, 78, 97,109,101, 32, 61, 32,111,115, 46,112, 97,
    116,104, 46, 66, 97,115,101, 78, 97,109,101, 40, 99,111,111,
    114,100, 97, 46,115, 99,114,105,112,116, 46,109, 97,105,110,
     41, 10,105,102, 32,110,111,116, 32,105,109,112,111,114,116,
     40, 99,111,111,114,100, 97, 46,115, 99,114,105,112,116, 46,
    109, 97,105,110, 44, 32,101,120,112,111,114,116, 78, 97,109,
    101, 41, 32,116,104,101,110, 10,101,114,114,111,114, 40, 34,
    105,109,112,111,114,116, 32,109, 97,105,110, 32,112, 97, 99,
    107, 97,103,101, 32,102, 97,105,108,101,100, 34, 41, 10,101,
    110,100, 10,101,110,100, 10,102,117,110, 99,116,105,111,110,
     32, 95,101,120,105,116, 95, 40, 41, 10,108,111, 99, 97,108,
     32,101,120,112,111,114,116, 78, 97,109,101, 32, 61, 32,111,
    115, 46,112, 97,116,104, 46, 66, 97,115,101, 78, 97,109,101,
     40, 99,111,111,114,100, 97, 46,115, 99,114,105,112,116, 46,
    109, 97,105,110, 41, 10, 95, 71, 91,101,120,112,111,114,116,
     78, 97,109,101, 93, 46,101,120,105,116, 40, 41, 10,101,110,
    100, 10,102,117,110, 99,116,105,111,110, 32, 95, 82, 69, 81,
     85, 69, 83, 84, 40,115,101,108,102, 44, 32, 97,114,103,115,
     41, 10,112,114,105,110,116, 40,115,101,108,102, 41, 10,112,
    114,105,110,116, 40, 34,103,103,103,103,103,103, 34, 44, 32,
     97,114,103,115, 41, 10,101,110,100,32
   };
   tolua_dobuffer(tolua_S,(char*)B,sizeof(B),"tolua embedded: lualib/lib.lua");
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

