#pragma once 

#include "coord/builtin/type.h"
#include "coord/sql/sql_rows.h"
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

/*
 * example:
 *
 *  local rows = conn:Query("select * from user")
 *  while rows:Next() then
 *      local row = rows:Proto("model.User")
 *      print(row:DebugString())
 *  end
 *  
 */
class MySQLConnection;

class mysql_rows : public sql_rows {
CC_CLASS(mysql_rows);
public:
    mysql_rows(Coord *coord, MYSQL *conn);
    virtual ~mysql_rows();
public:
    virtual int Index();
    /// 是否还有下一行
    virtual bool Next();                                    
    /// 转换成lua的表格式                              
    virtual int Lua(lua_State* L);                          
    /// 转换成proto格式
    virtual protobuf::MessageRef Proto(const char* name);     
    virtual int Proto(protobuf::MessageRef& proto); 
    /// 返回列名
    virtual const char* Column(int index);                  
    /// 返回列的数量
    virtual int ColumnCount();                              
    virtual const char* String(int index);
    virtual const char* String(const char* field);
    virtual double Number(int index);
    virtual double Number(const char* field);
public:
    MYSQL_ROW                   row;
    MYSQL*                      conn;
    MYSQL_RES*                  result;
    MYSQL_FIELD*                columnArr;
    std::map<std::string, int>  columnDict;
    int                         columnCount;
    int                         index;
};

mysql_rows* newMySQLRows(Coord* coord, MYSQL *conn);
}//tolua_export
}//tolua_export


