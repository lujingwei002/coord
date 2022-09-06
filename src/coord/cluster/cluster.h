#pragma once 

#include "coord/coordx.h"
#include "coord/protobuf/init.h"
#include "coord/cluster/cluster_config.h"
#include "coord/protobuf/declare.h"
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>
namespace coord {//tolua_export
    
class Coord;


namespace cluster {//tolua_export


class cluster_client;
class cluster_server;
class cluster_node_config;
class cluster_node;
class GateNotify;
class Request;
class ClusterRouter;
class Promise;

class Cluster {//tolua_export
RC_CLASS(Cluster);
public:
    Cluster(Coord *coord);
    virtual ~Cluster();
public:
    int main();
    /// 获取cluser的配置信息
    ClusterConfig* DefaultConfig();
    /// 向节点发送notify消息
    int Notify(const char* node, const char* route, const char* data);//tolua_export
    /// 向节点发送notify消息
    int Notify(const char* node, const char* route, const char* data, size_t len);
    /// 向节点发送request消息
    Promise* Request(const char* node, const char* route, const char* data);//tolua_export
    /// 向节点发送request消息
    Promise* Request(const char* node, const char* route, const char* data, size_t len);
    /// 向节点发送request消息
    Promise* Request(const char* node, const char* route, protobuf::MessageRef& proto);//tolua_export
    /// 向节点发送request消息
    Promise* Request(const char* node, const char* route, google::protobuf::Message* message);

    void Reload();//tolua_export
public:
    void reload(const char* node, uint64_t version);
    //接收到新节点通知
    void recvNodeNew(cluster_node* node);
    //接收到节点过期的通知
    void recvNodeExpire(cluster_node* node);
    void recvClientClose(cluster_client* client);
    void recvClusterNotify(cluster::GateNotify* notify);
    void recvClusterRequest(cluster::Request* request);
public:
    std::string                             Name;       //tolua_export 节点名字
    std::string                             FullName;   //tolua_export 节点版本名字
    uint64_t                                Version;    //tolua_export 节点版本
    ClusterRouter*                          Router;     //tolua_export
public:
    Coord*                                  coord;
    cluster_server*                         server;
    std::map<std::string, cluster_client*>  clientDict;
    cluster_node_config*                    nodeConfig;
    ClusterConfig                           config;
};//tolua_export

Cluster* newCluster(Coord* coord);
}//tolua_export
}//tolua_export


