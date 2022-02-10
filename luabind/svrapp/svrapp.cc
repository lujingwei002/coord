#include "svrapp/svrapp.h"
#include "file/file.h"
#include "log/log.h"
#include <signal.h>

namespace Svrapp
{
    lua_State* L;

    static void _atexit() 
    {
        LOG_INFO("_atexit");
        if (L != NULL) 
        {
            lua_getglobal(L, "_atexit");
            if(!lua_isnil(L, -1))
            {
                lua_pcall(L, 0, 0, 0);
            }
        }    
    }

    static void sig_int(int b)
    {
        LOG_INFO("sig_int");
        if (L != NULL) 
        {
            lua_getglobal(L, "_atint");
            if(!lua_isnil(L, -1))
            {
                lua_pcall(L, 0, 0, 0);
                return;
            }
        } 
        exit(0);
    }


    static void lua_printstack(lua_State *L) 
    {
        lua_getglobal(L, "debug");  
        lua_getfield(L, -1, "traceback");  
        lua_pcall(L, 0, 1, 0);   
        const char* sz = lua_tostring(L, -1);  
        printf("%s\n", sz);
    }

    void main(int argc, char** argv)
    {
        //切换工作路径
        //const char* self_dir = File::dirname(argv[0]);
        //File::chdir(self_dir);
        //Log::info("running dir is %s", File::getcwd());
        //建虚拟机
        L = lua_open();
        luaL_openlibs(L);

        //参数压栈
        lua_newtable(L);
        lua_setglobal(L, "arg");
        lua_getglobal(L, "arg");
        for (int i = 1; i <= argc; i++)
        {
            lua_pushnumber(L, i);
            lua_pushstring(L, argv[i - 1]);
            lua_settable(L, -3);
        }
        lua_pop(L, 1);
    }

    int lfork_daemon(lua_State* L)
    {
        bool is_daemon = (bool)lua_toboolean(L, 1);

        if (is_daemon) 
        {
            int pid;
            pid = fork();
            if(pid){
                exit(0);
            }else if(pid < 0){
                LOG_ERROR("fork error");
                exit(1);
            }
            setsid();
            pid = fork();
            if(pid){
                exit(0);
            }else if(pid < 0){
                LOG_ERROR("fork error");
                exit(1);
            }
        }
        //ps, 关了就不要写
        /*for(i = 0; i <=2; i++){
          close(i);
          }*/
        signal(SIGHUP, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);
        signal(SIGTERM, SIG_IGN);
        signal(SIGHUP, SIG_IGN);
        //往关闭的socket写数据
        signal(SIGPIPE, SIG_IGN);
        //google protobuf出错时候会出这个
        signal(SIGABRT, SIG_IGN);
        atexit(_atexit);
        //ctrl-c信号
        signal(SIGINT, sig_int);

        return 0;
    }

    int lua_dofile(const char* filepath)
    {
        if(luaL_dofile(L, filepath))
        {
            if (lua_isstring(L, -1))
            {
                LOG_ERROR("dofile error %s\n", lua_tostring(L, -1));
                lua_printstack(L);
            }
        }
        return 0;
    }

    void exit()
    {

    }
}

static luaL_Reg lua_lib[] = 
{
    {"fork_daemon", Svrapp::lfork_daemon},
    {NULL, NULL}
};

int luaopen_svrapp(lua_State *L)
{
    luaL_register(L, "Svrapp", lua_lib);
    return 1;
}

