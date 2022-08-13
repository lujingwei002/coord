
#pragma once

#include "coord/builtin/type.h"
namespace coord {
    class RcObject;
    class Promise;
    class ref_manager;
    
    namespace path {
        bool IsAbsolutePath(const char* path);
        std::string PathJoin(const std::string& p1, const std::string& p2);
        std::string DirName(const std::string& path);
        int RealPath(const std::string& path, std::string& realPath);
        int MakeDir(const std::string& path, int mode);
        int RemoveDir(const std::string& path);
        bool Exists(const std::string& path);
        int Unlink(const std::string& path);
        int FileLock(const std::string& path);
        int RemoveDirRecursive(const std::string& path);
    }
}
