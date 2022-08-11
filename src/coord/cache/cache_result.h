#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include <vector>
#include <iostream>
#include <map>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
namespace coord {//tolua_export
    

class Coord;
    namespace redis {
        class RedisResult;
}

namespace cache {//tolua_export

class CacheResult : public Destoryable {//tolua_export
CC_CLASS(CacheResult);
public:
    CacheResult(Coord *coord, redis::RedisResult* result);
    virtual ~CacheResult();
public:
    const char* String();//tolua_export
    bool Empty();//tolua_export
    bool Error();//tolua_export
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
public:
    Coord*                  coord;
    redis::RedisResult*     result;
};//tolua_export



}//tolua_export
}//tolua_export


