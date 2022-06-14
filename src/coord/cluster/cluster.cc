#include "coord/cluster/cluster.h"
#include "coord/cluster/cluster_redis_config.h"
#include "coord/cluster/cluster_client.h"
#include "coord/cluster/cluster_server.h"
#include "coord/cluster/cluster_router.h"
#include "coord/cluster/cluster_result.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_response.h"
#include "coord/config/config.h"
#include "coord/builtin/exception.h"
#include "coord/coord.h"
#include "proto/coord.pb.h"

namespace coord {
namespace cluster {
CC_IMPLEMENT(Cluster, "coord::cluster::Cluster")
Cluster* newCluster(Coord* coord) {
    auto self = new Cluster(coord);
    return self;
}

Cluster::Cluster(Coord *coord) {
    this->coord = coord;
    this->Router = new ClusterRouter(this->coord);
    this->server = nullptr;
    this->nodeConfig = nullptr;
    this->config.Port = 4567;
    this->config.Host = "127.0.0.1";
    this->config.Driver = "redis://:123456@127.0.0.1:6379/1/cluster";
    this->config.Heartbeat = 60;
    this->config.Expire = 120;
    this->config.Name = "gamesvr_1";
    this->config.ReloadInterval = 30;
    this->config.ReconnectInterval = 10;
    this->config.RegisterInterval = 30;
    this->config.RecvBuffer = 4096;
}

Cluster::~Cluster() {
    delete this->Router;
    this->Router = nullptr;
    for(auto it = this->clientDict.begin(); it != this->clientDict.end();) {
        cluster_client* client = it->second;
        this->coord->Destory(client);
        ++it;
    }
    if(this->server) {
        delete this->server;
        this->server = nullptr;
    }
    if(this->Router) {
        delete this->Router;
        this->Router = nullptr;
    }
    if(this->nodeConfig) {
        delete this->nodeConfig;
        this->nodeConfig = nullptr;
    }
}

int Cluster::main() {
    this->coord->coreLogDebug("[Cluster] main, register_interval=%d, reload_interval=%d, heartbeat=%d, reconnect_interval=%d",
        this->config.RegisterInterval,
        this->config.ReloadInterval,
        this->config.Heartbeat,
        this->config.ReconnectInterval
        );
    int err = 0; 
    //启动server
    this->server = newClusterServer(this->coord, this);
    err = this->server->main();
    if (err < 0){
        return err;
    }  
    //连接配置文件
    this->nodeConfig = newClusterRedisConfig(this->coord, this);
    err = this->nodeConfig->main();
    if (err < 0){
        return err;
    }    
    this->Name = this->nodeConfig->name;
    this->FullName = this->nodeConfig->fullName;
    this->Version = this->nodeConfig->version;
    //定时注册
    this->coord->SetInterval(this->config.RegisterInterval * 1000, [this](){this->nodeConfig->heartbeat();return 0;});
    this->coord->SetInterval(this->config.ReloadInterval * 1000, [this](){this->nodeConfig->reload();return 0;});
    this->coord->SetInterval(this->config.Heartbeat * 1000, [this](){this->server->heartbeat();return 0;});
    this->coord->SetInterval(this->config.ReconnectInterval * 1000, [this](){
        for(auto const& it : this->clientDict) {
            it.second->tryReconnect();
        }
        return 0;
    });
    return 0;
}

void Cluster::recvNodeNew(cluster_node* node) {
    this->coord->coreLogError("[Cluster] recvNodeNew, node=%s, version=%ld, host=%s, port=%d", node->name.c_str(), node->version, node->host.c_str(), node->port);
    auto it = this->clientDict.find(node->name);
    if (it != this->clientDict.end()) {
        this->coord->coreLogError("[Cluster] recvNodeNew failed, client conflict, node=%s", node->name.c_str());
        return;
    }
    cluster_client* client = newClusterClient(this->coord, this, node->name.c_str(), node->version, node->host.c_str(), node->port);
    int err = client->connect();
    if (err < 0) {
        this->coord->coreLogError("[Cluster] recvNodeNew failed, error=%d", err);
        return;
    }
    this->clientDict[node->name] = client;
}

void Cluster::recvNodeExpire(cluster_node* node) {
    this->coord->coreLogError("[Cluster] recvNodeExpire, node='%s', host='%s', port=%d", node->name.c_str(), node->host.c_str(), node->port);
    auto it = this->clientDict.find(node->name);
    if (it == this->clientDict.end()) {
        this->coord->coreLogError("[Cluster] recvNodeExpire, node='%s', error='client not found'", node->name.c_str());
        return;
    }
    cluster_client* client = it->second;
    this->clientDict.erase(it);
    this->coord->Destory(client);
}

void Cluster::Reload() {
    this->nodeConfig->reload();
}

void Cluster::reload(const char* node, uint64_t version) {
    auto it = this->clientDict.find(node);
    if (it != this->clientDict.end() && it->second->version == version) {
        return;
    }
    this->nodeConfig->reload(node, version);
} 

ClusterConfig* Cluster::DefaultConfig() {
    return &this->config;
}

int Cluster::Notify(const char* nodeName, const char* route, const char* data) {
    return this->Notify(nodeName, route, data, strlen(data));
}

int Cluster::Notify(const char* nodeName, const char* route, const char* data, size_t len) {
    auto it = this->clientDict.find(nodeName);
    if (it == this->clientDict.end()) {
        return -1;
    }
    cluster_client* client = it->second;
    return client->notify(route, data, len);
}

void Cluster::recvClusterNotify(cluster::Notify* notify) {
    this->coord->coreLogDebug("[Cluster] recvClusterNotify");
    try{
        //传递到逻辑层
        this->Router->recvClusterNotify(notify);
    } catch(ScriptException& e){
    }
}

Promise* Cluster::Request(const char* node, const char* route, const char* data) {
    return this->Request(node, route, data, strlen(data));
}

Promise* Cluster::Request(const char* node, const char* route, const char* data, size_t len) {
    auto it = this->clientDict.find(node);
    if (it == this->clientDict.end()) {
        return NULL;
    }
    cluster_client* client = it->second;
    return client->request(route, data, len);
}

Promise* Cluster::Request(const char* node, const char* route, protobuf::Reflect& proto) {
    return this->Request(node, route, proto.GetMessage());
}

Promise* Cluster::Request(const char* node, const char* route, google::protobuf::Message* message) {
    auto it = this->clientDict.find(node);
    if (it == this->clientDict.end()) {
        return NULL;
    }
    cluster_client* client = it->second;
    return client->request(route, message);
}

void Cluster::recvClusterRequest(cluster::Request* request) {
    this->coord->coreLogDebug("[Cluster] recvClusterRequest");
    try{
        //传递到逻辑层
        this->Router->recvClusterRequest(request);
    } catch(ScriptException& e){
        Response* response = request->GetResponse();
        response->String(e.What());
        response->Reject(500);
    }
}

}
}        
