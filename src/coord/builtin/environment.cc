#include "coord/builtin/environment.h"
#include "coord/builtin/init.h"
#include "coord/coord.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <uv.h>

namespace coord {
const char* TAG = "Environment";
Environment* newEnvironment(Coord* coord) {
    Environment* self = new Environment(coord);
    return self;
}

int Environment::main(const char* configFilePath) {

    char buffer[PATH_MAX];
    size_t len = sizeof(buffer);
    {
        len = sizeof(buffer);
        uv_fs_t req;
        int err = uv_fs_realpath(&this->coord->loop, &req, configFilePath, nullptr);
        if (err) {
            return err;
        }
        this->ConfigFilePath = (char*)req.ptr;
    }
    {
        auto pos = this->ConfigFilePath.rfind("/");
        if (pos != std::string::npos) {
            this->ConfigFileDir = this->ConfigFilePath.substr(0, pos);
        }
    }
    {
        len = sizeof(buffer);
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
        len = sizeof(buffer);
        int err = uv_cwd(buffer, &len);
        if (err) {
            return err;
        }
        this->WorkingDir = buffer;
    }
    {
        len = sizeof(buffer);
        int err = uv_os_homedir(buffer, &len);
        if (err) {
            return err;
        }
        this->HomeDir = buffer;
    }
    {
        len = sizeof(buffer);
        int err = this->searchCoordDir(buffer, &len);
        if (err) {
            return err;
        }
        this->CoordDir = buffer;
    }

    this->Package = this->CoordDir + "/package";                        // 引擎目录
    this->Package = this->WorkingDir + "/package;" + this->Package;     // 工作目录
    this->Package = this->ConfigFileDir + "/package;" + this->Package;  // 配置文件目录
    this->Package = this->ConfigFileDir + ";" + this->Package;          // 配置文件目录

    this->coord->LogInfo(R"(
/---------------------------/
/                           /       
/                           /       
/       coord               /       
/                           /       
/                           /       
/-------------------------- /)");

    this->coord->LogInfo("[%s] Version: %s", TAG, this->Version.c_str());
    this->coord->LogInfo("[%s] Config File Dir: %s", TAG, this->ConfigFileDir.c_str());
    this->coord->LogInfo("[%s] Config File Path: %s", TAG, this->ConfigFilePath.c_str());
    this->coord->LogInfo("[%s] Working Dir: %s", TAG, this->WorkingDir.c_str());
    this->coord->LogInfo("[%s] ExecPath: %s", TAG, this->ExecPath.c_str());
    this->coord->LogInfo("[%s] ExecDir: %s", TAG, this->ExecDir.c_str());
    this->coord->LogInfo("[%s] CoordDir: %s", TAG, this->CoordDir.c_str());
    this->coord->LogInfo("[%s] ProjectDir: %s", TAG, this->ProjectDir.c_str());
    this->coord->LogInfo("[%s] Package: %s", TAG, this->Package.c_str());
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
