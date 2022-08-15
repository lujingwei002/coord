#pragma once 

#include "coordx/memory/slice.h"
#include <optional>

#if defined(__linux__)
// Linux系统
#include <limits.h>

#elif defined(_WIN32)
// Windows系统
#define PATH_MAX 1024
#endif

#include <string>

#include <uv.h>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

namespace coordx {//tolua_export
    namespace path { //tolua_export
        bool IsAbsolutePath(const char* path);
        std::string PathJoin(const std::string& p1, const std::string& p2);
        std::string DirName(const std::string& path);
        int RealPath(const std::string& path, std::string& realPath);
        int MakeDir(const std::string& path, int mode);
        int RemoveDir(const std::string& path);
        bool Exists(const std::string& path);                                   //tolua_export
        int Unlink(const std::string& path);
        /// 锁定文件
        int FileLock(const std::string& path);
        int RemoveDirRecursive(const std::string& path);
        uv_stat_t* FileStat(const char* path);
        int ReadFile(const char* path, byte_slice& buffer);
        const char* FileType(const char* path);                                 
        int BaseName(lua_State* L);                                             //tolua_export
        const char* BaseName(const char* path);                                 //tolua_export
        bool IsDir(const char *dir);                                            //tolua_export
        std::string ExtName(std::string& path);                                 //tolua_export
        int GetCwd(char* path);                                                 //tolua_export
        int GetCwd(lua_State *L);                                               //tolua_export
        int ListDir(lua_State *L);                                              //tolua_export 
    }//tolua_export
}//tolua_export
