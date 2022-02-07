#ifndef __LJSON_H__
#define __LJSON_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}

int luaopen_json(lua_State *L);

#endif
