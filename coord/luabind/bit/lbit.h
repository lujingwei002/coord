#ifndef _L_BIT_H_
#define _L_BIT_H_

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}


int luaopen_bit(lua_State *L);

#endif
