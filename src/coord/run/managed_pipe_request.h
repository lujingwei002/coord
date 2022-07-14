#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include <uv.h>
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

namespace run {//tolua_export
class ManagedPipeAgent;
class ManagedPipeServer;

class ManagedPipeRequest : public Destoryable  { //tolua_export
CC_CLASS(ManagedPipeRequest);
public:
    ManagedPipeRequest(Coord* coord, ManagedPipeAgent* agent);
    virtual ~ManagedPipeRequest();
public:
    size_t Count();
    const char* Arg(size_t i);
    
public:
    int parse(const char*data, size_t len);
    
public:
    ManagedPipeAgent*           agent; 
    Coord*                      coord;
    std::vector<std::string>    args;
};//tolua_export

ManagedPipeRequest* newManagedPipeRequest(Coord* coord, ManagedPipeAgent* agent);

}//tolua_export
}//tolua_export


