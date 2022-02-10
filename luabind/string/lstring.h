#ifndef __LSTRING_H__
#define __LSTRING_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}


int luaopen_cstring(lua_State *L);

#endif
