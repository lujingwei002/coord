#include "coord/run/running.h"
#include "coord/builtin/init.h"
#include "coord/builtin/environment.h"
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
#include "coord/run/managed_pipe_server.h"

namespace coord {
namespace run {
static const char* TAG = "Running";

Running::Running(Coord* coord) {
    this->coord = coord;
    this->server = nullptr;
}
Running::~Running() { 

    if(nullptr == this->server) {
        delete this->server;
        this->server = nullptr;
    }
}

int Running::main() {
    // 环境初始化
    // 切换工作目录
    int err = uv_chdir(this->coord->Environment->WorkingDir.c_str());
    if (err) {
        return err;
    }
    this->Pid = uv_os_getpid();
    if (!coord::path::Exists(this->coord->Environment->ProcDir)){
        return ErrorNoSuchFileOrDirectory;
    }
    if (coord::path::Exists(this->coord->Environment->RunDir)){
        return ErrorRunning;
    }
    err = coord::path::MakeDir(this->coord->Environment->RunDir, 0755);
    if (err) {
        return err;
    }
    err = coord::path::FileLock(this->coord->Environment->PidPath);
    if (err) {
        return err;
    }
    //记录Pid
    std::ofstream outfile(this->coord->Environment->PidPath, std::ios::trunc);
    outfile << this->Pid << std::endl;
    //开启管道
    this->server = newManagedPipeServer(this->coord, this);
    err = this->server->start();
    if (err) {
        return err;
    }
    return 0;
}

void Running::onDestory() {
    int err = coord::path::RemoveDirRecursive(this->coord->Environment->RunDir);
    if (err){
        this->coord->CoreLogError("[%s] RemoveDir failed, error=%d", TAG, err);
    }
}

}
}
