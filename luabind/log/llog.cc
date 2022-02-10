#include "log/llog.h"
#include "log/log.h"

#define FATAL   0
#define ERROR   1
#define WARN    2
#define INFO    3
#define DEBUG   4
#define MSG     5

static int lfatal(lua_State* L)
{
    const char* str = (const char*)lua_tostring(L, 1);
    Log::fatal("%s", str);
    return 0;
}
static int lerror(lua_State* L)
{
    const char* str = (const char*)lua_tostring(L, 1);
    Log::error("%s", str);
    return 0;
}
static int lwarn(lua_State* L)
{
    const char* str = (const char*)lua_tostring(L, 1);
    Log::warn("%s", str);
    return 0;
}
static int linfo(lua_State* L)
{
    const char* str = (const char*)lua_tostring(L, 1);
    Log::info("%s", str);
    return 0;
}
static int lmsg(lua_State* L)
{
    const char* str = (const char*)lua_tostring(L, 1);
    Log::msg("%s", str);
    return 0;
}


static int ldebug(lua_State* L)
{
    const char* str = (const char*)lua_tostring(L, 1);
    Log::debug("%s", str);
    return 0;
}

static int lstdout2file(lua_State* L)
{
    if (!lua_isstring(L, 1))
    {
        return 0;
    }
    const char* file_path = (const char*)lua_tostring(L, 1);
    Log::stdout2file(file_path);
    return 0;
}

static int lclosealllevel(lua_State* L)
{
    Log::closealllevel();
    return 0;
}

static int lopenlevel(lua_State* L)
{
    if (!lua_isnumber(L, 1))
    {
        return 0;
    }
    int level = (int)lua_tonumber(L, 1);
    Log::openlevel(level);
    return 0;
}


static int lcloselevel(lua_State* L)
{
    if (!lua_isnumber(L, 1))
    {
        return 0;
    }
    int level = (int)lua_tonumber(L, 1);
    Log::closelevel(level);
    return 0;
}

static luaL_Reg lua_lib[] = 
{
    {"fatal", lfatal},
    {"error", lerror},
    {"warn", lwarn},
    {"info", linfo},
    {"debug", ldebug},
    {"msg", lmsg},
    {"closelevel", lcloselevel},
    {"openlevel", lopenlevel},
    {"closealllevel", lclosealllevel},
    {"stdout2file", lstdout2file},
    {NULL, NULL}
};

int luaopen_log(lua_State *L)
{
    luaL_register(L, "Log", lua_lib);
    lua_pushstring(L, "FATAL");
    lua_pushnumber(L, FATAL);
    lua_settable(L, -3);
    lua_pushstring(L, "ERROR");
    lua_pushnumber(L, ERROR);
    lua_settable(L, -3);
    lua_pushstring(L, "WARN");
    lua_pushnumber(L, WARN);
    lua_settable(L, -3);
    lua_pushstring(L, "INFO");
    lua_pushnumber(L, INFO);
    lua_settable(L, -3);
    lua_pushstring(L, "DEBUG");
    lua_pushnumber(L, DEBUG);
    lua_settable(L, -3);
    lua_pushstring(L, "MSG");
    lua_pushnumber(L, MSG);
    lua_settable(L, -3);
    return 1;
}

