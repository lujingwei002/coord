#include "net/ltimer.h"
#include "net/ae.h"
#include "log/log.h"


typedef struct TimerData 
{
    char callback[64];
    int msec;
    int timerid;
    int msgid;
    void* userdata;
    lua_State* L;
}TimerData;

typedef struct SelfTimerData 
{
    lua_State* L;
    char callback[64];
}SelfTimerData;

static SelfTimerData s_self_timer_data;
static int s_timer_counter = 0;
static int s_min_msec = 0x7fffffff;
static int s_call_lua_time = 0;

//login.hello_world
//hello_world
static int lua_pushluafunction(lua_State *L, const char *func)
{
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
    }else{
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

static void timer_finalizer_proc(struct aeEventLoop *eventLoop, void *clientData) 
{
    TimerData *timedata = (TimerData *)clientData;
    if (timedata) 
    {
        free(timedata);
    }
    s_timer_counter--;
}

/*
 * 如果lua返回0则删除timer, 
 * 如果n=0, 则以上次的时间再次触发
 * 如果n>0, 则n毫秒后再次触发
 */
static int timer_proc(struct aeEventLoop *eventLoop, long long id, void *clientData)
{
    TimerData *timerdata = (TimerData *)clientData;
    if(timerdata == NULL)
    {
        LOG_ERROR("timer is null");
        return AE_NOMORE;
    }
    lua_State *L = timerdata->L;
    if(lua_pushluafunction(L, timerdata->callback) == 0)
    {
        LOG_ERROR("push func %s fail", timerdata->callback);
        return AE_NOMORE;
    }
    //LOG_LOG("[TIMER_START] %s", timerdata->callback);
    s_call_lua_time++;
    lua_pushnumber(L, timerdata->timerid);
    
    if(lua_pcall(L, 1, 1, 0) != 0)
    {
        LOG_ERROR("%s", lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return timerdata->msec;
    }
    //LOG_LOG("[TIMER_END] %s", timerdata->callback);
    int ir = (int)lua_tointeger(L, -1);
    lua_pop(L, lua_gettop(L));
    if(ir == 1)
    {
        return timerdata->msec;
    }else if(ir != 0)
    {
        return ir;
    }else
    {
        return AE_NOMORE;
    }
} 

/*
 * 如果lua返回0则删除timer, 如果n>0, 则n毫秒后再次触发
 */
static int self_timer_proc(struct aeEventLoop *eventLoop, long long timerid, void *clientData)
{
    lua_State *L = s_self_timer_data.L;
    if (L == NULL) 
    {
        LOG_ERROR("lua_State is nil");
        s_timer_counter--;
        return AE_NOMORE;
    }
    size_t selfid = (size_t)clientData;
    if(lua_pushluafunction(L, s_self_timer_data.callback) == 0)
    {
        LOG_ERROR("push func %s fail", s_self_timer_data.callback);
        s_timer_counter--;
        return AE_NOMORE;
    }
    lua_pushnumber(L, timerid);
    lua_pushnumber(L, selfid);
    s_call_lua_time++;
    if(lua_pcall(L, 2, 1, 0) != 0)
    {
        LOG_ERROR("%s", lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        s_timer_counter--;
        return AE_NOMORE;
    }
    int ir = (int)lua_tointeger(L, -1);
    lua_pop(L, lua_gettop(L));
    if(ir != 0)
    {
        return ir;
    }else
    {
        s_timer_counter--;
        return AE_NOMORE;
    }
} 

/*
 * @arg1 loop
 * @arg2 milliseconds
 * @arg3 callback
 */
static int laddtimer(lua_State *L)
{
    if (lua_gettop(L) == 3 && lua_isuserdata(L, 1) && lua_isnumber(L, 2) && lua_isstring(L, 3)) 
    {
        aeEventLoop *loop;
        int msec;
        char *funcname;
        loop = (aeEventLoop *)lua_touserdata(L, 1);
        msec = (int)lua_tonumber(L, 2);
        funcname = (char *)lua_tostring(L, 3);
        TimerData *timerdata = (TimerData *)malloc(sizeof(TimerData));
        if(timerdata == NULL)
        {
            LOG_ERROR("malloc fail");
            return 0;
        }
        timerdata->msec = msec;
        timerdata->L = L;
        strcpy(timerdata->callback, funcname);
        s_timer_counter++;
        if(s_min_msec > msec)s_min_msec = msec;
        int timerid = aeCreateTimeEvent(loop, msec, timer_proc, timerdata, timer_finalizer_proc);
        timerdata->timerid = timerid;
        lua_pushnumber(L, timerid);
        return 1;
    }
    LOG_ERROR("args wrong");
    return 0;
}

static int lsetselftimerloop(lua_State *L)
{
    if (lua_gettop(L) == 1 && lua_isstring(L, 1)) 
    {
        const char *callback   = (const char *)lua_tostring(L, 1);
        strcpy(s_self_timer_data.callback, callback);
        s_self_timer_data.L = L;
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int lstopselftimer(lua_State *L)
{
    if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isnumber(L, 2)) 
    {
        aeEventLoop *loop;
        int timerid;
        loop = (aeEventLoop *)lua_touserdata(L, 1); 
        timerid = (int)lua_tonumber(L, 2);
        if(aeDeleteTimeEvent(loop, timerid) == AE_OK)
        {
            s_timer_counter--;
        }
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

/*
 * @arg1 loop
 * @arg2 milliseconds
 * @arg3 selfid
 */
static int laddselftimer(lua_State *L)
{
    if (lua_gettop(L) == 3 && lua_isuserdata(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)) 
    {
        aeEventLoop *loop;
        int milliseconds;
        size_t selfid;
        loop = (aeEventLoop *)lua_touserdata(L, 1); 
        milliseconds = (int)lua_tonumber(L, 2);
        selfid = (size_t)lua_tonumber(L, 3);
        s_timer_counter++;
        if(s_min_msec > milliseconds)s_min_msec = milliseconds;
        int timerid = aeCreateTimeEvent(loop, milliseconds, self_timer_proc, (void *)selfid, NULL);
        lua_pushnumber(L, timerid);
        return 1;
    }
    return 0;
}

static luaL_Reg lua_lib[] = 
{
    {"addtimer", laddtimer},
    {"addselftimer", laddselftimer},
    {"stopselftimer", lstopselftimer},
    {"setselftimerloop", lsetselftimerloop},
    {NULL, NULL}
};

int luaopen_timer(lua_State *L)
{
    luaL_register(L, "Timer", lua_lib);
    return 1;
}

