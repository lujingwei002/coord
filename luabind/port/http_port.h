

#ifndef _HTTP_PORT_H_
#define _HTTP_PORT_H_

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}



int luaopen_http_port(lua_State *L);

#endif
