#include "coord/coord.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

extern "C"
{
    int luaopen_hostd(lua_State* tolua_S);
}

int onAwake(coord::Coord* coorda) {
    //coorda->CloseLogLevel(coord::log::DEBUG);
    int err = coorda->script->Import(luaopen_hostd);
    if (err) {
        return err;
    }
    return 0;
}

void onDestory(coord::Coord* coorda) {
    
}

int main(int argc, const char** argv) {
    return coord::Main(argc, argv);
}