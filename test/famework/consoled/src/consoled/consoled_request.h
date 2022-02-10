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

namespace consoled {//tolua_export
class ConsoledAgent;
class ConsoledServer;

class ConsoledRequest : public coord::Destoryable  { //tolua_export
CC_CLASS(ConsoledRequest);
public:
    ConsoledRequest(coord::Coord* coord, ConsoledAgent* agent);
    virtual ~ConsoledRequest();
public:
    size_t Count();
    const char* Arg(size_t i);
    
public:
    int parse(const char*data, size_t len);
    
public:
    ConsoledAgent* agent; 
    coord::Coord* coord;
    std::vector<std::string> args;
};//tolua_export

ConsoledRequest* newConsoledRequest(coord::Coord* coord, ConsoledAgent* agent);

}//tolua_export


