#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/redis/redis_reply.h"
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
class Reply;
}
namespace cache {//tolua_export

class CacheReader : public Destoryable {//tolua_export
CC_CLASS(CacheReader);
public:
    CacheReader(std::nullptr_t);
    CacheReader(Coord *coord, const redis::Reply* reply);
    CacheReader(Coord *coord, const redis::Reply& reply);
    virtual ~CacheReader();
public:
    const char* String();//tolua_export
    bool Empty();//tolua_export
    bool Error();//tolua_export
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
public:
    Coord*              coord;
    redis::Reply        reply;
};//tolua_export

inline bool CacheReader::Empty() {return this->reply.Empty();}
inline bool CacheReader::Error() {return this->reply.Error();}

CacheReader* newCacheReader(Coord* coord, const redis::Reply* conn);
}//tolua_export
}//tolua_export


