#include "coord/cache/cache_client.h"
#include "coord/cache/cache_result.h"
#include "coord/redis/init.h"
#include "coord/coord.h"
#include "coord/coordx.h"
namespace coord {
namespace cache {

CC_IMPLEMENT(Client, "coord::cache::Client")

Client* newClient(Coord *coord) {
    Client* self = new Client(coord);
    return self;
}

Client::Client(Coord *coord) {
    this->coord = coord;
    this->client = nullptr;
}   

Client::~Client() {
    if(this->client){
        this->client->Close();
        this->coord->Destory(this->client);
        this->client = nullptr;
    }
}

CacheConfig* Client::DefaultConfig() {
    return &this->config;
}

void Client::destory() {
    if(this->client){
        this->client->Close();
        this->coord->Destory(this->client);
        this->client = nullptr;
    }
}

int Client::main() {
    if(this->client != nullptr){
        return -1;
    }
    auto client = this->coord->NewRedisClient();
    auto config = client->DefaultConfig();
    config->Host = this->config.Host;
    config->Port = this->config.Port;
    config->Password = this->config.Password;
    config->DB = this->config.DB;
    int err = client->Connect();
    if (err < 0) {
        this->coord->Destory(client);
        return err;
    }
    this->client = client;
    return 0;
}

int Client::Set(const char* key, const char* data, size_t expire) {
    return this->Set(key, data, strlen(data), expire);
}

int Client::Set(const char* key, const char* data, size_t len, size_t expire){
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    if (expire <= 0) {
        expire = this->config.ExpireTime;
    }
    if (expire > 0){
        auto result = this->client->SETEX(key, data, len, expire);
        if (result->Error()) {
            return -1;
        }
    } else {
        auto result = this->client->SET(key, data, len);
        if (result->Error()) {
            return -1;
        }
    }
    return 0;
}

CacheResult* Client::Get(const char* key) {
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    auto result = this->client->GET(key);
    return new CacheResult(this->coord, result);
}

int Client::Delete(const char* key) {
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    auto result = this->client->DEL(key);
    if (result->Error()) {
        return -1;
    }
    return 0;
}

}}     
