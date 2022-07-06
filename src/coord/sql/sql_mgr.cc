#include "coord/sql/sql_mgr.h"
#include "coord/sql/sql_client.h"
#include "coord/sql/mysql/mysql_client.h"
#include "coord/config/config.h"
#include "coord/coord.h"
namespace coord {
namespace sql {


sql_mgr* newSQLMgr(Coord* coord) {
    auto mgr = new sql_mgr(coord);
    return mgr;
}

sql_mgr::sql_mgr(Coord *coord) {
    this->coord = coord;
}

sql_mgr::~sql_mgr() {
    for(auto it = this->clientDict.begin(); it != this->clientDict.end();) {
        SQLClient* client = it->second;
        delete client;
        ++it;
    }
    this->clientDict.clear();
}

void sql_mgr::free(SQLClient* conn) {
    delete conn;
}

SQLClient* sql_mgr::getClient(const char* name) {
    auto it = this->clientDict.find(name);
    if (it != this->clientDict.end()){
        return it->second;
    }
    SQLConfig config;
    int err = this->coord->Config->SQLConfig(name, &config);
    if (err != 0) {
        this->coord->coreLogError("[sql_mgr] getClient failed, function='SQLConfig', error=%d", err);
        return nullptr;
    }
    if (config.Driver == "mysql") {
        SQLClient* client = newMySQLClient(this->coord);
        SQLConfig* config1 = client->DefaultConfig();
        *config1 = config;
        int err = client->Connect();
        if (err < 0){
            delete client;
            return nullptr;
        }
        this->clientDict[name] = client;
        return client;
    } else {
        this->coord->coreLogError("[sql_mgr] getClient failed, error='driver not implement'");
        return nullptr;
    }
}


}
}        