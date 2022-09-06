#pragma once 


#include "coord/coordx.h"
#include "coord/memory/type.h"
#include <stdint.h>
#include <vector>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
namespace coord {//tolua_export
    
class Coord;  
class SceneMgr;  
class Object;

class Scene : public coord::RcObject {//tolua_export
RC_CLASS(Scene);
public:
    Scene(Coord* cord, SceneMgr* sceneMgr);
    ~Scene();
public:
    Object* Instantiate(const char* name, const char* filePath);//tolua_export
    Object* CreateObject(const char* name);//tolua_export  
public:
    int addObject(Object* object);
    Object* createObjectInternal(const char* name);
    int create(const char* sceneName);
    void onUpdate(uint64_t cur_tick);
    void onReload();
    void onAwake();
    void onStart();
    //销毁
    virtual void onDestory();
public:
    char                    name[64];   //tolua_export
    std::vector<Object*>    objectArr;
    Coord*                  coord;
    SceneMgr*               sceneMgr;
    uint64_t                id;
};//tolua_export

Scene *newScene(Coord* cord, SceneMgr *sceneMgr);
}//tolua_export
