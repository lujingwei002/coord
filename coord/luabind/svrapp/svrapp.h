
#include "net/ae.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}

namespace Svrapp
{
    extern aeEventLoop* ev_loop;
    extern lua_State* L;
    void main(int argc, char** argv);

    int lua_dofile(const char* filepath);
};

int luaopen_svrapp(lua_State *L);
