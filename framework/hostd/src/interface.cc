/*
** Lua binding: hostd
** Generated automatically by tolua++-1.0.92 on Mon Sep 13 17:33:12 2021.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_hostd_open (lua_State* tolua_S);

#include "hostd.h"
#include "hostd/hostd_server.h"
#include "hostd/hostd_agent.h"
#include "hostd/hostd_request.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_hostd__Hostd (lua_State* tolua_S)
{
 hostd::Hostd* self = (hostd::Hostd*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"coord::Coord");
 tolua_usertype(tolua_S,"hostd::Hostd");
 tolua_usertype(tolua_S,"coord::Destoryable");
 tolua_usertype(tolua_S,"hostd::HostdServer");
 tolua_usertype(tolua_S,"hostd::HostdConfig");
 tolua_usertype(tolua_S,"coord::Component");
 tolua_usertype(tolua_S,"coord::net::ITcpAgentHandler");
 tolua_usertype(tolua_S,"coord::net::ITcpHandler");
 tolua_usertype(tolua_S,"hostd::HostdRequest");
 tolua_usertype(tolua_S,"hostd::HostdAgent");
}

/* get function: Host of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_get_hostd__HostdConfig_Host
static int tolua_get_hostd__HostdConfig_Host(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_set_hostd__HostdConfig_Host
static int tolua_set_hostd__HostdConfig_Host(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Port of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_get_hostd__HostdConfig_Port
static int tolua_get_hostd__HostdConfig_Port(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_set_hostd__HostdConfig_Port
static int tolua_set_hostd__HostdConfig_Port(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: User of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_get_hostd__HostdConfig_User
static int tolua_get_hostd__HostdConfig_User(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->User);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: User of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_set_hostd__HostdConfig_User
static int tolua_set_hostd__HostdConfig_User(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Password of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_get_hostd__HostdConfig_Password
static int tolua_get_hostd__HostdConfig_Password(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  hostd::HostdConfig */
#ifndef TOLUA_DISABLE_tolua_set_hostd__HostdConfig_Password
static int tolua_set_hostd__HostdConfig_Password(lua_State* tolua_S)
{
  hostd::HostdConfig* self = (hostd::HostdConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  hostd::Hostd */
#ifndef TOLUA_DISABLE_tolua_hostd_hostd_Hostd_new00
static int tolua_hostd_hostd_Hostd_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"hostd::Hostd",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   hostd::Hostd* tolua_ret = (hostd::Hostd*)  new hostd::Hostd(coord);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"hostd::Hostd");
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

/* method: new_local of class  hostd::Hostd */
#ifndef TOLUA_DISABLE_tolua_hostd_hostd_Hostd_new00_local
static int tolua_hostd_hostd_Hostd_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"hostd::Hostd",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   hostd::Hostd* tolua_ret = (hostd::Hostd*)  new hostd::Hostd(coord);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"hostd::Hostd");
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

/* function: hostd::NewHostd */
#ifndef TOLUA_DISABLE_tolua_hostd_hostd_NewHostd00
static int tolua_hostd_hostd_NewHostd00(lua_State* tolua_S)
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
   hostd::Hostd* tolua_ret = (hostd::Hostd*)  hostd::NewHostd();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"hostd::Hostd");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewHostd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __coord of class  hostd::HostdAgent */
#ifndef TOLUA_DISABLE_tolua_get_hostd__HostdAgent___coord__net__ITcpAgentHandler__
static int tolua_get_hostd__HostdAgent___coord__net__ITcpAgentHandler__(lua_State* tolua_S)
{
  hostd::HostdAgent* self = (hostd::HostdAgent*)  tolua_tousertype(tolua_S,1,0);
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
TOLUA_API int tolua_hostd_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"hostd",0);
  tolua_beginmodule(tolua_S,"hostd");
   tolua_cclass(tolua_S,"HostdConfig","hostd::HostdConfig","",NULL);
   tolua_beginmodule(tolua_S,"HostdConfig");
    tolua_variable(tolua_S,"Host",tolua_get_hostd__HostdConfig_Host,tolua_set_hostd__HostdConfig_Host);
    tolua_variable(tolua_S,"Port",tolua_get_hostd__HostdConfig_Port,tolua_set_hostd__HostdConfig_Port);
    tolua_variable(tolua_S,"User",tolua_get_hostd__HostdConfig_User,tolua_set_hostd__HostdConfig_User);
    tolua_variable(tolua_S,"Password",tolua_get_hostd__HostdConfig_Password,tolua_set_hostd__HostdConfig_Password);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Hostd","hostd::Hostd","coord::Component",tolua_collect_hostd__Hostd);
   #else
   tolua_cclass(tolua_S,"Hostd","hostd::Hostd","coord::Component",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Hostd");
    tolua_function(tolua_S,"new",tolua_hostd_hostd_Hostd_new00);
    tolua_function(tolua_S,"new_local",tolua_hostd_hostd_Hostd_new00_local);
    tolua_function(tolua_S,".call",tolua_hostd_hostd_Hostd_new00_local);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"NewHostd",tolua_hostd_hostd_NewHostd00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"hostd",0);
  tolua_beginmodule(tolua_S,"hostd");
   tolua_cclass(tolua_S,"HostdServer","hostd::HostdServer","coord::net::ITcpHandler",NULL);
   tolua_beginmodule(tolua_S,"HostdServer");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"hostd",0);
  tolua_beginmodule(tolua_S,"hostd");
   tolua_cclass(tolua_S,"HostdAgent","hostd::HostdAgent","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"HostdAgent");
    tolua_variable(tolua_S,"__coord__net__ITcpAgentHandler__",tolua_get_hostd__HostdAgent___coord__net__ITcpAgentHandler__,NULL);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"hostd",0);
  tolua_beginmodule(tolua_S,"hostd");
   tolua_cclass(tolua_S,"HostdRequest","hostd::HostdRequest","coord::Destoryable",NULL);
   tolua_beginmodule(tolua_S,"HostdRequest");
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 extern "C"{
 TOLUA_API int luaopen_hostd (lua_State* tolua_S) {
 return tolua_hostd_open(tolua_S);
};
}
#endif

