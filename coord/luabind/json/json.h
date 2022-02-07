#ifndef __JSON_H__
#define __JSON_H__

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}

/*
 * Json.encode({a='a', b='b'})
 * Json.decode(str)
 * //str to lua table
 * int json_decode(lua_State *L, char *str)
 *
 * //lua table to str
 * char *json_encode(lua_State *L)
 *
 */
namespace Json 
{
    char *encode(lua_State *L);
    int decode(lua_State* L, char *str);
};

#endif
