#pragma once 

#include "coord/builtin/type.h"
#include <map>
#include <string>

namespace coord {//tolua_export
///
/// | key                   | type   |  desc           | attr   |
/// | ------                | ------ | ------          |------  |
/// | [group]:[node]        | hash   | 网关的属性       | {"version":"0.0.0", "host":"127.0.0.1", "port":"8080"} |
/// | [group]               | set    | 网关列表         | [node1, node2] |
/// | [group]:[version]     | set    | 网关版本列表     | [node1, node2] |
/// | [group]:[node]:user   | hash   | 网关用户列表     | {"userid1":"node1", "userid2":"node2"} |
/// | [group]:userid        | string | 用户所在的节点   | node1 |
namespace redis {
class AsyncClient;
class Client;
class Reply;
}
namespace cluster {
class Request;
class Result;
}
class Coord;
namespace gate {

class Gate;

class gate_cluster  {
CC_CLASS(gate_cluster);  
public:
    gate_cluster(Coord* coord, Gate* gate);
    virtual ~gate_cluster();
public:
    int main();
    void onDestory();
    int clearUser();
    int clearSelf();
    int registerSelf();
    int tryRegisterAgent(uint64_t sessionId, uint64_t userId);
    int registerAgent(uint64_t sessionId, uint64_t userId);
    void unregisterAgent(uint64_t sessionId, uint64_t userId);
    void persistAgent(uint64_t userId);
    void persistSelf();
    void checkExpireGate();
    void recvConnectCacheSucc(redis::AsyncClient* client, const redis::Reply* reply);
    void recvConnectCacheErr(redis::AsyncClient* client, const redis::Reply* reply);
    void recvCacheScriptLoadSucc(redis::AsyncClient* client, const redis::Reply* reply, const char* name);
    void recvCacheScriptLoadError(redis::AsyncClient* client, const redis::Reply* reply);
    void recvTryRegisterSucc(redis::AsyncClient* client, const redis::Reply* reply, uint64_t sessionId, uint64_t userId);
    void recvTryRegisterError(redis::AsyncClient* client, const redis::Reply* reply, uint64_t sessionId, uint64_t userId);
    void recvRegisterSucc(redis::AsyncClient* client, const redis::Reply* reply, uint64_t sessionId, uint64_t userId);
    void recvRegisterError(redis::AsyncClient* client, const redis::Reply* reply, uint64_t sessionId, uint64_t userId);
    void recvUnregisterSucc(redis::AsyncClient* client, const redis::Reply* reply, uint64_t sessionId, uint64_t userId);
    void recvUnregisterError(redis::AsyncClient* client, const redis::Reply* reply, uint64_t sessionId, uint64_t userId);
    //中断上一个请求
    void abortRegisterOrInsteadRequest(uint64_t userId);
    //cluster
    void recvClusterUserInstead(cluster::Request* request);
    void recvClusterUserInsteadSucc(cluster::Result* result, uint64_t sessionId, uint64_t userId);
    void recvClusterUserInsteadErr(cluster::Result* result, uint64_t sessionId, uint64_t userId);
public:
    Coord*                                          coord;
    Gate*                                           gate;
    redis::AsyncClient*                             asyncClient;
    redis::Client*                                  syncClient;
    std::string                                     group;
    std::string                                     userHashKey;
    std::string                                     gateSetKey;
    std::string                                     gateSetVersionKey;
    std::map<std::string, std::string>              scriptShaDict;          // lua script sha
    std::map<uint64_t, uint64_t>                    registeringUserDict;    // user id => session id, 只记录一个session, 新的进来，就取消上一个请求
    std::map<uint64_t, cluster::Request*>           insteadRequestDict;     // user id => cluster request, 只记录一个session, 新的进来，就取消上一个请求
    std::string                                     selfKey;
};

gate_cluster* newgate_cluster(Coord* coord, Gate* gate);



}//tolua_export
}//tolua_export


