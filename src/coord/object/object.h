#pragma once 

#include "coord/coordx.h"
#include "coord/coordx.h"

#include <stdlib.h> 
#include <stdint.h> 
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

namespace coord {//tolua_export
class Node;
class Component;
class ScriptComponent;
class Transform;
class Scene;
class Coord;
namespace net {
class ITcpHandler;
class ITcpServer;
}
namespace http {
class IHttpHandler;
class HttpRequest;
class HttpResponse;
class HttpFrame;
}
class Object : public coordx::RcObject {//tolua_export
CC_CLASS(Object)
public:
    Object(Coord* coord, const char* name);
    virtual ~Object();
public:
    //创建
    void Create();//tolua_export
    //保存
    int Save();//tolua_export
    //帧函数
    void onUpdate(uint64_t cur_tick);
    //帧函数
    void onReload();
    //唤醒
    void onAwake();
    //开始
    void onStart();
    //销毁
    void onDestory();
public:
    //组件相关
    template<class T>
    T* AddComponent();

    template<class T>
    int RemoveComponent();

    template<class T>
    T* GetComponent();
    int AddComponent(Component* component);//tolua_export
    int AddScript(lua_State* L);//tolua_export
    int RemoveComponent(Component* component);//tolua_export
    Component* GetComponent(Type* type);//tolua_export
    Component* GetComponent(const char* name);//tolua_export
    int GetComponent(lua_State* L);//tolua_export
    ScriptComponent* GetScript(const char* classname);//tolua_export
    
    /// #子对象相关
    Object* GetChild(int index);    //tolua_export
    Object* GetParent();            //tolua_export
    int AddChild(Object* obj);      //tolua_export
    int ChildIndex(Object* obj);    //tolua_export                  //tolua_export
    void Trace(int deep = 0);       //tolua_export
public:
    int removeChild(Object* obj);   
    int removeFromParent();
    void setScene(Scene* scene);
public:
    int             id;             //tolua_export
    void*           data;           //tolua_export
    char            name[64];       //tolua_export
    Transform*      transform;      //tolua_export
    Scene*          scene;          //tolua_export
    Coord*          coord;          //tolua_export
private:
    Object*                             parent;
    std::vector<Object*>                children;
    std::vector<Component*>             componentArr;
    std::map<uint32_t, Component*>      messageListner;
    std::map<std::string, Component*>   componentDict;
};//tolua_export


Object* newObject(Coord* coord, const char* name);

template<class T>T* Object::AddComponent(){
    T* component = new T(this->coord);
    this->AddComponent(component);
    return component;
}

template<class T>
T* Object::GetComponent(){
    return this->GetComponent(T::_type);
}

template<class T>
int Object::RemoveComponent(){
    Component* component = this->GetComponent(T::_type);
    return this->RemoveComponent(component);
}

}//tolua_export
