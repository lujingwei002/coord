#include "stdafx.h"
/*
 *   local arfd = Ar.create(buf, buflen)
 *   local uid = Ar.read_int(arfd)
 *   local uname = Ar.read_str(arfd)
 */

static int lrewind(lua_State *L)
{
    int fd = (int)lua_tointeger(L, 1);
    Ar::rewind(fd);
    return 0;
}

static int ldatalen(lua_State *L)
{
    int fd = (int)lua_tointeger(L, 1);
    int len = Ar::datalen(fd);
    lua_pushinteger(L, len);
    return 1;
}

static int lremain(lua_State *L)
{
    int fd = (int)lua_tointeger(L, 1);
    int len = Ar::datalen(fd);
    lua_pushinteger(L, len);
    return 1;
}

static int lgetptr(lua_State *L)
{
    int fd = (int)lua_tointeger(L, 1);
    char* ptr = Ar::getptr(fd);
    lua_pushlightuserdata(L, ptr);
    return 1;
}

static int ltest(lua_State *L)
{
    printf("test\n");
    return 0;
}

/*
 * for test
 */
static int lmalloc(lua_State *L) 
{
    int len = (int)lua_tointeger(L, 1);
    char *buf = (char *)malloc(len);
    lua_pushlightuserdata(L, buf);
    return 1;
}

static int lfree(lua_State *L)
{
    int fd = (int)lua_tointeger(L, 1);
    Ar::free(fd);
    return 0;
}

static int lcreate(lua_State *L)
{
	if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        char *buf = (char *)lua_touserdata(L, 1);
        int buf_len = (int)lua_tointeger(L, 2);
        int fd = Ar::create(buf, buf_len);
        lua_pushinteger(L, fd);
        return 1;
    }
    return 0;
}

static int lwritestr(lua_State *L)
{
	if (lua_gettop(L) == 2 && lua_isnumber(L, 1) && lua_isstring(L, 2))
    {
        char *str;
        size_t str_len;
        int fd = (int)lua_tointeger(L, 1);
        str = (char *)lua_tolstring(L, 2, &str_len);
        int real_len = Ar::writebuf(fd, str, str_len);
        lua_pushinteger(L, real_len); 
        return 1;
	}
    return 0;
}

static int lwritelstr(lua_State *L)
{
	if (lua_gettop(L) == 2 && lua_isnumber(L, 1) && lua_isstring(L, 2))
    {
        int fd = (int)lua_tointeger(L, 1);
        char *str = (char *)lua_tostring(L, 2);
        int str_len = Ar::writelstr(fd, str);
        lua_pushinteger(L, str_len); 
        return 1;
	}
    return 0;
}

static int lwriteint8(lua_State *L)
{
	if (lua_gettop(L) == 2 && lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        int fd = (int)lua_tointeger(L, 1);
        int8 val = (int8)lua_tointeger(L, 2);
        Ar::writeint8(fd, val);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static int lwriteint16(lua_State *L)
{
	if (lua_gettop(L) == 2 && lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        int fd = (int)lua_tointeger(L, 1);
        int16 val = (int16)lua_tointeger(L, 2);
        Ar::writeint16(fd, val);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static int lwriteint32(lua_State *L)
{
	if (lua_gettop(L) == 2 && lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        int fd = (int)lua_tointeger(L, 1);
        int32 val = (int32)lua_tointeger(L, 2);
        Ar::writeint32(fd, val);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static int lwriteint64(lua_State *L){
	if (lua_gettop(L) == 2 && lua_isnumber(L, 1) && lua_isnumber(L, 2)){
        int fd = (int)lua_tointeger(L, 1);
        int64 val = (int64)lua_tointeger(L, 2);
        Ar::writeint64(fd, val);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static int lreaduint8(lua_State *L)
{
    if (lua_gettop(L) == 1 && lua_isnumber(L, 1))
    {
        int fd = (int)lua_tointeger(L, 1);
        uint8 val = Ar::readuint8(fd);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}


static int lreadint8(lua_State *L)
{
	if (lua_gettop(L) == 1 && lua_isnumber(L, 1))
    {
        int fd = (int)lua_tointeger(L, 1);
        int8 val = Ar::readint8(fd);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static int lreadint16(lua_State *L)
{
    if (lua_gettop(L) == 1 && lua_isnumber(L, 1))
    {
        int fd = (int)lua_tointeger(L, 1);
        int16 val = Ar::readint16(fd);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static int lreadint32(lua_State *L)
{
	if (lua_gettop(L) == 1 && lua_isnumber(L, 1))
    {
        int fd = (int)lua_tointeger(L, 1);
        int32 val = Ar::readint32(fd);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static int lreadint64(lua_State *L)
{
	if (lua_gettop(L) == 1 && lua_isnumber(L, 1)){
        int fd = (int)lua_tointeger(L, 1);
        int64 val = Ar::readint64(fd);
        lua_pushinteger(L, val); 
        return 1;
	}
    return 0;
}

static luaL_Reg lua_lib[] = {
    {"malloc",      lmalloc},
    {"create",      lcreate},
    {"free",        lfree},
    {"datalen",     ldatalen},
    {"remain",      lremain},
    {"getptr",      lgetptr},
    {"rewind",      lrewind},
    {"test",        ltest},
    {"readuint8",   lreaduint8},
    {"readint8",    lreadint8},
    {"readint16",   lreadint16},
    {"readint32",   lreadint32},
    {"readint64",   lreadint64},
    {"readlstr",    Ar::lreadlstr},
    {"readstr",     Ar::lreadstr},

    {"writeint8",   lwriteint8},
    {"writeint16",  lwriteint16},
    {"writeint32",  lwriteint32},
    {"writeint64",  lwriteint64},
    {"writelstr",   lwritelstr},
    {"writestr",    lwritestr},

    {0, 0}
};

int luaopen_ar(lua_State *L){
	luaL_register(L, "Ar", lua_lib);
    return 1;
}

