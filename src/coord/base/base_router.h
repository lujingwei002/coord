#pragma once 

#include "coord/component/component.h"
#include "coord/component/script_component.h"
#include "coord/coordx.h"
#include "coord/coordx.h"
#include "coord/script/script.h"
#include "coord/coord.h"
#include <map>
#include <string>
#include <functional>
namespace coord {//tolua_export

class Coord;

class ScriptComponent;


template<typename TRequest, typename TNotify, typename TResponse>
class base_router {//tolua_export
public:

typedef std::function<void (TRequest* request)> RouterRecvRequestFunc; 
typedef std::function<void (TNotify* notify)> RouterRecvNotifyFunc; 

class base_router_handler {
friend base_router;
private:
    base_router_handler(Coord* coord, RouterRecvRequestFunc recvRequest, int ref = 0): 
        coord(coord), recvRequestFunc(recvRequest), ref(ref) {
        this->times = 0;
        this->consumeTime = 0;
    }
    base_router_handler(Coord* coord, RouterRecvNotifyFunc recvNotify, int ref = 0): 
        coord(coord), recvNotifyFunc(recvNotify), ref(ref) {
        this->times = 0;
        this->consumeTime = 0;
    }
    ~base_router_handler() {
        if(this->ref >= 0) {
            luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
            this->ref = 0;
        }
    }
private:
    void recvRequest(TRequest* request) {
        if(this->recvRequestFunc != nullptr){
            this->recvRequestFunc(request);
        } 
    }
    void recvNotify(TNotify* notify) {
        if(this->recvNotifyFunc != nullptr){
            this->recvNotifyFunc(notify);
        } 
    }
private:
    Coord*                              coord;
    RouterRecvRequestFunc               recvRequestFunc;
    RouterRecvNotifyFunc                recvNotifyFunc;
    int                                 ref;    
    int                                 times;              //处理次数
    int                                 consumeTime;        //耗时
};

class base_router_tree {
friend base_router;
private:
    base_router_tree() {
    }
    ~base_router_tree() {
    }
private:
    std::map<std::string, base_router_handler*> handlerDict;
};

protected:
    base_router(Coord* coord) {
        this->coord = coord;
    }
    virtual ~base_router() {
    }
public:
    virtual const char* TypeName() const {
        return nullptr;
    }
    bool Notify(const char* route, RouterRecvNotifyFunc func) {
        if(func == NULL) {
            return this->addRoute("NOTIFY", route, NULL);
        } else {
            base_router_handler* handler = new base_router_handler(this->coord, func);
            return this->addRoute("NOTIFY", route, handler);
        }
    }
    bool Notify(const char* route, ScriptComponent* object, int ref) {
        if(object == NULL) {
            return this->addRoute("NOTIFY", route, NULL);
        } else {
            base_router_handler* handler = new base_router_handler(this->coord, std::bind(&ScriptComponent::recvNotify, object, std::placeholders::_1, "recvNotify", ref), ref);
            return this->addRoute("NOTIFY", route, handler);
        }
    }
    int Notify(lua_State* L) {
#ifndef TOLUA_RELEASE
        tolua_Error tolua_err;
        if (
            !tolua_isusertype(L,1,this->TypeName(),0,&tolua_err) ||
            !tolua_isstring(L,2,0,&tolua_err) ||
            !tolua_isusertype(L,3,"coord::ScriptComponent",0,&tolua_err) ||
            !tolua_isfunction(L,4,0,&tolua_err) ||
            !tolua_isnoobj(L,5,&tolua_err)
        )
            goto tolua_lerror;
        else
#endif
        {
            const char* route = (const char*) tolua_tostring(L, 2, 0);
            coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,3,0));
            lua_pushvalue(L, 4);
            int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
            if (ref < 0) {
                tolua_error(L, "error in function 'Notify'.\nattempt to set a nil function", NULL);
                return 0;
            }
            bool result = this->Notify(route, object, ref);
            if(!result) {
                luaL_unref(L, LUA_REGISTRYINDEX, ref);
            }
            tolua_pushboolean(L, result);
        }
        return 1;
#ifndef TOLUA_RELEASE
        tolua_lerror:
        tolua_error(L,"#ferror in function 'Notify'.",&tolua_err);
        return 0;
#endif
    }
    bool Request(const char* route, RouterRecvRequestFunc func) {
        if(func == nullptr) {
            return this->addRoute("REQUEST", route, nullptr);
        } else {
            base_router_handler* handler = new base_router_handler(this->coord, func);
            return this->addRoute("REQUEST", route, handler);
        }
    }
    bool Request(const char* route, ScriptComponent* object, int ref) {
        if(object == nullptr) {
            return this->addRoute("REQUEST", route, nullptr);
        } else {
            base_router_handler* handler = new base_router_handler(this->coord, std::bind(&ScriptComponent::recvRequest, object, std::placeholders::_1, "recvRequest", ref), ref);
            return this->addRoute("REQUEST", route, handler);
        }
    }
    int Request(lua_State* L) {
        #ifndef TOLUA_RELEASE
        tolua_Error tolua_err;
        if (
            !tolua_isusertype(L,1, this->TypeName(),0,&tolua_err) ||
            !tolua_isstring(L,2,0,&tolua_err) ||
            !tolua_isusertype(L,3,"coord::ScriptComponent",0,&tolua_err) ||
            !tolua_isfunction(L,4,0,&tolua_err) ||
            !tolua_isnoobj(L,5,&tolua_err)
        )
            goto tolua_lerror;
        else
#endif
        {
            const char* route = (const char*) tolua_tostring(L, 2, 0);
            coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,3,0));
            lua_pushvalue(L, 4);
            int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
            if (ref < 0) {
                tolua_error(L, "error in function 'Request'.\nattempt to set a nil function", NULL);
                return 0;
            }
            bool result = this->Request(route, object, ref);
            if(!result) {
                luaL_unref(L, LUA_REGISTRYINDEX, ref);
            }
            tolua_pushboolean(L, result);
        }
        return 1;
#ifndef TOLUA_RELEASE
        tolua_lerror:
        tolua_error(L,"#ferror in function 'Request'.",&tolua_err);
        return 0;
#endif
    }
    void Trace() {
        for(auto const& it : this->trees){
            auto event = it.first;
            auto tree = it.second;
            for(auto const& it1 : tree->handlerDict) {
                auto handler = it1.second;
                uint64_t averageTime = handler->times <= 0 ? 0 : (handler->consumeTime/handler->times);
                this->coord->CoreLogDebug("[%s] %10s | %10d | %10s | %s", this->TypeName(), event.c_str(), handler->times, coordx::date::FormatNano(averageTime), it1.first.c_str());
            }
        }
    }
protected:
    void recvRequest(TRequest* request) {
        this->coord->CoreLogDebug("[base_router] recvRequest %s", request->TypeName());
        base_router_handler* handler = this->searchHandler("REQUEST", request->Route.c_str());
        if(handler == nullptr){
            this->coord->CoreLogDebug("[%s] recvRequest failed, error='router not found', path=%s", this->TypeName(), request->Route.c_str());
            TResponse* response = request->GetResponse();
            response->String("Not Found");
            response->Reject(404);
        } else {
            uint64_t t1 = this->coord->NanoTime();
            handler->recvRequest(request);
            handler->times++;
            handler->consumeTime += (this->coord->NanoTime() - t1);
        }
    }
    void recvNotify(TNotify* notify) {
        this->coord->CoreLogDebug("[%s] recvNotify %s", this->TypeName(), notify->TypeName());
        base_router_handler* handler = this->searchHandler("NOTIFY", notify->Route.c_str());
        if(handler == nullptr){
            this->coord->CoreLogDebug("[%s] recvNotify %s failed, error='router not found', path=%s", this->TypeName(), notify->TypeName(), notify->Route.c_str());
            return;
        }
        uint64_t t1 = this->coord->NanoTime();
        handler->recvNotify(notify);
        handler->times++;
        handler->consumeTime += (this->coord->NanoTime() - t1);
    }
private:
    base_router_handler* searchHandler(const char* method, const char* route) {
        base_router_tree* tree = this->getTree(method);
        auto it = tree->handlerDict.find(route);
        if (it == tree->handlerDict.end()){
            return nullptr;
        } 
        return it->second;
    }
    bool addRoute(const char* method, const char* route, base_router_handler* handler) {
        base_router_tree* tree = this->getTree(method);
        this->coord->CoreLogDebug("[%s] add route, method=%-10s, route=%-64s, handler=0x%x", this->TypeName(), method, route, handler);
        auto it = tree->handlerDict.find(route);
        if (it != tree->handlerDict.end()) {
            delete it->second;
            tree->handlerDict.erase(it);
            tree->handlerDict[route] = handler;
        } else {
            tree->handlerDict[route] = handler;
        }
        return true;
    }
    base_router_tree* getTree(const char* method) {
        const auto it = this->trees.find(method);
        if (it == this->trees.end()){
            base_router_tree* tree = new base_router_tree();
            this->trees[method] = tree;
            return tree;
        } else {
            return it->second;
        }
    }
private:
    Coord*                                      coord;
    std::map<std::string, base_router_tree*>    trees;
};//tolua_export

//RC_IMPLEMENT(base_router, "coord::base_router")

}//tolua_export
 
