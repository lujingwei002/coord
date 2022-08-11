#pragma once 

#include "coord/component/component.h"
#include "coord/redis/redis_result.h"
#include <uv.h>
#include <map>
#include <string>

namespace coord {

class Coord;
namespace redis {
class AsyncClient;
class Client;
class RedisResult;
class RedisPromise;
}

namespace login {

class LoginSvr;

class login_cluster {
public:
    login_cluster(Coord* coord, LoginSvr* loginSvr);
    virtual ~login_cluster();
public:
    int main();
    void recvConnectCacheSucc(redis::AsyncClient* client, const redis::RedisResultPtr& reply);
    void recvConnectCacheErr(redis::AsyncClient* client, const redis::RedisResultPtr& reply);
    void recvCacheScriptLoadSucc(redis::AsyncClient* client, const redis::RedisResultPtr& reply, const char* name);
    void recvCacheScriptLoadError(redis::AsyncClient* client, const redis::RedisResultPtr& reply);
    redis::RedisPromise* getRanomGate();
    redis::RedisPromise* getBalanceGate();
    redis::RedisPromise* listGate();
public:
    Coord*                              coord;
    LoginSvr*                           loginSvr;
    redis::AsyncClient*                 asyncClient;
    redis::Client*                      syncClient;
    std::string                         group;
    std::string                         gateSetKey;
    std::map<std::string, std::string>  scriptShaDict;          // lua script sha
};

login_cluster* newLoginCluster(Coord* coord, LoginSvr* loginSvr);


}
}