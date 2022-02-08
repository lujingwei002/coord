#pragma once 

#include "coord/builtin/type.h"
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
///
///
///
namespace redis {//tolua_export

class Reply;

class Client {//tolua_export
CC_CLASS(Client);
public:
    Client(Coord *coord);
    virtual ~Client();
public:
    int Connect();                              //tolua_export
    RedisConfig* DefaultConfig();               //tolua_export
    void Close();                               //tolua_export

    /// #connection
    Reply SELECT(const char* db);               //tolua_export
    Reply AUTH(const char* password);           //tolua_export
    uint64_t TIME();                            //tolua_export

    /// #string 
    Reply DEL(const char* key);                                            //tolua_export
    Reply GET(const char* key);                                            //tolua_export
    Reply SET(const char* key, const char* value);                         //tolua_export
    Reply SET(const char* key, const char* data, size_t len);
    int EXPIRE(const char* key, uint64_t expire);//tolua_export
    Reply SETEX(const char* key, const char* data, size_t len, size_t expire);
    Reply SETEX(const char* key, const char* data, size_t expire);

    /// #hash
    Reply HGETALL(const char* key);                                        //tolua_export
    int HDEL(const char* key, const char* field);                          //tolua_export
    Reply HMSET(const char* key, const char* field, const char* value);    //tolua_export
    Reply HMSET(const char* key, const char* field, uint64_t value);       //tolua_export

    /// #set
    Reply SADD(const char* key, const char* value);
    Reply SREM(const char* key, const char* value);
public:
    RedisConfig     config;
    Coord*          coord;
    redisContext*   context;
};//tolua_export

Client* newClient(Coord *coord);

}//tolua_export
}//tolua_export


