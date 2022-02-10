#pragma once 

#include "coord/builtin/init.h"
#include "coord/redis/redis_config.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
namespace coord {//tolua_export
    
class Coord;

namespace redis {//tolua_export

enum redis_client_status {
    redis_client_status_nil = 0,
    redis_client_status_connected = 1,
    redis_client_status_connecting = 2,
    redis_client_status_error = 3,
    redis_client_status_closing = 4,
    redis_client_status_closed = 5,
};

class Reply;
class Promise;

class AsyncClient : public Destoryable {//tolua_export
CC_CLASS(AsyncClient);
public:
    AsyncClient(Coord *coord);
    virtual ~AsyncClient();
public:
    Promise* Connect();                                                            //tolua_export
    RedisConfig* DefaultConfig();                                                  //tolua_export
    void Close();                                                                  //tolua_export

    /// #connection                                                 
    Promise* SELECT(const char* db);                                               //tolua_export
    Promise* AUTH(const char* password);                                           //tolua_export

    /// #string
    Promise* DEL(const char* key);                                                 //tolua_export
    Promise* GET(const char* key);                                                 //tolua_export
    Promise* SET(const char* key, const char* value);                              //tolua_export
    Promise* SET(const char* key, const char* data, size_t len);
    Promise* EXPIRE(const char* key, uint64_t expire);                             //tolua_export
    Promise* SETEX(const char* key, const char* data, size_t len, size_t expire);
    Promise* SETEX(const char* key, const char* data, size_t expire);

    /// #hash
    Promise* HGETALL(const char* key);                                             //tolua_export
    Promise* HDEL(const char* key, const char* field);                             //tolua_export
    Promise* HMSET(const char* key, const char* field, const char* value);         //tolua_export
    Promise* HMSET(const char* key, const char* field, uint64_t value);            //tolua_export

    /// #script
    Promise* SCRIPT_LOAD(const char* str);                                         //tolua_export
    Promise* EVALSHA(const char* sha1, const char* format, ...);
public:
    Promise* select(const char* db);                        
    Promise* auth(const char* password); 
    void recvConnectError(const char* error); 
    void recvConnect();
    void recvDisconnectError(const char* error);
    void recvDisconnect();
    void recvGetCallback(Promise* promise, Reply& reply);
    void resolveConnect();
    void rejectConnect();
public:
    RedisConfig                         config;
    Coord*                              coord;
    redisAsyncContext*                  context;
    Promise*                            connectPromise;
    int                                 status;
    std::map<Promise*, Promise*>        promiseDict;
};//tolua_export

AsyncClient* newAsyncClient(Coord *coord);

}//tolua_export
}//tolua_export


