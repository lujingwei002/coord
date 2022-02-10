#include "util/os/path.h"

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

const char* DirName(const char* path) {
    static thread_local char dir[PATH_MAX];
    size_t strLen = strlen(path);
    int startPos = 0;
    int endPos = 0;
    for (int i = strLen - 1; i >= 0; i--) {
        if (path[i] == '/') {
            endPos = i;
            break;
        }
    }
 
    if (startPos > endPos) {
        return NULL;
    } else {
        memcpy(dir, path + startPos, endPos - startPos + 1);
        dir[endPos - startPos + 1] = 0;
        return dir;
    }
}

//功能：目录或者文件是否已经存在
bool Exist(const char *filePath) {
    int amode = 0;
    if(::access(filePath, amode))  {
        return false;
    }
    return true;
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

std::string Join(std::string& dir, std::string& name) {
    if (dir.length() <= 0){
        return name;
    }
    if (name.length() <= 0){
        return dir;
    }
    if (dir.length() > 0 && dir[dir.length() - 1] == '/') {
        return dir + name;
    }
    if (name.length() > 0 && name[0] == '/') {
        return dir + name;
    }
    return dir + "/" + name;
}

std::string ExtName(std::string& path) {
    size_t found = path.rfind(".");
    if (found == std::string::npos) {
        return path;
    }
    return path.substr(found + 1, path.size() - found + 1);
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

}
}