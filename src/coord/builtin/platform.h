#pragma once 


#if defined(__linux__)
// Linux系统
#include <limits.h>

#elif defined(_WIN32)
// Windows系统
#define PATH_MAX 1024
#endif

#include <string>
namespace coord {
    bool IsAbsolutePath(const char* path);
    std::string PathJoin(std::string p1, std::string p2);
}
