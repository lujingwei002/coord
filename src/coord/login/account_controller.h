#pragma once 

#include "coord/component/component.h"
#include "coord/http/http_request.h"
#include <uv.h>
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
    void reqLogin(const http::HttpRequestPtr& request);
    void reqList(const http::HttpRequestPtr& request);
public:
    Coord*              coord;
    LoginSvr*           loginSvr;
};

account_controller* newAccountController(Coord* coord, LoginSvr* loginSvr);


}
}
