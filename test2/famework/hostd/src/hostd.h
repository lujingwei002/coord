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

namespace hostd {//tolua_export

class HostdServer;

class HostdConfig {//tolua_export
public:
    std::string Host;       //tolua_export
    uint16_t    Port;       //tolua_export  节点端口
    std::string User;       //tolua_export
    std::string Password;   //tolua_export
};//tolua_export

class Hostd : public coord::Component {//tolua_export
CC_CLASS(Hostd);
public:
    Hostd(coord::Coord *coord);//tolua_export
    virtual ~Hostd();
public:
    virtual void onAwake();
public:
    int readConfig();
 
    //获取cluser的配置信息
    HostdConfig* DefaultConfig();
public:

public:
    coord::Coord*          coord;
    HostdConfig     config;
    HostdServer*    server;
};//tolua_export

Hostd* NewHostd();//tolua_export

}//tolua_export



