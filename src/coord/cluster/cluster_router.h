#pragma once 

#include "coord/component/component.h"
#include "coord/coordx.h"
#include <map>
#include <string>
#include <functional>
namespace coord {//tolua_export

class Coord;

class ScriptComponent;

namespace cluster {//tolua_export

class Request;
class GateNotify;

typedef std::function<void (Request* request)> ClusterRouter_RecvClusterRequest; 
typedef std::function<void (GateNotify* notify)> ClusterRouter_RecvClusterNotify; 

class cluster_router_handler {
public:
    cluster_router_handler(Coord* coord, ClusterRouter_RecvClusterRequest recvClusterRequest, int ref = 0): 
        coord(coord), recvClusterRequestFunc(recvClusterRequest), ref(ref) {
        this->times = 0;
        this->consumeTime = 0;
    }
    cluster_router_handler(Coord* coord, ClusterRouter_RecvClusterNotify recvClusterNotify, int ref = 0): 
        coord(coord), recvClusterNotifyFunc(recvClusterNotify), ref(ref) {
        this->times = 0;
        this->consumeTime = 0;
    }
    ~cluster_router_handler();
public:
    void recvClusterRequest(Request* request);
    void recvClusterNotify(GateNotify* notify);
public:
    Coord*                              coord;
    ClusterRouter_RecvClusterRequest    recvClusterRequestFunc;
    ClusterRouter_RecvClusterNotify     recvClusterNotifyFunc;
    int                                 ref;    
    int                                 times;              //处理次数
    int                                 consumeTime;        //耗时
};

class cluster_router_tree {
public:
    cluster_router_tree() {
    }
    ~cluster_router_tree() {
    }
public:
    std::map<std::string, cluster_router_handler*> handlerDict;
};

class ClusterRouter {//tolua_export
RC_CLASS(ClusterRouter);
public:
    ClusterRouter(Coord* coord);
    virtual ~ClusterRouter();
public:
    bool Notify(const char* route, ClusterRouter_RecvClusterNotify func);
    bool Notify(const char* route, ScriptComponent* object, int ref);
    int Notify(lua_State* L);//tolua_export
    bool Request(const char* route, ClusterRouter_RecvClusterRequest func);
    bool Request(const char* route, ScriptComponent* object, int ref);//tolua_export
    int Request(lua_State* L);//tolua_export
    void Trace();//tolua_export
public:
    void recvClusterRequest(cluster::Request* request);
    void recvClusterNotify(cluster::GateNotify* notify);
private:
    cluster_router_handler* searchHandler(const char* event, const char* path);
    bool addRoute(const char* event, const char* path, cluster_router_handler* handler);
    cluster_router_tree* getTree(const char* event);
public:
    Coord*                                      coord;
    std::map<std::string, cluster_router_tree*> trees;
};//tolua_export

ClusterRouter* newClusterRouter(Coord* coord);

}//tolua_export
}//tolua_export
 
