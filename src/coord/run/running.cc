#include "coord/run/running.h"
#include "coord/builtin/init.h"
#include "coord/environment/environment.h"
#include "coord/coord.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <uv.h>
#include <ctype.h>
#include "coord/builtin/string.h"
#include "coord/builtin/error.h"

namespace coord {
namespace run {
static const char* TAG = "Running";

Running::Running(Coord* coord) {
    this->coord = coord;
}
Running::~Running() { 
}

int Running::main() {
    // 环境初始化
    // 切换工作目录
    // int err = uv_chdir(this->coord->Environment->WorkingDir.c_str());
    // if (err) {
    //     return err;
    // }
    if (!coord::path::Exists(this->coord->Environment->ProcDir)){
        return ErrorNoSuchFileOrDirectory;
    }
    if (coord::path::Exists(this->coord->Environment->RunDir)){
        return ErrorRunning;
    }
    int err = coord::path::MakeDir(this->coord->Environment->RunDir, 0755);
    if (err) {
        return err;
    }
    err = coord::path::FileLock(this->coord->Environment->PidPath);
    if (err) {
        return err;
    }
    //记录Pid
    std::ofstream outfile(this->coord->Environment->PidPath, std::ios::trunc);
    outfile << this->coord->Environment->Pid << std::endl;
    return 0;
}

void Running::onDestory() {
    auto environment = this->coord->Environment;
    if (environment->RunDir.length() > 0) {
        int err = coord::path::RemoveDirRecursive(environment->RunDir);
        if (err){
            this->coord->CoreLogError("[%s] RemoveDir failed, error=%d", TAG, err);
        }
    }
}

}
}
