#ifndef __L_OS_H__
#define __L_OS_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}

int luaopen_myos(lua_State *L);

#endif
