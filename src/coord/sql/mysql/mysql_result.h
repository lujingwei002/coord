#pragma once 

#include "coord/coordx.h"
#include "coord/sql/sql_result.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <mysql/mysql.h>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
namespace coord {//tolua_export
    
class Coord;

namespace sql {//tolua_export

class MySQLConnection;
class mysql_result : public sql_result {
CC_CLASS(mysql_result);
public:
    mysql_result(Coord *coord, MYSQL *conn);
    virtual ~mysql_result();        
public:
    MYSQL *conn;
};

mysql_result* newMySQLResult(Coord* coord, MYSQL *conn);
}//tolua_export
}//tolua_export


