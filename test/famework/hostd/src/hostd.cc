#include "hostd.h"
#include "hostd/hostd_server.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace hostd {

CC_IMPLEMENT(Hostd, "hostd::Hostd")

Hostd* NewHostd() {
    Hostd* hostd = new Hostd(coorda);
    return hostd;
}

Hostd::Hostd(coord::Coord *coord) {
    this->coord = coord;
    this->server = NULL;
}

Hostd::~Hostd() {
    if(this->server) {
        delete this->server;
        this->server = NULL;
    }
}

void Hostd::onAwake() {
    this->coord->LogDebug("[Hostd] Awake");
    int err = 0; 
    err = this->readConfig();
    if (err < 0){
        this->coord->LogDebug("[Hostd] Awake failed, error=%d", err);
        return;
    }
    //启动server
    this->server = newHostdServer(this->coord, this);
    err = this->server->start();
    if (err < 0){
        this->coord->LogDebug("[Hostd] Awake failed, error=%d", err);
        return;
    } 
}

int Hostd::readConfig() {
    HostdConfig* config = &this->config;
    if(!this->coord->config->Get("HOSTD", "port", config->Port)) {
        return -1;
    }
    if(!this->coord->config->Get("HOSTD", "host", config->Host)) {
        return -1;
    }
    if(!this->coord->config->Get("HOSTD", "user", config->User)) {
        return -1;
    }
    if(!this->coord->config->Get("HOSTD", "password", config->Password)) {
        return -1;
    }

    return 0;
}

HostdConfig* Hostd::DefaultConfig() {
    return &this->config;
}



}
      