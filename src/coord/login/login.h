#pragma once 

#include "coord/component/component.h"
#include "coord/login/login_config.h"
#include <uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export

class Coord;

namespace http {
class HttpServer;
}
namespace login {//tolua_export



class account_controller;
class login_cluster;

class LoginSvr {//tolua_export
public:
    LoginSvr(Coord* coord);
    virtual ~LoginSvr();
public:
    LoginConfig* DefaultConfig();//tolua_export
public:
    int main();
    void onDestory();
public:
    Coord*              coord;
    http::HttpServer*   httpServer;
    LoginConfig         config;
    account_controller* accountController;
    login_cluster*      loginCluster;
};//tolua_export

LoginSvr* newLoginSvr(Coord* coord);


}//tolua_export
}//tolua_export