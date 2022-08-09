#include "coord/cluster/cluster_redis_config.h"
#include "coord/cluster/cluster.h"
#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_client.h"
#include "coord/redis/redis_promise.h"
#include "coord/redis/redis_reply.h"
#include "coord/config/config.h"
#include "coord/net/url.h"
#include "coord/coord.h"
namespace coord {
namespace cluster {

cluster_redis_config* newClusterRedisConfig(Coord* coord, Cluster* cluster) {
    cluster_redis_config* self = new cluster_redis_config(coord, cluster);
    return self;
}

cluster_redis_config::cluster_redis_config(Coord *coord, Cluster* cluster) : cluster_node_config(coord, cluster) {
    this->asyncClient = nullptr;
    this->syncClient = nullptr;
}

cluster_redis_config::~cluster_redis_config() {
    if(this->asyncClient != nullptr) {
        this->coord->Destory(this->asyncClient);
        this->asyncClient = nullptr;
    }
    if(this->syncClient != nullptr) {
        this->coord->Destory(this->syncClient);
        this->syncClient = nullptr;
    }
}

int cluster_redis_config::registerSelf() {
    if(this->syncClient == nullptr) {
        return -1;
    }
    auto reply = this->syncClient->HMSET(this->group.c_str(), this->name.c_str(), this->version);
    if(reply.Error()){
        this->coord->CoreLogError("[cluster_redis_config] registerSelf failed, error=%s", reply.String());
        return -1;
    }
    reply = this->syncClient->SETEX(this->rkey.c_str(), this->address.c_str(),  this->cluster->config.Expire);
    if(reply.Error()){
        return -2;
    }
    return 0;
}

int cluster_redis_config::heartbeat() {
    this->coord->CoreLogDebug("[cluster_redis_config] heartbeat");
    auto promise = this->asyncClient->EXPIRE(this->rkey.c_str(), this->cluster->config.Expire);
    if (promise == nullptr) {
        this->coord->CoreLogError("[cluster_redis_config] heartbeat failed, function='asyncClient->EXPIRE'");
        return -1;
    }
    promise->Then([this](auto client, auto reply){
        this->coord->CoreLogDebug("[cluster_redis_config] heartbeat, reply=%d", reply->Integer());    
        if (reply->Integer() != 1) {
            this->coord->CoreLogError("[cluster_redis_config] heartbeat failed, reply=%d", reply->Integer());    
        }
    });
    promise->Else([this](auto client, auto reply){
        this->coord->CoreLogError("[cluster_redis_config] heartbeat failed, reply='%s'", reply->String());    
    });
    return 0;
} 

int cluster_redis_config::reload() {
    this->checkNodeStatusAsync();
    return 0;
}

int cluster_redis_config::reload(const char* nodeName, uint64_t version) {
    return this->checkNodeStatusAsync(nodeName, version);
}

int cluster_redis_config::checkNodeStatusAsync(std::string nodeName, uint64_t version) {
    static thread_local char rkey[1024];
    int err = snprintf(rkey, sizeof(rkey), "%s:%s#%ld", this->group.c_str(), nodeName.c_str(), version);
    if (err < 0) {
        this->coord->CoreLogError("[cluster_redis_config] checkNodeStatusAsync failed, function='snprintf', group=%s, node=%s, version=%ld", 
            this->group.c_str(), nodeName.c_str(), version);
        return -1;
    }
    auto promise = this->asyncClient->GET(rkey);
    if (!promise) {
        this->coord->CoreLogError("[cluster_redis_config] checkNodeStatusAsync failed, function='this->asyncClient->GET', group=%s, node=%s, version=%ld", 
            this->group.c_str(), nodeName.c_str(), version);
        return -1;
    }
    promise->Then([this, nodeName, version](redis::AsyncClient* client, const redis::Reply* reply) {
        if (reply->Empty()) {
            auto it = this->nodeDict.find(nodeName);
            if (it != this->nodeDict.end()) {
                this->nodeDict.erase(it);
                this->recvNodeExpire(it->second);
            }
            auto promise = this->asyncClient->HDEL(this->group.c_str(), nodeName.c_str());   
            if (!promise) {
                this->coord->CoreLogError("[cluster_redis_config] checkNodeStatusAsync failed, function='this->asyncClient->HDEL', group=%s, node=%s, version=%ld", 
                    this->group.c_str(), nodeName.c_str(), version);
                return;
            }  
            promise->Then([this, nodeName, version](redis::AsyncClient* client, const redis::Reply* reply) {
            });   
            promise->Else([this, nodeName, version](redis::AsyncClient* client, const redis::Reply* reply) {
                this->coord->CoreLogError("[cluster_redis_config] checkNodeStatusAsync failed, function='this->asyncClient->HDEL', group=%s, node=%s, version=%ld", 
                this->group.c_str(), nodeName.c_str(), version);
            });       
        } else {
            const char* address = reply->String();
            auto it = this->nodeDict.find(nodeName);
            if (it == this->nodeDict.end()) {
                cluster_node* node = new cluster_node(nodeName.c_str(), address, version);
                this->recvNodeNew(node);
            } else if (it->second->version != version) {
                this->nodeDict.erase(it);
                this->recvNodeExpire(it->second);
                cluster_node* node = new cluster_node(nodeName.c_str(), address, version);
                this->recvNodeNew(node);
            }
        }      
    });
    promise->Else([this, nodeName, version](redis::AsyncClient* client, const redis::Reply* reply) {
        this->coord->CoreLogError("[cluster_redis_config] checkNodeStatusAsync failed, function='this->asyncClient->GET', group=%s, node=%s, version=%ld", 
            this->group.c_str(), nodeName.c_str(), version);
    });
    return 0;
}

int cluster_redis_config::checkNodeStatusAsync() {
    auto promise = this->asyncClient->HGETALL(this->group.c_str());
    if (promise == NULL) {
        this->coord->CoreLogError("[cluster_redis_config] checkNodeStatusAsync failed, function='asyncClient->HGETALL'");
        return -1;
    }
    promise->Then([this](redis::AsyncClient* client, const redis::Reply* reply){
        this->coord->CoreLogDebug("[cluster_redis_config] checkNodeStatusAsync");    
        //1.检查新增或者过期的节点
        for (int i = 0; i < reply->ArrayCount() / 2; i++){
            const char* nodeName = reply->String(i*2);
            uint64_t version = atol(reply->String(i*2+1));
            this->checkNodeStatusAsync(nodeName, version);
        }
        //2.检查删除的节点
        std::map<std::string, bool> lastNodeDict;
        for (int i = 0; i < reply->ArrayCount() / 2; i++){
            const char* nodeName = reply->String(i*2);
            lastNodeDict[nodeName] = true;
        }
        for(auto it = this->nodeDict.begin(); it != this->nodeDict.end();) {
            if(lastNodeDict.find(it->first) == lastNodeDict.end()) {
                this->recvNodeExpire(it->second);
                this->nodeDict.erase(it++);
            } else {
                ++it;
            }
        }
    });
    promise->Else([this](redis::AsyncClient* client, const redis::Reply* reply){
        this->coord->CoreLogError("[cluster_redis_config] checkNodeStatusAsync failed, reply='%s'", reply->String());
    });
    return 0;
}

int cluster_redis_config::checkNodeStatus(const char* nodeName, uint64_t version) {
    static thread_local char rkey[1024];
    int err = snprintf(rkey, sizeof(rkey), "%s:%s#%ld", this->group.c_str(), nodeName, version);
    if (err < 0) {
        this->coord->CoreLogError("[cluster_redis_config] checkNodeStatus failed, function='snprintf', group=%s, node=%s, version=%ld", 
            this->group.c_str(), nodeName, version);
        return -1;
    }
    auto reply = this->syncClient->GET(rkey);
    if (reply.Error()) {
        return -1;
    }
    if (reply.Empty()) {
        auto it = this->nodeDict.find(nodeName);
        if (it != this->nodeDict.end()) {
            this->nodeDict.erase(it);
            this->recvNodeExpire(it->second);
        }
        this->syncClient->HDEL(this->group.c_str(), nodeName);
    } else {
        const char* address = reply.String();
        auto it = this->nodeDict.find(nodeName);
        if (it == this->nodeDict.end()) {
            cluster_node* node = new cluster_node(nodeName, address, version);
            this->recvNodeNew(node);
        } else if (it->second->version != version) {
            this->nodeDict.erase(it);
            this->recvNodeExpire(it->second);
            cluster_node* node = new cluster_node(nodeName, address, version);
            this->recvNodeNew(node);
        }
    }
    return 0;
}

int cluster_redis_config::checkNodeStatus() {
    auto reply = this->syncClient->HGETALL(this->group.c_str());
    if (reply.Error()) {
        this->coord->CoreLogError("[cluster_redis_config] checkNodeStatus, HGETALL failed");
        return -1;
    }
    //1.检查新增或者过期的节点
    for (int i = 0; i < reply.ArrayCount() / 2; i++){
        const char* nodeName = reply.String(i*2);
        uint64_t version = atol(reply.String(i*2+1));
        this->checkNodeStatus(nodeName, version);
    }
    //2.检查删除的节点
    std::map<std::string, bool> lastNodeDict;
    for (int i = 0; i < reply.ArrayCount() / 2; i++){
        const char* nodeName = reply.String(i*2);
        lastNodeDict[nodeName] = true;
    }
    for(auto it = this->nodeDict.begin(); it != this->nodeDict.end();) {
        if(lastNodeDict.find(it->first) == lastNodeDict.end()) {
            this->recvNodeExpire(it->second);
            this->nodeDict.erase(it++);
        } else {
            ++it;
        }
    }
    return 0;
}

void cluster_redis_config::recvNodeExpire(cluster_node* node) {
    this->coord->CoreLogDebug("[cluster_redis_config] recvNodeExpire, node=%s", node->name.c_str());
    this->cluster->recvNodeExpire(node);
    delete node;
}

void cluster_redis_config::recvNodeNew(cluster_node* node) {
    this->coord->CoreLogDebug("[cluster_redis_config] recvNodeNew, node=%s", node->name.c_str());
    this->nodeDict[node->name] = node;
    this->cluster->recvNodeNew(node);
}

int cluster_redis_config::connect() {
    if(this->syncClient != nullptr) {
        return -1;
    }
    //同步连接
    {    
        net::Url url;
        int err = url.Parse(this->cluster->config.Driver.c_str(), this->cluster->config.Driver.length());
        if (err < 0){
            this->coord->CoreLogError("[cluster_redis_config] start.http_parser_parse_url failed, error=%d", err);
            return err;
        }
        redis::Client* client = this->coord->NewRedisClient();
        auto redis = client->DefaultConfig();
        redis->Host = url.Host;
        redis->Port = url.Port;
        redis->Password = url.Password;
        size_t dbIndex = url.Path.find("/");
        if (dbIndex == std::string::npos) {
            this->coord->CoreLogError("[cluster_redis_config] start.http_parser_parse_url failed, driver=%s, error='driver format err'", 
                this->cluster->config.Driver.c_str());
            this->coord->Destory(client);
            return -1;
        }
        size_t keyIndex = url.Path.find("/", dbIndex + 1);
        if (keyIndex == std::string::npos) {
            this->coord->CoreLogError("[cluster_redis_config] start.http_parser_parse_url failed, driver=%s, error='driver format err'", 
                this->cluster->config.Driver.c_str());
            this->coord->Destory(client);
            return -1;
        }
        redis->DB = url.Path.substr(dbIndex + 1, keyIndex - dbIndex - 1);
        this->group = url.Path.substr(keyIndex + 1);
        err = client->Connect();
        if (err < 0){
            this->coord->Destory(client);
            this->coord->CoreLogError("[cluster_redis_config] start, driver->Connect failed, error='%d'", err);
            return err;
        }
        this->syncClient = client;
        this->coord->CoreLogDebug("[cluster_redis_config] connect, host=%s, port=%d, db=%s, group=%s", 
            redis->Host.c_str(), redis->Port, redis->DB.c_str(), this->group.c_str());
    }    
    //异步链接
    {
        redis::AsyncClient* client = this->coord->NewAsyncRedisClient();
        *(client->DefaultConfig()) = *(this->syncClient->DefaultConfig());
        auto promise = client->Connect();
        if (promise == NULL) {
            this->coord->Destory(client);
            this->coord->CoreLogError("[GateCluster] start failed, func='client->Connect'");
            return -1;
        }
        promise->Then([this](redis::AsyncClient* client, const redis::Reply* reply) {
            this->coord->CoreLogDebug("[cluster_redis_config] connect success, reply='%s'", reply->String());
        });
        promise->Else([this](redis::AsyncClient* client, const redis::Reply* reply) {
            this->coord->CoreLogError("[cluster_redis_config] connect failed, reply='%s'", reply->String());
        });
        this->asyncClient = client;
    }
    return 0;
}

int cluster_redis_config::main() {
    int err = this->connect();
    if (err < 0){
        return err;
    }
    this->address = this->cluster->config.Host+ ":" + std::to_string(this->cluster->config.Port);
    this->version = this->syncClient->TIME();
    this->name = this->cluster->config.Name;
    this->fullName = this->cluster->config.Name + "#" + std::to_string(this->version);
    this->rkey = this->group + ":" + this->fullName;

    err = this->registerSelf();
    if (err < 0){
        this->coord->CoreLogError("[cluster_redis_config] main failed, function='registerSelf', error='%d'", err);
        return err;
    }
    err = this->checkNodeStatus();
    if (err < 0){
        this->coord->CoreLogError("[cluster_redis_config] main failed, function='checkNodeStatus', error='%d'", err);
        return err;
    }
    return 0;
}


}
}        