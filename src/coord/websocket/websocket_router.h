#pragma once 

#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/coordx.h"
#include "coord/http/http_base.h"
#include <map>
#include <string>
#include <functional>
namespace coord {//tolua_export

class Coord;

class ScriptComponent;

namespace websocket {//tolua_export

class Agent;
class Frame;

typedef std::function<void (Agent* agent)> RecvWebSocketFunc; 
typedef std::function<void (Agent* agent, Frame* frame)> RecvWebSocketFrameFunc; 


class router_handler {
public:
    router_handler(Coord* coord, RecvWebSocketFunc recvWebSocketNewFunc, int ref = 0): 
        coord(coord), recvWebSocketNewFunc(recvWebSocketNewFunc), ref(ref) {
        this->times = 0;
        this->consumeTime = 0;
    }
    router_handler(Coord* coord, RecvWebSocketFrameFunc recvWebSocketFrameFunc, int ref = 0): 
        coord(coord), recvWebSocketFrameFunc(recvWebSocketFrameFunc), ref(ref) {
        this->times = 0;
        this->consumeTime = 0;
    }
    ~router_handler();
public:
    void recvWebSocketNew(Agent* agent);
    void recvWebSocketClose(Agent* agent);
    void recvWebSocketFrame(Agent* agent, Frame* frame);
public:
    Coord*                              coord;
    RecvWebSocketFunc                   recvWebSocketNewFunc;
    RecvWebSocketFrameFunc              recvWebSocketFrameFunc;
    int                                 ref;    
    int                                 times;              //处理次数
    int                                 consumeTime;        //耗时
};

class router_tree {
public:
    router_tree() {
    }
    ~router_tree() {
    }
public:
    std::map<std::string, router_handler*> handlerDict;
};

class Router {//tolua_export
RC_CLASS(Router);
public:
    Router(Coord* coord);
    virtual ~Router();
public:
    bool Message(const char* route, RecvWebSocketFrameFunc func);
    bool Message(const char* route, ScriptComponent* object, int ref);
    int Message(lua_State* L);//tolua_export
    void Trace();
public:
    void recvWebSocketFrame(Agent* agent, Frame* frame);
    void recvWebSocketNew(Agent* agent);
    void recvWebSocketClose(Agent* agent);
private:
    router_handler* searchHandler(const char* method, const char* path);
    bool addRoute(const char* method, const char* path, router_handler* handler);
    router_tree* getTree(const char* event);
public:
    Coord* coord;
    std::map<std::string, router_tree*> trees;
};//tolua_export

Router* newRouter(Coord* coord);

}//tolua_export
}//tolua_export
 