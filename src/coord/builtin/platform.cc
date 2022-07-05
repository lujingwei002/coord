#include "coord/builtin/platform.h"
#include "coord/coord.h"
#include <uv.h>


namespace coord {
    namespace path {
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
            int err = uv_fs_realpath(&coorda->loop, &req, path.c_str(), nullptr);
            if (err) {
                return err;
            }
            realPath.assign((char*)req.ptr);
            return 0;
        }
    }
}
