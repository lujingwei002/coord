#include "coord/scene/scene.h"
#include "coord/scene/scene_mgr.h"
#include "coord/object/object.h"
#include "coord/script/script.h"
#include "coord/log/log.h"
#include "coord/coord.h"
#include <stdio.h>
#include <iostream>

namespace coord {

CC_IMPLEMENT(Scene, "coord::Scene")

Scene *newScene(Coord* coord, SceneMgr *sceneMgr) {
    Scene *scene = new Scene(coord, sceneMgr);
    return scene;
}

Scene::Scene(Coord* coord, SceneMgr *sceneMgr) {
    this->coord = coord;
    this->sceneMgr = sceneMgr;
}

Scene::~Scene() {
    this->coord->coreLogDebug("[Scene] ~Scene, name=%s", this->name);
    while(this->objectArr.size() > 0){
        Object* object = this->objectArr.back();
        this->objectArr.pop_back();
        delete object;
    }
}

Object* Scene::CreateObject(const char* name) {
    Object* object = this->createObjectInternal(name);
    if (object == nullptr) {
        return nullptr;
    }
    object->onAwake();
    return object;
}

Object* Scene::createObjectInternal(const char* name) {
    Object* object = newObject(this->coord, name);
    this->addObject(object);
    return object;
}

Object* Scene::Instantiate(const char* name, const char* filePath) {
    lua_State* L = this->coord->Script->L;
    //LOG_DEBUG("scene[%d] create object local %s", this->id, filePath);
    Object* object = NULL;
    if (filePath == NULL) {
        object = newObject(this->coord, name);
    } 
    else {
        //调用脚本初始化实体
        lua_getglobal(L, "instantiate");
        lua_getglobal(L, filePath);
        if (lua_pcall(L, 1, 1, 0) != 0) {
            //LOG_DEBUG("node[%d] create object local error %s", this->id, lua_tostring(L, -1));
            //this->TraceStack();
        }
        tolua_Error tolua_err;
        if(!tolua_isusertype(L, -1, "GameObject", 0, &tolua_err)) {
            this->coord->coreLogError("object is nil");
            lua_pop(L, lua_gettop(L));
            return NULL;
        }
        object = (Object*)tolua_tousertype(L, -1, 0);
        lua_pop(L, lua_gettop(L));
    }
    if (object == NULL) {
        this->coord->coreLogError("Scene.CreateObject failed");
        return NULL;
    }
    this->addObject(object);
    object->onAwake();
    return object;
}

int Scene::addObject(Object* object) {
    if (nullptr == object) {
        return -1;
    }
    //从场景分离
    if (object->scene) {
        return -1;
    } 
    object->setScene(this);
    this->objectArr.push_back(object);
    return 0;
}

void Scene::onUpdate(uint64_t cur_tick) {
    //this->coord->coreLogError("[Scene<%s>] onUpdate", this->name);
    std::vector<Object*> objectArr;
    for (auto object : this->objectArr) {
        objectArr.push_back(object);
    }
    for (auto object : objectArr) {
        object->onUpdate(cur_tick);
    }
} 

void Scene::onReload() {
    std::vector<Object*> objectArr;
    for (auto object : this->objectArr) {
        objectArr.push_back(object);
    }
    for (auto object : objectArr) {
        object->onReload();
    }
} 

void Scene::onAwake() {
    this->coord->coreLogDebug("[Scene<%s>] onAwake", this->name);
    std::vector<Object*> objectArr;
    for (auto object : this->objectArr) {
        objectArr.push_back(object);
    }
    for (auto object : objectArr) {
        object->onAwake();
    }
} 

void Scene::onStart() {
    std::vector<Object*> objectArr;
    for (auto object : this->objectArr) {
        objectArr.push_back(object);
    }
    for (auto object : objectArr) {
        object->onStart();
    }
} 

int Scene::create(const char* sceneName) {
    strcpy(this->name, sceneName);
    return 0;
}

int Scene::Destory() {
    //处理节点
    std::vector<Object*> objectArr;
    for (auto object : this->objectArr){
        objectArr.push_back(object);
    } 
    for (auto object : objectArr){
        this->coord->Destory(object);
    } 


    

    this->onDestory();
    // 删除自身
    delete this;
    return 0;
}

void Scene::onDestory() {
    //处理节点
    for (auto it = this->objectArr.rbegin(); it < this->objectArr.rend(); ++it){
        Object* object = *it;
        this->coord->Destory(object);
    }
    this->objectArr.clear();
    // std::vector<Object*> objectArr;
    // for (auto object : this->objectArr){
    //     objectArr.push_back(object);
    // } 
    // for (auto object : objectArr){
    //     object->onDestory();
    // } 
}

}
