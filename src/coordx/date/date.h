#pragma once 

#include <stdint.h>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
namespace coordx {//tolua_export
namespace date { //tolua_export

    const char* FormatNano(uint64_t nano);
     
} //tolua_export
}//tolua_export


