

#ifndef _WEBSOCK_PORT_H_
#define _WEBSOCK_PORT_H_


extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}



int luaopen_websock_port(lua_State *L);

#endif
