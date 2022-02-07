#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include <libuv/uv.h>
#include <map>
#include <tuple>
#include "coord/builtin/slice.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export
class Coord;

namespace managed {//tolua_export
class ManagedAgent;
class ManagedServer;

class ManagedRequest : public Destoryable  { //tolua_export
CC_CLASS(ManagedRequest);
public:
    ManagedRequest(Coord* coord, ManagedAgent* agent);
    virtual ~ManagedRequest();
public:
    size_t Count();
    const char* Arg(size_t i);
    
public:
    int parse(const char*data, size_t len);
    
public:
    ManagedAgent* agent; 
    Coord* coord;
    std::vector<std::string> args;
};//tolua_export

ManagedRequest* newManagedRequest(Coord* coord, ManagedAgent* agent);

}//tolua_export
}//tolua_export


