#ifndef __LSOCKET_H__
#define __LSOCKET_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}


int luaopen_socket(lua_State *L);

#endif
