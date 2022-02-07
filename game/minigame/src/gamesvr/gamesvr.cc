#include "gamesvr.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace gamesvr {

CC_IMPLEMENT(GameSvr, "gamesvr::GameSvr")

GameSvr* NewGameSvr() {
    GameSvr* gamesvr = new GameSvr(coorda);
    return gamesvr;
}

GameSvr::GameSvr(coord::Coord *coord) : Component(coord) {
   
}

GameSvr::~GameSvr() {
 
}

void GameSvr::onAwake() {
    this->coord->LogDebug("[GameSvr] onAwake");
    int err = 0; 
    err = this->readConfig();
    if (err < 0){
        this->coord->LogDebug("[GameSvr] onAwake failed, error=%d", err);
        return;
    }
}

int GameSvr::readConfig() {
    GameSvrConfig* config = &this->config;
    if(!this->coord->config->Get("GameSvr", "port", config->Port)) {
        return -1;
    }
    if(!this->coord->config->Get("GameSvr", "host", config->Host)) {
        return -1;
    }
    if(!this->coord->config->Get("GameSvr", "user", config->User)) {
        return -1;
    }
    if(!this->coord->config->Get("GameSvr", "password", config->Password)) {
        return -1;
    }

    return 0;
}

GameSvrConfig* GameSvr::DefaultConfig() {
    return &this->config;
}



}
      