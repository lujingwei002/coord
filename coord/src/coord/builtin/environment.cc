#include "coord/builtin/environment.h"
#include "coord/builtin/init.h"
#include "coord/coord.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <uv.h>

namespace coord {

Environment* newEnvironment(Coord* coord) {
    Environment* self = new Environment(coord);
    return self;
}

int Environment::main() {
    char buffer[PATH_MAX];
    size_t len = sizeof(buffer);
    {
        int err = uv_exepath(buffer, &len);
        if (err) {
            return err;
        }
        this->ExecPath = buffer;
    }
    {
        auto pos = this->ExecPath.rfind("/");
        if (pos != std::string::npos) {
            this->ExecDir = this->ExecPath.substr(0, pos);
        }
    }
    {
        auto pos = this->ExecDir.rfind("/");
        if (pos != std::string::npos) {
            this->ProjectDir = this->ExecDir.substr(0, pos);
        }

    }
    {
        int err = uv_cwd(buffer, &len);
        if (err) {
            return err;
        }
        this->WorkingDir = buffer;
    }
    {
        int err = uv_os_homedir(buffer, &len);
        if (err) {
            return err;
        }
        this->HomeDir = buffer;
    }
    {
        int err = this->searchCoordDir(buffer, &len);
        if (err) {
            return err;
        }
        this->CoordDir = buffer;
    }
    printf("ExecPath: %s\n", this->ExecPath.c_str());
    printf("ExecDir: %s\n", this->ExecDir.c_str());
    printf("CoordDir: %s\n", this->CoordDir.c_str());
    printf("ProjectDir: %s\n", this->ProjectDir.c_str());
    return 0;
}

int Environment::searchCoordDir(char* buffer, size_t* len) {
    int err = uv_os_getenv("COORD_ROOT", buffer, len);
    if(!err) {
        return 0;
    }
    std::vector<std::string> searchDirArr;
    searchDirArr.push_back("/usr");
    searchDirArr.push_back("/usr/local");
    searchDirArr.push_back(this->HomeDir);
    for (size_t i = 0; i < searchDirArr.size(); i++) {
        sprintf(buffer, "%s%s", searchDirArr[i].c_str(), "/coord");
        uv_fs_t req;
        int err = uv_fs_stat(&this->coord->loop, &req, buffer, NULL);
        if(!err) {
            return 0;
        }
    }
    return -1;
}

}