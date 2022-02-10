#include "coord/scene/scene.h"
#include "coord/coord.h"
#include "coord/scene/scene_mgr.h"
#include "coord/builtin/environment.h"
#include "coord/json/init.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <fstream>

namespace coord {

SceneMgr* newSceneMgr(Coord *coord) {
    SceneMgr* sceneMgr = new SceneMgr(coord);
    return sceneMgr;
}

SceneMgr::SceneMgr(Coord *coord) {
    this->coord = coord;
    this->mainScene = nullptr;
    this->mainObject = nullptr;
}

SceneMgr::~SceneMgr() {
    this->coord->coreLogDebug("[SceneMgr] ~SceneMgr");
    while(this->sceneArr.size() > 0){
        Scene* scene = this->sceneArr.back();
        this->sceneArr.pop_back();
        this->coord->Destory(scene);
    }
    this->sceneArr.clear();
}

Scene* SceneMgr::CreateScene(const char* sceneName) {
    Scene* scene = newScene(this->coord, this);
    scene->create(sceneName);
    this->sceneArr.push_back(scene);
    return scene;
}

void SceneMgr::onUpdate(uint64_t cur_tick) {
    //this->coord->coreLogError("[SceneMgr] onUpdate, from=%ld", this->coord->frame);
    std::vector<Scene*> sceneArr;
    for (auto scene : this->sceneArr) {
        sceneArr.push_back(scene);
    }
    for (auto scene : sceneArr) {
        scene->onStart();
    }
    for (auto scene : sceneArr) {
        scene->onUpdate(cur_tick);
    }
} 

void SceneMgr::onReload() {
    std::vector<Scene*> sceneArr;
    for (auto scene : this->sceneArr) {
        sceneArr.push_back(scene);
    }
    for (auto scene : sceneArr) {
        scene->onReload();
    }
}

Scene* SceneMgr::loadSceneInternal(const char* filePath) {
    std::ifstream ifile;
    ifile.open(filePath, std::ios::in);
    if(!ifile){
        this->coord->coreLogError("[SceneMgr] loadSceneInternal failed, error='file not found', file='%s'", filePath);
        return nullptr;
    }
    std::string str((std::istreambuf_iterator<char>(ifile)),  
    std::istreambuf_iterator<char>());
    auto json = this->coord->Json->Decode(str);
    if (json == nullptr) {
        return nullptr;
    }
    Scene* scene = this->CreateScene(json.GetString("name"));
    auto objectArr = json.GetArray("objectArr");
    for (int i = 0; i < objectArr.Count(); i++) {
        auto objectConf = objectArr.GetObject(i);
        Object* object = scene->createObjectInternal(objectConf.GetString("name"));
        if (nullptr == object) {
            this->coord->Destory(scene);
            return nullptr;
        }
    }
    return scene;
}

Scene* SceneMgr::LoadScene(const char* filePath) {
    Scene* scene = this->loadSceneInternal(filePath);
    if (scene == nullptr) {
        return nullptr;
    }
    scene->onAwake();
    return scene;
}

void SceneMgr::onAwake() {
    std::string filePath = this->coord->Environment->CoordDir + "/data/Main Scene.sc";
    Scene* scene = this->loadSceneInternal(filePath.c_str());
    if (nullptr == scene) {
        this->coord->coreLogError("[SceneMgr] onAwake failed, function='this->LoadScene'");
        return;
    }
    if (scene->objectArr.size() < 0) {
        this->coord->coreLogError("[SceneMgr] onAwake failed, error='empty scene'");
        return;
    }
    this->mainScene = scene;
    this->mainObject = scene->objectArr[0];
    scene->onAwake();
    return;
}

}