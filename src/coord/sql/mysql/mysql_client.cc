#include "coord/sql/mysql/mysql_client.h"
#include "coord/sql/mysql/mysql_result.h"
#include "coord/sql/mysql/mysql_rows.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/init.h"
#include "util/date/date.h"
#include "coord/coord.h"

namespace coord {
namespace sql {

CC_IMPLEMENT(MySQLClient, "coord::mysql::MySQLClient")

MySQLClient* newMySQLClient(Coord *coord) {
    auto client = new MySQLClient(coord);
    return client;
}

MySQLClient::MySQLClient(Coord *coord) : SQLClient(coord) {
    this->conn = nullptr;
}   

MySQLClient::~MySQLClient() {
    if(this->conn != nullptr){
        mysql_close(this->conn);
        this->conn = nullptr;
    }
}

int MySQLClient::Connect() {
    MYSQL* conn = mysql_init(NULL);
    if(conn == nullptr) {
        this->coord->CoreLogError("[MySQLClient] Connect failed, host=%s, port=%d, error='%s'", config.Host.c_str(), config.Port, mysql_error(conn));
        return ErrorUnknown;
    }
    my_bool b = true;
    int err = mysql_options(conn, MYSQL_OPT_RECONNECT, &b);
    if (err != 0){
        this->coord->CoreLogError("[MySQLClient] Connect failed, host=%s, port=%d, error='%s'", config.Host.c_str(), config.Port, mysql_error(conn));
        return ErrorUnknown;
    }
    auto config = this->config;
    conn = mysql_real_connect(conn, config.Host.c_str(), config.User.c_str(), config.Password.c_str(), config.DB.c_str(), config.Port, NULL, MYSQL_OPT_RECONNECT);    
    if(conn == nullptr){
        this->coord->CoreLogError("[MySQLClient] Connect failed, host=%s, port=%d, error='%s'", config.Host.c_str(), config.Port, mysql_error(conn));
        return ErrorUnknown;
    }
    err = mysql_set_character_set(conn, config.CharacterSet.c_str()); 
    if (err != 0){
        this->coord->CoreLogError("[MySQLClient] Connect failed, host=%s, port=%d, error='%s'", config.Host.c_str(), config.Port, mysql_error(conn));
        return ErrorUnknown;
    }
    this->conn = conn;
    return 0;
}

const char* MySQLClient::realEscapeString(const char* src, size_t srcLen, size_t* dstLen) {
    static thread_local std::string buffer;
    if (this->conn == nullptr) {
        return nullptr;
    }
    buffer.reserve(srcLen * 2 + 1);
    size_t realLen = mysql_real_escape_string(this->conn, (char*)buffer.data(), src, srcLen);   
    *dstLen = realLen;
    return buffer.data();
}

SQLRows MySQLClient::query(const char* statement) {
    if(this->conn == nullptr){
        return SQLRows(this->coord);
    }
    this->coord->CoreLogDebug("[MySQLClient] query, %s", statement);
    int err = mysql_query(this->conn, statement);
    if (err != 0){
        this->coord->CoreLogError("[MySQLClient] query failed, statement=`%s`, error=`%s`", statement, mysql_error(conn));
        return SQLRows(this->coord);
    }
    return SQLRows(this->coord, newMySQLRows(this->coord, this->conn));
}


SQLRows MySQLClient::get(const char* statement) {
    if(this->conn == nullptr){
        return SQLRows(this->coord);
    }
    this->coord->CoreLogDebug("[MySQLClient] get, %s", statement);
    uint64_t t1 = uv_hrtime();
    int err = mysql_query(this->conn, statement);
    uint64_t duration = uv_hrtime() - t1;
    this->coord->CoreLogDebug("[MySQLClient] get, %s %s", date::FormatNano(duration), statement);
    if (err != 0){
        this->coord->CoreLogError("[MySQLClient] get failed, statement=`%s`, error=`%s`", statement, mysql_error(conn));
        return SQLRows(this->coord);
    }
    return SQLRows(this->coord, newMySQLRows(this->coord, this->conn));
}

SQLResult MySQLClient::execute(const char* statement) {
    if(this->conn == nullptr){
        return SQLResult(this->coord);
    }
    int err = mysql_query(this->conn, statement);
    if (err != 0){
        this->coord->CoreLogError("[MySQLClient] execute failed, statement=`%s`, error=`%s`", statement, mysql_error(conn));
        return SQLResult(this->coord);
    }
    return SQLResult(this->coord, newMySQLResult(this->coord, this->conn));
}

int MySQLClient::Ping() {
    if(this->conn == nullptr){
        return ErrorUnknown;
    }
    int err = mysql_ping(this->conn);
    if (err != 0){
        this->coord->CoreLogError("[MySQLClient] Ping failed, error='%s'", mysql_error(conn));
        return ErrorUnknown;
    }
    return 0;
}

const char* MySQLClient::Error() {
    if(this->conn == nullptr){
        return nullptr;
    }
    return mysql_error(this->conn);
}

void MySQLClient::Close() {
    if(this->conn != nullptr){
        return;
    }
    mysql_close(this->conn);
    this->conn = nullptr;
}

uint64_t MySQLClient::RowsAffected(){
    if(this->conn == nullptr){
        return 0;
    }
    return mysql_affected_rows(this->conn);
}

uint64_t MySQLClient::LastInsertId(){
    if(this->conn == nullptr){
        return 0;
    }
    return mysql_insert_id(this->conn);
    
}

}
}        