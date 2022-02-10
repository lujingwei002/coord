/*
** Lua binding: loginsvr
** Generated automatically by tolua++-1.0.92 on Thu Oct 28 15:11:36 2021.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_loginsvr_open (lua_State* tolua_S);

#include "loginsvr.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_loginsvr__LoginSvr (lua_State* tolua_S)
{
 loginsvr::LoginSvr* self = (loginsvr::LoginSvr*) tolua_tousertype(tolua_S,1,0);
	delete self;
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"coord::Component");
 tolua_usertype(tolua_S,"loginsvr::LoginSvrConfig");
 tolua_usertype(tolua_S,"loginsvr::LoginSvr");
 tolua_usertype(tolua_S,"coord::Coord");
}

/* get function: Host of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_loginsvr__LoginSvrConfig_Host
static int tolua_get_loginsvr__LoginSvrConfig_Host(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Host'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Host);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Host of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_loginsvr__LoginSvrConfig_Host
static int tolua_set_loginsvr__LoginSvrConfig_Host(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Port of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_loginsvr__LoginSvrConfig_Port
static int tolua_get_loginsvr__LoginSvrConfig_Port(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Port'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->Port);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Port of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_loginsvr__LoginSvrConfig_Port
static int tolua_set_loginsvr__LoginSvrConfig_Port(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: User of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_loginsvr__LoginSvrConfig_User
static int tolua_get_loginsvr__LoginSvrConfig_User(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'User'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->User);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: User of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_loginsvr__LoginSvrConfig_User
static int tolua_set_loginsvr__LoginSvrConfig_User(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: Password of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_get_loginsvr__LoginSvrConfig_Password
static int tolua_get_loginsvr__LoginSvrConfig_Password(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'Password'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->Password);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: Password of class  loginsvr::LoginSvrConfig */
#ifndef TOLUA_DISABLE_tolua_set_loginsvr__LoginSvrConfig_Password
static int tolua_set_loginsvr__LoginSvrConfig_Password(lua_State* tolua_S)
{
  loginsvr::LoginSvrConfig* self = (loginsvr::LoginSvrConfig*)  tolua_tousertype(tolua_S,1,0);
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

/* method: new of class  loginsvr::LoginSvr */
#ifndef TOLUA_DISABLE_tolua_loginsvr_loginsvr_LoginSvr_new00
static int tolua_loginsvr_loginsvr_LoginSvr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"loginsvr::LoginSvr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   loginsvr::LoginSvr* tolua_ret = (loginsvr::LoginSvr*)  new loginsvr::LoginSvr(coord);
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"loginsvr::LoginSvr");
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

/* method: new_local of class  loginsvr::LoginSvr */
#ifndef TOLUA_DISABLE_tolua_loginsvr_loginsvr_LoginSvr_new00_local
static int tolua_loginsvr_loginsvr_LoginSvr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"loginsvr::LoginSvr",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"coord::Coord",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  coord::Coord* coord = ((coord::Coord*)  tolua_tousertype(tolua_S,2,0));
  {
   loginsvr::LoginSvr* tolua_ret = (loginsvr::LoginSvr*)  new loginsvr::LoginSvr(coord);
   tolua_pushusertype_and_takeownership(tolua_S,(void *)tolua_ret,"loginsvr::LoginSvr");
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

/* function: loginsvr::NewLoginSvr */
#ifndef TOLUA_DISABLE_tolua_loginsvr_loginsvr_NewLoginSvr00
static int tolua_loginsvr_loginsvr_NewLoginSvr00(lua_State* tolua_S)
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
   loginsvr::LoginSvr* tolua_ret = (loginsvr::LoginSvr*)  loginsvr::NewLoginSvr();
   tolua_pushusertype(tolua_S,(void*)tolua_ret,"loginsvr::LoginSvr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NewLoginSvr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_loginsvr_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"loginsvr",0);
  tolua_beginmodule(tolua_S,"loginsvr");
   tolua_cclass(tolua_S,"LoginSvrConfig","loginsvr::LoginSvrConfig","",NULL);
   tolua_beginmodule(tolua_S,"LoginSvrConfig");
    tolua_variable(tolua_S,"Host",tolua_get_loginsvr__LoginSvrConfig_Host,tolua_set_loginsvr__LoginSvrConfig_Host);
    tolua_variable(tolua_S,"Port",tolua_get_loginsvr__LoginSvrConfig_Port,tolua_set_loginsvr__LoginSvrConfig_Port);
    tolua_variable(tolua_S,"User",tolua_get_loginsvr__LoginSvrConfig_User,tolua_set_loginsvr__LoginSvrConfig_User);
    tolua_variable(tolua_S,"Password",tolua_get_loginsvr__LoginSvrConfig_Password,tolua_set_loginsvr__LoginSvrConfig_Password);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"LoginSvr","loginsvr::LoginSvr","coord::Component",tolua_collect_loginsvr__LoginSvr);
   #else
   tolua_cclass(tolua_S,"LoginSvr","loginsvr::LoginSvr","coord::Component",NULL);
   #endif
   tolua_beginmodule(tolua_S,"LoginSvr");
    tolua_function(tolua_S,"new",tolua_loginsvr_loginsvr_LoginSvr_new00);
    tolua_function(tolua_S,"new_local",tolua_loginsvr_loginsvr_LoginSvr_new00_local);
    tolua_function(tolua_S,".call",tolua_loginsvr_loginsvr_LoginSvr_new00_local);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"NewLoginSvr",tolua_loginsvr_loginsvr_NewLoginSvr00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 extern "C"{
 TOLUA_API int luaopen_loginsvr (lua_State* tolua_S) {
 return tolua_loginsvr_open(tolua_S);
};
}
#endif

