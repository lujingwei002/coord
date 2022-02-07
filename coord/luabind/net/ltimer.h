#ifndef __LTIMER_H__
#define __LTIMER_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}


int luaopen_timer(lua_State *L);

#endif
