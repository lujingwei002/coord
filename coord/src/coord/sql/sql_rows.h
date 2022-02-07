#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/protobuf/init.h"
#include <libuv/uv.h>
#include <vector>
#include <iostream>
#include <string>
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

class SQLConnection;

class sql_rows : public Destoryable {
public:
    sql_rows(Coord *coord);
    virtual ~sql_rows();                                     
public:
    virtual int Index() = 0;
    virtual bool Next() = 0;                                
    virtual protobuf::Reflect Proto(const char* name) = 0;  
    virtual int Proto(protobuf::Reflect& proto) = 0;
    virtual int Lua(lua_State* L) = 0;                      
    virtual const char* Column(int index) = 0;              
    virtual int ColumnCount() = 0;                          
    virtual const char* String(int index) = 0;
    virtual const char* String(const char* field) = 0;
    virtual double Number(int index) = 0;
    virtual double Number(const char* field) = 0;
public:
    Coord*  coord;
    int     ref;
};

class SQLRows : public Destoryable {//tolua_export
CC_CLASS(SQLRows);
public:
    SQLRows(Coord* coord, sql_rows* rows);
    SQLRows(Coord* coord);    
    SQLRows(const SQLRows& other);
    ~SQLRows();
public:
    SQLRows& operator=(const SQLRows& other);
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
    int Index();
    bool Next();                                //tolua_export   
    protobuf::Reflect Proto(const char* name);  //tolua_export
    int Proto(protobuf::Reflect& proto);        //tolua_export
    int Lua(lua_State* L);                      //tolua_export
    const char* Column(int index);              //tolua_export
    int ColumnCount();                          //tolua_export
    const char* String(int index);              //tolua_export
    const char* String(const char* field);      //tolua_export
    double Number(int index);                   //tolua_export
    double Number(const char* field);           //tolua_export
public:
    Coord*      coord;
    sql_rows*   rows;
};//tolua_export

inline bool SQLRows::operator== (std::nullptr_t v) const {
    return this->rows == nullptr;
}

inline bool SQLRows::operator!= (std::nullptr_t v) const {
    return this->rows != nullptr;
}

inline int SQLRows::Index() {                       
    if (!this->rows)return 0;   
    return this->rows->Index();     
} 

inline bool SQLRows::Next() {                       
    if (!this->rows)return false;   
    return this->rows->Next();     
}            
                      
inline protobuf::Reflect SQLRows::Proto(const char* name) {
    static thread_local protobuf::Reflect nullPtr(this->coord);
    if (!this->rows)return nullPtr;
    return this->rows->Proto(name);
}

inline int SQLRows::Proto(protobuf::Reflect& proto) {
    if (!this->rows)return -1;
    return this->rows->Proto(proto);
}

inline int SQLRows::Lua(lua_State* L) {
    if (!this->rows)return 0;
    return this->rows->Lua(L);
}

inline const char* SQLRows::Column(int index) {
    if (!this->rows)return nullptr;
    return this->rows->Column(index);
}

inline int SQLRows::ColumnCount() {
    if (!this->rows)return 0;
    return this->rows->ColumnCount();
}

inline const char* SQLRows::String(int index) {
    if (!this->rows)return nullptr;
    return this->rows->String(index);
}

inline const char* SQLRows::String(const char* field) {
    if (!this->rows)return nullptr;
    return this->rows->String(field);
}

inline double SQLRows::Number(int index) {
    if (!this->rows)return 0;
    return this->rows->Number(index);
}

inline double SQLRows::Number(const char* field) {
    if (!this->rows)return 0;
    return this->rows->Number(field);
}

}//tolua_export
}//tolua_export


