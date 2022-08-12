#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/base/base_reader.h"
#include "coord/base/base_response.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export

class Coord;
class base_reader;
class base_response;
class base_agent;

class base_request : public RcObject, public base_reader { //tolua_export
CC_CLASS(base_request);
protected:
    base_request(Coord* coord, base_agent* agent);
    virtual ~base_request();
public:
    virtual base_response* GetResponse();
    virtual void DebugLog();
public:
    uint64_t                    Id;
    std::string                 Route;
    uint64_t                    SessionId;  //tolua_export
    uint64_t                    ReqTime; 
protected:
    virtual void onDestory(); 
protected:
    base_agent*                 agent;
    base_response*              response;
};//tolua_export

}//tolua_export
