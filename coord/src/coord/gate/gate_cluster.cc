#include "coord/gate/gate_cluster.h"
#include "coord/gate/gate.h"
#include "coord/builtin/slice.h"
#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_client.h"
#include "coord/redis/redis_promise.h"
#include "coord/redis/redis_reply.h"
#include "coord/config/config.h"
#include "coord/cluster/cluster.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_result.h"
#include "coord/cluster/cluster_router.h"
#include "coord/cluster/cluster_promise.h"
#include "coord/cluster/cluster_response.h"
#include "coord/net/url.h"
#include "coord/builtin/argument.h"
#include "coord/coord.h"
#include "proto/coord.pb.h"

namespace coord {
namespace gate {
CC_IMPLEMENT(gate_cluster, "coord::gate::gate_cluster")

gate_cluster* newgate_cluster(Coord* coord, Gate* gate) {
    gate_cluster* gateCluster = new gate_cluster(coord, gate);
    return gateCluster;
}

gate_cluster::gate_cluster(Coord* coord, Gate* gate) {
    this->coord = coord;
    this->gate = gate;
    this->asyncClient = NULL;
    this->syncClient = NULL;
}

gate_cluster::~gate_cluster() {
    this->coord->coreLogDebug("[gate_cluster] ~gate_cluster");
    if(this->asyncClient != NULL) {
        delete this->asyncClient;
        this->asyncClient = NULL;
    }
    if(this->syncClient != NULL) {
        delete this->syncClient;
        this->syncClient = NULL;
    }
}

void gate_cluster::onDestory() {
    this->coord->coreLogDebug("[gate_cluster] onDestory");
    int err = this->clearSelf();
    if (err) {
        this->coord->coreLogError("[gate_cluster] clearSelf failed, error=%d", err);
    }
    err = this->clearUser();
    if (err) {
        this->coord->coreLogError("[gate_cluster] clearUser failed, error=%d", err);
    }
}

int gate_cluster::registerSelf() {
    this->coord->coreLogDebug("[gate_cluster] registerSelf");
    {
        auto reply = this->syncClient->HMSET(this->selfKey.c_str(), "version", this->coord->config->Basic.ShortVersion.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='HMSET err'");
            return -1;
        }
        reply = this->syncClient->HMSET(this->selfKey.c_str(), "address", this->gate->address.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='HMSET err'");
            return -1;
        }
        reply = this->syncClient->HMSET(this->selfKey.c_str(), "host", this->coord->config->Gate.Host.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='HMSET err'");
            return -1;
        }
        reply = this->syncClient->HMSET(this->selfKey.c_str(), "port", std::to_string(this->coord->config->Gate.Port).c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='HMSET err'");
            return -1;
        }
        reply = this->syncClient->HMSET(this->selfKey.c_str(), "online", "0");
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='HMSET err'");
            return -1;
        }
        int err = this->syncClient->EXPIRE(this->selfKey.c_str(), this->coord->config->Gate.RegisterExpire);
        if (err) {
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='EXPIRE err'");
            return -1;
        }
    }
    {
        auto reply = this->syncClient->SADD(this->gateSetKey.c_str(), this->coord->config->Basic.Name.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='SADD err'");
            return -1;
        }
    }
    {
        auto reply = this->syncClient->SADD(this->gateSetVersionKey.c_str(), this->coord->config->Basic.Name.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] registerSelf failed, error='SADD err'");
            return -1;
        }
    }
    return 0;
}

int gate_cluster::clearSelf() {
    this->coord->coreLogError("[gate_cluster] clearSelf");
    {
        auto reply = this->syncClient->DEL(this->selfKey.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] clearSelf failed, error='DEL err'");
            return -1;
        }
    }
    {
        auto reply = this->syncClient->SREM(this->gateSetKey.c_str(), this->coord->config->Basic.Name.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] clearSelf failed, error='SREM err'");
            return -1;
        }
    }
    {
        auto reply = this->syncClient->SREM(this->gateSetVersionKey.c_str(), this->coord->config->Basic.Name.c_str());
        if (reply.Error()){
            this->coord->coreLogError("[gate_cluster] clearSelf failed, error='SREM err'");
            return -1;
        }
    }
    return 0;
}

int gate_cluster::clearUser() {
    this->coord->coreLogError("[gate_cluster] clearUser");
    auto reply = this->syncClient->HGETALL(this->userHashKey.c_str());
    if (reply.Error()){
        this->coord->coreLogError("[gate_cluster] clearUser failed, error='HGETALL err'");
        return -1;
    }
    std::map<std::string, bool> lastNodeDict;
    for (int i = 0; i < reply.ArrayCount() / 2; i++){
        const char* userId = reply.String(i*2);
        std::string userKey = this->group + ":" + userId;
        auto reply1 = this->syncClient->GET(userKey.c_str());
        if (reply1.Error()) {
            this->coord->coreLogError("[gate_cluster] clearUser failed, user key=%s, error='GET err'", userKey.c_str());
            continue;
        }
        if (reply1.Empty()) {
            this->coord->coreLogError("[gate_cluster] clearUser failed, user key=%s, error='GET empty'", userKey.c_str());
            continue;
        }
        if (strcmp(reply1.String(), this->coord->config->Basic.Name.c_str()) != 0) {
           this->coord->coreLogError("[gate_cluster] clear failed, local='%s', other='%s'", this->coord->config->Basic.Name.c_str(), reply1.String());
            continue;
        }
        this->coord->coreLogDebug("[gate_cluster] clearUser, user key=%s, gate=%s\n", userKey.c_str(), reply1.String());
        auto reply2 = this->syncClient->DEL(userKey.c_str());
        if (reply2.Error()) {
            this->coord->coreLogError("[gate_cluster] clearUser failed, error='DEL err'");
            continue;
        }
    }
    reply = this->syncClient->DEL(this->userHashKey.c_str());
    if (reply.Error()){
        this->coord->coreLogError("[gate_cluster] clearUser failed, error='DEL err'");
        return -1;
    }
    return 0;
}

int gate_cluster::main() {
    if(this->syncClient != NULL) {
        return -1;
    }
    auto gateConfig = this->gate->DefaultConfig();
    //同步连接
    {
        net::Url url;
        int err = url.Parse(gateConfig->Cluster.c_str(), gateConfig->Cluster.length());
        if (err < 0){
            this->coord->coreLogError("[gate_cluster] main.http_parser_parse_url failed, error=%d", err);
            return err;
        }
        redis::Client* client = redis::newClient(this->coord);
        auto config = client->DefaultConfig();
        config->Host = url.Host;
        config->Port = url.Port;
        config->Password = url.Password;
        size_t dbIndex = url.Path.find("/");
        if (dbIndex == std::string::npos) {
            this->coord->coreLogError("[gate_cluster] main failed, func='http_parser_parse_url', url=%s, error='url format err'", gateConfig->Cluster.c_str());
            delete client;
            return -1;
        }
        size_t keyIndex = url.Path.find("/", dbIndex + 1);
        if (keyIndex == std::string::npos) {
            this->coord->coreLogError("[gate_cluster] main failed, func='http_parser_parse_url', url=%s, error='url format err'", gateConfig->Cluster.c_str());
            delete client;
            return -1;
        }
        config->DB = url.Path.substr(dbIndex + 1, keyIndex - dbIndex - 1);
        this->group = url.Path.substr(keyIndex + 1);
        err = client->Connect();
        if (err < 0){
            delete client;
            this->coord->coreLogError("[gate_cluster] main failed, func='client->Connect' failed, error='%d'", err);
            return err;
        }
        this->syncClient = client;
        this->coord->coreLogDebug("[gate_cluster] main, host=%s, port=%d, db=%s, group=%s", config->Host.c_str(), config->Port, config->DB.c_str(), this->group.c_str());
    }
    //异步链接
    {
        redis::AsyncClient* client = redis::newAsyncClient(this->coord);
        *(client->DefaultConfig()) = *(this->syncClient->DefaultConfig());
        auto promise = client->Connect();
        if (promise == NULL) {
            delete client;
            this->coord->coreLogError("[gate_cluster] main failed, func='client->Connect'");
            return -1;
        }
        promise->Then(std::bind(&gate_cluster::recvConnectCacheSucc, this, std::placeholders::_1, std::placeholders::_2));
        promise->Else(std::bind(&gate_cluster::recvConnectCacheErr, this, std::placeholders::_1, std::placeholders::_2));
        this->asyncClient = client;
    }
    this->selfKey = this->group + ":" + this->coord->config->Basic.Name;
    this->userHashKey = this->group + ":" + this->coord->config->Basic.Name + ":user";
    this->gateSetKey = this->group;
    this->gateSetVersionKey = this->group + ":version:" + this->coord->config->Basic.ShortVersion;
    //清除数据
    int err = this->clearUser();
    if (err) {
        this->coord->coreLogError("[gate_cluster] main filed, func='clearUser', error=%d", err);
        return err;
    }
    err = this->registerSelf();
    if (err) {
        this->coord->coreLogError("[gate_cluster] main filed, func='registerSelf', error=%d", err);
        return err;
    }
    //注册cluster路由
    this->coord->Cluster->Router->Request("gate.UserInstead", std::bind(&gate_cluster::recvClusterUserInstead, this, std::placeholders::_1));
    this->coord->SetInterval(this->gate->config.RegisterExpire / 2 * 1000, [this](){this->persistSelf();return 0;});
    this->coord->SetInterval(this->gate->config.RegisterExpire / 2 * 1000, [this](){this->checkExpireGate();return 0;});
    return 0;
}

void gate_cluster::recvClusterUserInstead(cluster::Request* request) {
    //通知他下线
    gate_cluster_instead_request arg;
    gate_cluster_instead_response response;
    if (request->Proto(arg)) {
        request->GetResponse()->Proto(response);
        request->GetResponse()->Reject(-1);
        return;
    } 
    this->coord->DontDestory(request);
    uint64_t userId = arg.userid();
    //取消上一个请求
    this->abortRegisterOrInsteadRequest(userId);
    this->insteadRequestDict[userId] = request;
    this->gate->recvUserInstead(userId);
}

void gate_cluster::recvConnectCacheSucc(redis::AsyncClient* client, redis::Reply& reply) {
    this->coord->coreLogDebug("[gate_cluster] recvConnectCacheSucc %s", reply.String());
    //心跳的sha1
    auto promise = this->asyncClient->SCRIPT_LOAD(R"(
        local v = redis.call('get', KEYS[1]) 
        if v ~= ARGV[1] then 
            return v 
        end 
        redis.call('EXPIRE', KEYS[1], ARGV[2]) 
        return 'OK')"
    );
    promise->Then(std::bind(&gate_cluster::recvCacheScriptLoadSucc, this, std::placeholders::_1, std::placeholders::_2, "heartbeat"));
    promise->Else(std::bind(&gate_cluster::recvCacheScriptLoadError, this, std::placeholders::_1, std::placeholders::_2));

    //注册的sha1
    promise = this->asyncClient->SCRIPT_LOAD(R"(
        local v = redis.call('get', KEYS[1]) 
        if v ~= false then 
            return v 
        end 
        redis.call('HSET', KEYS[2], ARGV[1], ARGV[2]) 
        redis.call('SETEX', KEYS[1], ARGV[3], ARGV[2]) 
        return 'OK')"
    );
    promise->Then(std::bind(&gate_cluster::recvCacheScriptLoadSucc, this, std::placeholders::_1, std::placeholders::_2, "register"));
    promise->Else(std::bind(&gate_cluster::recvCacheScriptLoadError, this, std::placeholders::_1, std::placeholders::_2));

    //删除的sha1
    promise = this->asyncClient->SCRIPT_LOAD(R"(
        local v = redis.call('get', KEYS[1]) 
        if v ~= ARGV[2] then 
            return v 
        end 
        redis.call('HDEL', KEYS[2], ARGV[1]) 
        redis.call('DEL', KEYS[1]) 
        return 'OK')"
    );
    promise->Then(std::bind(&gate_cluster::recvCacheScriptLoadSucc, this, std::placeholders::_1, std::placeholders::_2, "unregister"));
    promise->Else(std::bind(&gate_cluster::recvCacheScriptLoadError, this, std::placeholders::_1, std::placeholders::_2));

    //check的sha1
    // keys1 = group
    // argv1 = group
    // argv2 = node
    promise = this->asyncClient->SCRIPT_LOAD(R"(
        if not redis.call('SET', ARGV[1]..':lock', ARGV[2], 'nx', 'ex', 60) then
            return 'LOCK'
        end
        local rows = redis.call('SMEMBERS', KEYS[1])
        local affected = 0
        --检查网关列表
        for k, v in pairs(rows) do
            local rkey = ARGV[1]..':'..v
            if redis.call('EXISTS', rkey) == 0 then
                redis.call('SREM', KEYS[1], v)
                affected = affected + 1
            end
        end
        --检查版本网关列表
        local versionArr = redis.call('KEYS', ARGV[1]..':version:*')
        for k, versionKey in pairs(versionArr) do
            local version = string.match(versionKey, ARGV[1]..':version:(.+)')
            if version then   
                local rows = redis.call('SMEMBERS', versionKey)
                for k, v in pairs(rows) do
                    local rkey = ARGV[1]..':'..v
                    local versionReal = redis.call('HGET', rkey, 'version')
                    if not versionReal or versionReal ~= version then
                        redis.call('SREM', versionKey, v)
                        affected = affected + 1
                    end
                end
            end
        end
        redis.call('DEL', ARGV[1]..':lock')
        return affected
    )");
    promise->Then(std::bind(&gate_cluster::recvCacheScriptLoadSucc, this, std::placeholders::_1, std::placeholders::_2, "check"));
    promise->Else(std::bind(&gate_cluster::recvCacheScriptLoadError, this, std::placeholders::_1, std::placeholders::_2));
}

void gate_cluster::recvConnectCacheErr(redis::AsyncClient* client, redis::Reply& reply) {
    this->coord->coreLogDebug("[gate_cluster] recvConnectCacheErr, reply='%s'", reply.String());
}

void gate_cluster::recvCacheScriptLoadSucc(redis::AsyncClient* client, redis::Reply& reply, const char* name) {
    this->coord->coreLogError("[gate_cluster] recvCacheScriptLoadSucc, name=%s, reply='%s'", name, reply.String());
    this->scriptShaDict[name] = reply.String();
}

void gate_cluster::recvCacheScriptLoadError(redis::AsyncClient* client, redis::Reply& reply) {
    this->coord->coreLogDebug("[gate_cluster] recvCacheScriptLoadError, reply='%s'", reply.String());
}

void gate_cluster::recvRegisterSucc(redis::AsyncClient* client, redis::Reply& reply, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvRegisterSucc, sessionId=%ld, userId=%ld, reply='%s'", sessionId, userId, reply.String());
    auto it = this->registeringUserDict.find(userId);
    if (it == this->registeringUserDict.end()) {
        return;
    }
    if (it->second != sessionId) {
        return;
    }
    const char* localNodeName = this->coord->Cluster->Name.c_str();
    const char* otherNodeName = reply.String();
    //1.如果在其他节点中，通知节点踢用户下线
    //2.如果在本节点中，踢用户下线
    //3.如果注册成功
    if (strcmp(otherNodeName, "OK") == 0) {
        this->registeringUserDict.erase(it);
        this->gate->recvUserLoginSucc(sessionId, userId);
    } else if (strcmp(otherNodeName, localNodeName) == 0) {
        //通知他下线
        this->gate->recvUserInstead(userId);
    } else {
        //通过cluster通知其下线
        gate_cluster_instead_request request;
        request.set_userid(userId);
        auto promise = this->coord->Cluster->Request(otherNodeName, "gate.UserInstead", &request);
        if (promise == NULL) {
            this->registeringUserDict.erase(it);
            this->gate->recvUserLoginErr(sessionId, userId);
            return;
        }
        promise->Then(std::bind(&gate_cluster::recvClusterUserInsteadSucc, this, std::placeholders::_1, sessionId, userId));
        promise->Else(std::bind(&gate_cluster::recvClusterUserInsteadErr, this, std::placeholders::_1, sessionId, userId));
    }
}

void gate_cluster::recvClusterUserInsteadSucc(cluster::Result* result, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvClusterUserInsteadSucc, sessionId=%ld, userId=%ld, reply='%s'", sessionId, userId);
    auto it = this->registeringUserDict.find(userId);
    if (it == this->registeringUserDict.end()) {
        return;
    }
    if (it->second != sessionId) {
        return;
    }
    int err = this->tryRegisterAgent(it->second, userId);
    if (err) {
        this->registeringUserDict.erase(it);
        this->gate->recvUserLoginErr(it->second, userId);
    }
}

void gate_cluster::recvClusterUserInsteadErr(cluster::Result* result, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvClusterUserInsteadErr, sessionId=%ld, userId=%ld, reply='%s'", sessionId, userId);
    auto it = this->registeringUserDict.find(userId);
    if (it == this->registeringUserDict.end()) {
        return;
    }
    if (it->second != sessionId) {
        return;
    }    
    this->registeringUserDict.erase(it);
    this->gate->recvUserLoginErr(it->second, userId);
}

void gate_cluster::recvRegisterError(redis::AsyncClient* client, redis::Reply& reply, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvRegisterError, sessionId=%ld, userId=%ld, reply='%s'", sessionId, userId, reply.String());
    auto it = this->registeringUserDict.find(userId);
    if (it == this->registeringUserDict.end()) {
        return;
    }
    if (it->second != sessionId) {
        return;
    }
    this->registeringUserDict.erase(it);
    //注册失败，原因末知
    this->gate->recvUserLoginErr(sessionId, userId);
}

void gate_cluster::abortRegisterOrInsteadRequest(uint64_t userId) {
    {
        auto it = this->registeringUserDict.find(userId);
        if (it != this->registeringUserDict.end()) {
            this->coord->coreLogDebug("[gate_cluster] abortRegisterOrInsteadRequest, userId=%ld", userId);
            this->gate->recvUserLoginErr(it->second, userId);
            this->registeringUserDict.erase(it);
        }
    }
    {
        auto it = this->insteadRequestDict.find(userId);
        if (it != this->insteadRequestDict.end()) {
            this->coord->coreLogDebug("[gate_cluster] abortRegisterOrInsteadRequest, userId=%ld", userId);
            auto request = it->second;
            gate_cluster_instead_response response;
            response.set_userid(userId);
            request->GetResponse()->Proto(response);
            request->GetResponse()->Reject(-1);
            this->coord->Destory(request);
            this->insteadRequestDict.erase(it);
        }
    }
}

int gate_cluster::registerAgent(uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] registerAgent, sessionId=%ld, userId=%ld", sessionId, userId);
    auto it = this->scriptShaDict.find("register");
    if (it == this->scriptShaDict.end()) {
        return -1;
    }
    //取消上一个请求
    this->abortRegisterOrInsteadRequest(userId);
    //设置新的请求
    this->registeringUserDict[userId] = sessionId;
    auto sha1 = it->second;
    const char* localNodeName = this->coord->Cluster->Name.c_str();
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "2 %s:%ld %s %ld %s %d", 
        this->group.c_str(), userId, 
        this->userHashKey.c_str(),
        userId,
        localNodeName, 
        this->gate->config.UserRegisterExpire);
    promise->Then(std::bind(&gate_cluster::recvRegisterSucc, this, std::placeholders::_1, std::placeholders::_2, sessionId, userId));
    promise->Else(std::bind(&gate_cluster::recvRegisterError, this, std::placeholders::_1, std::placeholders::_2, sessionId, userId));
    return 0;
}

void gate_cluster::recvTryRegisterSucc(redis::AsyncClient* client, redis::Reply& reply, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvTryRegisterSucc, sessionId=%ld, userId=%ld, reply=%s", sessionId, userId, reply.String());
    auto it = this->registeringUserDict.find(userId);
    if (it == this->registeringUserDict.end()) {
        return;
    }
    if (it->second != sessionId) {
        return;
    }
    if (strcmp(reply.String(), "OK") == 0) {
        this->registeringUserDict.erase(it);
        this->gate->recvUserLoginSucc(sessionId, userId);
    } else {
        //第二次尝试如果失败，就直接失败了
        this->registeringUserDict.erase(it);
        this->gate->recvUserLoginErr(sessionId, userId);
    }
}

void gate_cluster::recvTryRegisterError(redis::AsyncClient* client, redis::Reply& reply, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvTryRegisterError, sessionId=%ld, userId=%ld, reply=%s", sessionId, userId, reply.String());
    auto it = this->registeringUserDict.find(userId);
    if (it == this->registeringUserDict.end()) {
        return;
    }
    if (it->second != sessionId) {
        return;
    }
    this->registeringUserDict.erase(it);
    //注册失败，原因末知
    this->gate->recvUserLoginErr(sessionId, userId);
}

int gate_cluster::tryRegisterAgent(uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] tryRegisterAgent, sessionId=%ld, userId=%ld", sessionId, userId);
    auto it = this->scriptShaDict.find("register");
    if (it == this->scriptShaDict.end()) {
        this->coord->coreLogDebug("[gate_cluster] tryRegisterAgent failed, sessionId=%ld, userId=%ld, error='sha1 not found'", sessionId, userId);
        return -1;
    }
    auto sha1 = it->second;
    const char* localNodeName = this->coord->Cluster->Name.c_str();
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "2 %s:%ld %s %ld %s %d", 
        this->group.c_str(), userId, 
        this->userHashKey.c_str(),
        userId,
        localNodeName, 
        this->gate->config.UserRegisterExpire);
    promise->Then(std::bind(&gate_cluster::recvTryRegisterSucc, this, std::placeholders::_1, std::placeholders::_2, sessionId, userId));
    promise->Else(std::bind(&gate_cluster::recvTryRegisterError, this, std::placeholders::_1, std::placeholders::_2, sessionId, userId));
    return 0;
}

void gate_cluster::recvUnregisterSucc(redis::AsyncClient* client, redis::Reply& reply, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvUnregisterSucc, sessionId=%ld, userId=%ld, reply='%s'", sessionId, userId, reply.String());
    this->gate->recvUserLogoutSucc(sessionId, userId);
    auto it1 = this->registeringUserDict.find(userId);
    auto it2 = this->insteadRequestDict.find(userId);
    if (it1 != this->registeringUserDict.end() && it2 != this->insteadRequestDict.end()) {
        this->coord->coreLogError("[gate_cluster] recvUnregisterSucc, sessionId=%ld, userId=%ld, reply='%s'", sessionId, userId, reply.String());
        //通知本地的
        int err = this->tryRegisterAgent(it1->second, userId);
        if (err) {
            this->registeringUserDict.erase(it1);
            this->gate->recvUserLoginErr(it1->second, userId);
        }
        //拒绝远程的
        auto request = it2->second;
        gate_cluster_instead_response response;
        response.set_userid(userId);
        request->GetResponse()->Proto(response);
        request->GetResponse()->Reject(-1);
        this->coord->Destory(request);
        this->insteadRequestDict.erase(it2);
    }else if (it1 != this->registeringUserDict.end()) {
        int err = this->tryRegisterAgent(it1->second, userId);
        if (err) {
            this->registeringUserDict.erase(it1);
            this->gate->recvUserLoginErr(it1->second, userId);
        }
    } if (it2 != this->insteadRequestDict.end()) {
        auto request = it2->second;
        gate_cluster_instead_response response;
        response.set_userid(userId);
        request->GetResponse()->Proto(response);
        request->GetResponse()->Resolve();
        this->coord->Destory(request);
        this->insteadRequestDict.erase(it2);
    }
}

void gate_cluster::recvUnregisterError(redis::AsyncClient* client, redis::Reply& reply, uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] recvRegisterError, sessionId=%ld, userId=%ld, reply=%s", sessionId, userId, reply.String());
    this->gate->recvUserLogoutErr(sessionId, userId);

    int succ = 0;
    {
        auto it = this->registeringUserDict.find(userId);    
        if (it != this->registeringUserDict.end()) {
            succ++;
            this->registeringUserDict.erase(it);
            this->gate->recvUserLoginErr(it->second, userId);
        } 
    }
    {
        auto it = this->insteadRequestDict.find(userId);
        if (it != this->insteadRequestDict.end()) {
            succ++;
            auto request = it->second;
            gate_cluster_instead_response response;
            response.set_userid(userId);
            request->GetResponse()->Proto(response);
            request->GetResponse()->Reject(-1);
            this->coord->Destory(request);
            this->insteadRequestDict.erase(it);
        }
    }
    if (succ == 0) {
        this->coord->coreLogError("[gate_cluster] recvUnregisterError, sessionId=%ld, userId=%ld, reply='%s'", sessionId, userId, reply.String());
    }
}

void gate_cluster::unregisterAgent(uint64_t sessionId, uint64_t userId) {
    this->coord->coreLogDebug("[gate_cluster] unregisterAgent, sessionId=%ld, userId=%ld", sessionId, userId);
    auto it = this->scriptShaDict.find("unregister");
    if (it == this->scriptShaDict.end()) {
        this->coord->coreLogDebug("[gate_cluster] unregisterAgent failed, sessionId=%ld, userId=%ld, error='sha1 not found'", sessionId, userId);
        return;
    }
    auto sha1 = it->second;
    const char* localNodeName = this->coord->Cluster->Name.c_str();
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "2 %s:%d %s %ld %s", 
        this->group.c_str(), userId, 
        this->userHashKey.c_str(),
        userId,
        localNodeName);
    promise->Then(std::bind(&gate_cluster::recvUnregisterSucc, this, std::placeholders::_1, std::placeholders::_2, sessionId, userId));
    promise->Else(std::bind(&gate_cluster::recvUnregisterError, this, std::placeholders::_1, std::placeholders::_2, sessionId, userId));
}

void gate_cluster::persistAgent(uint64_t userId){
    this->coord->coreLogDebug("[gate_cluster] persistAgent, userId=%ld", userId);
    auto it = this->scriptShaDict.find("heartbeat");
    if (it == this->scriptShaDict.end()) {
        return;
    }
    auto sha1 = it->second;
    const char* localNodeName = this->coord->Cluster->Name.c_str();
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "1 %s:%ld %s %d", 
        this->group.c_str(), userId, 
        localNodeName,
        this->gate->config.UserRegisterExpire);
    if (promise == nullptr) {
        this->coord->coreLogDebug("[gate_cluster] persistAgent failed, userId=%ld, error='EVALSHA'", userId);
        return;
    }
    promise->Then([this, userId](redis::AsyncClient* client, redis::Reply& reply){
        this->coord->coreLogDebug("[gate_cluster] persistAgent succ, userId=%ld, reply='%s'", userId, reply.String());
    });
    promise->Else([this, userId](redis::AsyncClient* client, redis::Reply& reply){
        this->coord->coreLogDebug("[gate_cluster] persistAgent error, userId=%ld, reply='%s'", userId, reply.String());
    });
}

void gate_cluster::persistSelf(){
    this->coord->coreLogDebug("[gate_cluster] persistSelf");
    auto promise = this->asyncClient->EXPIRE(this->selfKey.c_str(), this->coord->config->Gate.RegisterExpire);
    if (promise == nullptr) {
        this->coord->coreLogDebug("[gate_cluster] persistSelf failed, function='EVALSHA'");
        return;
    }
    promise->Then([this](redis::AsyncClient* client, redis::Reply& reply){
        this->coord->coreLogError("[gate_cluster] persistSelf succ, reply=%ld", reply.Integer());
    });
    promise->Else([this](redis::AsyncClient* client, redis::Reply& reply){
        this->coord->coreLogError("[gate_cluster] persistSelf error, reply='%s'", reply.String());
    });
    //更新在线人数
    promise = this->asyncClient->HMSET(this->selfKey.c_str(), "online", std::to_string(this->gate->GetOnlineNum()).c_str());
    if (promise == nullptr) {
        this->coord->coreLogDebug("[gate_cluster] persistSelf failed, function='HMSET'");
        return;
    }
 }

void gate_cluster::checkExpireGate() {
    auto it = this->scriptShaDict.find("check");
    if (it == this->scriptShaDict.end()) {
        return;
    }
    auto sha1 = it->second;
    auto promise = this->asyncClient->EVALSHA(sha1.c_str(), "1 %s %s %s",  
        this->gateSetKey.c_str(),
        this->group.c_str(),
        this->coord->config->Basic.Name.c_str());
    if (promise == nullptr) {
        this->coord->coreLogDebug("[gate_cluster] checkExpireGate failed, function='EVALSHA'");
        return;
    }
    promise->Then([this](auto client, auto& reply){
        this->coord->coreLogError("[gate_cluster] checkExpireGate succ, reply=%ld", reply.Integer());
    });
    promise->Else([this](auto client, auto& reply){
        this->coord->coreLogError("[gate_cluster] checkExpireGate error, reply='%s'", reply.String());
    });
    return;
}

}
} 
