/*
** Lua binding: consoled
** Generated automatically by tolua++-1.0.92 on Thu Oct 21 14:25:46 2021.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_consoled_open (lua_State* tolua_S);

#include "consoled.h"
#include "consoled/consoled_server.h"
#include "consoled/consoled_agent.h"
#include "consoled/consoled_request.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_consoled__Consoled (lua_State* tolua_S)
{
 consoled::Consoled* self = (consoled::Consoled*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"coord::Coord");
 tolua_usertype(tolua_S,"consoled::ConsoledAgent");
 tolua_usertype(tolua_S,"consoled::ConsoledConfig");
 tolua_usertype(tolua_S,"coord::Component");
 tolua_usertype(tolua_S,"consoled::Consoled");
 tolua_usertype(tolua_S,"consoled::ConsoledRequest");
 tolua_usertype(tolua_S,"coord::net::ITcpHandler");
 tolua_usertype(tolua_S,"coord::net::ITcpAgentHandler");
 tolua_usertype(tolua_S,"coord::Destoryable");
 tolua_usertype(tolua_S,"consoled::ConsoledServer");
}

/* get function: Host of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_get_consoled__ConsoledConfig_Host
static int tolua_get_consoled__ConsoledConfig_Host(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_set_consoled__ConsoledConfig_Host
static int tolua_set_consoled__ConsoledConfig_Host(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Port of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_get_consoled__ConsoledConfig_Port
static int tolua_get_consoled__ConsoledConfig_Port(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_set_consoled__ConsoledConfig_Port
static int tolua_set_consoled__ConsoledConfig_Port(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: User of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_get_consoled__ConsoledConfig_User
static int tolua_get_consoled__ConsoledConfig_User(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->User);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: User of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_set_consoled__ConsoledConfig_User
static int tolua_set_consoled__ConsoledConfig_User(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Password of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_get_consoled__ConsoledConfig_Password
static int tolua_get_consoled__ConsoledConfig_Password(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  consoled::ConsoledConfig */
#ifndef TOLUA_DISABLE_tolua_set_consoled__ConsoledConfig_Password
static int tolua_set_consoled__ConsoledConfig_Password(lua_State* tolua_S)
{
  consoled::ConsoledConfig* self = (consoled::ConsoledConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  consoled::Consoled */
#ifndef TOLUA_DISABLE_tolua_consoled_consoled_Consoled_new00
static int tolua_consoled_consoled_Consoled_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"consoled::Consoled",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   consoled::Consoled* tolua_ret = (consoled::Consoled*)  new consoled::Consoled(coord);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"consoled::Consoled");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  consoled::Consoled */
#ifndef TOLUA_DISABLE_tolua_consoled_consoled_Consoled_new00_local
static int tolua_consoled_consoled_Consoled_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"consoled::Consoled",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   consoled::Consoled* tolua_ret = (consoled::Consoled*)  new consoled::Consoled(coord);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"consoled::Consoled");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: consoled::NewConsoled */
#ifndef TOLUA_DISABLE_tolua_consoled_consoled_NewConsoled00
static int tolua_consoled_consoled_NewConsoled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   consoled::Consoled* tolua_ret = (consoled::Consoled*)  consoled::NewConsoled();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"consoled::Consoled");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewConsoled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __coord of class  consoled::ConsoledAgent */
#ifndef TOLUA_DISABLE_tolua_get_consoled__ConsoledAgent___coord__net__ITcpAgentHandler__
static int tolua_get_consoled__ConsoledAgent___coord__net__ITcpAgentHandler__(lua_State* tolua_S)
{
  consoled::ConsoledAgent* self = (consoled::ConsoledAgent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__coord'",NULL);
#endif
#ifdef __cplusplus
  tolua_pushusertype(tolua_S,(void*)static_cast<coord::net::ITcpAgentHandler*>(self), "coord::net::ITcpAgentHandler");
#else
  tolua_pushusertype(tolua_S,(void*)((coord::net::ITcpAgentHandler*)self), "coord::net::ITcpAgentHandler");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_consoled_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"consoled",0);
  tolua_beginmodule(tolua_S,"consoled");
   tolua_cclass(tolua_S,"ConsoledConfig","consoled::ConsoledConfig","",NULL);
   tolua_beginmodule(tolua_S,"ConsoledConfig");
    tolua_variable(tolua_S,"Host",tolua_get_consoled__ConsoledConfig_Host,tolua_set_consoled__ConsoledConfig_Host);
    tolua_variable(tolua_S,"Port",tolua_get_consoled__ConsoledConfig_Port,tolua_set_consoled__ConsoledConfig_Port);
    tolua_variable(tolua_S,"User",tolua_get_consoled__ConsoledConfig_User,tolua_set_consoled__ConsoledConfig_User);
    tolua_variable(tolua_S,"Password",tolua_get_consoled__ConsoledConfig_Password,tolua_set_consoled__ConsoledConfig_Password);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Consoled","consoled::Consoled","coord::Component",tolua_collect_consoled__Consoled);
   #else
   tolua_cclass(tolua_S,"Consoled","consoled::Consoled","coord::Component",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Consoled");
    tolua_function(tolua_S,"new",tolua_consoled_consoled_Consoled_new00);
    tolua_function(tolua_S,"new_local",tolua_consoled_consoled_Consoled_new00_local);
    tolua_function(tolua_S,".call",tolua_consoled_consoled_Consoled_new00_local);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"NewConsoled",tolua_consoled_consoled_NewConsoled00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"consoled",0);
  tolua_beginmodule(tolua_S,"consoled");
   tolua_cclass(tolua_S,"ConsoledServer","consoled::ConsoledServer","coord::net::ITcpHandler",NULL);
   tolua_beginmodule(tolua_S,"ConsoledServer");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"consoled",0);
  tolua_beginmodule(tolua_S,"consoled");
   tolua_cclass(tolua_S,"ConsoledAgent","consoled::ConsoledAgent","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"ConsoledAgent");
    tolua_variable(tolua_S,"__coord__net__ITcpAgentHandler__",tolua_get_consoled__ConsoledAgent___coord__net__ITcpAgentHandler__,NULL);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"consoled",0);
  tolua_beginmodule(tolua_S,"consoled");
   tolua_cclass(tolua_S,"ConsoledRequest","consoled::ConsoledRequest","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"ConsoledRequest");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 extern "C"{
 TOLUA_API int luaopen_consoled (lua_State* tolua_S) {
 return tolua_consoled_open(tolua_S);
};
}
#endif

