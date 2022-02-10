#include "json/ljson.h"
#include "json/json.h"
#include "log/log.h"

static int lencode(lua_State *L)
{
    char *str = Json::encode(L);
    if(str == NULL)
    {
        LOG_ERROR("null");
        return 0;
    }
    lua_pushstring(L, str);
    free(str);
    return 1;
}

static int ldecode(lua_State *L)
{
    if(!lua_isstring(L, 1))
    {
        printf("is not string\n");
        return 0;
    }
    char *str = (char *)lua_tostring(L, 1);
    if(Json::decode(L, str) == 0)
    {
        printf("decode fail\n");
        return 0;
    }
    return 1;
}

static luaL_Reg lua_lib[] = 
{
    {"encode", lencode},
    {"decode", ldecode},
    {NULL, NULL}
};

int luaopen_json(lua_State *L)
{
    luaL_register(L, "Json", lua_lib);
    return 1;
}

