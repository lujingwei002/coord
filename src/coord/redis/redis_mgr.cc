#include "coord/redis/redis_mgr.h"
#include "coord/redis/redis_client.h"
#include "coord/redis/redis_async_client.h"
#include "coord/config/config.h"
#include "coord/coord.h"
namespace coord {
namespace redis {



RedisMgr::RedisMgr(Coord *coord) {
    this->coord = coord;
}

RedisMgr::~RedisMgr() {
    // 清理client
    std::vector<Client*> clientArr;
    for(auto it : this->clientSet) {
        clientArr.push_back(it);
    }
    for(auto it : clientArr) {
        this->coord->Destory(it);
    }
    clientArr.clear();
    this->clientDict.clear();
    this->clientSet.clear();

    // 清理async client
    std::vector<AsyncClient*> asyncClientArr;
    for(auto it : this->asyncClientSet) {
        asyncClientArr.push_back(it);
    }
    for(auto it : asyncClientArr) {
        this->coord->Destory(it);
    }
    asyncClientArr.clear();
    this->asyncClientDict.clear();
    this->asyncClientSet.clear();
}

void RedisMgr::free(Client* client) {
    auto it = this->clientSet.find(client);
    if (it == this->clientSet.end()) {
        return;
    }
    this->clientSet.erase(it);

    auto it2 = this->clientDict.find(client->name);
    if (it2 != this->clientDict.end()) {
        this->clientDict.erase(it2);;
    }
}

void RedisMgr::free(AsyncClient* client) {
   auto it = this->asyncClientSet.find(client);
    if (it == this->asyncClientSet.end()) {
        return;
    }
    this->asyncClientSet.erase(it);

    auto it2 = this->asyncClientDict.find(client->name);
    if (it2 != this->asyncClientDict.end()) {
        this->asyncClientDict.erase(it2);
    }
}

Client* RedisMgr::NewClient() {
    Client* client = new redis::Client(this->coord, this);
    this->clientSet.insert(client);
    return client;
}

Client* RedisMgr::GetClient(const char* name) {
    auto it = this->clientDict.find(name);
    if (it != this->clientDict.end()){
        return it->second;
    }
    RedisConfig config;
    int err = this->coord->Config->RedisConfig(name, &config);
    if (err != 0) {
        this->coord->CoreLogError("[coord::RedisMgr] GetClient.RedisConfig failed, error=%d", err);
        return nullptr; 
    }
    Client* client = this->NewClient();
    client->name = name;
    *(client->DefaultConfig()) = config;
    this->clientDict[name] = client;
    return client;
}

AsyncClient* RedisMgr::NewAsyncClient() {
    AsyncClient* client = new redis::AsyncClient(this->coord, this);
    this->asyncClientSet.insert(client);
    return client;
}

AsyncClient* RedisMgr::GetAsyncClient(const char* name) {
    auto it = this->asyncClientDict.find(name);
    if (it != this->asyncClientDict.end()){
        return it->second;
    }
    RedisConfig config;
    int err = this->coord->Config->RedisConfig(name, &config);
    if (err != 0) {
        this->coord->CoreLogError("[coord::RedisMgr] GetAsyncClient.RedisConfig failed, error=%d", err);
        return NULL;
    }
    AsyncClient* client = this->NewAsyncClient();
    client->name = name;
    *(client->DefaultConfig()) = config;
    this->asyncClientDict[name] = client;
    return client;
}

}
}        
