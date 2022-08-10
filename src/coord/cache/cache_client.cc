#include "coord/cache/cache_client.h"
#include "coord/cache/cache_reader.h"
#include "coord/redis/redis_client.h"
#include "coord/redis/redis_result.h"
#include "coord/coord.h"
#include "coord/builtin/exception.h"
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
        auto reply = this->client->SETEX(key, data, len, expire);
        if (reply.Error()) {
            return -1;
        }
    } else {
        auto reply = this->client->SET(key, data, len);
        if (reply.Error()) {
            return -1;
        }
    }
    return 0;
}

CacheReader Client::Get(const char* key) {
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    auto reply = this->client->GET(key);
    return CacheReader(this->coord, reply);
}

int Client::Delete(const char* key) {
    if(this->client == nullptr){
        throw NotConfigException("cache");
    }
    auto reply = this->client->DEL(key);
    if (reply.Error()) {
        return -1;
    }
    return 0;
}

}}     
