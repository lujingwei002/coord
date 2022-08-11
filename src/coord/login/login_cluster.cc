#include "coord/login/login_cluster.h"
#include "coord/login/login.h"
#include "coord/http/init.h"
#include "coord/net/url.h"
#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_client.h"
#include "coord/redis/redis_promise.h"
#include "coord/redis/redis_result.h"
#include "coord/coord.h"

namespace coord {
namespace login {

login_cluster* newLoginCluster(Coord* coord, LoginSvr* loginSvr) {
    login_cluster* self = new login_cluster(coord, loginSvr);
    return self;
}

login_cluster::login_cluster(Coord* coord, LoginSvr* loginSvr) {
    this->coord = coord;
    this->loginSvr = loginSvr;
    this->asyncClient = NULL;
    this->syncClient = NULL;
}

login_cluster::~login_cluster() {
    if(this->asyncClient != NULL) {
        this->coord->Destory(this->asyncClient);
        this->asyncClient = NULL;
    }
    if(this->syncClient != NULL) {
        this->coord->Destory(syncClient);
        this->syncClient = NULL;
    }
}

int login_cluster::main() {
    if(this->syncClient != NULL) {
        return -1;
    }
    auto loginConfig = this->loginSvr->DefaultConfig();
    //同步连接
    {
        net::Url url;
        int err = url.Parse(loginConfig->Cluster.c_str(), loginConfig->Cluster.length());
        if (err < 0){
            this->coord->CoreLogError("[login_cluster] main.http_parser_parse_url failed, error=%d", err);
            return err;
        }
        redis::Client* client = this->coord->NewRedisClient();
        auto config = client->DefaultConfig();
        config->Host = url.Host;
        config->Port = url.Port;
        config->Password = url.Password;
        size_t dbIndex = url.Path.find("/");
        if (dbIndex == std::string::npos) {
            this->coord->CoreLogError("[login_cluster] main failed, func='http_parser_parse_url', url=%s, error='url format err'", loginConfig->Cluster.c_str());
            this->coord->Destory(client);
            return -1;
        }
        size_t keyIndex = url.Path.find("/", dbIndex + 1);
        if (keyIndex == std::string::npos) {
            this->coord->CoreLogError("[login_cluster] main failed, func='http_parser_parse_url', url=%s, error='url format err'", loginConfig->Cluster.c_str());
            this->coord->Destory(client);
            return -1;
        }
        config->DB = url.Path.substr(dbIndex + 1, keyIndex - dbIndex - 1);
        this->group = url.Path.substr(keyIndex + 1);
        err = client->Connect();
        if (err < 0){
            this->coord->Destory(client);
            this->coord->CoreLogError("[login_cluster] main failed, func='client->Connect' failed, error='%d'", err);
            return err;
        }
        this->syncClient = client;
        this->coord->CoreLogDebug("[login_cluster] main, host=%s, port=%d, db=%s, group=%s", config->Host.c_str(), config->Port, config->DB.c_str(), this->group.c_str());
    }
    //异步链接
    {
        redis::AsyncClient* client = this->coord->NewAsyncRedisClient();
        *(client->DefaultConfig()) = *(this->syncClient->DefaultConfig());
        auto promise = client->Connect();
        if (promise == NULL) {
            this->coord->Destory(client);
            this->coord->CoreLogError("[login_cluster] main failed, func='client->Connect'");
            return -1;
        }
        promise->Then(std::bind(&login_cluster::recvConnectCacheSucc, this, std::placeholders::_1, std::placeholders::_2));
        promise->Else(std::bind(&login_cluster::recvConnectCacheErr, this, std::placeholders::_1, std::placeholders::_2));
        this->asyncClient = client;
    }
    this->gateSetKey = this->group;
    return 0;
}

void login_cluster::recvConnectCacheSucc(redis::AsyncClient* client, const redis::RedisResultPtr& reply) {
    this->coord->CoreLogError("[login_cluster] recvConnectCacheSucc %s", reply->String());

    auto promise = this->asyncClient->SCRIPT_LOAD(R"(
        while true do
            local v = redis.call('SRANDMEMBER', KEYS[1]) 
            if not v then 
                return v 
            end 
            local rkey = ARGV[1]..':'..v
            if redis.call('EXISTS', rkey) then
                return redis.call('HMGET', rkey, 'address', 'host', 'port', 'online', 'version') 
            else
                redis.call('SREM', KEYS[1], v) 
            end
        end
        return nil
        )"
    );
    promise->Then(std::bind(&login_cluster::recvCacheScriptLoadSucc, this, std::placeholders::_1, std::placeholders::_2, "random"));
    promise->Else(std::bind(&login_cluster::recvCacheScriptLoadError, this, std::placeholders::_1, std::placeholders::_2));

    promise = this->asyncClient->SCRIPT_LOAD(R"(
        local rows = redis.call('SORT', KEYS[1], 'BY', 'gate:*->online', 'asc', 'limit', '0', '10', 'get', '#') 
        for k, v in pairs(rows) do
            local rkey = ARGV[1]..':'..v
            if redis.call('EXISTS', rkey) then
                return redis.call('HMGET', rkey, 'address', 'host', 'port', 'online', 'version') 
            end
        end
        return nil
        )"
    );
    promise->Then(std::bind(&login_cluster::recvCacheScriptLoadSucc, this, std::placeholders::_1, std::placeholders::_2, "balance"));
    promise->Else(std::bind(&login_cluster::recvCacheScriptLoadError, this, std::placeholders::_1, std::placeholders::_2));

    promise = this->asyncClient->SCRIPT_LOAD(R"(
        local rows = redis.call('SORT', KEYS[1], 'BY', 'gate:*->online', 'asc', 'limit', '0', '10', 'get', 'gate:*->address', 'get', 'gate:*->host', 'get', 'gate:*->port', 'get', 'gate:*->online', 'get', 'gate:*->version') 
        return rows
        )"
    );
    promise->Then(std::bind(&login_cluster::recvCacheScriptLoadSucc, this, std::placeholders::_1, std::placeholders::_2, "list"));
    promise->Else(std::bind(&login_cluster::recvCacheScriptLoadError, this, std::placeholders::_1, std::placeholders::_2));
}

void login_cluster::recvConnectCacheErr(redis::AsyncClient* client, const redis::RedisResultPtr& reply) {
    this->coord->CoreLogError("[login_cluster] recvConnectCacheErr, reply='%s'", reply->String());
}

void login_cluster::recvCacheScriptLoadSucc(redis::AsyncClient* client, const redis::RedisResultPtr& reply, const char* name) {
    this->coord->CoreLogError("[login_cluster] recvCacheScriptLoadSucc, name=%s, reply='%s'", name, reply->String());
    this->scriptShaDict[name] = reply->String();
}

void login_cluster::recvCacheScriptLoadError(redis::AsyncClient* client, const redis::RedisResultPtr& reply) {
    this->coord->CoreLogError("[login_cluster] recvCacheScriptLoadError, reply='%s'", reply->String());
}

redis::RedisPromise* login_cluster::getBalanceGate() {
    auto it = this->scriptShaDict.find("balance");
    if (it == this->scriptShaDict.end()) {
        return nullptr;
    }
    std::string version = "0.0";
    auto sha1 = it->second;
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "1 %s:version:%s %s", 
        this->group.c_str(), version.c_str(), 
        this->group.c_str());
    return promise;
}

redis::RedisPromise* login_cluster::getRanomGate() {
    auto it = this->scriptShaDict.find("random");
    if (it == this->scriptShaDict.end()) {
        return nullptr;
    }
    std::string version = "0.0";
    auto sha1 = it->second;
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "1 %s:version:%s %s", 
        this->group.c_str(), version.c_str(), 
        this->group.c_str());
    return promise;
}

redis::RedisPromise* login_cluster::listGate() {
    auto it = this->scriptShaDict.find("list");
    if (it == this->scriptShaDict.end()) {
        return nullptr;
    }
    std::string version = "0.0";
    auto sha1 = it->second;
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "1 %s:version:%s %s", 
        this->group.c_str(), version.c_str(), 
        this->group.c_str());
    return promise;
}

}
}