#pragma once 

#include "coord/builtin/type.h"
#include "coord/cluster/cluster_node_config.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;

namespace redis {
class AsyncClient;
class Client;
class RedisResult;
}

///
/// | key                   | type   |  desc           | attr   |
/// | ------                | ------ | ------          |------  |
/// | [group]               | hash   | 节点集合         | {"name:"version"} |
/// | [group]:[fullName]    | string | 节点             | address |

/// [group]中取出所有节点，（然后逐个获取[group]:[fullName], 对比本地数据，检查是否有删除的节点，是否有新增加的节点，是否有版本改变的节点）
/// 
namespace cluster {//tolua_export

class Cluster;

class cluster_redis_config : public cluster_node_config {//tolua_export
public:
    cluster_redis_config(Coord *coord, Cluster* cluster);
    virtual ~cluster_redis_config();
public:
    virtual int main();
    virtual int reload();
    virtual int reload(const char* node, uint64_t version);
    virtual int heartbeat();
public:
    int connect();
    int registerSelf();
    int checkNodeStatusAsync();
    int checkNodeStatusAsync(std::string nodeName, uint64_t version);
    int checkNodeStatus();
    int checkNodeStatus(const char* nodeName, uint64_t version);
    void recvNodeExpire(cluster_node* node);
    void recvNodeNew(cluster_node* node);
public:
    redis::Client*                                  syncClient;
    redis::AsyncClient*                             asyncClient;
    std::string                                     group;
    std::string                                     address;
    std::map<std::string, cluster_node*>            nodeDict;
    std::string                                     rkey;
};//tolua_export

cluster_redis_config* newClusterRedisConfig(Coord* coord, Cluster* cluster);
}//tolua_export
}//tolua_export


