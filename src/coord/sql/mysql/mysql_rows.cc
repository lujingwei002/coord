#include "coord/sql/mysql/mysql_rows.h"
#include "coord/sql/mysql/mysql_client.h"
#include "coord/coord.h"

namespace coord {
namespace sql {
RC_IMPLEMENT(mysql_rows, "coord::mysql::mysql_rows")

mysql_rows* newMySQLRows(Coord* coord, MYSQL *conn) {
    auto self = new mysql_rows(coord, conn);
    return self;
}

mysql_rows::mysql_rows(Coord *coord, MYSQL *conn) : sql_rows(coord) {
    this->conn = conn;
    this->result = nullptr;
    this->columnArr = nullptr;
    this->columnCount = 0;
    this->index = -1;
    MYSQL_RES* result = mysql_store_result(this->conn);
    if (!result) {
        return;
    }
    this->result = result;
    this->columnCount = mysql_num_fields(result);   
    this->columnArr = mysql_fetch_fields(result); 
    for (int i = 0; i < this->columnCount; i++) {
        this->columnDict[this->columnArr[i].name] = i;
    }    
}

mysql_rows::~mysql_rows() {
    if(this->result == nullptr) {
        return;
    }
    mysql_free_result(this->result);
    this->result = nullptr;
}

const char* mysql_rows::Column(int index) {
    if (index < 0 || index >= this->columnCount) {
        return nullptr;
    }
    return this->columnArr[index].name;
}

int mysql_rows::ColumnCount() {
    return this->columnCount;
}

int mysql_rows::Index() {
    return this->index;
}

bool mysql_rows::Next() {
    if (this->result == nullptr) {
        return false;
    }
    this->row = mysql_fetch_row(this->result);
    if (this->row != nullptr) {
        this->index++;
        return true;
    }
    mysql_free_result(this->result);
    this->result = nullptr;
    //是否还有结果集
    int err = mysql_next_result(this->conn);
    if (err){
        return false;
    }
    MYSQL_RES* result = mysql_store_result(this->conn);
    if (result == nullptr) {
        return false;
    }
    this->result = result;
    this->row = mysql_fetch_row(this->result);
    if(this->row == nullptr){
        mysql_free_result(this->result);
        this->result = nullptr;
        return false;
    }
    this->index++;
    return true;  
}

const char* mysql_rows::String(const char* field) {
    auto it = this->columnDict.find(field);
    if (it == this->columnDict.end()) {
        this->coord->CoreLogError("[mysql_rows] Number failed, field='%s', error='field not found'", field);
        return nullptr;
    }
    return this->String(it->second);
}

const char* mysql_rows::String(int index) {
    static thread_local std::string value;
    MYSQL_RES* result = this->result;
    if (result == nullptr) {
        return nullptr;
    }
    if (this->columnArr == nullptr) {
        return nullptr;
    }
    value.clear();
    MYSQL_FIELD* columnArr = this->columnArr;
    if (columnArr[index].type != FIELD_TYPE_STRING &&
                columnArr[index].type != FIELD_TYPE_ENUM &&
                columnArr[index].type != FIELD_TYPE_SET &&
                columnArr[index].type != FIELD_TYPE_INTERVAL &&
                columnArr[index].type != FIELD_TYPE_VAR_STRING &&
                columnArr[index].type != FIELD_TYPE_TINY_BLOB &&
                columnArr[index].type != FIELD_TYPE_MEDIUM_BLOB &&
                columnArr[index].type != FIELD_TYPE_LONG_BLOB &&
                columnArr[index].type != FIELD_TYPE_BLOB &&
                columnArr[index].type != FIELD_TYPE_CHAR){
        return nullptr;
    }
    unsigned long* fieldLength = mysql_fetch_lengths(result); 
    value.assign(row[index], fieldLength[index]);
    return value.data();
}

double mysql_rows::Number(const char* field) {
    auto it = this->columnDict.find(field);
    if (it == this->columnDict.end()) {
        this->coord->CoreLogError("[mysql_rows] Number failed, field='%s', error='field not found'", field);
        return 0;
    }
    return this->Number(it->second);
}

double mysql_rows::Number(int index) {
    MYSQL_RES* result = this->result;
    if (result == nullptr) {
        return 0;
    }
    if (this->columnArr == nullptr) {
        return 0;
    }
    MYSQL_FIELD* columnArr = this->columnArr;
    if (columnArr[index].type != FIELD_TYPE_FLOAT &&
                columnArr[index].type != FIELD_TYPE_DECIMAL &&
                columnArr[index].type != FIELD_TYPE_NEWDECIMAL &&
                columnArr[index].type != FIELD_TYPE_TINY &&
                columnArr[index].type != FIELD_TYPE_INT24 &&
                columnArr[index].type != FIELD_TYPE_SHORT &&
                columnArr[index].type != FIELD_TYPE_LONG &&
                columnArr[index].type != FIELD_TYPE_LONGLONG &&
                columnArr[index].type != FIELD_TYPE_DOUBLE &&
                columnArr[index].type != FIELD_TYPE_TIMESTAMP){
        return 0;
    }
    return atof(row[index]);
}

int mysql_rows::Lua(lua_State* L) {
    MYSQL_RES* result = this->result;
    if (result == nullptr) {
        return 0;
    }
    if (this->columnArr == nullptr) {
        return 0;
    }
    unsigned long* fieldLength = mysql_fetch_lengths(result); 
    MYSQL_FIELD* columnArr = this->columnArr;
    lua_newtable(L);
    for(int i = 0; i < this->columnCount; i++) {
        lua_pushstring(L, columnArr[i].name);
        if(row[i] != nullptr) {
            if (columnArr[i].type == FIELD_TYPE_STRING || 
                columnArr[i].type == FIELD_TYPE_VAR_STRING || 
                columnArr[i].type == FIELD_TYPE_TINY_BLOB || 
                columnArr[i].type == FIELD_TYPE_MEDIUM_BLOB || 
                columnArr[i].type == FIELD_TYPE_LONG_BLOB || 
                columnArr[i].type == FIELD_TYPE_BLOB ||
                columnArr[i].type == FIELD_TYPE_CHAR) {
                lua_pushlstring(L, row[i], fieldLength[i]);
            } else if(columnArr[i].type == FIELD_TYPE_FLOAT || 
                     columnArr[i].type == FIELD_TYPE_DECIMAL || 
                     columnArr[i].type == FIELD_TYPE_NEWDECIMAL || 
                     columnArr[i].type == FIELD_TYPE_TINY || 
                     columnArr[i].type == FIELD_TYPE_INT24 || 
                     columnArr[i].type == FIELD_TYPE_SHORT || 
                     columnArr[i].type == FIELD_TYPE_LONG || 
                     columnArr[i].type == FIELD_TYPE_LONGLONG || 
                     columnArr[i].type == FIELD_TYPE_DOUBLE ||
                     columnArr[i].type == FIELD_TYPE_TIMESTAMP) {
                lua_pushnumber(L, atof(row[i]));
            } else if(columnArr[i].type == FIELD_TYPE_DATE || 
                     columnArr[i].type == FIELD_TYPE_TIME || 
                     columnArr[i].type == FIELD_TYPE_DATETIME || 
                     columnArr[i].type == FIELD_TYPE_YEAR || 
                     columnArr[i].type == FIELD_TYPE_NEWDATE) {
                lua_pushlstring(L, row[i], fieldLength[i]);
            } else if(columnArr[i].type == FIELD_TYPE_ENUM || 
                     columnArr[i].type == FIELD_TYPE_SET || 
                     columnArr[i].type == FIELD_TYPE_INTERVAL) {
                lua_pushlstring(L, row[i], fieldLength[i]);
            } else if(columnArr[i].type == FIELD_TYPE_GEOMETRY) {
                lua_pushlstring(L, row[i], fieldLength[i]);
            } else if(columnArr[i].type == FIELD_TYPE_BIT) {
                lua_pushnumber(L, atoi(row[i]));
            } else if(columnArr[i].type == FIELD_TYPE_NULL) {
                lua_pushnil(L);
            } else {
                lua_pushnumber(L, atoi(row[i]));
            }
        }else {
            lua_pushnil(L);
        }
        lua_settable(L, -3);
    }
    return 1;
}

protobuf::MessageRef mysql_rows::Proto(const char* name) {
    auto proto = this->coord->Proto->NewMessage(name);
    int err = this->Proto(proto);
    if (err) {
        return protobuf::MessageRef::NullPtr;
    }
    return proto;
}

int mysql_rows::Proto(protobuf::MessageRef& proto) {
    MYSQL_RES* result = this->result;
    if (result == nullptr) {
        return -1;
    }
    if (this->columnArr == nullptr) {
        return -1;
    }
    unsigned long* fieldLength = mysql_fetch_lengths(result); 
    MYSQL_FIELD* columnArr = this->columnArr;
    for(int i = 0; i < this->columnCount; i++) {
        if(row[i] != nullptr) {
            if (columnArr[i].type == FIELD_TYPE_STRING || 
                columnArr[i].type == FIELD_TYPE_VAR_STRING || 
                columnArr[i].type == FIELD_TYPE_TINY_BLOB || 
                columnArr[i].type == FIELD_TYPE_MEDIUM_BLOB || 
                columnArr[i].type == FIELD_TYPE_LONG_BLOB || 
                columnArr[i].type == FIELD_TYPE_BLOB ||
                columnArr[i].type == FIELD_TYPE_CHAR) {
                if (!proto->SetString(columnArr[i].name, row[i], fieldLength[i])){
                    this->coord->CoreLogError("[MySQLRows] Proto failed, column=%s, type=%d, error='SetString err'", columnArr[i].name, columnArr[i].type);
                }
            } else if(columnArr[i].type == FIELD_TYPE_FLOAT ||  
                      columnArr[i].type == FIELD_TYPE_DECIMAL || 
                      columnArr[i].type == FIELD_TYPE_NEWDECIMAL || 
                      columnArr[i].type == FIELD_TYPE_TINY || 
                      columnArr[i].type == FIELD_TYPE_INT24 || 
                      columnArr[i].type == FIELD_TYPE_SHORT || 
                      columnArr[i].type == FIELD_TYPE_LONG || 
                      columnArr[i].type == FIELD_TYPE_LONGLONG || 
                      columnArr[i].type == FIELD_TYPE_DOUBLE ||
                      columnArr[i].type == FIELD_TYPE_TIMESTAMP) {
                if(!proto->SetNumber(columnArr[i].name, atof(row[i]))){
                    this->coord->CoreLogError("[MySQLRows] Proto failed, column=%s, type=%d, error='SetNumber err'", columnArr[i].name, columnArr[i].type);
                }
            } else if(columnArr[i].type == FIELD_TYPE_DATE || 
                     columnArr[i].type == FIELD_TYPE_TIME || 
                     columnArr[i].type == FIELD_TYPE_DATETIME || 
                     columnArr[i].type == FIELD_TYPE_YEAR || 
                     columnArr[i].type == FIELD_TYPE_NEWDATE) {
                if (!proto->SetString(columnArr[i].name, row[i], fieldLength[i])){
                    this->coord->CoreLogError("[MySQLRows] Proto failed, column=%s, type=%d, error='SetString err'", columnArr[i].name, columnArr[i].type);
                }
            } else if(columnArr[i].type == FIELD_TYPE_ENUM || 
                     columnArr[i].type == FIELD_TYPE_SET || 
                     columnArr[i].type == FIELD_TYPE_INTERVAL) {
                if (!proto->SetString(columnArr[i].name, row[i], fieldLength[i])){
                    this->coord->CoreLogError("[MySQLRows] Proto failed, column=%s, type=%d, error='SetString err'", columnArr[i].name, columnArr[i].type);
                }
            } else if(columnArr[i].type == FIELD_TYPE_GEOMETRY) {
                if (!proto->SetString(columnArr[i].name, row[i], fieldLength[i])){
                    this->coord->CoreLogError("[MySQLRows] Proto failed, column=%s, type=%d, error='SetString err'", columnArr[i].name, columnArr[i].type);
                }
            } else if(columnArr[i].type == FIELD_TYPE_BIT) {
                if(!proto->SetNumber(columnArr[i].name, atof(row[i]))){
                    this->coord->CoreLogError("[MySQLRows] Proto failed, column=%s, type=%d, error='SetNumber err'", columnArr[i].name, columnArr[i].type);
                }
            } else if(columnArr[i].type == FIELD_TYPE_NULL) {
                
            } else {
                this->coord->CoreLogError("[MySQLRows] Proto failed, column=%s, type=%d, error='Set err'", columnArr[i].name, columnArr[i].type);
            }
        }
    }
    return 0;
}

}
}        