#include "coord/sql/sql_result.h"
#include "coord/sql/sql_client.h"
#include "coord/coord.h"

namespace coord {
namespace sql {

RC_IMPLEMENT(SQLResult, "coord::sql::SQLResult")

sql_result::sql_result(Coord *coord) {
    this->coord = coord;
    this->ref = 0;
}

sql_result::~sql_result() {
}

uint64_t sql_result::RowsAffected() {
    return this->rowsAffected;
}

uint64_t sql_result::LastInsertId() {
    return this->lastInsertId;
}


SQLResult::SQLResult(Coord* coord, sql_result* result) {
    this->coord = coord;
    this->result = result;
    this->result->ref++;
}

SQLResult::SQLResult(Coord* coord) {
    this->coord = coord;
    this->result = nullptr;
}

SQLResult::~SQLResult() {
    if (this->result != nullptr){
        this->result->ref--;
        if (this->result->ref == 0) {
            delete this->result;
        }
        this->result = nullptr;
    }
}

SQLResult::SQLResult(const SQLResult& other) {
    this->result = other.result;
    this->coord = other.coord;
    if(this->result != nullptr) {
        this->result->ref++;
    }
}

SQLResult& SQLResult::operator=(const SQLResult& other) {
    if (this->result != nullptr){
        this->result->ref--;
        if (this->result->ref == 0) {
            delete this->result;
        }
        this->result = nullptr;
    }
    this->coord = other.coord;
    this->result = other.result;
    if(this->result != nullptr) {
        this->result->ref++;
    }
    return *this;
}

}
}        