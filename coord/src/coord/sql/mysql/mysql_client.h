#pragma once 

#include "coord/builtin/type.h"
#include "coord/sql/sql_client.h"
#include "coord/sql/sql_result.h"
#include "tolua++/tolua++.h"
#include <libuv/uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <mysql/mysql.h>


namespace coord {//tolua_export
    
class Coord;

namespace sql {//tolua_export

/*
 * example:
 *
 *  local rows = conn:Query("select * from user where userid=?", userId)
 *  while rows:Next() then
 *      local row = rows:Proto("model.User")
 *      print(row:DebugString())
 *  end
 *  
 */
class MySQLResult;
class MySQLRows;

class MySQLClient : public SQLClient {//tolua_export
CC_CLASS(MySQLClient);
public:
    MySQLClient(Coord *coord);
    virtual ~MySQLClient();
public:
    //链接数据库
    virtual int Connect();                              
    //执行PING命令
    virtual int Ping();                                 
    virtual const char* Error();                        
    virtual void Close();                               
    virtual uint64_t RowsAffected();                    
    virtual uint64_t LastInsertId();                    
    virtual const char* realEscapeString(const char* src, size_t srcLen, size_t* dstLen);
protected:
    virtual SQLRows get(const char* statement); 
    virtual SQLResult execute(const char* statement);
    virtual SQLRows query(const char* statement);
    
public:
    MYSQL *conn;
};//tolua_export

MySQLClient* newMySQLClient(Coord *coord);

}//tolua_export
}//tolua_export


