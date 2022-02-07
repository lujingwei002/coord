#ifndef __LREDIS_H__
#define __LREDIS_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}


int luaopen_redis(lua_State *L);
#endif
