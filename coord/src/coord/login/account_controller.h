#pragma once 

#include "coord/component/component.h"
#include <libuv/uv.h>
#include <map>
#include <string>

namespace coord {

class Coord;

namespace http {
class HttpServer;
class HttpRequest;
}


namespace login {

class LoginSvr;

class account_controller {
public:
    account_controller(Coord* coord, LoginSvr* loginSvr);
    virtual ~account_controller();
public:
    int main();
    void reqLogin(http::HttpRequest* request);
    void reqList(http::HttpRequest* request);
public:
    Coord*              coord;
    LoginSvr*           loginSvr;
};

account_controller* newAccountController(Coord* coord, LoginSvr* loginSvr);


}
}