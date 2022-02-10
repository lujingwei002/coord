#include "lmysql.h"
#include "log/log.h"

typedef struct MySql
{
    MYSQL *conn;
}MySql;


static int lcreate(lua_State *L)
{
    if (lua_gettop(L) == 0)
    {
        MySql *mysql = (MySql *)lua_newuserdata(L, sizeof(MySql));
        if(mysql == NULL)
        {
            LOG_ERROR("newuserdata fail");
        }
        mysql->conn = mysql_init(NULL);
        if(mysql->conn == NULL)
        {
            LOG_ERROR("mysql_init fail %u: %s", mysql_error(mysql->conn), mysql_error(mysql->conn));
            return 0;
        }
        luaL_getmetatable(L, "MySqlMetatable");
        lua_setmetatable(L, -2);
        return 1;
    }
    lua_pushnil(L);
    return 1;
}

static int lconnect(lua_State *L)
{
    if(lua_gettop(L) == 5 && lua_isstring(L, 2) && lua_isstring(L, 3) && lua_isstring(L, 4) && lua_isstring(L, 5)
    ){
        MySql *mysql = (MySql *)luaL_checkudata(L, 1, "MySqlMetatable");
        const char *host = lua_tostring(L, 2);
        const char *dbname = lua_tostring(L, 3);
        const char *user = lua_tostring(L, 4);
        const char *passwd = lua_tostring(L, 5);
        my_bool b = true;
        mysql_options(mysql->conn, MYSQL_OPT_RECONNECT, &b);
        mysql->conn = mysql_real_connect(mysql->conn, host, user, passwd, dbname, 0, NULL, MYSQL_OPT_RECONNECT);
        if(mysql->conn == NULL)
        {
            LOG_ERROR("connect fail host(%s) dbname(%s) user(%s), %s", host, dbname, user, mysql_error(mysql->conn));
            lua_pushboolean(L, false);
            return 1;
        }
        mysql_query(mysql->conn, "set names utf8");
        //mysql_options(mysql->conn, MYSQL_SET_CHARSET_NAME, "utf8");
        lua_pushboolean(L, true);
        return 1;
    }
    lua_pushboolean(L, false);
    return 1;
}

static int lcommand(lua_State *L)
{
    if(lua_gettop(L) == 2 && lua_isstring(L, 2)){
        MySql *mysql = (MySql *)luaL_checkudata(L, 1, "MySqlMetatable");
        if(mysql == NULL){
            LOG_ERROR("checkuserdata fail");
            lua_pushboolean(L, false);
            return 1;
        }
        MYSQL *conn = mysql->conn;
        if(conn == NULL){
            LOG_ERROR("disconnect");
            lua_pushboolean(L, false);
            return 1;
        }
        mysql_query(mysql->conn, "set names utf8");
        const char *command = lua_tostring(L, 2);
        if(mysql_query(conn, command) != 0){
            LOG_ERROR("%s", mysql_error(conn));
            lua_pushboolean(L, false);
            lua_pushstring(L, mysql_error(conn));
            return 2;
        }
        lua_pushboolean(L, true);
        return 1;
    }
    lua_pushboolean(L, false);
    return 1;
}

static int laffected_rows(lua_State *L)
{
    if(lua_gettop(L) == 1){
        MySql *mysql = (MySql *)luaL_checkudata(L, 1, "MySqlMetatable");
        lua_pushnumber(L, mysql_affected_rows(mysql->conn));
        return 1;
    }
    lua_pushnumber(L, 0);
    return 1;
}

static int lselect(lua_State *L)
{
    if(lua_gettop(L) == 2 && lua_isstring(L, 2)){
        MYSQL_RES *result;
        MYSQL_ROW row;
        MYSQL_FIELD *fields;
        int index = 1;
        MySql *mysql = (MySql *)luaL_checkudata(L, 1, "MySqlMetatable");
        if(mysql == NULL){
            LOG_ERROR("checkuserdata fail");
            return 0;
        }
        MYSQL *conn = mysql->conn;
        if(conn == NULL){
            LOG_ERROR("disconnect");
            return 0;
        }
        mysql_query(mysql->conn, "set names utf8");
        const char *command = lua_tostring(L, 2);
        mysql_query(conn, command);
        result = mysql_store_result(conn);
        if(result == NULL){
            LOG_ERROR("select fail %d %s command %s", mysql_errno(conn), mysql_error(conn), command);
            return 0;
        }
        lua_newtable(L);
        while(result != NULL){
            int num_fields = mysql_num_fields(result);
            fields = mysql_fetch_fields(result);
            if(fields == NULL){
                mysql_free_result(result);
                LOG_ERROR("select fail fetch_fields command:%s", command);
                break;
            }
            while ((row = mysql_fetch_row(result))){
                unsigned long *lengths = mysql_fetch_lengths(result);
                lua_pushnumber(L, index);
                lua_newtable(L);
                index++;
                for(int i = 0; i < num_fields; i++){
                    lua_pushstring(L, fields[i].name);
                    if(row[i] != NULL){
                        if(fields[i].type == FIELD_TYPE_STRING
                            || fields[i].type == FIELD_TYPE_VAR_STRING
                            || fields[i].type == FIELD_TYPE_TINY_BLOB
                            || fields[i].type == FIELD_TYPE_MEDIUM_BLOB
                            || fields[i].type == FIELD_TYPE_LONG_BLOB
                            || fields[i].type == FIELD_TYPE_BLOB){
                            lua_pushlstring(L, row[i], lengths[i]);
                        }else if(fields[i].type == FIELD_TYPE_FLOAT
                            || fields[i].type == FIELD_TYPE_DOUBLE
                        ){
                            lua_pushnumber(L, atof(row[i]));
                        }
                        else{
                            lua_pushnumber(L, atoi(row[i]));
                        }
                    }else{
                        lua_pushnil(L);
                    }
                    lua_settable(L, -3);
                }
                lua_settable(L, -3);
            }
            mysql_free_result(result);
            result = NULL;
            //是否还有结果集
            if(mysql_next_result(conn) == 0){
                result = mysql_store_result(conn);
            }
        }
        return 1;
    }
    lua_pushnumber(L, -1);
    return 1;
}

static int lping(lua_State *L)
{
    if(lua_gettop(L) == 1)
    {
        MySql *mysql = (MySql *)luaL_checkudata(L, 1, "MySqlMetatable");
        if(mysql == NULL)
        {
            LOG_ERROR("checkuserdata fail");
            lua_pushboolean(L, false);
            return 0;
        }
        MYSQL *conn = mysql->conn;
        if(conn == NULL)
        {
            LOG_ERROR("disconnect");
            lua_pushboolean(L, false);
            return 1;
        }
        if(mysql_ping(mysql->conn))
        {
            lua_pushboolean(L, false);
            return 1;
        }
        lua_pushboolean(L, true);
        return 1;
    }
    lua_pushboolean(L, false);
    return 1;
}

static char *escape_buf;
static size_t escape_buf_len;

static int lreal_escape_string(lua_State *L)
{
    if(lua_gettop(L) == 2){
        MySql *sql = (MySql *)luaL_checkudata(L, 1, "MySqlMetatable");
        if(sql == NULL){
            LOG_ERROR("checkuserdata fail");
            return 0;
        }
        size_t str_len;
        const char *str = (const char *)lua_tolstring(L, 2, &str_len);
        if(str_len == 0){
            lua_pushstring(L, "");
            return 1;
        }
        if(escape_buf_len < str_len * 2){
            if(escape_buf != NULL){
                escape_buf_len = 0;
                free(escape_buf);
            }
            escape_buf = (char *)malloc(str_len * 2);
            if(escape_buf == NULL){
                LOG_ERROR("malloc fail");
                lua_pushboolean(L, false);
                return 1;
            }
            escape_buf_len = str_len * 2;
        }
        int len = mysql_real_escape_string(sql->conn, escape_buf, str, str_len);
        lua_pushlstring(L, escape_buf, len);
        return 1;
    }
    lua_pushboolean(L, false);
    return 1;
}


static int lclose(lua_State *L)
{
    if(lua_gettop(L) == 1){
        MySql *sql = (MySql *)luaL_checkudata(L, 1, "MySqlMetatable");
        if(sql == NULL){
            LOG_ERROR("checkuserdata fail");
            return 0;
        }
        if(sql->conn){
            mysql_close(sql->conn);
            sql->conn = NULL;
        }
        lua_pushboolean(L, true);
        return 1;
    }
    lua_pushboolean(L, false);
    return 1;
}



static luaL_Reg lua_lib[] = 
{
    {"create", lcreate},
    {NULL, NULL}
};

static luaL_Reg lua_metatable[] = 
{
    {"connect", lconnect},
    {"select", lselect},
    {"command", lcommand},
    {"affected_rows", laffected_rows},
    {"escape", lreal_escape_string},
    {"close", lclose},
    {"ping", lping},
    {"__gc", lclose},
    {NULL, NULL}
};


int luaopen_mysql(lua_State *L)
{
	luaL_register(L, "mysql", (luaL_Reg*)lua_lib);
    luaL_newmetatable(L, "MySqlMetatable");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    luaL_register(L, NULL, (luaL_Reg*)lua_metatable);
    return 0;
}

