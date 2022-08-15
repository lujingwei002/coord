#pragma once 

#include "coord/coordx.h"
#include "coord/cache/cache_config.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

/// #example
/// ```c++
///     auto reader = coorda->Cache->Get("k");
///     if (reader.Error()) {
///         return;
///     }
///     coorda->LogDebug("Value is %s", reader.String());
/// ```    

namespace coord {
    
class Coord;
    namespace redis {
        class Client;
    }
    namespace cache {
        class CacheResult;
        class Promise;
    }
}

namespace coord {//tolua_export
namespace cache {//tolua_export



class Client {//tolua_export
CC_CLASS(Client);
public:
    Client(Coord *coord);
    virtual ~Client();           
public:  
    /// 获取配置对象                               
    CacheConfig* DefaultConfig(); 
    /// 读取key         
    CacheResult* Get(const char* key);       
    /// 设置key=value, 过期时间为expire                               
    int Set(const char* key, const char* value, size_t expire);     
    /// 设置key=value, 过期时间为expire              
    int Set(const char* key, const char* value, size_t len, size_t expire);  
    /// 删除key
    int Delete(const char* key);   
public:
    int main();                                                                                                       
    void destory();                                                                                     
public:
    CacheConfig         config;
    Coord*              coord;
    redis::Client*      client;
};//tolua_export

Client* newClient(Coord *coord);

}//tolua_export
}//tolua_export


