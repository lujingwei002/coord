#include "lsocket.h"
#include "log/log.h"
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>


static int lgetpeerip(lua_State *L){
    int sockfd;
    sockfd = (int)lua_tonumber(L, 1);
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    getpeername(sockfd, (struct sockaddr *)&addr, &addr_len);
    lua_pushstring(L, inet_ntoa(addr.sin_addr));
    return 1;
}

static int lsetnonblock(lua_State *L){
    int sockfd;
    int error;
    sockfd = (int)lua_tonumber(L, 1);
    error = fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);
    lua_pushinteger(L, error);
    return 1;
}

static int lclose(lua_State *L){
    int sockfd;
    int error;
    sockfd = (int)lua_tonumber(L, 1);
    error = close(sockfd);
    lua_pushinteger(L, error);
    return 1;
}

static int ltest(lua_State *L){
    printf("test\n");
    return 0;
}

static int lsocket(lua_State *L){
    int sockfd;
    int domain;//AF_INET
    int type;//SOCK_STREAM
    int protocol;//0
    domain = (int)lua_tointeger(L, 1);
    type = (int)lua_tointeger(L, 2);
    protocol = (int)lua_tointeger(L, 3);
    sockfd = socket(domain, type, protocol);
    lua_pushinteger(L, sockfd);
    return 1;
}

static int laccept(lua_State *L){
    int listenfd;
    int sockfd;
    listenfd = (int)lua_tointeger(L, 1);
	struct sockaddr_in addr;	
	socklen_t addrlen = sizeof(addr);	
    sockfd = accept(listenfd, (struct sockaddr*)&addr, &addrlen);
    lua_pushinteger(L, sockfd);
    return 1;
}

static int lconnect(lua_State *L){
    if (lua_gettop(L) != 3 || !lua_isnumber(L, 1) || !lua_isstring(L, 2) || !lua_isnumber(L, 3)) {
        printf("arg invalid\n");
        return 0;
    }
    int sockfd;
    char *host;
    unsigned short port;
    int error;
    sockfd = (int)lua_tointeger(L, 1);
    host = (char *)lua_tostring(L, 2);
    port = (unsigned short)lua_tointeger(L, 3);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;	
    if(inet_addr(host) != (in_addr_t)-1){
        addr.sin_addr.s_addr = inet_addr(host);   
    }else{
        struct hostent *hostent;
        hostent = gethostbyname(host);
        if(hostent->h_addr_list[0] == NULL){
            LOG_ERROR("connect fail %s", host);
            return 0;
        }
        memcpy(&addr.sin_addr, (struct in_addr *)hostent->h_addr_list[0], sizeof(struct in_addr));
    } 
    addr.sin_port = htons(port);        
    error = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if(error < 0){
        LOG_ERROR("connect fail errno:%d:%s\n", errno, strerror(errno));
        return 0;
    }
    lua_pushboolean(L, true);
    return 1;
}

static int llisten(lua_State *L){
    int sockfd;
    char *host;
    unsigned short port;
    int error;
    sockfd = (int)lua_tointeger(L, 1);
    host = (char *)lua_tostring(L, 2);
    port = (unsigned short)lua_tointeger(L, 3);
	struct sockaddr_in addr;
	bzero((void*)&addr, sizeof(addr));	
	addr.sin_family = AF_INET;	
	addr.sin_addr.s_addr = INADDR_ANY;	
	addr.sin_port = htons(port);	
    int reuse = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	error = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	if(error < 0){		
        LOG_ERROR("fail to bind %d %d %s", port, errno, strerror(errno));
        lua_pushinteger(L, error);
		return 1;	
    }
	error = listen(sockfd, 5);	
	if(error < 0){		
        LOG_ERROR("fail to listen %d %s", errno, strerror(errno));
        lua_pushinteger(L, error);
		return 1;	
	}
    lua_pushinteger(L, error);
    return 1;
}

static int lrecv(lua_State *L)
{
    int error;
    int sockfd;
    static char buf[10240];
    int buflen;
    sockfd = (int)lua_tointeger(L, 1);
    buflen = (int)lua_tointeger(L, 2);
    error = recv(sockfd, buf, buflen, 0);
    if (error <= 0)
    {
        lua_pushinteger(L, error);
        return 1;
    }
    lua_pushinteger(L, error);
    lua_pushlstring(L, buf, error);
    return 2;
}

static int lsend(lua_State *L){
    int error;
    int sockfd;
    char *buf;
    size_t len;
    sockfd = (int)lua_tointeger(L, 1);
    buf = (char *)lua_tolstring(L, 2, &len);
    error = send(sockfd, buf, len, 0);
    lua_pushinteger(L, error);
    return 1;
}

static luaL_Reg lua_lib[] =
{
    {"test", ltest},
    {"socket", lsocket},
    {"listen", llisten},
    {"connect", lconnect},
    {"accept", laccept},
    {"recv", lrecv},
    {"send", lsend},
    {"close", lclose},
    {"setnonblock", lsetnonblock},
    {"getpeerip", lgetpeerip},
    {NULL, NULL}
};

int luaopen_socket(lua_State *L)
{
	luaL_register(L, "Socket", lua_lib);

    lua_pushstring(L, "AF_INET");
    lua_pushinteger(L, AF_INET);
    lua_settable(L, -3);

    lua_pushstring(L, "SOCK_STREAM");
    lua_pushinteger(L, SOCK_STREAM);
    lua_settable(L, -3);

    lua_pushstring(L, "SOL_SOCKET");
    lua_pushinteger(L, SOL_SOCKET);
    lua_settable(L, -3);

    lua_pushstring(L, "SO_ERROR");
    lua_pushinteger(L, SO_ERROR);
    lua_settable(L, -3);

    lua_pushstring(L, "EAGAIN");
    lua_pushinteger(L, EAGAIN);
    lua_settable(L, -3);

	return 1;
}

