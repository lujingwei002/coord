#include "coord/redis/redis_mgr.h"
#include "coord/redis/redis_client.h"
#include "coord/redis/redis_async_client.h"
#include "coord/config/config.h"
#include "coord/coord.h"
namespace coord {
namespace redis {


RedisMgr* newRedisMgr(Coord* coord) {
    auto mgr = new RedisMgr(coord);
    return mgr;
}

RedisMgr::RedisMgr(Coord *coord) {
    this->coord = coord;
}

RedisMgr::~RedisMgr() {
    for(auto it = this->clientDict.begin(); it != this->clientDict.end();) {
        Client* client = it->second;
        delete client;
        ++it;
    }
    this->clientDict.clear();
    for(auto it = this->asyncClientDict.begin(); it != this->asyncClientDict.end();) {
        AsyncClient* client = it->second;
        delete client;
        ++it;
    }
    this->asyncClientDict.clear();
}

void RedisMgr::Free(Client* conn) {
    delete conn;
}

Client* RedisMgr::GetClient(const char* name) {
    auto it = this->clientDict.find(name);
    if (it != this->clientDict.end()){
        return it->second;
    }
    RedisConfig config;
    int err = this->coord->config->RedisConfig(name, &config);
    if (err != 0) {
        this->coord->coreLogError("[coord::RedisMgr] GetClient.RedisConfig failed, error=%d", err);
        return NULL; 
    }
    Client* client = newClient(this->coord);
    *(client->DefaultConfig()) = config;
    this->clientDict[name] = client;
    return client;
}

AsyncClient* RedisMgr::GetAsyncClient(const char* name) {
    auto it = this->asyncClientDict.find(name);
    if (it != this->asyncClientDict.end()){
        return it->second;
    }
    RedisConfig config;
    int err = this->coord->config->RedisConfig(name, &config);
    if (err != 0) {
        this->coord->coreLogError("[coord::RedisMgr] GetAsyncClient.RedisConfig failed, error=%d", err);
        return NULL;
    }
    AsyncClient* client = newAsyncClient(this->coord);
    *(client->DefaultConfig()) = config;
    this->asyncClientDict[name] = client;
    return client;
}

}
}        
