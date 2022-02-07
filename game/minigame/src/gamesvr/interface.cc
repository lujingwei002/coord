/*
** Lua binding: gamesvr
** Generated automatically by tolua++-1.0.92 on Sat Sep 18 11:22:21 2021.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_gamesvr_open (lua_State* tolua_S);

#include "gamesvr.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_gamesvr__GameSvr (lua_State* tolua_S)
{
 gamesvr::GameSvr* self = (gamesvr::GameSvr*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"gamesvr::GameSvr");
 tolua_usertype(tolua_S,"coord::Coord");
 tolua_usertype(tolua_S,"gamesvr::GameSvrConfig");
 tolua_usertype(tolua_S,"coord::Component");
}

/* get function: Host of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_gamesvr__GameSvrConfig_Host
static int tolua_get_gamesvr__GameSvrConfig_Host(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_gamesvr__GameSvrConfig_Host
static int tolua_set_gamesvr__GameSvrConfig_Host(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Port of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_gamesvr__GameSvrConfig_Port
static int tolua_get_gamesvr__GameSvrConfig_Port(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_gamesvr__GameSvrConfig_Port
static int tolua_set_gamesvr__GameSvrConfig_Port(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: User of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_gamesvr__GameSvrConfig_User
static int tolua_get_gamesvr__GameSvrConfig_User(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->User);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: User of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_gamesvr__GameSvrConfig_User
static int tolua_set_gamesvr__GameSvrConfig_User(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Password of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_gamesvr__GameSvrConfig_Password
static int tolua_get_gamesvr__GameSvrConfig_Password(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  gamesvr::GameSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_gamesvr__GameSvrConfig_Password
static int tolua_set_gamesvr__GameSvrConfig_Password(lua_State* tolua_S)
{
  gamesvr::GameSvrConfig* self = (gamesvr::GameSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  gamesvr::GameSvr */
#ifndef TOLUA_DISABLE_tolua_gamesvr_gamesvr_GameSvr_new00
static int tolua_gamesvr_gamesvr_GameSvr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"gamesvr::GameSvr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   gamesvr::GameSvr* tolua_ret = (gamesvr::GameSvr*)  new gamesvr::GameSvr(coord);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"gamesvr::GameSvr");
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

/* method: new_local of class  gamesvr::GameSvr */
#ifndef TOLUA_DISABLE_tolua_gamesvr_gamesvr_GameSvr_new00_local
static int tolua_gamesvr_gamesvr_GameSvr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"gamesvr::GameSvr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   gamesvr::GameSvr* tolua_ret = (gamesvr::GameSvr*)  new gamesvr::GameSvr(coord);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"gamesvr::GameSvr");
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

/* function: gamesvr::NewGameSvr */
#ifndef TOLUA_DISABLE_tolua_gamesvr_gamesvr_NewGameSvr00
static int tolua_gamesvr_gamesvr_NewGameSvr00(lua_State* tolua_S)
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
   gamesvr::GameSvr* tolua_ret = (gamesvr::GameSvr*)  gamesvr::NewGameSvr();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"gamesvr::GameSvr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewGameSvr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_gamesvr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"gamesvr",0);
  tolua_beginmodule(tolua_S,"gamesvr");
   tolua_cclass(tolua_S,"GameSvrConfig","gamesvr::GameSvrConfig","",NULL);
   tolua_beginmodule(tolua_S,"GameSvrConfig");
    tolua_variable(tolua_S,"Host",tolua_get_gamesvr__GameSvrConfig_Host,tolua_set_gamesvr__GameSvrConfig_Host);
    tolua_variable(tolua_S,"Port",tolua_get_gamesvr__GameSvrConfig_Port,tolua_set_gamesvr__GameSvrConfig_Port);
    tolua_variable(tolua_S,"User",tolua_get_gamesvr__GameSvrConfig_User,tolua_set_gamesvr__GameSvrConfig_User);
    tolua_variable(tolua_S,"Password",tolua_get_gamesvr__GameSvrConfig_Password,tolua_set_gamesvr__GameSvrConfig_Password);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"GameSvr","gamesvr::GameSvr","coord::Component",tolua_collect_gamesvr__GameSvr);
   #else
   tolua_cclass(tolua_S,"GameSvr","gamesvr::GameSvr","coord::Component",NULL);
   #endif
   tolua_beginmodule(tolua_S,"GameSvr");
    tolua_function(tolua_S,"new",tolua_gamesvr_gamesvr_GameSvr_new00);
    tolua_function(tolua_S,"new_local",tolua_gamesvr_gamesvr_GameSvr_new00_local);
    tolua_function(tolua_S,".call",tolua_gamesvr_gamesvr_GameSvr_new00_local);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"NewGameSvr",tolua_gamesvr_gamesvr_NewGameSvr00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 extern "C"{
 TOLUA_API int luaopen_gamesvr (lua_State* tolua_S) {
 return tolua_gamesvr_open(tolua_S);
};
}
#endif

