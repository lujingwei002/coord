#pragma once 

#include "coord/coordx.h"
#include "coord/redis/declare.h"
#include <vector>
#include <iostream>
#include <map>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

namespace coord {
class Coord;
}

namespace coord {//tolua_export
namespace cache {//tolua_export

class CacheResult : public coordx::RcObject {//tolua_export
CC_CLASS(CacheResult);
public:
    CacheResult(Coord *coord, const redis::RedisResultRef& result);
    virtual ~CacheResult();
public:
    const char* String();//tolua_export
    bool Empty();//tolua_export
    bool Error();//tolua_export
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
public:
    Coord*                  coord;
    redis::RedisResultRef   result;
};//tolua_export



}//tolua_export
}//tolua_export


