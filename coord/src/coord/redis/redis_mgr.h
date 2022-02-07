#pragma once 

#include "coord/builtin/type.h"
#include "coord/redis/redis_config.h"
#include <libuv/uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>

namespace coord {//tolua_export
    
class Coord;

namespace redis {//tolua_export

class Client;
class AsyncClient;

class RedisMgr {//tolua_export
public:
    RedisMgr(Coord *coord);
    virtual ~RedisMgr();
public:
    Client* GetClient(const char* name);
    AsyncClient* GetAsyncClient(const char* name);
    void Free(Client* conn);
    void Free(AsyncClient* conn);
public:
    std::map<std::string, Client*>      clientDict;
    std::map<std::string, AsyncClient*> asyncClientDict;
    Coord*                              coord;
};//tolua_export

RedisMgr* newRedisMgr(Coord* coord);
}//tolua_export
}//tolua_export


