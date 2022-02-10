#ifndef _RMI_PORT_H_
#define _RMI_PORT_H_

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


int luaopen_rmi_port(lua_State *L);

#endif
