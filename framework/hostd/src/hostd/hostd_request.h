#pragma once 

#include "coord/builtin/init.h"
#include <libuv/uv.h>
#include <map>
#include <tuple>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {
class Coord;
}

namespace hostd {//tolua_export
class HostdAgent;
class HostdServer;

class HostdRequest : public coord::Destoryable  { //tolua_export
CC_CLASS(HostdRequest);
public:
    HostdRequest(coord::Coord* coord, HostdAgent* agent);
    virtual ~HostdRequest();
public:
    size_t Count();
    const char* Arg(size_t i);
    
public:
    int parse(const char*data, size_t len);
    
public:
    HostdAgent* agent; 
    coord::Coord* coord;
    std::vector<std::string> args;
};//tolua_export

HostdRequest* newHostdRequest(coord::Coord* coord, HostdAgent* agent);

}//tolua_export


