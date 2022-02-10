#ifndef __COORD_PATH_H__
#define __COORD_PATH_H__

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
#include <string>

namespace os { //tolua_export
namespace path { //tolua_export
       
    int BaseName(lua_State* L);//tolua_export
    const char* BaseName(const char* path);//tolua_export
    const char* DirName(const char* path);//tolua_export
    bool Exist(const char *dir);//tolua_export
    bool IsDir(const char *dir);//tolua_export
    std::string Join(std::string& dir, std::string& name);
    std::string ExtName(std::string& path);
    const char* FileType(const char* path);
} //tolua_export
} //tolua_export


#endif