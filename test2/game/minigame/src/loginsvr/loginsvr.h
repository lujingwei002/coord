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

namespace loginsvr {//tolua_export

class LoginSvrConfig {//tolua_export
public:
    std::string Host;       //tolua_export
    uint16_t    Port;       //tolua_export  节点端口
    std::string User;       //tolua_export
    std::string Password;   //tolua_export
};//tolua_export

class LoginSvr : public coord::Component {//tolua_export
CC_CLASS(LoginSvr);
public:
    LoginSvr(coord::Coord *coord);//tolua_export
    virtual ~LoginSvr();
public:
    virtual void onAwake();
public:
    int readConfig();
    //获取cluser的配置信息
    LoginSvrConfig* DefaultConfig();
public:
    coord::Coord*          coord;
    LoginSvrConfig     config;
};//tolua_export

LoginSvr* NewLoginSvr();//tolua_export

}//tolua_export



