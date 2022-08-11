#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/redis/redis_config.h"
#include "coord/redis/redis_result.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

///
/// #example
/// ```c++
/// auto client = redis::newClient(coorda);
/// auto config = client->DefaultConfig();
/// config->Host = "127.0.0.1";
/// config->Password = "123456"
/// config->Port = 6379;
/// config->DB = "2"
/// client->Connect();
/// ```
///

namespace coord {
    class Coord;
    namespace redis {
        class RedisResult;
        class RedisMgr;
    }
}

namespace coord {//tolua_export
namespace redis {//tolua_export


class Client : public Destoryable {//tolua_export
CC_CLASS(Client);
friend Coord;
friend RedisMgr;
private:
    Client(Coord *coord, RedisMgr* redisMgr);
    virtual ~Client();
private:
    Coord*          coord;
    RedisMgr*       redisMgr;
    std::string     name;
    RedisConfig     config;
    redisContext*   context;
protected:
    virtual void onDestory();


public:
    int Connect();                              //tolua_export
    RedisConfig* DefaultConfig();               //tolua_export
    void Close();                               //tolua_export

    /// #connection
    RedisResultPtr SELECT(const char* db);      //tolua_export
    RedisResultPtr AUTH(const char* password);  //tolua_export
    uint64_t TIME();                            //tolua_export

    /// #string 
    RedisResultPtr DEL(const char* key);                                                //tolua_export
    RedisResultPtr GET(const char* key);                                                //tolua_export
    RedisResultPtr SET(const char* key, const char* value);                             //tolua_export
    RedisResultPtr SET(const char* key, const char* data, size_t len);
    int EXPIRE(const char* key, uint64_t expire);                                       //tolua_export
    RedisResultPtr SETEX(const char* key, const char* data, size_t len, size_t expire); //tolua_export
    RedisResultPtr SETEX(const char* key, const char* data, size_t expire);             //tolua_export

    /// #hash
    RedisResultPtr HGETALL(const char* key);                                        //tolua_export
    int HDEL(const char* key, const char* field);                                   //tolua_export
    RedisResultPtr HMSET(const char* key, const char* field, const char* value);    //tolua_export
    RedisResultPtr HMSET(const char* key, const char* field, uint64_t value);       //tolua_export

    /// #set
    RedisResultPtr SADD(const char* key, const char* value);                        //tolua_export
    RedisResultPtr SREM(const char* key, const char* value);                        //tolua_export
};//tolua_export



}//tolua_export
}//tolua_export


