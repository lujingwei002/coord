#pragma once 

#include "coord/component/component.h"
#include <uv.h>
#include <map>
#include <string>

namespace coord {

class Coord;
namespace redis {
class AsyncClient;
class Client;
class Reply;
class Promise;
}

namespace login {

class LoginSvr;

class login_cluster {
public:
    login_cluster(Coord* coord, LoginSvr* loginSvr);
    virtual ~login_cluster();
public:
    int main();
    void recvConnectCacheSucc(redis::AsyncClient* client, redis::Reply& reply);
    void recvConnectCacheErr(redis::AsyncClient* client, redis::Reply& reply);
    void recvCacheScriptLoadSucc(redis::AsyncClient* client, redis::Reply& reply, const char* name);
    void recvCacheScriptLoadError(redis::AsyncClient* client, redis::Reply& reply);
    redis::Promise* getRanomGate();
    redis::Promise* getBalanceGate();
    redis::Promise* listGate();
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