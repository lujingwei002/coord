#ifndef _COORD_SCENEMGR_H_
#define _COORD_SCENEMGR_H_

#include <vector>
#include <iostream>
#include <stdint.h>

namespace coord {//tolua_export
    
class Scene;
class Coord;
class Object;

class SceneMgr {//tolua_export
public:
    SceneMgr(Coord *coord);
    ~SceneMgr();
public:
    Scene* CreateScene(const char* sceneName);
    Scene* LoadScene(const char* filePath);
public:
    Scene* loadSceneInternal(const char* filePath);
    void onUpdate(uint64_t cur_tick);
    void onAwake();
    void onReload();
public:
    Coord*                  coord;
    std::vector<Scene*>     sceneArr;
    Scene*                  mainScene;
    Object*                 mainObject;
};//tolua_export

SceneMgr* newSceneMgr(Coord *coord);
}//tolua_export

#endif
