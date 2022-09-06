#include "coord/sql/sql_rows.h"
#include "coord/sql/sql_client.h"
#include "coord/coord.h"

namespace coord {
namespace sql {
    
RC_IMPLEMENT(SQLRows, "coord::sql::SQLRows")

sql_rows::sql_rows(Coord *coord) {
    this->coord = coord;
    this->ref = 0;
} 

sql_rows::~sql_rows() {
}

SQLRows::SQLRows(Coord* coord, sql_rows* rows) {
    this->coord = rows->coord;
    this->rows = rows;
    this->rows->ref++;
}

SQLRows::SQLRows(Coord* coord) {
    this->coord = coord;
    this->rows = nullptr;
}

SQLRows::~SQLRows() {
    if (this->rows != nullptr){
        this->rows->ref--;
        if (this->rows->ref == 0) {
            delete this->rows;
        }
        this->rows = nullptr;
    }
}

SQLRows::SQLRows(const SQLRows& other) {
    this->coord = other.coord;
    this->rows = other.rows;
    if(this->rows != nullptr) {
        this->rows->ref++;
    }
}

SQLRows& SQLRows::operator=(const SQLRows& other) {
    if (this->rows != nullptr){
        this->rows->ref--;
        if (this->rows->ref == 0) {
            delete this->rows;
        }
        this->rows = nullptr;
    }
    this->coord = other.coord;
    this->rows = other.rows;
    if(this->rows != nullptr) {
        this->rows->ref++;
    }
    return *this;
}



}
}         