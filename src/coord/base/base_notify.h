#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/base/base_reader.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {
    class Coord;
    class base_reader;
    class base_agent;
}

namespace coord {//tolua_export


class base_notify : public RcObject, public base_reader { //tolua_export
CC_CLASS(base_notify);
public:
    base_notify(Coord* coord, base_agent* agent);
    virtual ~base_notify();
public:
    virtual void onDestory(); 
public:
    std::string     Route;
    uint64_t        ReqTime; 
protected:
    base_agent*     agent;
};//tolua_export

}//tolua_export


