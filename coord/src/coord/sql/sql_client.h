#pragma once 

#include "coord/builtin/init.h"
#include "coord/builtin/slice.h"
#include "coord/sql/sql_result.h"
#include "coord/sql/sql_rows.h"
#include "coord/protobuf/init.h"
#include "tolua++/tolua++.h"
#include <libuv/uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <string>
#include <mysql/mysql.h>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace coord {//tolua_export
    
class Coord;

namespace sql {//tolua_export

class SQLResult;
class SQLRows;

class SQLConfig {//tolua_export
public:
    std::string         Driver;         //tolua_export
    std::string         User;           //tolua_export
    std::string         Password;       //tolua_export
    std::string         DB;             //tolua_export
    std::string         CharacterSet;   //tolua_export
    std::string         Host;           //tolua_export
    uint16_t            Port;           //tolua_export
};//tolua_export

class SQLClient {//tolua_export
CC_CLASS(SQLClient);
public:
    SQLClient(Coord *coord);
    virtual ~SQLClient();
public:
    virtual SQLConfig* DefaultConfig();                     //tolua_export
    virtual int Connect() = 0;                              //tolua_export
    virtual int Ping() = 0;                                 //tolua_export
    virtual const char* Error() = 0;                        //tolua_export
    virtual void Close() = 0;                               //tolua_export
    virtual uint64_t RowsAffected() = 0;                    //tolua_export
    virtual uint64_t LastInsertId() = 0;                    //tolua_export  
    int Query(lua_State* L);                                //tolua_export
    int Get(lua_State* L);                                  //tolua_export
    int Execute(lua_State* L);                              //tolua_export
    template<class... T>
    const char* Format(const char* statement, T... args);
    template<class... T>
    SQLRows Get(const char* statement, T... args);
    template<class... T>
    SQLRows Query(const char* statement, T... args);
    template<class... T>
    SQLResult Execute(const char* statement, T... args);
    template<class... T>
    int Get(protobuf::Reflect& proto, const char* statement, T... args);
protected:
    virtual SQLRows get(const char* statement) = 0;
    virtual SQLResult execute(const char* statement) = 0;   
    virtual SQLRows query(const char* statement) = 0;   
    virtual const char* realEscapeString(const char* src, size_t srcLen, size_t* dstLen) = 0;
    template<class... T>
    int formatPlaceholder(std::string& buffer, const char* statement, const char* arg, T... other);
    template<class... T>
    int formatPlaceholder(std::string& buffer, const char* statement, char* arg, T... other);
    template<class... T>
    int formatPlaceholder(std::string& buffer, const char* statement, std::string& arg, T... other);
    template<class T, class... Args>
    int formatPlaceholder(std::string& buffer, const char* statement, T arg, Args... other);
    template<class... T>
    int formatPlaceholder(std::string& buffer, const char* statement);
private:
    const char* formatPlaceholder(lua_State* L);
public:
    SQLConfig   config;
    Coord*      coord;
};//tolua_export

template<class... T>
const char* SQLClient::Format(const char* statement, T... args) {
    static thread_local std::string buffer;
    buffer.clear();
    this->formatPlaceholder(buffer, statement, args...);
    return buffer.c_str();
}

template<class... T>
int SQLClient::Get(protobuf::Reflect& proto, const char* statement, T... args) {
    SQLRows rows = this->Get(statement, args...);
    if (rows == nullptr) {
        return -1;
    }
    if (!rows.Next()) {
        return ErrorNotResult;
    }
    return rows.Proto(proto);
}

template<class... T>
SQLRows SQLClient::Get(const char* statement, T... args) {
    std::string buffer;
    int err = this->formatPlaceholder(buffer, statement, args...);
    if (err) {
        return nullptr;
    }
    return this->get(buffer.c_str());
}
template<class... T>
SQLRows SQLClient::Query(const char* statement, T... args) {
    std::string buffer;
    int err = this->formatPlaceholder(buffer, statement, args...);
    if (err) {
        return nullptr;
    }
    return this->query(buffer.c_str());
}
template<class... T>
SQLResult SQLClient::Execute(const char* statement, T... args) {
    std::string buffer;
    int err = this->formatPlaceholder(buffer, statement, args...);
    if (err) {
        return nullptr;
    }
    return this->execute(buffer.c_str());
}

template<class... T>
int SQLClient::formatPlaceholder(std::string& buffer, const char* statement, char* arg, T... other) {
    return this->formatPlaceholder(buffer, statement, (const char*)arg, other...);
}

template<class... T>
int SQLClient::formatPlaceholder(std::string& buffer, const char* statement, const char* arg, T... other) {
    char* begin = (char*)statement;
    char* it = (char*)statement;
    while (*it != '?' && *it != 0) it++;
    if (*it == 0) return formatPlaceholder(buffer, statement);
    buffer.append(begin, it - begin);

    size_t dstLen = 0;
    auto escapeArg = this->realEscapeString(arg, strlen(arg), &dstLen);
    if (escapeArg == nullptr) {
        return -1;
    }
    buffer.append("'");
    buffer.append(escapeArg, dstLen);
    buffer.append("'");
    return formatPlaceholder(buffer, it + 1, other...);
}

template<class... T>
int SQLClient::formatPlaceholder(std::string& buffer, const char* statement, std::string& arg, T... other) {
    char* begin = (char*)statement;
    char* it = (char*)statement;
    while (*it != '?' && *it != 0) it++;
    if (*it == 0) return formatPlaceholder(buffer, statement);
    buffer.append(begin, it - begin);

    size_t dstLen = 0;
    auto escapeArg = this->realEscapeString(arg.data(), arg.length(), &dstLen);
    if (escapeArg == nullptr) {
        return -1;
    }
    buffer.append("'");
    buffer.append(escapeArg, dstLen);
    buffer.append("'");
    return formatPlaceholder(buffer, it + 1, other...);
}

template<class T, class... Args>
int SQLClient::formatPlaceholder(std::string& buffer, const char* statement, T arg, Args... other) {
    char* begin = (char*)statement;
    char* it = (char*)statement;
    while (*it != '?' && *it != 0) it++;
    if (*it == 0) return formatPlaceholder(buffer, statement);
    buffer.append(begin, it - begin);

    buffer.append(std::to_string(arg));
    return formatPlaceholder(buffer, it + 1, other...);
}

template<class... T>
int SQLClient::formatPlaceholder(std::string& buffer, const char* statement) {
    buffer.append(statement);
    return 0;
}

}//tolua_export
}//tolua_export


 