#include "coord/builtin/platform.h"

namespace coord {
    bool IsAbsolutePath(const char* path) {
        return path[0] == '/';
    }
    std::string PathJoin(std::string p1, std::string p2) {
        return p1 + "/"  + p2;
    }
}
