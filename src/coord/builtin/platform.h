#pragma once 

#include "coord/builtin/slice.h"

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


namespace coord {
    namespace path {
        bool IsAbsolutePath(const char* path);
        std::string PathJoin(const std::string& p1, const std::string& p2);
        std::string DirName(const std::string& path);
        int RealPath(const std::string& path, std::string& realPath);
        int MakeDir(const std::string& path, int mode);
        int RemoveDir(const std::string& path);
        bool Exists(const std::string& path);
        int Unlink(const std::string& path);

        /// 锁定文件
        int FileLock(const std::string& path);

        int RemoveDirRecursive(const std::string& path);
        uv_stat_t* FileStat(const char* path);
        int ReadFile(const char* path, byte_slice& buffer);
    }
}
