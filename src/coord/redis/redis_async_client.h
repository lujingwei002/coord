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
namespace coord {
    class Coord;
    namespace redis {
        class Reply;
        class RedisPromise;
        class RedisMgr;
    }
}

namespace coord {//tolua_export
    


namespace redis {//tolua_export



class AsyncClient : public Destoryable {//tolua_export
CC_CLASS(AsyncClient);
friend RedisMgr;
friend Coord;
private:
    AsyncClient(Coord *coord, RedisMgr* redisMgr);
    virtual ~AsyncClient();
private:
    static void getCallback(redisAsyncContext *c, void *data, void *privdata);
    static void disconnectCallback(const redisAsyncContext* c, int status);
    static void connectCallback(const redisAsyncContext* c, int status);
    RedisPromise* select(const char* db);                        
    RedisPromise* auth(const char* password); 
    void recvConnectError(const char* error); 
    void recvConnect();
    void recvDisconnectError(const char* error);
    void recvDisconnect();
    void recvGetCallback(RedisPromise* promise, const Reply& reply);
    void resolveConnect();
    void rejectConnect();
private:
    RedisMgr*                           redisMgr;
    std::string                         name;
    RedisConfig                         config;
    Coord*                              coord;
    redisAsyncContext*                  context;
    RedisPromise*                       connectPromise;
    int                                 status;
    std::map<RedisPromise*, RedisPromise*>        promiseDict;




public:
    RedisPromise* Connect();                                                            //tolua_export
    RedisConfig* DefaultConfig();                                                  //tolua_export
    void Close();                                                                  //tolua_export

    /// #connection                                                 
    RedisPromise* SELECT(const char* db);                                               //tolua_export
    RedisPromise* AUTH(const char* password);                                           //tolua_export

    /// #string
    RedisPromise* DEL(const char* key);                                                 //tolua_export
    RedisPromise* GET(const char* key);                                                 //tolua_export
    RedisPromise* SET(const char* key, const char* value);                              //tolua_export
    RedisPromise* SET(const char* key, const char* data, size_t len);
    RedisPromise* EXPIRE(const char* key, uint64_t expire);                             //tolua_export
    RedisPromise* SETEX(const char* key, const char* data, size_t len, size_t expire);
    RedisPromise* SETEX(const char* key, const char* data, size_t expire);

    /// #hash
    RedisPromise* HGETALL(const char* key);                                             //tolua_export
    RedisPromise* HDEL(const char* key, const char* field);                             //tolua_export
    RedisPromise* HMSET(const char* key, const char* field, const char* value);         //tolua_export
    RedisPromise* HMSET(const char* key, const char* field, uint64_t value);            //tolua_export

    /// #script
    RedisPromise* SCRIPT_LOAD(const char* str);                                         //tolua_export
    RedisPromise* EVALSHA(const char* sha1, const char* format, ...);
};//tolua_export



}//tolua_export
}//tolua_export


