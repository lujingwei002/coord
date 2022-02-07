#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include <libuv/uv.h>
#include <map>
#include <tuple>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export

class Coord;
class BaseRequest;
class RequestPipeline : public Destoryable { //tolua_export
public:
    RequestPipeline(Coord* coord, BaseRequest* request);
    virtual ~RequestPipeline();
public:
    
public:
    Coord*          coord;
    BaseRequest*    request;
};//tolua_export

RequestPipeline* newRequestPipeline(Coord* coord, BaseRequest* request);
}//tolua_export