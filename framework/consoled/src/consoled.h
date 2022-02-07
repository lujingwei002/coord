#pragma once 

#include "coord/builtin/init.h"
#include "coord/protobuf/init.h"
#include "coord/component/init.h"
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>

namespace coord {
class Coord;
}

namespace consoled {//tolua_export

class ConsoledServer;

class ConsoledConfig {//tolua_export
public:
    std::string Host;       //tolua_export
    uint16_t    Port;       //tolua_export  节点端口
    std::string User;       //tolua_export
    std::string Password;   //tolua_export
};//tolua_export

class Consoled : public coord::Component {//tolua_export
CC_CLASS(Consoled);
public:
    Consoled(coord::Coord *coord);//tolua_export
    virtual ~Consoled();
public:
    //获取cluser的配置信息
    ConsoledConfig* DefaultConfig();
public:
    int readConfig();
    virtual void onAwake();
public:
    coord::Coord*       coord;
    ConsoledConfig      config;
    ConsoledServer*     server;
};//tolua_export

Consoled* NewConsoled();//tolua_export

}//tolua_export



