#include "coord/coord.h"

extern "C"
{
    int luaopen_loginsvr(lua_State* tolua_S);
}

int onAwake(coord::Coord* coorda) {
    //coorda->CloseLogLevel(coord::log::DEBUG);
    int err = coorda->Script->Import(luaopen_loginsvr);
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