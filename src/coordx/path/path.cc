#include "coordx/path/path.h"
#include "coordx/reactor/reactor.h"
#include "coordx/log/print.h"
#include <uv.h>
#include <sys/file.h> // flock
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h> // open
#include <fstream> 
#include <iostream>
#include <cstring>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

namespace coordx {
    uv_loop_t uvloop;
    namespace path {
        int BaseName(lua_State* L) {
            char *path;
            size_t strLen = 0;
            path = (char *)lua_tolstring(L, 1, &strLen);
            int startPos = 0;
            for (int i = strLen - 1; i >= 0; i--) {
                if (path[i] == '/') {
                    startPos = i + 1;
                    break;
                }
            }
            int endPos = strLen - 1;
            for (int i = strLen - 1; i >= startPos; i--) {
                if (path[i] == '.') {
                    endPos = i - 1;
                    break;
                }
            }
            if (startPos > endPos) {
                lua_pushstring(L, "");
                return 1;
            } else {
                lua_pushlstring(L, path + startPos, endPos - startPos + 1);
                return 1;
            }
        }

        const char* BaseName(const char* path) {
            static thread_local char name[PATH_MAX];
            size_t strLen = strlen(path);
            int startPos = 0;
            for (int i = strLen - 1; i >= 0; i--) {
                if (path[i] == '/') {
                    startPos = i + 1;
                    break;
                }
            }
            int endPos = strLen - 1;
            for (int i = strLen - 1; i >= startPos; i--) {
                if (path[i] == '.') {
                    endPos = i - 1;
                    break;
                }
            }
            if (startPos > endPos) {
                return NULL;
            } else {
                memcpy(name, path + startPos, endPos - startPos + 1);
                name[endPos - startPos + 1] = 0;
                return name;
            }
        }

        std::string ExtName(std::string& path) {
            size_t found = path.rfind(".");
            if (found == std::string::npos) {
                return path;
            }
            return path.substr(found + 1, path.size() - found + 1);
        }

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

        bool IsAbsolutePath(const char* path) {
            return path[0] == '/';
        }

        std::string PathJoin(const std::string& p1, const std::string& p2) {
            return p1 + "/"  + p2;
        }

        std::string DirName(const std::string& path) {
            auto pos = path.rfind("/");
            if (pos != std::string::npos) {
                return path.substr(0, pos);
            } else {
                return path;
            }
        }

        int RealPath(const std::string& path, std::string& realPath) {
            uv_fs_t req;
            int err = uv_fs_realpath(&uvloop, &req, path.c_str(), nullptr);
            if (err) {
                Errorln("RealPath failed, path=%s, error=%s", path.c_str(), uv_strerror(err));
                return err;
            }
            realPath.assign((char*)req.ptr);
            return 0;
        }

        int MakeDir(const std::string& path, int mode) {
            uv_fs_t req;
            int err = uv_fs_mkdir(&uvloop, &req, path.c_str(), mode, nullptr);
            if (err) {
                return err;
            }
            return 0;
        }

        bool Exists(const std::string& path) {
            uv_fs_t req;
            int err = uv_fs_stat(&uvloop, &req, path.c_str(), nullptr);
            if (err) {
                return false;
            }
            return true;
        }

        int FileLock(const std::string& path) {
            int fd = open(path.c_str(), O_RDWR|O_CREAT, 0755);
            if (fd < 0) {
                return 1;
            }
            if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
                return 2;
            }
            return 0;
        }

        int RemoveDir(const std::string& path) {
            uv_fs_t req;
            int err = uv_fs_rmdir(&uvloop, &req, path.c_str(), nullptr);
            if (err) {
                Errorln("RemoveDir failed, path='%s', err='%s'", path.c_str(), uv_strerror(err));
                return err;
            }
            return 0;
        }

        int Unlink(const std::string& path) {
            uv_fs_t req;
            int err = uv_fs_unlink(&uvloop, &req, path.c_str(), nullptr);
            if (err) {
                Errorln("Unlink failed, path='%s', err='%s'", path.c_str(), uv_strerror(err));
                return err;
            }
            return 0;
        }

        int RemoveDirRecursive(const std::string& path) {
            uv_fs_t req;
            uv_dirent_t ent;
            uv_fs_scandir(&uvloop, &req, path.c_str(), 0, NULL);
            int err;
            while(uv_fs_scandir_next(&req, &ent) != UV_EOF) {
                if (ent.type == UV_DIRENT_DIR) {
                    std::string newPath = PathJoin(path, ent.name);
                    err = RemoveDirRecursive(newPath);
                    if (err) {
                        return err;
                    }
                } else {
                    std::string newPath = PathJoin(path, ent.name);
                    err = Unlink(newPath);
                    if (err) {
                        return err;
                    }
                }
            }
            return RemoveDir(path);
        }


        uv_stat_t* FileStat(const char* path) {
            static thread_local uv_fs_t req;
            int err = uv_fs_stat(&uvloop, &req, path, NULL);
            if (err) {
                return NULL;
            }
            uv_stat_t* stat = (uv_stat_t*)req.ptr;
            return stat;
        }
        
        int ReadFile(const char* path, byte_slice& buffer) {
            std::ifstream file(path); 
            if (!file.is_open()) { 
                return -1;
            } 
            file.seekg(0, std::ios::end);    
            size_t length = file.tellg();          
            file.seekg(0, std::ios::beg);   
            int err = buffer.Reserve(length);    
            if (err) {
                file.close(); 
                return -1;
            }
            file.read(buffer.Data(), length);   
            buffer.Resize(length); 
            file.close(); 
            return 0;
        }

        const char* FileType(const char* path) {
            static thread_local char buffer[PATH_MAX];
            size_t len = strlen(path);
            for (size_t i = len - 1; i >= 0; i--) {
                if (path[i] == '.') {
                    memcpy(buffer, path + i + 1, len - i - 1);
                    buffer[len - i - 1] = 0;
                    return buffer;
                }
            }
            return NULL;
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
        bool IsDir(const char *dir) {
            struct stat buffer; 
            if (stat(dir, &buffer) < 0) { 
                return false;
            }
            if (S_ISDIR(buffer.st_mode)) {
                return true;
            }
            return false;
        }
    }
}
