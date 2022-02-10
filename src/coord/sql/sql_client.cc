#include "coord/sql/sql_client.h"
#include "coord/sql/sql_result.h"
#include "coord/sql/sql_rows.h"
#include "coord/coord.h"

namespace coord {
namespace sql {

CC_IMPLEMENT(SQLClient, "coord::sql::SQLClient")


SQLClient::SQLClient(Coord *coord) {
    this->coord = coord;
}   

SQLClient::~SQLClient() {
}

SQLConfig* SQLClient::DefaultConfig() {
    return &this->config;
}

int SQLClient::Query(lua_State* L) {
    tolua_Error tolua_err;
    static byte_slice value;
    if (
        !tolua_isstring(L,2,0,&tolua_err)
    )
        goto tolua_lerror;
    else {
        const char* statement = this->formatPlaceholder(L);
        if (!statement)goto tolua_lerror;
        {
            SQLRows tolua_ret = this->query(statement);
            SQLRows* tolua_obj = new SQLRows(tolua_ret);
            tolua_pushusertype_and_takeownership(L, (void*)tolua_obj, "coord::sql::SQLRows");
        }
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Query'.",&tolua_err);
    return 0;
}

int SQLClient::Execute(lua_State* L) {
    tolua_Error tolua_err;
    static byte_slice value;
    if (
        !tolua_isstring(L,2,0,&tolua_err)
    )
        goto tolua_lerror;
    else {
        const char* statement = this->formatPlaceholder(L);
        if (!statement)goto tolua_lerror;
        {
            SQLResult tolua_ret = this->execute(statement);
            SQLResult* tolua_obj = new SQLResult(tolua_ret);
            tolua_pushusertype_and_takeownership(L, (void*)tolua_obj, "coord::sql::SQLResult");
        }
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Execute'.",&tolua_err);
    return 0;
}

int SQLClient::Get(lua_State* L) {
    tolua_Error tolua_err;
    static byte_slice value;
    if (
        !tolua_isstring(L,2,0,&tolua_err)
    )
        goto tolua_lerror;
    else {
        const char* statement = this->formatPlaceholder(L);
        if (!statement)goto tolua_lerror;
        {
            SQLRows tolua_ret = this->get(statement);
            SQLRows* tolua_obj = new SQLRows(tolua_ret);
            //tolua_pushusertype(L,(void*)tolua_ret,"coord::sql::SQLRows");
            tolua_pushusertype_and_takeownership(L, (void*)tolua_obj, "coord::sql::SQLRows");
        }
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Query'.",&tolua_err);
    return 0;
}

const char* SQLClient::formatPlaceholder(lua_State* L) {
    static thread_local byte_slice buffer;
    buffer.Resize(0);
    int i = 2;
    char* data = ((char*)  tolua_tostring(L, i, 0));
    i = i + 1;
    char* offset = data;
    char* start = offset;
    while(*offset != 0) {
        if (*offset == '?') {
            coord::Append(buffer, start, offset - start);
            if (lua_isstring(L,i)) {
                size_t len = 0;
                const char* str = (const char*)lua_tolstring(L, i, &len);
                size_t realLen = 0;
                const char* value = this->realEscapeString(str, len, &realLen);
                coord::Append(buffer, '\'');
                coord::Append(buffer, value, realLen);
                coord::Append(buffer, '\'');
            } else {
                return NULL;
            }
            i = i + 1;
            offset = offset + 1;
            start = offset;
        } else { 
            offset = offset + 1;
        }
    }
    if (offset - start > 0) {
        coord::Append(buffer, start, offset - start);
    }
    coord::Append(buffer, 0);
    return buffer.Data();
}

}
}         