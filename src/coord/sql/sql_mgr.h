#pragma once 

#include "coord/builtin/type.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <mysql/mysql.h>
namespace coord {//tolua_export
    
class Coord;

namespace sql {//tolua_export

class SQLClient;

class sql_mgr {//tolua_export
public:
    sql_mgr(Coord *coord);
    virtual ~sql_mgr();
public:
    SQLClient* getClient(const char* name);
    void free(SQLClient* conn);
public:
    std::map<std::string, SQLClient*> clientDict;
    Coord* coord;
};//tolua_export

sql_mgr* newSQLMgr(Coord* coord);
}//tolua_export
}//tolua_export


