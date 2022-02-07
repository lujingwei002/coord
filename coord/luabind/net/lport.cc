#include "net/lport.h"
#include "net/port.h"
#include "net/ae.h"
#include "log/log.h"
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>


static int lclose(lua_State *L)
{
    if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        int sockfd = (int)lua_tonumber(L, 2);
        const char *reason = "";
        if(lua_isstring(L, 3)) 
        {
            reason = (char *)lua_tostring(L, 3);
        } else {
            reason = strerror(errno);
        }
        Port::close(sockfd, reason);
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int llisten(lua_State *L)
{
    if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
        if(port == NULL)
        {
            LOG_ERROR("bad port\n");
            return 0;
        }
        unsigned short listenport = (unsigned short)lua_tonumber(L, 2);
        int sockfd = Port::listen(port, listenport);
        lua_pushinteger(L, sockfd);
        return 1;
    }
    LOG_ERROR("arg wrong\n");
    return 0;
}

//功能：同步连接
static int lsyncconnect(lua_State *L)
{   
    Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
    const char *ip = (const char *)lua_tostring(L, 2);
    unsigned short portnum = (unsigned short)lua_tonumber(L, 3);
    int sockfd = Port::syncconnect(port, ip, portnum);
    lua_pushinteger(L, sockfd);
    return 1;
}

//功能：释放port
static int lfree(lua_State *L)
{
    Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
    if(port == NULL)
    {
        return 0;
    }
    Port::free(port);
    return 0;
}

//功能：异步连接
static int lconnect(lua_State *L)
{   
    Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
    if (port == NULL) 
    {
        LOG_ERROR("connect arg wrong\n");
        return 0;
    }
    const char *ip = (const char *)lua_tostring(L, 2);
    unsigned short portnum = (unsigned short)lua_tonumber(L, 3);
    int sockfd = Port::connect(port, ip, portnum);
    lua_pushinteger(L, sockfd);
    return 1;
} 

static int lon_read(lua_State *L)
{
    if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isstring(L, 2))
    {
        Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
        const char *funcname 	= (const char *)lua_tostring(L, 2);
	    strcpy(port->lua_on_read, funcname);
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

//连接失败回调
static int lon_connect_err(lua_State *L)
{
    if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isstring(L, 2))
    {
        Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
        const char *funcname = (const char *)lua_tostring(L, 2);
	    strcpy(port->lua_on_connect_err, funcname);
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

//连接成功回调
static int lon_connect_suc(lua_State *L)
{
    if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isstring(L, 2))
    {
        Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
        const char *funcname = (const char *)lua_tostring(L, 2);
	    strcpy(port->lua_on_connect_suc, funcname);
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

//功能：新连接回调
static int lon_accept(lua_State *L)
{
    if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isstring(L, 2))
    {
        Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
        const char *funcname = (const char *)lua_tostring(L, 2);
	    strcpy(port->lua_on_accept, funcname);
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int lon_close(lua_State *L)
{
    if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isstring(L, 2))
    {
        Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
        const char *funcname 	= (const char *)lua_tostring(L, 2);
	    strcpy(port->lua_on_close, funcname);
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int lcreate(lua_State *L)
{
    if (lua_isuserdata(L, 1))
    {
        struct aeEventLoop *loop = (struct aeEventLoop *)lua_touserdata(L, 1);
        Port::Port *port = Port::create(loop);
        port->L = L;
        lua_pushlightuserdata(L, port);
        return 1;
    }
    return 0;
}

//功能：发送数据
static int lsend(lua_State *L)
{
    int error;
    int sockfd;
    char *buf;
    size_t len;
    sockfd = (int)lua_tointeger(L, 1);
    buf = (char *)lua_touserdata(L, 2);
    len = (int)lua_tointeger(L, 3);
    error = ::send(sockfd, buf, len, 0);
    lua_pushinteger(L, error);
    return 1;
}

//功能：接收数据
static int lrecv(lua_State *L)
{
    int result;
    int sockfd;
    char *buf;
    int buflen;
    sockfd = (int)lua_tointeger(L, 1);
    buf = (char *)lua_touserdata(L, 2);
    buflen = (int)lua_tointeger(L, 3);
    result = ::recv(sockfd, buf, buflen, 0);
    if (result == 0) 
    {
        lua_pushinteger(L, -1);
        lua_pushstring(L, strerror(errno));
        return 2;
    }
    if (result == -1 && errno == EAGAIN) 
    {
        lua_pushinteger(L, 0);
        return 1;
    }
    if (result == -1) 
    {
        lua_pushinteger(L, -1);
        lua_pushstring(L, strerror(errno));
        return 2;
    }
    lua_pushinteger(L, result);
    return 1;
}

static int lgetpeerport(lua_State *L)
{
    if (lua_isnumber(L, 1))
    {
        int sockfd = (int)lua_tonumber(L, 1);
        lua_pushinteger(L, Port::getpeerport(sockfd));
        return 1;
    }
    return 0;
}

static int lgetpeerip(lua_State *L)
{
    if (lua_isnumber(L, 1))
    {
        int sockfd = (int)lua_tonumber(L, 1);
        lua_pushstring(L, Port::getpeerip(sockfd));
        return 1;
    }
    return 0;
}

static int lshutdown(lua_State *L)
{
    if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        //Port *port 	= (Port *)lua_touserdata(L, 1);
        int sockfd = (int)lua_tonumber(L, 2);
        if(Port::shutdown(sockfd)) {
            return 0;
        }
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int lrename(lua_State *L)
{
    if (lua_gettop(L) == 2 && lua_isuserdata(L, 1) && lua_isstring(L, 2))
    {
        Port::Port *port = (Port::Port *)lua_touserdata(L, 1);
        const char *name = (const char *)lua_tostring(L, 2);
        if(Port::rename(port, name)) {
            return 0;
        }
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int lremove_write_event(lua_State *L){
    int sockfd = lua_tointeger(L, 1);
    if(Port::remove_write_event(sockfd)) {
        return 0;
    }
    lua_pushboolean(L, 1);
    return 1;
}

static int ladd_write_event(lua_State *L){
    int sockfd = lua_tointeger(L, 1);
    if(Port::add_write_event(sockfd)) {
        return 0;
    }
    lua_pushboolean(L, 1);
    return 1;
}

static int lsetuid(lua_State *L)
{
    if(lua_isuserdata(L, 1) && lua_isnumber(L, 2))
    {
        //Port *port = (Port *)lua_touserdata(L, 1);
        int sockfd = (int)lua_tonumber(L, 2);
        int uid	= (int)lua_tonumber(L, 3);
        if(Port::setuid(sockfd, uid)) {
            return 0;
        }
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int lgetuserdata(lua_State *L)
{
    if(lua_isnumber(L, 1))
    {
        int sockfd = (int)lua_tonumber(L, 1);
        lua_pushinteger(L, Port::getuserdata(sockfd));
        return 1;
    }
    return 0;
}

static int lsetuserdata(lua_State *L)
{
    if(lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        int sockfd = (int)lua_tonumber(L, 1);
        int userdata = (int)lua_tonumber(L, 2);
        if(Port::setuserdata(sockfd, userdata)) {
            return 0;
        }
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static int lgetsrvid(lua_State *L)
{
    if(lua_isnumber(L, 1))
    {
        int sockfd = (int)lua_tonumber(L, 1);
        lua_pushinteger(L, Port::getsrvid(sockfd));
        return 1;
    }
    return 0;
}

static int lsetsrvid(lua_State *L)
{
    if(lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        int sockfd = (int)lua_tonumber(L, 1);
        int srvid = (int)lua_tonumber(L, 2);
        if(Port::setsrvid(sockfd, srvid)) {
            return 0;
        }
        lua_pushboolean(L, 1);
        return 1;
    }
    return 0;
}

static luaL_Reg lua_lib[] = 
{
    {"create", lcreate},
    {"free", lfree},
    {"listen", llisten},
    {"connect", lconnect},
    {"syncconnect", lsyncconnect},
    {"on_read", lon_read},
    {"on_accept", lon_accept},
    {"on_connect_suc", lon_connect_suc},
    {"on_connect_err", lon_connect_err},
    {"on_close", lon_close},
    {"rename", lrename},
    {"close", lclose},
    {"shutdown", lshutdown},
    {"getpeerport", lgetpeerport},
    {"getpeerip", lgetpeerip},
    {"setuid", lsetuid},
    {"setuserdata", lsetuserdata},
    {"getuserdata", lgetuserdata},
    {"setsrvid", lsetsrvid},
    {"getsrvid", lgetsrvid},
    {"remove_write_event", lremove_write_event},
    {"add_write_event", ladd_write_event},
    {"recv", lrecv},
    {"send", lsend},
    {NULL, NULL},
};

int luaopen_port(lua_State *L){
	luaL_register(L, "Port", (luaL_Reg*)lua_lib);
    return 1;
}
