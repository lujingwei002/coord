#include "coord/cache/cache_async_client.h"
#include "coord/cache/cache_result.h"
#include "coord/cache/cache_promise.h"
#include "coord/redis/init.h"
#include "coord/coord.h"
#include "coord/coordx.h"
namespace coord {
namespace cache {

RC_IMPLEMENT(AsyncClient, "coord::cache::AsyncClient")

AsyncClient* newAsyncClient(Coord *coord) {
    AsyncClient* self = new AsyncClient(coord);
    return self;
}

AsyncClient::AsyncClient(Coord *coord) {
    this->coord = coord;
    this->client = nullptr;
}   

AsyncClient::~AsyncClient() {
    if(this->client){
        this->client->Close();
        this->coord->Destory(this->client);
        this->client = nullptr;
    }
}

CacheConfig* AsyncClient::DefaultConfig() {
    return &this->config;
}

void AsyncClient::destory() {
    if(this->client){
        this->client->Close();
        this->coord->Destory(this->client);
        this->client = nullptr;
    }
}

Promise* AsyncClient::main() {
    if(this->client != nullptr){
        return nullptr;
    }
    auto client = this->coord->NewAsyncRedisClient();
    auto config = client->DefaultConfig();
    config->Host = this->config.Host;
    config->Port = this->config.Port;
    config->Password = this->config.Password;
    config->DB = this->config.DB;

    Promise* promise = cache::newPromise(this->coord, this);
    if (promise == nullptr) {
        this->coord->Destory(client);
        return nullptr;
    }
    auto p = client->Connect();
    if (p == nullptr) {
        this->coord->Destory(client);
        this->coord->Destory(promise);
        return nullptr;
    }
    p->Then([this, promise](auto client, auto reply){
       // CacheResult result = new CacheResult(this->coord, nullptr);
        promise->resolve(this, nullptr);
        this->coord->Destory(promise);
    });
    p->Else([this, promise](auto client, auto reply){
       // CacheResult result = new CacheResult(this->coord, nullptr);
        promise->reject(this, nullptr);
        this->coord->Destory(promise);
    });
    this->client = client;
    return promise;
}

Promise* AsyncClient::Set(const char* key, const char* data, size_t expire) {
    return this->Set(key, data, strlen(data), expire);
}

Promise* AsyncClient::Set(const char* key, const char* data, size_t len, size_t expire){
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    if (expire <= 0) {
        expire = this->config.ExpireTime;
    }
    if (expire > 0){
        auto p = this->client->SETEX(key, data, len, expire);
        if (p == nullptr) {
            return nullptr;
        }
        Promise* promise = cache::newPromise(this->coord, this);
        p->Then([this, promise](auto client, auto reply){
            auto result = new CacheResult(this->coord, reply);
            promise->resolve(this, result);
            this->coord->Destory(promise);
            this->coord->Destory(result);
        });
        p->Else([this, promise](auto client, auto reply) {
            auto result = new CacheResult(this->coord, reply);
            promise->reject(this, result);
            this->coord->Destory(promise);
            this->coord->Destory(result);
        });
        return promise;
    } else {
        auto p = this->client->SET(key, data, len);
        if (p == nullptr) {
            return nullptr;
        }
        Promise* promise = cache::newPromise(this->coord, this);
        p->Then([this, promise](auto client, auto reply){
            auto result = new CacheResult(this->coord, reply);
            promise->resolve(this, result);
            this->coord->Destory(promise);
            this->coord->Destory(result);
        });
        p->Else([this, promise](auto client, auto reply) {
            auto result = new CacheResult(this->coord, reply);
            promise->reject(this, result);
            this->coord->Destory(promise);
            this->coord->Destory(result);
        });
        return promise;
    }
    return nullptr;
}

Promise* AsyncClient::Get(const char* key) {
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    auto p = this->client->GET(key);
    if (p == nullptr) {
        return nullptr;
    }
    Promise* promise = cache::newPromise(this->coord, this);
    p->Then([this, promise](auto client, auto reply){
        auto result = new CacheResult(this->coord, reply);
        promise->resolve(this, result);
        this->coord->Destory(promise);
        this->coord->Destory(result);
    });
    p->Else([this, promise](auto client, auto reply) {
        auto result = new CacheResult(this->coord, reply);
        promise->reject(this, result);
        this->coord->Destory(promise);
        this->coord->Destory(result);
    });
    return promise;
}

Promise* AsyncClient::Delete(const char* key) {
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    auto p = this->client->DEL(key);
    if (p == nullptr) {
        return nullptr;
    }
    Promise* promise = cache::newPromise(this->coord, this);
    p->Then([this, promise](auto client, auto reply){
        auto result = new CacheResult(this->coord, reply);
        promise->resolve(this, result);
        this->coord->Destory(promise);
        this->coord->Destory(result);
    });
    p->Else([this, promise](auto client, auto reply) {
        auto result = new CacheResult(this->coord, reply);
        promise->reject(this, result);
        this->coord->Destory(promise);
        this->coord->Destory(result);
    });
    return promise;
}

}}     
