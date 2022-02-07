#include "loginsvr.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace loginsvr {

CC_IMPLEMENT(LoginSvr, "loginsvr::LoginSvr")

LoginSvr* NewLoginSvr() {
    LoginSvr* self = new LoginSvr(coorda);
    return self;
}

LoginSvr::LoginSvr(coord::Coord *coord) : Component(coord) {
    
}

LoginSvr::~LoginSvr() {
 
}

void LoginSvr::onAwake() {
    this->coord->LogDebug("[LoginSvr] onAwake");
    int err = 0; 
    err = this->readConfig();
    if (err < 0){
        this->coord->LogDebug("[LoginSvr] onAwake failed, error=%d", err);
        return;
    }
}

int LoginSvr::readConfig() {
    LoginSvrConfig* config = &this->config;
    if(!this->coord->config->Get("LoginSvr", "port", config->Port)) {
        return -1;
    }
    if(!this->coord->config->Get("LoginSvr", "host", config->Host)) {
        return -1;
    }
    if(!this->coord->config->Get("LoginSvr", "user", config->User)) {
        return -1;
    }
    if(!this->coord->config->Get("LoginSvr", "password", config->Password)) {
        return -1;
    }
    return 0;
}

LoginSvrConfig* LoginSvr::DefaultConfig() {
    return &this->config;
}



}
      