#ifndef __LMYSQL_H__
#define __LMYSQL_H__
#include <mysql/mysql.h>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}


/*
 *  local conn = Mysql.connect(ip, dbname, user, password)
 *  Mysql.command(conn, 'xx')
 *  Mysql.select(conn, 'xxx')
 *  Mysql.close(conn)
 *
 */
int luaopen_mysql(lua_State *L);

#endif
