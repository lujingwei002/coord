#include "net/lae.h"
#include "net/ae.h"
#include "log/log.h"

/*
 * 
 *  local loop = Ae.create(1024)
 *  Ae.create_file_event(loop, sockfd, Ae.AE_READABLE, on_read)
 *  Ae.run_once()
 */



#define MAX_FILE_DATA 10240

static aeEventLoop *main_loop;

typedef struct FileData 
{
    lua_State *L;
    char file_read_proc[64]; //MAX_PATH
    char file_writ_proc[64]; //MAX_PATH
    char time_proc[64];
}FileData;

typedef struct TimeData 
{
    lua_State *L;
    char time_proc[64];
    int interval;
}TimeData;

static FileData file_data_array[MAX_FILE_DATA];


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


static void file_proc(struct aeEventLoop *eventLoop, int sockfd, void *clientData, int mask) 
{
    printf("file_proc sockfd(%d)\n", sockfd);
    FileData *filedata = (FileData *)clientData;
    lua_State *L = filedata->L;
    
    if (mask & AE_READABLE && filedata->file_read_proc[0]) 
    {
        lua_pushluafunction(L, filedata->file_read_proc);
        lua_pushinteger(L, sockfd);
        lua_pushinteger(L, mask);
        if (lua_pcall(L, 2, 0, 0) != 0)
        {
            LOG_ERROR("error running function %s: %s", filedata->file_read_proc, lua_tostring(L, -1));
        }
    }
    if (mask & AE_WRITABLE && filedata->file_writ_proc[0]) 
    {
        lua_pushluafunction(L, filedata->file_writ_proc);
        lua_pushinteger(L, sockfd);
        lua_pushinteger(L, mask);
        if (lua_pcall(L, 2, 0, 0) != 0)
        {
            LOG_ERROR("error running function %s: %s", filedata->file_writ_proc, lua_tostring(L, -1));
        }
    }
}

static int time_proc(struct aeEventLoop *eventLoop, long long id, void *clientData) 
{
    TimeData *timedata = (TimeData *)clientData;
    lua_State *L = timedata->L;
    lua_pushluafunction(L, timedata->time_proc);
    lua_pushnumber(L, id);
    if (lua_pcall(L, 1, 1, 0) != 0)
    {
        LOG_ERROR("error running function %s: %s", timedata->time_proc, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return AE_NOMORE;
    }
    if (lua_isnumber(L, -1))
    {
        int ir = (int)lua_tointeger(L, -1);
        return ir;
    }
    return timedata->interval;
}

static void finalizer_proc(struct aeEventLoop *eventLoop, void *clientData) 
{
    TimeData *timedata = (TimeData *)clientData;
    if (timedata) 
    {
        free(timedata);
    }
}

/*  
static void before_sleep_proc(struct aeEventLoop *eventLoop) 
{
    int idx = (int)clientData;
    FileData *client_data = get_client_data(idx);
    lua_State *L = client_data->L;
    char *func_name = client_data->func_name;
    lua_pushluafunction(L, func_name);
    
    if (lua_pcall(L, 0, 0, 0) != 0){
        LOG_ERROR("error running function %s: %s", client_data->sleep_proc, lua_tostring(L, -1));
     }
}
*/

/*
 * 跑一帧
 * @arg1 event loop
 */
static int lrun_once(lua_State *L) 
{
    aeEventLoop *event_loop;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    aeOnce(event_loop);
    return 0;
}

static int lget_api_name(lua_State* L) 
{
    char *str = aeGetApiName();
    lua_pushstring(L, str);
    return 1;
}

/*
 * 主循环
 */
static int lmain(lua_State *L) 
{
    aeEventLoop *event_loop;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    aeMain(event_loop);
    return 0;
}

/*
 * @arg1 fd
 * @arg2 mask
 * @arg3 milliseconds
 */
static int lwait(lua_State *L) 
{
    int fd;
    int mask;
    int result;
    long long milliseconds;
    fd = (int)lua_tointeger(L, 1);
    mask = (int)lua_tointeger(L, 2);
    milliseconds = (long long)lua_tonumber(L, 3);
    result = aeWait(fd, mask, milliseconds);
    lua_pushinteger(L, result);
    return 1;
}

/*
 *  @arg1 event looop
 *  @arg2 flag2  AE_FILE_EVENTS AE_TIME_EVENTS AE_ALL_EVENTS AE_DONT_WAIT
 */
static int lprocess_events(lua_State *L) 
{
    aeEventLoop *event_loop;
    int flags;
    int error;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    flags = (int)lua_tointeger(L, 2);
    error = aeProcessEvents(event_loop, flags);
    lua_pushinteger(L, error);
    return 1;
}

/*
 *  @arg1 event loop
 *  @arg2 timeid
 */
static int ldelete_time_event(lua_State *L) 
{
    aeEventLoop *event_loop;
    long long id;
    int error;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    id = (long long)lua_tonumber(L, 2);
    error = aeDeleteTimeEvent(event_loop, id);
    lua_pushinteger(L, error);
    return 1;
}

/*
 * @arg1 event loop
 * @arg2 milliseconds
 * @arg3 time proc name 
 */

static int lcreate_time_event(lua_State *L) 
{
    aeEventLoop *event_loop;
    long long milliseconds;
    char *time_proc_name;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    milliseconds = (long long)lua_tonumber(L, 2);
    time_proc_name = (char *)lua_tostring(L, 3);
    TimeData *timedata = (TimeData *)malloc(sizeof(TimeData));
    if (!timedata) 
    {
        lua_pushinteger(L, AE_ERR);
        return 1;
    }
    if (time_proc_name) 
    {
        strcpy(timedata->time_proc, time_proc_name);
    }
    timedata->interval = milliseconds;
    timedata->L = L;
    int id = aeCreateTimeEvent(event_loop, milliseconds, time_proc, (void *)timedata, finalizer_proc);
    lua_pushnumber(L, id);
    return 1;
}

/*
 * @arg1 event loop
 * @arg2 socket
 * @return mask   AE_READABLE AE_WRITABLE AE_NONE
 */
static int lget_file_events(lua_State *L) 
{
    aeEventLoop *event_loop;
    int sockfd;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    sockfd = (int)lua_tointeger(L, 2);
    int mask = aeGetFileEvents(event_loop, sockfd);
    lua_pushinteger(L, mask);
    return 1;
}

/*
 *  @arg1 event loop
 *  @arg2 sockfd
 *  @arg3 mask  AE_READABLE AE_WRITABLE AE_NONE
 */
static int ldelete_file_event(lua_State *L) 
{
    aeEventLoop *event_loop;
    int sockfd;
    int mask;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    sockfd = (int)lua_tointeger(L, 2);
    mask = (int)lua_tointeger(L, 3);
    aeDeleteFileEvent(event_loop, sockfd, mask);
    return 0;
} 

/*
 * @arg1 event loop
 * @arg2 sockfd
 * @arg3 mask
 * @arg4 file proc name
 *
 */
static int lcreate_file_event(lua_State *L) 
{
    aeEventLoop *event_loop;
    int sockfd;
    int mask;
    int error;
    char *file_proc_name;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    sockfd = (int)lua_tointeger(L, 2);
    mask = (int)lua_tointeger(L, 3);
    file_proc_name = (char *)lua_tostring(L, 4);
    if (sockfd >= MAX_FILE_DATA) 
    {
        //可以考虑用MALLOC
        LOG_ERROR("333");
        lua_pushinteger(L, AE_ERR);
        return 1;
    }
    if (mask & AE_READABLE) 
    {
        strcpy(file_data_array[sockfd].file_read_proc, file_proc_name);
    }
    if (mask & AE_WRITABLE) 
    {
        strcpy(file_data_array[sockfd].file_writ_proc, file_proc_name);
    }
    file_data_array[sockfd].L = L;
    error = aeCreateFileEvent(event_loop, sockfd, mask, file_proc, &file_data_array[sockfd]);
    printf("file_proc_name(%s) sockfd(%d) error(%d) mask(%d)\n", file_proc_name, sockfd, error, mask);
    lua_pushinteger(L, error);
    return 1;
}

static int lmain_loop(lua_State *L) 
{
    lua_pushlightuserdata(L, main_loop);
    return 1;
}
/*
 * 
 * @arg1 max sock size
 * @return event loop
 */
static int lcreate(lua_State *L) 
{
    int setsize;
    setsize = (int)lua_tointeger(L, 1);
    aeEventLoop *event_loop = aeCreateEventLoop(setsize);
    if (main_loop == NULL) {
        main_loop = event_loop;
    }
    lua_pushlightuserdata(L, event_loop);
    return 1;
}

static int lfree(lua_State *L) 
{
    aeEventLoop *event_loop;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    aeDeleteEventLoop(event_loop);
    return 0;
}

static int lstop(lua_State *L) 
{
    aeEventLoop *event_loop;
    event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    aeStop(event_loop);
    return 0;
}

/*  
static int lset_before_sleep_proc(lua_State *L) 
{
    //aeEventLoop *event_loop;
    //event_loop = (aeEventLoop *)lua_touserdata(L, 1); 
    //aeSetBeforeSleepProc(event_loop, before_sleep_proc);  
    return 0;
}*/

static luaL_Reg lua_lib[] =
{
    {"get_api_name", lget_api_name},
    {"main", lmain},
    {"run_once", lrun_once},
    {"stop", lstop},
    {"wait", lwait},
    {"get_file_events", lget_file_events},
    {"lprocess_events", lprocess_events},
    {"create_file_event", lcreate_file_event},
    {"delete_file_event", ldelete_file_event},
    {"create_time_event", lcreate_time_event},
    {"delete_time_event", ldelete_time_event},
    {"create", lcreate},
    {"free", lfree},
    {"main_loop", lmain_loop},
    {NULL, NULL}
};

int luaopen_ae(lua_State *L)
{
	luaL_register(L, "Ae", lua_lib);

    lua_pushstring(L, "NONE");
    lua_pushinteger(L, AE_NONE);
    lua_settable(L, -3);

    lua_pushstring(L, "READABLE");
    lua_pushinteger(L, AE_READABLE);
    lua_settable(L, -3);

    lua_pushstring(L, "WRITABLE");
    lua_pushinteger(L, AE_WRITABLE);
    lua_settable(L, -3);

    lua_pushstring(L, "OK");
    lua_pushinteger(L, AE_OK);
    lua_settable(L, -3);

    lua_pushstring(L, "ERR");
    lua_pushinteger(L, AE_ERR);
    lua_settable(L, -3);

    lua_pushstring(L, "FILE_EVENTS");
    lua_pushinteger(L, AE_FILE_EVENTS);
    lua_settable(L, -3);

    lua_pushstring(L, "TIME_EVENTS");
    lua_pushinteger(L, AE_TIME_EVENTS);
    lua_settable(L, -3);

    lua_pushstring(L, "ALL_EVENTS");
    lua_pushinteger(L, AE_ALL_EVENTS);
    lua_settable(L, -3);

    lua_pushstring(L, "DONT_WAIT");
    lua_pushinteger(L, AE_DONT_WAIT);
    lua_settable(L, -3);

    lua_pushstring(L, "NOMORE");
    lua_pushinteger(L, AE_NOMORE);
    lua_settable(L, -3);
	return 1;
}

