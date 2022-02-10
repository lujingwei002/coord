#ifndef __COORD_OS_H__
#define __COORD_OS_H__

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

namespace os { //tolua_export
    int GetCwd(char* path);
    int GetCwd(lua_State *L);//tolua_export
    int RealPath(const char* path, char* resolvedPath); 
    const char* RealPath(const char* path);
    int RealPath(lua_State *L); //tolua_export
    int ListDir(lua_State *L); //tolua_export   
} //tolua_export


#endif