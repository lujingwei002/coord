
#include "coord/object/object.h"
#include "coord/component/component.h"
#include "coord/component/script_component.h"
#include "coord/display/transform.h"
#include "coord/net/tcp_listener.h"
#include "coord/http/http_server.h"
#include "coord/log/log.h"
#include "coord/coord.h"

#include <string.h>
#include <type_traits>
namespace coord {
CC_IMPLEMENT(Object, "coord::Object")

Object* newObject(Coord* coord, const char* name) {
    Object* object = new Object(coord, name);
    return object;
}

Object::Object(Coord* coord, const char* name) {
    this->coord = coord;
    this->data = nullptr;
    this->scene = nullptr;
    this->id = 0;
    this->transform = nullptr;
    this->parent = nullptr;
    strcpy(this->name, name);
}

Object::~Object() {
    this->coord->CoreLogDebug("[Object] ~Object, name=%s", this->name);
    for(auto object : this->children) {
        delete object;
    }
    this->children.clear();
    for (auto component : this->componentArr) {
        delete component;
    }
    this->componentArr.clear();
}

void Object::Create() {

}

int Object::Save() {
    return 0;
}

int Object::AddScript(lua_State* L) {
    if (!lua_istable(L, 2)) {
        this->coord->CoreLogError("[Object] AddScript failed, error='arg 1 table expected");
        return 0;
    }
    // 验证是否一个合法的lua component
    lua_pushvalue(L, 2);                        // arg component component
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);   // arg component
    lua_pushstring(L, "__COMPONENT");           // arg component '__COMPONENT'
    lua_gettable(L, -2);                        // arg component component['__COMPONENT']
    if (!lua_isstring(L, -1)) {
        lua_pop(L, 1);
        this->coord->CoreLogError("[Object] AddScript failed, error='invalid script component");
        return 0;
    }
    const char* scriptName =  (const char*)lua_tostring(L, -1);
    lua_pop(L, 1);
    ScriptComponent* component = new ScriptComponent(this->coord, scriptName, ref);
    int err = this->AddComponent(component);
    if (err) {
        return 0;
    }
    tolua_pushusertype(L, (void*)component, "coord::ScriptComponent");
    return 1;
} 

int Object::AddComponent(Component* component) {
    const char* typeName = component->TypeName();
    ScriptComponent* script = dynamic_cast<ScriptComponent*>(component);
    if (script) {
        typeName = script->GetScriptName();
    }
    this->coord->CoreLogDebug("[Object<%s>] AddComponent, type='%s'", this->name, typeName);
    auto it = this->componentDict.find(typeName);
    if (it != this->componentDict.end()) {
        this->coord->CoreLogError("[Object<%s>] AddComponent failed, type='%s'", this->name, typeName);
        return -1;
    }
    this->componentArr.push_back(component);
    this->componentDict[component->TypeName()] = component;
    component->SetObject(this);
    component->onAwake();
    return 0;
}

int Object::RemoveComponent(Component* component) {
    if (!component){
        return 0;
    }
    for (auto it = this->componentDict.begin(); it != this->componentDict.end(); ++it) {
        if (component == it->second){
            this->componentDict.erase(it);
            break;
        }
    }
    for (auto it = this->componentArr.begin(); it != this->componentArr.end(); ++it) {
        if (*it == component) {
            //交换，再删除
            this->componentArr.erase(it);
            break;
        }
    }
    component->onDestory();
    delete component;
    return 0;
}

void Object::onUpdate(uint64_t cur_tick) {
    //处理组件
    std::vector<Component*> componentArr;
    for (auto component : this->componentArr) {
        componentArr.push_back(component);
    }
    for (auto component : componentArr) {
        component->onUpdate(cur_tick);
    }
    //处理节点
    std::vector<Object*> objectArr;
    for (auto object : this->children){
        objectArr.push_back(object);
    } 
    for (auto object : objectArr){
        object->onUpdate(cur_tick);
    }
}

void Object::onReload() {
    //处理组件
    std::vector<Component*> componentArr;
    for (auto component : this->componentArr) {
        componentArr.push_back(component);
    }
    for (auto component : componentArr) {
        component->onReload();
    }
    //处理节点
    std::vector<Object*> objectArr;
    for (auto object : this->children){
        objectArr.push_back(object);
    } 
    for (auto object : objectArr){
        object->onReload();
    }
}

Object* Object::GetChild(int index){
    if (index < 0 || index >= (int)children.size()) {
        return nullptr;
    }
    return this->children[index];
}

int Object::AddChild(Object* object) {
    if (nullptr == object) {
        return -1;
    }
    //从父对象分离
    if (object->parent) {
        int err = object->removeFromParent();
        if (err) {
            return err;
        }
    }
    this->children.push_back(object);
    object->parent = this;
    return 0;
}

Object* Object::GetParent() {
    return this->parent;
}

int Object::ChildIndex(Object* object) {
    for(int i = 0; i < (int)this->children.size(); i++) {
        if (this->children[i] == object){
            return i;
        }
    }
    return -1;
}

int Object::removeFromParent() {
    if (nullptr == this->parent) {
        return 0;
    }
    int err = this->parent->removeChild(this);
    if (err) {
        return err;
    }
    this->parent = nullptr;
    return 0;
}

int Object::removeChild(Object* object) {
    for(auto it = this->children.begin(); it != this->children.end(); ++it) {
        if (*it == object) {
            this->children.erase(it);
            return 0;
        }
    }
    return -1;
}

Component* Object::GetComponent(Type* type) {
    for (auto component : this->componentArr) {
        if (type == component->GetType()) {
            return component;
        }
    }
    return nullptr;
}

Component* Object::GetComponent(const char* name) {
    std::map<std::string, Component*>::iterator it;
    it = this->componentDict.find(name);
    if (it == this->componentDict.end()) {
        return nullptr;
    }
    return it->second;
}

int Object::GetComponent(lua_State* L){
    const char* name = ((const char*)tolua_tostring(L, 2, 0));
    Component* component = this->GetComponent(name);
    if (component == NULL){
        return 0;
    }
    tolua_pushusertype(L, (void*)component, name);
    return 1;
}

ScriptComponent* Object::GetScript(const char* name){
    Component* component = this->GetComponent(name);
    if (component == nullptr) {
        return nullptr;
    }
    if (component->GetType() != ScriptComponent::_type) {
        return nullptr;
    }
    return (ScriptComponent*)component;
}

void Object::onDestory() {
    
    //处理节点
    std::vector<Object*> objectArr;
    for (auto object : this->children){
        objectArr.push_back(object);
    } 
    //for (auto object : objectArr){
       // this->coord
       // object->onDestory();
    //} 
    //处理组件
    std::vector<Component*> componentArr;
    for (auto component : this->componentArr) {
        componentArr.push_back(component);
    }
    for (auto component : componentArr) {
        component->onDestory();
    }
    //从父对象分离
    if (this->parent) {
        int err = this->removeFromParent();
        if (err) {
        //    return err;
        }
    }
}

void Object::onAwake() {
    this->coord->CoreLogDebug("[Object<%s>] onAwake", this->name);
    this->transform = this->AddComponent<Transform>();
}

void Object::onStart() {
    //处理组件
    std::vector<Component*> componentArr;
    for (auto component : this->componentArr) {
        if (!component->isStart) componentArr.push_back(component);
    }
    for (auto component : componentArr) {
        component->onStart();
        component->isStart = true;
    }
    //处理节点
    std::vector<Object*> objectArr;
    for (auto object : this->children){
        objectArr.push_back(object);
    } 
    for (auto object : objectArr){
        object->onStart();
    } 
}

void Object::Trace(int deep) {
    static char tab[1024];
    tab[0] = 0;
    for (int i = 0; i < deep; i++){
        strcat(tab, "  ");
    }
    //this->coord->CoreLogDebug("%s|-%s", tab, this->name);
    for (uint32_t i = 0; i < this->componentArr.size(); i++){
        Component* component = componentArr[i];
        if (component->GetType() == ScriptComponent::_type){
            //this->coord->CoreLogDebug("%s  <%s(%s)>", tab, component->TypeName(), ((ScriptComponent*)component)->scriptName);
        }
        else {
            //this->coord->CoreLogDebug("%s  <%s>", tab, component->TypeName());
        }
    }
    for (uint32_t i = 0; i < this->children.size(); i++){
        Object* obj = this->children[i];
        obj->Trace(deep + 1);
    }
}

void Object::setScene(Scene* scene) {
    this->scene = scene;
    for (auto object : this->children){
        object->setScene(scene);
    } 
}

}
