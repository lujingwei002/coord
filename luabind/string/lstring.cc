#include "lstring.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static int lcap(lua_State *L)
{
    
    if (lua_isstring(L, 1)) 
    {
        char dst[1024];
        size_t str_len;
        char *str = (char *)lua_tolstring(L, 1, &str_len);
        strcpy(dst, str);
        dst[0] = toupper(dst[0]);
        lua_pushlstring(L, dst, str_len);
        return 1;
    }
    return 0;
}

static char *s_join_buf;
static size_t s_join_buf_len = 0;
static int ljoin(lua_State *L)
{
    if (lua_isstring(L, 1) && lua_istable(L, 2)) 
    {
        char *joinstr = (char *)lua_tostring(L, 1);
        size_t str_len = 1;
        lua_pushnil(L);
        int count = 0;
        while (lua_next(L, 2) != 0) 
        {
            size_t len;
            lua_tolstring(L, -1, &len);
            str_len += (len + 1);
            lua_pop(L, 1);
            count = count + 1;
        }
        if (s_join_buf_len < str_len) 
        {
            char *newbuf;
            if (s_join_buf != NULL) 
            {
                newbuf = (char *)realloc(s_join_buf, str_len);
            } else 
            {
                newbuf = (char *)malloc(str_len);
            }
            if (newbuf == NULL) 
            {
                return 0;
            }
            s_join_buf = newbuf;
            s_join_buf_len = str_len;
        }
        s_join_buf[0] = 0;
        lua_pushnil(L);
        while (lua_next(L, 2) != 0) 
        {
            size_t len;
            char *str = (char *)lua_tolstring(L, -1, &len);
            str_len += (len + 1);
            strcat(s_join_buf, str);
            if (count > 1) 
            {
                strcat(s_join_buf, joinstr);
            }
            lua_pop(L, 1);
            count = count - 1;
        }
        lua_pushstring(L, s_join_buf);
        return 1;
    }
    return 0;
}

static int lgettable(lua_State *L) 
{
    char *func = (char *)lua_tostring(L, 1);
    char *start = (char *)func;
    char *class_name = start;
    char *pfunc = start;
    while(*pfunc != 0)
    {
        if(*pfunc == '.' && class_name == start)
        {
            *pfunc = 0;
            lua_getglobal(L, class_name);
            *pfunc = '.';
            if(lua_isnil(L, -1))
            {
                return 0;
            }
            class_name = pfunc + 1;
        }else if(*pfunc == '.')
        {
            *pfunc = 0;
            lua_pushstring(L, class_name);
            lua_gettable(L, -2);
            *pfunc = '.';
            if(lua_isnil(L, -1))
            {
                return 0;
            }
    	    lua_remove(L, -2);//弹出table
            class_name = pfunc + 1;
        }
        pfunc++;
    }
    if(class_name == start)
    {
        lua_getglobal(L, class_name);
        if(lua_isnil(L, -1))
        {
            return 0;
        }
    }else
    {
        lua_pushstring(L, class_name);
        lua_gettable(L, -2);
        if(lua_isnil(L, -1))
        {
            return 0;
        }
        lua_remove(L, -2);//弹出table
    }
    return 1;     
}

static int lsplit(lua_State *L)
{
    size_t i;
    if (lua_isstring(L, 1) && lua_isstring(L, 2)) 
    {
        size_t str_len;
        size_t token_len;
        char *str = (char *)lua_tolstring(L, 1, &str_len);
        char *token = (char *)lua_tolstring(L, 2, &token_len);
        char *last_str = str;
        lua_newtable(L);
        int index = 1;
        for (i = 0; i < str_len; i++) 
        {
            if (!strncmp(str + i, token, token_len)) 
            {
                lua_pushinteger(L, index++); 
                lua_pushlstring(L, last_str, str + i - last_str);
                lua_settable(L, -3);
                i = i + token_len - 1;
                last_str = str + i + token_len;
            }
        }
        if (last_str == str) 
        {
            lua_pushinteger(L, index);
            lua_pushstring(L, str);
            lua_settable(L, -3);
        } else 
        {
            lua_pushinteger(L, index); 
            lua_pushstring(L, last_str);
            lua_settable(L, -3);
        }
        return 1;
    }
    return 0;
}

static luaL_Reg lua_lib[] =
{
    {"gettable", lgettable},
    {"split", lsplit},
    {"join", ljoin},
    {"cap", lcap},
    {NULL, NULL}
};

int luaopen_cstring(lua_State *L)
{
	luaL_register(L, "string", lua_lib);
	return 1;
}

