#include "os/los.h"
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static int lfork(lua_State *L)
{
	int ir = fork();
    lua_pushinteger(L, ir);
    return 1;
}

static int lgetpid(lua_State *L)
{
	int ir = getpid();
    lua_pushinteger(L, ir);
    return 1;
}

static int lsetsid(lua_State *L)
{
	int ir = setsid();
    lua_pushinteger(L, ir);
    return 1;
}

static int ltime(lua_State *L)
{
    int t = time(NULL);
    lua_pushinteger(L, t);
    return 1;
}

/*
 * @arg1 number 毫秒数
 * @return bool
 */

static int lsleepmsec(lua_State *L)
{
	if (lua_gettop(L) == 1 && lua_isnumber(L, 1))
    {
		int t = (int)lua_tonumber(L, 1);
        int sec = t / 1000;
        int nsec = (t % 1000) * 1000000;
        struct timespec slptm;
        slptm.tv_sec = sec;
        slptm.tv_nsec = nsec;
        nanosleep(&slptm, NULL);
        return 0;
	}
    return 0;
}

static int lsleep(lua_State *L)
{
    int seconds;
    int error;
    seconds = (int)lua_tointeger(L, 1);
    error = sleep(seconds);
    lua_pushinteger(L, error);
    return 1;
}

static int lwaitpid(lua_State *L)
{
    int status;
    pid_t pid;
    int options;
    pid = (int)lua_tointeger(L, 1);
    status = (int)lua_tointeger(L, 2);
    options = (int)lua_tointeger(L, 3);
    pid = waitpid(pid, &status, options);
    lua_pushinteger(L, pid);
    lua_pushinteger(L, status);
    return 2;
}


static int lstrerror(lua_State *L)
{
    lua_pushstring(L, strerror(errno));
    return 1;
}

static int lerrno(lua_State *L)
{
    lua_pushinteger(L, errno);
    return 1;
}

static int ltest(lua_State *L)
{
    return 0;
}

static int lclose(lua_State *L)
{
    int fd;
    int error;
    fd = (int)lua_tonumber(L, 1);
    error = close(fd);
    lua_pushinteger(L, error);
    return 1;
}

static int lcmd(lua_State *L)
{
    if(lua_isstring(L, 1))
    {
		const char *str = lua_tostring(L, 1);
        //拆参数
        char buf[256];
        strcpy(buf, str);
        int len = strlen(buf);
        char *pbuf = buf;
        char *cmd = pbuf;
        char *argv[128];
        argv[0] = cmd;
        int need_blank = 0;
        int i ;
        int idx = 0;
        for(i = 0; i < len; i++)
        {
            if(need_blank == 0 && pbuf[i] != ' '){
                argv[idx++] = pbuf + i;
                need_blank = 1;
            }else if(need_blank == 1 && pbuf[i] == ' ')
            {
                pbuf[i] = 0;
                need_blank = 0;
            }
        }
        argv[idx] = NULL;
        int pid = fork();
        if(pid == 0)
        {
	        execvp(cmd, argv);	
            exit(1);
        }else if(pid < 0)
        {
        }else if(pid > 0)
        {
            int status;
            waitpid(pid, &status, 0);
        }
        lua_pushboolean(L, 1);
        return 1;
	}
    return 0;
}

static luaL_Reg lua_lib[] =
{
    {"test", ltest},
    {"cmd", lcmd},
    {"errno", lerrno},
    {"strerror", lstrerror},
    {"fork", lfork},
    {"getpid", lgetpid},
    {"setsid", lsetsid},
    {"close", lclose},
    {"time", ltime},
    {"waitpid", lwaitpid},
    {"sleep", lsleep},
    {"sleepmsec", lsleepmsec},
    {NULL, NULL}
};

int luaopen_myos(lua_State *L)
{
	luaL_register(L, "os", lua_lib);
	return 1;
}

