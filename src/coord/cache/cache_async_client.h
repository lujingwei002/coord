#pragma once 

#include "coord/builtin/inc.h"
#include "coord/cache/cache_config.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
namespace coord {//tolua_export
    
class Coord;
namespace redis {
class AsyncClient;
}
namespace cache {//tolua_export


class CacheResult;
class Promise;

class AsyncClient : public RcObject {//tolua_export
CC_CLASS(AsyncClient);
public:
    AsyncClient(Coord *coord);
    virtual ~AsyncClient();            
public:       
    CacheConfig* DefaultConfig();
    Promise* Get(const char* key); 
    Promise* Set(const char* key, const char* value, size_t expire); 
    Promise* Set(const char* key, const char* value, size_t len, size_t expire); 
    Promise* Delete(const char* key);  
public:
    Promise* main();                                                                                                       
    void destory();                                                                                                           
public:
    CacheConfig             config;
    Coord*                  coord;
    redis::AsyncClient*     client;
};//tolua_export

AsyncClient* newAsyncClient(Coord *coord);

}//tolua_export
}//tolua_export


