#pragma once 

#include "coord/builtin/type.h"

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

class SQLConnection;
class sql_result : public RcObject {
public:
    sql_result(Coord *coord);
    virtual ~sql_result();
public:
    uint64_t RowsAffected();        
    uint64_t LastInsertId();        
public:
    Coord*      coord;
    int         ref;
    uint64_t    rowsAffected;
    uint64_t    lastInsertId;
};

class SQLResult : public RcObject {//tolua_export
CC_CLASS(SQLResult);
public:
    SQLResult(Coord* coord);
    SQLResult(Coord* coord, sql_result* result);
    SQLResult(const SQLResult& other);
    ~SQLResult();
public:
    SQLResult& operator=(const SQLResult& other);
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
    uint64_t RowsAffected();                    //tolua_export     
    uint64_t LastInsertId();                    //tolua_export
public:
    Coord*      coord;
    sql_result* result;
};//tolua_export

inline bool SQLResult::operator== (std::nullptr_t v) const {
    return this->result == nullptr;
}

inline bool SQLResult::operator!= (std::nullptr_t v) const {
    return this->result != nullptr;
}

inline uint64_t SQLResult::RowsAffected() {
    if (!this->result)return 0;
    return this->result->RowsAffected();
} 

inline uint64_t SQLResult::LastInsertId() {
    if (!this->result)return 0;
    return this->result->LastInsertId();
}

}//tolua_export
}//tolua_export


