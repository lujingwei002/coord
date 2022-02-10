

#include "port/pb_port.h"
#include "net/port.h"
#include "pblua/pblua.h"
#include "net/recvbuf.h"
#include "net/sendbuf.h"
#include "log/log.h"
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_MSG_NAME_LEN 128
#define MAX_HEADER_LEN 256

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
            if(lua_isnil(L, -1)){
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

static void setnonblock(int sockfd)
{
    int flags;
    flags = fcntl(sockfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flags);
}

static void setblock(int sockfd)
{
    int flags;
    flags = fcntl(sockfd, F_GETFL);
    flags &= ~O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flags);
}


static char msg_name[MAX_MSG_NAME_LEN];
static char recv_msg_name[MAX_MSG_NAME_LEN];

static int time_diff(struct timeval *t1, struct timeval *t2)
{
    int usec = (t2->tv_sec - t1->tv_sec) * 1000000 + t2->tv_usec - t1->tv_usec;
    return usec;
}

static void XOR(char *str, int str_len)
{
    for(int i = 0; i < str_len; i++)
    {
        str[i] = str[i] ^ 0xff;
    }
}


static int pb_port_cb_packet(int sockfd, const char* data, int datalen)
{
    Port::Port *port = Port::sock2port(sockfd);
    if(port == NULL)
    {
        LOG_ERROR("port is null");
        return 0;
    }
    Port::Sock *sock = Port::sockfromfd(sockfd);
    if(sock == NULL)
    {
        LOG_ERROR("sock is null");
        return 0;
    }
    char *body = (char*)data;
    int body_len = datalen;
    if (body_len < 4)
    {
        return 0;
    }

    int plen = *(int *)body + 4;
    body += sizeof(int);
    body_len -= sizeof(int);

    int msg_name_len = *(unsigned short *)body;
    body += sizeof(unsigned short);
    body_len -= sizeof(unsigned short);
    if(msg_name_len >= MAX_MSG_NAME_LEN - 1)
    {
        LOG_ERROR("reach max msg name len %d/%d", msg_name_len, MAX_MSG_NAME_LEN);
        return plen;
    }
    memcpy(recv_msg_name, body, msg_name_len);
    recv_msg_name[msg_name_len] = 0;
    XOR(recv_msg_name, msg_name_len);

    body += msg_name_len;
    body_len -= msg_name_len;

    int seq = *(int *)body;
    body += sizeof(int);
    body_len -= sizeof(int);

    lua_State *L = port->L;
    const char *func = port->lua_on_read;

    sock->recv_seq = 4 * sock->recv_seq + 9;
    if(sock->uid != 0 && sock->recv_seq != seq)
    {
        LOG_ERROR("seq error expected %d recv %d", sock->recv_seq, seq);
    }else if(func[0] != 0)
    {
        struct timeval t1;
        gettimeofday(&t1, NULL);

        google::protobuf::Message* message = pblua_load_msg(recv_msg_name);
        
        if(message == NULL){
            LOG_ERROR("can not load %d msg %s", msg_name_len, recv_msg_name);
            return plen;
        }
        google::protobuf::io::ArrayInputStream stream(body, body_len);
        
        if(message->ParseFromZeroCopyStream(&stream) == 0){
            delete message;
            LOG_ERROR("parse fail\n");
            return plen;
        }

        LOG_INFO("[%d]RECV %s FROM %s plen:%d", sock->uid, recv_msg_name, port->name, plen);

        if(message->ByteSize() < 4096)
        {
            LOG_DEBUG("%s", message->DebugString().data());
        }

        lua_pushluafunction(L, func);
        //sock 
        lua_pushnumber(L, sockfd);
        //cmd
        lua_pushstring(L, recv_msg_name);
        //msg
        LuaMessage *message_lua = (LuaMessage *)lua_newuserdata(L, sizeof(LuaMessage));
        if(message_lua == NULL)
        {
            lua_pop(L, lua_gettop(L));
            delete message;
            LOG_ERROR("newuserdata null %s", recv_msg_name);
            return plen;
        }
        message_lua->message = message;
        message_lua->root_message = message_lua;
        message_lua->dirty = 0;
        luaL_getmetatable(L, "LuaMessage");
        lua_setmetatable(L, -2);
        int args_num = 3;
        if (lua_pcall(L, args_num, 1, 0) != 0)
        {
            LOG_ERROR("error running function %s: %s", func, lua_tostring(L, -1));
        }
        struct timeval t2;
        gettimeofday(&t2, NULL);
        LOG_INFO("[%d]REC_ %s FROM %s plen:%d usec:%d", sock->uid, recv_msg_name, port->name, plen, time_diff(&t1, &t2));
        lua_pop(L, lua_gettop(L));

    }
    return plen;
}

static int lcreate(lua_State *L)
{
    if (lua_isuserdata(L, 1))
    {
        struct aeEventLoop *loop = (struct aeEventLoop *)lua_touserdata(L, 1);
        Port::Port *port = Port::create(loop);
        port->L = L;
        Port::set_read_func(port, pb_port_cb_packet);
        lua_pushlightuserdata(L, port);
        return 1;
    }
    return 0;
}

static int lpost(lua_State *L)
{
	if (lua_isnumber(L, 1) && lua_isuserdata(L, 2)){
        struct timeval t1;
        gettimeofday(&t1, NULL);
        int sockfd = (int)lua_tonumber(L, 1);

        LuaMessage *message_lua = (LuaMessage *)luaL_checkudata(L, 2, "LuaMessage");
        if(message_lua == NULL)
        {
            LOG_ERROR("checkuserdata is null");
            return 0;
        }
        google::protobuf::Message *message = message_lua->message;
        if(message == NULL)
        {
            LOG_ERROR("message is null");
            return 0;
        }
        const char *cmd = message->GetDescriptor()->full_name().data();
        if(cmd == NULL)
        {
            LOG_ERROR("cmd is null");
            return 0;
        }
        if(Port::sock_is_close(sockfd))
        {
            LOG_ERROR("sock %d is close", sockfd);
            return 0;
        }

        int msg_name_len = strlen(cmd);
        memcpy(msg_name, cmd, msg_name_len);
        msg_name[msg_name_len] = 0;
        XOR(msg_name, msg_name_len);

        Port::Sock* sock = Port::sockfromfd(sockfd);
        if (sock == NULL)
        {
            LOG_ERROR("sock is null");
            return 0;
        }
        Port::Port *port = sock->port;
        if (port == NULL)
        {
            LOG_ERROR("port is null");
            return 0;
        }
        LOG_INFO("[%d]SEND %s TO %s", sock->uid, cmd, port->name)

        int body_len = message->ByteSize();
        int plen = 4 + msg_name_len + 2  + sizeof(int) + body_len;
        char *buf = Sendbuf::alloc(sockfd, plen);
        if(buf == NULL)
        {
            LOG_ERROR("alloc fail cmd:%s\n", cmd);
            return 0;
        }

        *((int *)buf) = plen - 4;
        buf += 4;
        *((unsigned short *)buf) = msg_name_len;
        buf += 2;
        memcpy(buf, msg_name, msg_name_len);
        buf += msg_name_len;
        
        sock->send_seq = 4 * sock->send_seq + 9;
        *((int *)buf) = sock->send_seq;
        buf += sizeof(int);

        char * buf_end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buf);
        if(buf_end - buf != body_len)
        {
            LOG_ERROR("serialize fail %d/%d cmd:%s\n", buf_end - buf, body_len, cmd);
            return 0;
        }
        //加进socket的发送队列
        Sendbuf::flush(sockfd, buf, plen);

        Port::add_write_event(sockfd);

        struct timeval t2;
        gettimeofday(&t2, NULL);

        LOG_INFO("[%d]SEND %s TO %s plen:%d usec:%d", sock->uid, cmd, port->name, plen, time_diff(&t1, &t2))
        if(body_len < 4096)
        {
            LOG_DEBUG("%s", message->DebugString().data());
        }
        lua_pushboolean(L, true);
        return 1;
	}
    lua_pushboolean(L, false);
    return 1;
}


static char *s_send_buf;
static int s_send_size;

static int lsend(lua_State *L)
{
	if (lua_isnumber(L, 1) && lua_isuserdata(L, 2) && lua_isnumber(L, 3))
    {
        struct timeval t1;
        gettimeofday(&t1, NULL);
        int sockfd = (int)lua_tonumber(L, 1);

        LuaMessage *message_lua = (LuaMessage *)luaL_checkudata(L, 2, "LuaMessage");
        if(message_lua == NULL)
        {
            LOG_ERROR("checkuserdata is null");
            return 0;
        }
        google::protobuf::Message *message = message_lua->message;
        if(message == NULL)
        {
            LOG_ERROR("message is null");
            return 0;
        }
        const char *cmd = message->GetDescriptor()->full_name().data();
        if(cmd == NULL)
        {
            LOG_ERROR("cmd is null");
            return 0;
        }
        
        if(Port::sock_is_close(sockfd)){
            LOG_ERROR("sock %d is close", sockfd);
            return 0;
        }
        int timeout_sec = (int)lua_tonumber(L, 3);

        int msg_name_len = strlen(cmd);
        memcpy(msg_name, cmd, msg_name_len);
        msg_name[msg_name_len] = 0;
        XOR(msg_name, msg_name_len);

        Port::Sock *sock = Port::sockfromfd(sockfd);
        Port::Port *port = sock->port;
        LOG_INFO("[%d]SEND %s TO %s", sock->uid, cmd, port->name)
        setblock(sockfd);
        struct timeval tv;tv.tv_sec = timeout_sec; tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET,SO_RCVTIMEO, (char *)&tv,sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET,SO_SNDTIMEO, (char *)&tv,sizeof(tv));

        int body_len = message->ByteSize();
        int plen = 4 + msg_name_len + 2  + sizeof(int) + body_len;
        if(s_send_size < plen)
        {
            s_send_size = plen;
            if(s_send_buf == NULL)
            {
                s_send_buf = (char *)malloc(s_send_size);
                if(s_send_buf == NULL)
                {
                    LOG_ERROR("malloc fail");
                    return 0;
            }
            }else
            {
                s_send_buf = (char *)realloc(s_send_buf, s_send_size);
                if(s_send_buf == NULL)
                {
                    LOG_ERROR("malloc fail");
                    return 0;
                }
            }
        }
        char *buf = s_send_buf;
        *((int *)buf) = plen - 4;
        buf += 4;
        *((unsigned short *)buf) = msg_name_len;
        buf += 2;
        memcpy(buf, msg_name, msg_name_len);
        buf += msg_name_len;
        
        sock->send_seq = 4 * sock->send_seq + 9;
        *((int *)buf) = sock->send_seq;
        buf += sizeof(int);

        char * buf_end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buf);
        if(buf_end - buf != body_len){
            LOG_ERROR("serialize fail %d/%d cmd:%s\n", buf_end - buf, body_len, cmd);
            return 0;
        }
        int n = send(sockfd, s_send_buf, plen, 0);
        if(n < plen){
            LOG_ERROR("send fail n(%d) error(%s)", n, strerror(errno));
            return 0;
        }
        struct timeval t2;
        gettimeofday(&t2, NULL);

        if(body_len < 4096){
            LOG_DEBUG("%s", message->DebugString().data());
        }
        LOG_INFO("[%d]SEND %s TO %s plen:%d usec:%d", sock->uid, cmd, port->name, plen, time_diff(&t1, &t2))
        lua_pushboolean(L, true);
        setnonblock(sockfd);
        return 1;
	}
    lua_pushboolean(L, false);
    return 1;
}

static char *s_recv_buf;
static int s_recv_len;
static int s_recv_size;

static int lrecv(lua_State *L)
{
	if (lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        struct timeval t1;
        gettimeofday(&t1, NULL);
        int sockfd = (int)lua_tonumber(L, 1);
        int timeout_sec = (int)lua_tonumber(L, 2);
        Port::Sock *sock = Port::sockfromfd(sockfd);
        if(sock == NULL)
        {
            LOG_ERROR("sock is null");
            return 0;
        }
        Port::Port* port = sock->port;
        if(port == NULL)
        {
            LOG_ERROR("port is null");
            return 0;
        }
        setblock(sockfd);
        struct timeval tv;tv.tv_sec = timeout_sec; tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET,SO_RCVTIMEO, (char *)&tv,sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET,SO_SNDTIMEO, (char *)&tv,sizeof(tv));
        if(s_recv_buf == NULL)
        {
            s_recv_size = 1024 * 1024;
            s_recv_buf = (char *)malloc(s_recv_size);
            if(s_recv_buf == NULL)
            {
                LOG_ERROR("malloc fail");
                return 0;
            }
        }
        if(s_recv_len < 4)
        {
            int n = recv(sockfd, s_recv_buf + s_recv_len, 4 - s_recv_len, 0);
            if(n <= 0)
            {
                LOG_ERROR("recv fail");
                return 0;
            }
            s_recv_len += n;
        }
        char *body = s_recv_buf;
        int plen = *(int *)body + 4;
        
        if(s_recv_size < plen)
        {
            s_recv_size = plen;
            s_recv_buf = (char *)realloc(s_recv_buf, s_recv_size);
            if(s_recv_buf == NULL)
            {
                LOG_ERROR("relloc fail");
                s_recv_size = 0;
                s_recv_len = 0;
                return 0;
            }
        }
        if(s_recv_len < plen)
        {
            int n = recv(sockfd, s_recv_buf + s_recv_len, plen - s_recv_len, 0);
            if(n <= 0)
            {
                LOG_ERROR("recv fail");
                return 0;
            }
            s_recv_len += n;
        }
        int body_len = s_recv_len;
        body += sizeof(int);
        body_len -= sizeof(int);

        int msg_name_len = *(unsigned short *)body;
        body += sizeof(unsigned short);
        body_len -= sizeof(unsigned short);
        if(msg_name_len >= MAX_MSG_NAME_LEN - 1)
        {
            LOG_ERROR("reach max msg name len %d/%d", msg_name_len, MAX_MSG_NAME_LEN);
            return 0;
        }
        memcpy(recv_msg_name, body, msg_name_len);
        recv_msg_name[msg_name_len] = 0;
        XOR(recv_msg_name, msg_name_len);

        body += msg_name_len;
        body_len -= msg_name_len;

        int seq = *(int *)body;
        body += sizeof(int);
        body_len -= sizeof(int);


        sock->recv_seq = 4 * sock->recv_seq + 9;
        if(sock->uid != 0 && sock->recv_seq != seq)
        {
            LOG_ERROR("seq error expected %d recv %d", sock->recv_seq, seq);
            return 0;
        }

        google::protobuf::Message* message = pblua_load_msg(recv_msg_name);
        if(message == NULL)
        {
            LOG_ERROR("can not load %d msg %s", msg_name_len, recv_msg_name);
            return 0;
        }
        google::protobuf::io::ArrayInputStream stream(body, body_len);
        
        if(message->ParseFromZeroCopyStream(&stream) == 0)
        {
            delete message;
            LOG_ERROR("parse fail\n");
            return 0;
        }

        LOG_INFO("[%d]RECV %s FROM %s plen:%d", sock->uid, recv_msg_name, port->name, plen);

        if(message->ByteSize() < 4096)
        {
            LOG_DEBUG("%s", message->DebugString().data());
        }
        //msg
        LuaMessage *message_lua = (LuaMessage *)lua_newuserdata(L, sizeof(LuaMessage));
        if(message_lua == NULL)
        {
            delete message;
            LOG_ERROR("newuserdata null %s", recv_msg_name);
            return 0;
        }
        message_lua->message = message;
        message_lua->root_message = message_lua;
        message_lua->dirty = 0;
        luaL_getmetatable(L, "LuaMessage");
        lua_setmetatable(L, -2);

        struct timeval t2;
        gettimeofday(&t2, NULL);
        LOG_INFO("[%d]RECV %s FROM %s plen:%d usec:%d", sock->uid, recv_msg_name, port->name, plen, time_diff(&t1, &t2));
        setnonblock(sockfd);
        
        s_recv_len -= plen;
        if(s_recv_len > 0)
        {
            memcpy(s_recv_buf, s_recv_buf + plen, s_recv_len);
        }
        return 1;
    }

    return 0;
}


static luaL_Reg lua_lib[] = 
{
    {"create", lcreate},
    {"send", lsend},
    {"post", lpost},
    {"recv", lrecv},
    {NULL, NULL}
};

int luaopen_pb_port(lua_State *L)
{
    luaL_register(L, "PBPort", lua_lib);
    return 1;
}

