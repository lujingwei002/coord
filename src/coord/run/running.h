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

namespace coord {//tolua_export
class Coord;
namespace run { //tolua_export

class Running {//tolua_export
friend class coord::Coord;
private:
    Running(Coord* coord);
    ~Running();
private:
    int main();
    void onDestory();
private:
    Coord*                  coord;
};//tolua_export

}//tolua_export

}//tolua_export
