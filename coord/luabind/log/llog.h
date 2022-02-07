#ifndef __LLOG_H__
#define __LLOG_H__
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}

int luaopen_log(lua_State *L);


#endif
