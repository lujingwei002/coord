#pragma once 

#include "coord/component/component.h"
#include "coord/coordx.h"
#include <map>
#include <string>
#include <functional>

namespace coord {//tolua_export

class Coord;

class ScriptComponent;

namespace worker {//tolua_export

class Request;
class Notify;

typedef std::function<void (Request* request)> RecvRequestFunc; 
typedef std::function<void (Notify* notify)> RecvNotifyFunc; 

class worker_router_handler {
public:
    worker_router_handler(Coord* coord, RecvRequestFunc recvWorkerRequest, int ref = 0): 
        coord(coord), recvWorkerRequestFunc(recvWorkerRequest), ref(ref) {
        this->times = 0;
        this->consumeTime = 0;
    }
    worker_router_handler(Coord* coord, RecvNotifyFunc recvWorkerNotify, int ref = 0): 
        coord(coord), recvWorkerNotifyFunc(recvWorkerNotify), ref(ref)  {
        this->times = 0;
        this->consumeTime = 0;
    }
    ~worker_router_handler();
public:
    void recvWorkerRequest(Request* request);
    void recvWorkerNotify(Notify* notify);
public:
    Coord*                          coord;
    RecvRequestFunc                 recvWorkerRequestFunc;
    RecvNotifyFunc                  recvWorkerNotifyFunc;
    int                             ref;
    int                             times;              //处理次数
    int                             consumeTime;        //耗时
};

class worker_router_tree {
public:
    worker_router_tree() {
    }
    ~worker_router_tree() {
    }
public:
    std::map<std::string, worker_router_handler*> handlerDict;
};

class WorkerRouter {//tolua_export
RC_CLASS(WorkerRouter);
public:
    WorkerRouter(Coord* coord);
    virtual ~WorkerRouter();
public:
    bool Request(const char* route, RecvRequestFunc func);
    int Request(lua_State* L);//tolua_export
    bool Notify(const char* route, RecvNotifyFunc func);
    int Notify(lua_State* L);//tolua_export
    void Trace();//tolua_export
public:
    bool request(const char* route, ScriptComponent* object, int ref);
    bool notify(const char* route, ScriptComponent* object, int ref);
    void recvWorkerRequest(worker::Request* request);
    void recvWorkerNotify(worker::Notify* notify);
private:
    worker_router_handler* searchHandler(const char* event, const char* route);
    bool addRoute(const char* event, const char* route, worker_router_handler* handler);
    worker_router_tree* getTree(const char* event);
public:
    Coord*                                      coord;
    std::map<std::string, worker_router_tree*>  trees;
};//tolua_export

WorkerRouter* newWorkerRouter(Coord* coord);


}//tolua_export
 
}//tolua_export
 