#pragma once 

#include "coord/builtin/init.h"
#include "coord/component/init.h"
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>

namespace coord {
class Coord;
}

namespace gamesvr {//tolua_export

class GameSvrConfig {//tolua_export
public:
    std::string Host;       //tolua_export
    uint16_t    Port;       //tolua_export  节点端口
    std::string User;       //tolua_export
    std::string Password;   //tolua_export
};//tolua_export

class GameSvr : public coord::Component {//tolua_export
CC_CLASS(GameSvr);
public:
    GameSvr(coord::Coord *coord);//tolua_export
    virtual ~GameSvr();
public:
    virtual void onAwake();
public:
    int readConfig();
    //获取cluser的配置信息
    GameSvrConfig* DefaultConfig();
public:
    coord::Coord*          coord;
    GameSvrConfig     config;
};//tolua_export

GameSvr* NewGameSvr();//tolua_export

}//tolua_export



