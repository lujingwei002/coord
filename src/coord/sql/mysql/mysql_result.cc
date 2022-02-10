#include "coord/sql/mysql/mysql_result.h"
#include "coord/sql/mysql/mysql_client.h"
#include "coord/coord.h"

namespace coord {
namespace sql {
CC_IMPLEMENT(mysql_result, "coord::mysql::mysql_result")

mysql_result* newMySQLResult(Coord* coord, MYSQL *conn) {
    auto self = new mysql_result(coord, conn);
    return self;
}

mysql_result::mysql_result(Coord *coord, MYSQL *conn) : sql_result(coord) {
    this->conn = conn;
    this->rowsAffected = mysql_affected_rows(this->conn);
    this->lastInsertId = mysql_insert_id(this->conn);
}

mysql_result::~mysql_result() {
}

}
}        