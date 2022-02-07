#include "util/os/os.h"

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

namespace os {
    
    //功能：当前目录
    int GetCwd(char* path){
        if (path == NULL){
            return 1;
        }
        path[0] = 0;
        if(getcwd(path, PATH_MAX) == NULL){
            return 1;
        }
        return 0;
    }

    int GetCwd(lua_State *L) {
        char path[PATH_MAX];
        if(GetCwd(path)){
            return 0;
        }
        lua_pushstring(L, path);
        return 1;
    }

    int RealPath(const char* path, char* resolvedPath) {
        if (resolvedPath == NULL){
            return 1;
        }
        if(realpath(path, resolvedPath) == NULL){
            return 1;
        }
        return 0;
    }
    
    const char* RealPath(const char* path) {
        static thread_local char resolvedPath[PATH_MAX];
        if(realpath(path, resolvedPath) == NULL){
            return NULL;
        }
        return resolvedPath;
    }

    int RealPath(lua_State *L) {
        if (!(lua_gettop(L) == 1 && lua_isstring(L, 1))) {
            return 0;
        }
        const char *path = (const char *)lua_tostring(L, 1);
        char resolvedPath[PATH_MAX];
        if(RealPath(path, resolvedPath)){
            return 0;
        }
        lua_pushstring(L, resolvedPath);
        return 1;
    }

    int ListDir(lua_State *L) {
        if (lua_gettop(L) == 1 && lua_isstring(L, 1)) {
            const char *dirName = (const char *)lua_tostring(L, 1);
            struct dirent *ent;
            lua_newtable(L);
            lua_newtable(L);
            DIR *dir = opendir(dirName);
            if(dir == NULL) {
                return 2;
            }
            int idx = 1;
            while((ent = readdir(dir)) != NULL) {
                if(ent->d_type & DT_REG) {
                    if(strcmp(ent->d_name, ".") == 0){
                        continue;
                    }
                    if(strcmp(ent->d_name, "..") == 0){
                        continue;
                    }
                    lua_pushnumber(L, idx++);
                    lua_pushstring(L, ent->d_name);
                    lua_settable(L, -4);
                }
            }
            closedir(dir);

            dir = opendir(dirName);
            if(dir == NULL) {
                return 2;
            }
            idx = 1;
            while((ent = readdir(dir)) != NULL) {
                if(ent->d_type & DT_DIR) {
                    if(strcmp(ent->d_name, ".") == 0){
                        continue;
                    }
                    if(strcmp(ent->d_name, "..") == 0){
                        continue;
                    }
                    lua_pushnumber(L, idx++);
                    lua_pushstring(L, ent->d_name);
                    lua_settable(L, -3);
                }
            }
            closedir(dir);
            return 2;
        }
        return 0;
    }

    
}