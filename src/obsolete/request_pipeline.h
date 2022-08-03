#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include <uv.h>
#include <map>
#include <tuple>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export

class Coord;
class IRequest;
class RequestPipeline : public Destoryable { //tolua_export
public:
    RequestPipeline(Coord* coord, IRequest* request);
    virtual ~RequestPipeline();
public:
    Coord*      coord;
    IRequest*   request;
};//tolua_export

RequestPipeline* newRequestPipeline(Coord* coord, IRequest* request);
}//tolua_export
