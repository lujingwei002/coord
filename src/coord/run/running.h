#pragma once 

#include <uv.h>
#include <map>
#include <string>
#include <optional>
#include <algorithm>
#include <cctype>
#include <functional>
#include <cstring>
#include <iostream>
#include <list>
#include <locale>
#include <sstream>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

#include "coord/run/run_config.h"
namespace coord {//tolua_export
class Coord;
namespace run { //tolua_export

class ManagedPipeServer;
class Running {//tolua_export
friend class coord::Coord;
friend class coord::run::ManagedPipeServer;
private:
    Running(Coord* coord);
    ~Running();
public:
    uv_pid_t    Pid;
private:
    int main();
    void onDestory();
private:
    Coord*                  coord;
    RunConfig               config;
    ManagedPipeServer*      server;
};//tolua_export

}//tolua_export

}//tolua_export
