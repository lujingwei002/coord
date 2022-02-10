
#include "pblua/pblua.h"
#include "port/rmi_port.h"
#include "log/log.h"
#include "net/port.h"
#include "net/recvbuf.h"
#include "net/sendbuf.h"
#include "json/json.h"

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

/*
plen msg_name arg_num
{unsigned char, str}
1, string
2, double
3, table -json
4, pb

 */

#define PROTO_RMI 1
#define PROTO_MSG 2

#define ARG_TYPE_END    0
#define ARG_TYPE_STRING 1 
#define ARG_TYPE_NUMBER 2
#define ARG_TYPE_TABLE 3
#define ARG_TYPE_PB 4
#define ARG_TYPE_NIL 5

#define MAX_MOD_NAME 64
#define MAX_ACTION_NAME  128


#define READ_UINT32(buf, buf_len) *(unsigned int *)buf;\
                                 if(buf_len < sizeof(unsigned int)){\
                                    LOG_ERROR("parse fail");\
                                    return 0;\
                                 }\
                                 buf += sizeof(unsigned int);\
                                 buf_len -= sizeof(unsigned int);

#define READ_UINT16(buf, buf_len) *(unsigned short *)buf;\
                                 if(buf_len < sizeof(unsigned short)){\
                                    LOG_ERROR("parse fail");\
                                    return 0;\
                                 }\
                                 buf += sizeof(unsigned short);\
                                 buf_len -= sizeof(unsigned short);

#define READ_UINT8(buf, buf_len) *(unsigned char *)buf;\
                                 if(buf_len < sizeof(unsigned char)){\
                                    LOG_ERROR("parse fail");\
                                    return 0;\
                                 }\
                                 buf += sizeof(unsigned char);\
                                 buf_len -= sizeof(unsigned char);


#define READ_STR(buf, buf_len, src, str_len)  if(buf_len < str_len){\
                                                 LOG_ERROR("parse fail");\
                                                 return 0;\
                                              }\
                                              memcpy(src, buf, str_len);\
                                              src[str_len] = 0;\
                                              buf += str_len;\
                                              buf_len -= str_len;

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


static int time_diff(struct timeval *t1, struct timeval *t2){
    int usec = (t2->tv_sec - t1->tv_sec) * 1000000 + t2->tv_usec - t1->tv_usec;
    return usec;
}


#define MAX_MSG_NAME 1024
static char msg_name[MAX_MSG_NAME];

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

static int cap(char *src, int src_len, char *dst)
{
//    dst[0] = src[0] - 32;
    for(int i = 0; i <= src_len; i++){
        dst[i] = src[i];
    }
    return 1;
}

static int rmi_port_proto_msg(int sockfd, const char* data, int datalen)
{
    struct timeval t1;
    gettimeofday(&t1, NULL);

    Port::Sock* sock = Port::sockfromfd(sockfd);
    if(sock == NULL)
    {
        LOG_ERROR("sock is null");
        return 0;
    }
    Port::Port *port = sock->port;
    if(port == NULL)
    {
        LOG_ERROR("port is null");
        return 0;
    }
    char *body = (char*)data;
    int body_len = datalen;

    int plen = *(int *)body + 4;
    body += sizeof(int);
    body_len -= sizeof(int);
    
    //int proto = *(unsigned char *)body;
    body += sizeof(unsigned char);
    body_len -= sizeof(unsigned char);

    int uid = *(int *)body;
    body += sizeof(int);
    body_len -= sizeof(int);

    int msg_name_len = *(unsigned short *)body;
    body += sizeof(unsigned short);
    body_len -= sizeof(unsigned short);
    if(msg_name_len >= MAX_MSG_NAME - 1)
    {
        LOG_ERROR("reach max msg name len %d/%d", msg_name_len, MAX_MSG_NAME);
        return plen;
    }
    memcpy(msg_name, body, msg_name_len);
    msg_name[msg_name_len] = 0;

    body += msg_name_len;
    body_len -= msg_name_len;

    lua_State *L = port->L;
    const char *func = port->lua_on_read;

    if(func[0] == 0)
    {
        LOG_ERROR("no callback %s", port->name);
        return plen;
    }

    google::protobuf::Message* message = pblua_load_msg(msg_name);
    if(message == NULL)
    {
        LOG_ERROR("can not load %d msg %s", msg_name_len, msg_name);
        return plen;
    }
    google::protobuf::io::ArrayInputStream stream(body, body_len);
    if(message->ParseFromZeroCopyStream(&stream) == 0)
    {
        delete message;
        LOG_ERROR("parse fail\n");
        return plen;
    }

    LOG_INFO("[%d]RECV %s FROM %s plen:%d", uid, msg_name, port->name, plen);

    if(message->ByteSize() < 4096)
    {
        LOG_DEBUG("%s", message->DebugString().data());
    }

    lua_pushluafunction(L, func);
    //sock 
    lua_pushnumber(L, sockfd);
    //uid
    lua_pushnumber(L, uid);
    //cmd
    lua_pushstring(L, msg_name);
    //msg
    LuaMessage *message_lua = (LuaMessage *)lua_newuserdata(L, sizeof(LuaMessage));
    if(message_lua == NULL)
    {
        lua_pop(L, lua_gettop(L));
        delete message;
        LOG_ERROR("newuserdata null %s", msg_name);
        return plen;
    }
    message_lua->message = message;
    message_lua->root_message = message_lua;
    message_lua->dirty = 0;
    luaL_getmetatable(L, "LuaMessage");
    lua_setmetatable(L, -2);
    int args_num = 4;
    if (lua_pcall(L, args_num, 0, 0) != 0)
    {
        LOG_ERROR("error running function %s: %s", func, lua_tostring(L, -1));
    }
    struct timeval t2;
    gettimeofday(&t2, NULL);
    LOG_INFO("[%d]RECV %s FROM %s usec:%d", uid, msg_name, port->name, time_diff(&t1, &t2));
    lua_pop(L, lua_gettop(L));
    return plen;
}

static int rmi_port_proto_rmi(int sockfd, const char* data, int datalen)
{
    struct timeval t1;
    gettimeofday(&t1, NULL);

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
    char *buf = (char*)data;
    int plen = *(int *)data + sizeof(unsigned int);

    unsigned int buf_len = (unsigned int)datalen;
    
    lua_State *L = port->L;

    unsigned int body_len = READ_UINT32(buf, buf_len);
    //proto
    int proto = READ_UINT8(buf, buf_len);
    LOG_INFO("proto %d", proto);
    
    char msg_name[MAX_MSG_NAME];
    char mod_name[MAX_MOD_NAME];
    char action_name[MAX_ACTION_NAME];
    char cap_mod_name[MAX_MOD_NAME];
    //mod_name
    unsigned short msg_name_len = READ_UINT16(buf, buf_len);
    if(msg_name_len >= MAX_MSG_NAME)
    {
        LOG_ERROR("limit reach");
        return plen;
    }
    READ_STR(buf, buf_len, msg_name, msg_name_len);
    int i = 0;
    for(i = 0; i < msg_name_len; i++)
    {
        if(msg_name[i] == '.')
        {
            mod_name[i] = 0;
            break;
        }else
        {
            mod_name[i] = msg_name[i];
        }
    }
    int j = 0;
    for(i = i + 1, j = 0;i < msg_name_len; i++, j++)
    {
        action_name[j] = msg_name[i];
    }
    action_name[j] = 0;
    int mod_name_len = strlen(mod_name);
    int action_name_len = strlen(action_name);

    cap(mod_name, mod_name_len, cap_mod_name); 

    LOG_INFO("[%s]CALL %s FROM %s", mod_name, msg_name, port->name);

    lua_getglobal(L, cap_mod_name);
    if(lua_isnil(L, -1))
    {
        LOG_ERROR("mod %s not found", cap_mod_name);
        return plen;
    }

    lua_pushlstring(L, action_name, action_name_len);
    lua_gettable(L, -2);
    if(lua_isnil(L, -1))
    {
        LOG_ERROR("%s not found", action_name);
        return plen;
    }
    lua_pushinteger(L, sockfd);
    int arg_num = 1;
    int max_arg_num = 20;
    
    while(true)
    {
        if(max_arg_num -- <= 0)
        {
            LOG_ERROR("arg num reach limit");
            break;
        }
        unsigned char t = READ_UINT8(buf, buf_len);
        if(t == ARG_TYPE_STRING)
        {
            arg_num++;
            unsigned short str_len = READ_UINT16(buf, buf_len);
            lua_pushlstring(L, buf, str_len);

            char tmp_c = buf[str_len];
            buf[str_len] = 0;
            LOG_DEBUG("%d %s", str_len, buf);
            //for (int i = 0; i < str_len; i++)
            //{
                //printf("dd %d\n", buf[i]);
            //}
            buf[str_len] = tmp_c;

            buf += str_len;
            buf_len -= str_len;
        }else if(t == ARG_TYPE_NUMBER)
        {
            arg_num++;
            int number = *(int *)buf;
            buf += sizeof(int);
            buf_len -= sizeof(int);
            lua_pushnumber(L, number);
            LOG_DEBUG("%ld", (size_t)number);
        }else if(t == ARG_TYPE_TABLE)
        {
            arg_num++;
            unsigned int str_len = READ_UINT32(buf, buf_len);
            Json::decode(L, buf);

            char tmp_c = buf[str_len];
            buf[str_len] = 0;
            LOG_DEBUG("%s", buf);
            buf[str_len] = tmp_c;

            buf += str_len;
            buf_len -= str_len;
            //LOG_DEBUG("lua table %d, %d %d", str_len, buf_len, sizeof(int));
        }else if(t == ARG_TYPE_NIL)
        {
            arg_num++;
            lua_pushnil(L);
            LOG_DEBUG("nil");
        }else if(t == ARG_TYPE_PB)
        {
            arg_num++;
            unsigned int str_len = READ_UINT32(buf, buf_len);
            unsigned short msg_name_len = READ_UINT16(buf, buf_len);
            if(msg_name_len >= MAX_MSG_NAME)
            {
                LOG_ERROR("msg name length limit reach");
                return plen;
            }
            READ_STR(buf, buf_len, msg_name, msg_name_len);
            google::protobuf::Message* message = pblua_load_msg(msg_name);
            if(message == NULL)
            {
                LOG_ERROR("can not load msg %s", msg_name);
                return plen;
            }
            int msg_len = str_len - msg_name_len - sizeof(unsigned short);
            //printf("%s %d\n", msg_name, msg_len);
            google::protobuf::io::ArrayInputStream stream(buf, msg_len);
            if(message->ParseFromZeroCopyStream(&stream) == 0)
            {
                LOG_ERROR("parse fail\n");
                return plen;
            }    
            buf += msg_len;
            LuaMessage *message_lua = (LuaMessage *)lua_newuserdata(L, sizeof(LuaMessage));
            if(message_lua == NULL)
            {
                LOG_ERROR("newuserdata null %s", msg_name);
                return plen;
            }
            message_lua->message = message;
            message_lua->root_message = message_lua;
            message_lua->dirty = 0;
            luaL_getmetatable(L, "LuaMessage");
            lua_setmetatable(L, -2);
            if(message->ByteSize() < 1024)
            {
                LOG_DEBUG("%s", message->DebugString().data());
            }
        
        }else if(t == ARG_TYPE_END)
        {
            break;
        }else
        {
            LOG_ERROR("unsport : %d", t);
            return plen;
        }
    }
    if(lua_pcall(L, arg_num, 0, 0))
    {
        LOG_ERROR("%s", lua_tostring(L, -1));
    }
    struct timeval t2;
    gettimeofday(&t2, NULL);
    LOG_INFO("[%s]CAL_ %s FROM %s usec:%d body_len:%d", mod_name, msg_name, port->name, time_diff(&t1, &t2), body_len);
    lua_pop(L, lua_gettop(L));
    return plen;
}


static int rmi_port_cb_packet(int sockfd, const char*data, int datalen)
{
    char *buf = (char*)data;
    unsigned int buf_len = (unsigned int)datalen;
    //body_len
    if(datalen < 4)
    {
        return 0;
    }
    int plen = READ_UINT32(buf, buf_len);
    if (datalen < plen)
    {
        return 0;
    }
    int proto = READ_UINT8(buf, buf_len);
    if(proto == PROTO_RMI)
    {
        return rmi_port_proto_rmi(sockfd, data, datalen);
    }else if(proto == PROTO_MSG)
    {
        return rmi_port_proto_msg(sockfd, data, datalen);
    }
    else
    {
        LOG_ERROR("error proto(%d)", proto);
    }
    return plen;
}


static int rmi_strlen(lua_State *L, int arg_index, const char *msg_name)
{
    int body_len = 0;
    body_len += sizeof(char);//proto
    int msg_name_len = strlen(msg_name);
    body_len += sizeof(unsigned short) + msg_name_len;
    int top = lua_gettop(L);
    //LOG_DEBUG("body_len:%d", body_len);
    for(int i = arg_index; i <= top; i++)
    {
        if(lua_type(L, i) == LUA_TNUMBER)
        {
            body_len += sizeof(unsigned char);
            body_len += sizeof(int); 
            //LOG_DEBUG("body_len:%d %d", body_len, sizeof(int));
        }
        else if(lua_type(L, i) == LUA_TSTRING)
        {
            size_t str_len = 0;
            lua_tolstring(L, i, &str_len);
            body_len += sizeof(unsigned char);
            body_len += sizeof(unsigned short);
            body_len += str_len;
            //LOG_DEBUG("body_len:%d", body_len);
        }else if(lua_isuserdata(L, i))
        {
            LuaMessage *message_lua = (LuaMessage *)luaL_checkudata(L, i, "LuaMessage");
            if(message_lua == NULL)
            {
                LOG_ERROR("checkuserdata is null");
                return 0;
            }
            google::protobuf::Message *message = message_lua->message;
            
            if(message == NULL){
                LOG_ERROR("message is null");
                return 0;
            }
            const char *msg_name = message->GetDescriptor()->full_name().data();
            
            if(msg_name == NULL){
                LOG_ERROR("cmd is null");
                return 0;
            }
            body_len += sizeof(unsigned char); //type
            body_len += sizeof(unsigned int);  //len
            body_len += sizeof(unsigned short);//msg name len
            body_len += strlen(msg_name);      //msg name
            body_len += message->ByteSize();   //msg
        
        }else if(lua_istable(L, i)){
            lua_pushvalue(L, i);
            char *str = Json::encode(L);
            lua_pop(L, 1);
            
            if(str == NULL){
                LOG_ERROR("fail");
                return 0;
            }
            int str_len = strlen(str);
            body_len += sizeof(unsigned char);
            body_len += sizeof(unsigned int);
            body_len += str_len;
            //printf("table len:%d\n", str_len);
            //释放
            free(str);
            //LOG_DEBUG("body_len:%d", body_len);
        }else if(lua_isnil(L, i))
        {
            body_len += sizeof(unsigned char);
        }
        else
        {
            LOG_ERROR("unsupport");
            return 0;
        }
    }
    body_len += sizeof(unsigned char);//end
    //LOG_DEBUG("body_len:%d", body_len);
    return body_len;
}


static int rmi_encode(lua_State *L, int arg_index, const char *msg_name, char *buf, int buf_len)
{

    int msg_name_len = strlen(msg_name);
    
    *(unsigned int *)buf = buf_len - sizeof(unsigned int);
    buf += sizeof(unsigned int);

    *(unsigned char *)buf = PROTO_RMI;
    buf += sizeof(unsigned char);

    *(unsigned short *)buf = msg_name_len;
    buf += sizeof(unsigned short);
    memcpy(buf, msg_name, msg_name_len);
    buf += msg_name_len;

    int top = lua_gettop(L);
    for(int i = arg_index; i <= top; i++)
    {
        if(lua_type(L, i) == LUA_TNUMBER)
        {
            *(unsigned char *)buf = ARG_TYPE_NUMBER;
            buf += sizeof(unsigned char);
            int number = (int)lua_tonumber(L, i);
            *(int*)buf = number;
            buf += sizeof(int); 

            LOG_DEBUG("arg%d:%ld", i - arg_index + 1, (size_t)number);
        }else if(lua_type(L, i) == LUA_TSTRING)
        {
            *(unsigned char *)buf = ARG_TYPE_STRING;
            buf += sizeof(unsigned char);
            size_t str_len = 0;
            const char * str = (const char *)lua_tolstring(L, i, &str_len);
            if(str == NULL)
            {
                LOG_ERROR("fail");
                return 0;
            }else
            {
                LOG_DEBUG("arg%d: %s(%d)", i - arg_index + 1, str, str_len);
                *(unsigned short *)buf = str_len;
                buf += sizeof(unsigned short);
                memcpy(buf, str, str_len);

                buf += str_len;
            }
        }else if(lua_isuserdata(L, i))
        {
            LuaMessage *message_lua = (LuaMessage *)luaL_checkudata(L, i, "LuaMessage");
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
            const char *msg_name = message->GetDescriptor()->full_name().data();
            if(msg_name == NULL)
            {
                LOG_ERROR("cmd is null");
                return 0;
            }
            int msg_name_len = strlen(msg_name);
            int msg_len = message->ByteSize();
            *(unsigned char *)buf = ARG_TYPE_PB;
            buf += sizeof(unsigned char);

            *(unsigned int *)buf = (sizeof(unsigned short) + msg_name_len + msg_len);
            buf += sizeof(unsigned int);

            *(unsigned short *)buf = msg_name_len;
            buf += sizeof(unsigned short);

            memcpy(buf, msg_name, msg_name_len);
            buf += msg_name_len;

            char * buf_end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buf);
            if(buf_end - buf != msg_len){
                LOG_ERROR("serialize fail %d/%d msg_name:%s\n", buf_end - buf, msg_len, msg_name);
                return 0;
            }
            buf += msg_len;

            LOG_DEBUG("arg%d:%s", i - arg_index + 1, message->GetTypeName().data());
            if(message->ByteSize() < 1024){
                LOG_DEBUG("%s", message->DebugString().data());
            }
            //printf("msg size %d\n", msg_len);

        }else if(lua_istable(L, i))
        {
            *(unsigned char *)buf = ARG_TYPE_TABLE;
            buf += sizeof(unsigned char);
            lua_pushvalue(L, i);
            char *str = Json::encode(L);
            lua_pop(L, 1);
            if(str == NULL){
                return 0;
            }
            LOG_DEBUG("arg%d:%s", i - arg_index + 1, str);
            int str_len = strlen(str);

            *(unsigned int *)buf = str_len;
            buf += sizeof(unsigned int);
            memcpy(buf, str, str_len);
            buf += str_len;
            //释放 
            free(str);
        }else if(lua_isnil(L, i)){
            *(unsigned char *)buf = ARG_TYPE_NIL;
            buf += sizeof(unsigned char);

            LOG_DEBUG("nil");
        }else {
            LOG_ERROR("unsupport");
            return 0;
        }
    }
    *(unsigned char *)buf = ARG_TYPE_END;
    buf += sizeof(unsigned char);
    return 1;
}



static char *get_buf;
static int get_buf_len;

//GET(sockfd, timeout, 'login.PLAYER_ENTER', uid)
static int lget(lua_State *L)
{
    if(lua_gettop(L) < 3)
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isnumber(L, 1))
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isnumber(L, 2))
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isstring(L, 3))
    {
        LOG_ERROR("POST arg err");
        return 0;
    }

    int sockfd = (int)lua_tointeger(L, 1);
    int timeout_sec = (int)lua_tointeger(L, 2);
    const char *msg_name = (const char *)lua_tostring(L, 3);

    if(Port::sock_is_close(sockfd))
    {
        LOG_ERROR("sock is close");
        return 0;
    }

    //Port::Sock *sock = Port::sockfromfd(sockfd);

    int body_len = rmi_strlen(L, 4, msg_name);
    if(body_len == 0)
    {
        LOG_ERROR("strlen fail");
        return 0;
    }
    int plen = body_len + sizeof(unsigned int);
    if(get_buf_len < plen)
    {
        if(get_buf != NULL)
        {
            free(get_buf);
        }
        get_buf = (char *)malloc(plen);
        if(get_buf == NULL)
        {
            LOG_ERROR("malloc fail");
            return 0;
        }
        get_buf_len = plen;
    }
    char *buf = get_buf;
    if(buf == NULL)
    {
        LOG_ERROR("alloc fail");
        return 0;
    }
    if(rmi_encode(L, 4, msg_name, buf, plen) == 0)
    {
        LOG_ERROR("encode fail");
        return 0;
    }
    LOG_INFO("GET %s body_len:%d", msg_name, body_len);


    setblock(sockfd);
    struct timeval tv;tv.tv_sec = timeout_sec; tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET,SO_RCVTIMEO, (char *)&tv,sizeof(tv));
    setsockopt(sockfd, SOL_SOCKET,SO_SNDTIMEO, (char *)&tv,sizeof(tv));
    int remain = plen;
    while(remain > 0)
    {
        int ir = send(sockfd, buf, remain, 0);
        if(ir <= 0)
        {
            LOG_ERROR("send fail %s", strerror(errno));
            setnonblock(sockfd);
            lua_pushstring(L, strerror(errno));
            return 1;
        }
        remain -= ir;
        buf += ir;
    }
    //接收一个json
    int ir = recv(sockfd, (char *)&plen, 4, 0); 
    if(ir < 4)
    {
        LOG_ERROR("recv fail %s", strerror(errno));
        setnonblock(sockfd);
        lua_pushstring(L, strerror(errno));
        return 1;
    }
    if(get_buf_len < plen + 1)
    {
        if(get_buf != NULL)
        {
            free(get_buf);
        }
        get_buf = (char *)malloc(plen + 1);
        if(get_buf == NULL)
        {
            LOG_ERROR("malloc fail");
            setnonblock(sockfd);
            lua_pushstring(L, strerror(errno));
            return 1;
        }
        get_buf_len = plen + 1;
    }
    buf = get_buf;
    remain = plen;
    while(remain > 0)
    {
        int ir = recv(sockfd, buf, remain, 0);
        if(ir <= 0)
        {
            LOG_ERROR("recv fail %s", strerror(errno));
            setnonblock(sockfd);
            lua_pushstring(L, strerror(errno));
            return 1;
        }
        remain -= ir;
        buf += ir;
    }
    LOG_INFO("REPLY");
    get_buf[plen] = 0;
    Json::decode(L, get_buf);
    setnonblock(sockfd);
    return 1;
}


//REPLY(sockfd, 'hello')
static int lreply(lua_State *L)
{
    int sockfd = (int)lua_tointeger(L, 1);
    Port::Sock *sock = Port::sockfromfd(sockfd);
    
    if(sock == NULL)
    {
        LOG_ERROR("sock is bad");
        return 0;
    }

    char *str = Json::encode(L);
    int str_len = strlen(str);

    char *buf = Sendbuf::alloc(sockfd, str_len + 4);
    if(buf == NULL)
    {
        free(str);
        LOG_ERROR("alloc fail");
        return 0;
    }
    *(int *)buf = str_len;
    buf += sizeof(int);
    memcpy(buf, str, str_len);
    Sendbuf::flush(sockfd, buf, str_len + 4);

    Port::add_write_event(sockfd);
    free(str);

    return 1;
}


/*
 * 广播
 */
//BROADCAST(sockfd, 'login.PLAYER_ENTER', uid)
static int lbroadcast(lua_State *L)
{
    if(lua_gettop(L) < 2)
    {
        LOG_ERROR("BROADCAST arg err");
        return 0;
    }
    if(!lua_isuserdata(L, 1))
    {
        LOG_ERROR("BROADCAST arg err");
        return 0;
    }
    if(!lua_isstring(L, 2))
    {
        LOG_ERROR("BROADCAST arg err");
        return 0;
    }

    struct timeval t1;
    gettimeofday(&t1, NULL);

    Port::Port* port = (Port::Port*)lua_touserdata(L, 1);
    const char *msg_name = (const char *)lua_tostring(L, 2);

    if(port == NULL)
    {
        LOG_ERROR("port is nil");
        return 0;
    }
    int body_len = rmi_strlen(L, 4, msg_name);
    if(body_len == 0)
    {
        LOG_ERROR("strlen fail");
        return 0;
    }
    LOG_INFO("BROADCAST %s TO %s body_len:%d", msg_name, port->name, body_len);
    for(int sockfd = 1; sockfd < MAX_SOCK; sockfd++)
    {
        Port::Sock *sock = Port::sockfromfd(sockfd);
        if(sock->port != port)
        {
            continue;
        }

        int plen = body_len + sizeof(unsigned int);
        char *buf = Sendbuf::alloc(sockfd, plen);
        
        if(buf == NULL)
        {
            LOG_ERROR("alloc fail");
            return 0;
        }
        if(rmi_encode(L, 3, msg_name, buf, plen) == 0)
        {
            LOG_ERROR("encode fail");
            return 0;
        }
        Sendbuf::flush(sockfd, buf, plen);
        Port::add_write_event(sockfd);
    }
    struct timeval t2;
    gettimeofday(&t2, NULL);
    LOG_INFO("BROADCAS_ %s TO %s usec:%d", msg_name, port->name, time_diff(&t1, &t2));
    lua_pushinteger(L, 1);
    return 1;

}

//POST(sockfd, 'login.PLAYER_ENTER', uid)
static int lpost(lua_State *L)
{
    if(lua_gettop(L) < 2)
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isnumber(L, 1))
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isstring(L, 2))
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    struct timeval t1;
    gettimeofday(&t1, NULL);
    int sockfd = (int)lua_tointeger(L, 1);
    if(sockfd == 0)
    {
        LOG_ERROR("is nil");
        return 0;
    }
    const char *msg_name = (const char *)lua_tostring(L, 2);
    Port::Sock* sock = Port::sockfromfd(sockfd);
    if(sock == NULL)
    {
        LOG_ERROR("sock is null %s", msg_name);
        return 0;
    }
    Port::Port* port = sock->port;
    if(port == NULL)
    {
        LOG_ERROR("port is null %s", msg_name);
        return 0;
    }
    if(Port::sock_is_close(sockfd))
    {
        LOG_ERROR("sock is close %s %s", port->name, msg_name);
        return 0;
    }

    LOG_INFO("POST %s TO %s", msg_name, port->name);
    int body_len = rmi_strlen(L, 3, msg_name);
    if(body_len == 0)
    {
        LOG_ERROR("strlen fail");
        return 0;
    }
    int plen = body_len + sizeof(unsigned int);
    char *buf = Sendbuf::alloc(sockfd, plen);
    if(buf == NULL)
    {
        LOG_ERROR("alloc fail");
        return 0;
    }
    if(rmi_encode(L, 3, msg_name, buf, plen) == 0)
    {
        LOG_ERROR("encode fail");
        return 0;
    }
    Sendbuf::flush(sockfd, buf, plen);

    Port::add_write_event(sockfd);


    struct timeval t2;
    gettimeofday(&t2, NULL);
    LOG_INFO("POS_ %s TO %s usec:%d body_len:%d", msg_name, port->name, time_diff(&t1, &t2), body_len);

    lua_pushboolean(L, true);
    return 1;
}

//FORWARD(sockfd, uid, msg)
static int lforward(lua_State *L)
{
    struct timeval t1;
    gettimeofday(&t1, NULL);
    if(lua_gettop(L) < 3)
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isnumber(L, 1)){
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isnumber(L, 2))
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    if(!lua_isuserdata(L, 3))
    {
        LOG_ERROR("POST arg err");
        return 0;
    }
    int sockfd = (int)lua_tointeger(L, 1);
    if(sockfd  == 0)
    {
        LOG_ERROR("is nil");
        return 0;
    }
    int uid = (int)lua_tointeger(L, 2);
    Port::Sock* sock = Port::sockfromfd(sockfd);
    if(sock == NULL)
    {
        LOG_ERROR("sock is null");
        return 0;
    }
    Port::Port *port = sock->port;
    if(port == NULL){
        LOG_ERROR("port is null");
        return 0;
    }
    if(Port::sock_is_close(sockfd))
    {
        LOG_ERROR("sock is close");
        return 0;
    }
    LuaMessage *message_lua = (LuaMessage *)luaL_checkudata(L, 3, "LuaMessage");
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

    int msg_name_len = strlen(cmd);
    memcpy(msg_name, cmd, msg_name_len);
    msg_name[msg_name_len] = 0;

    LOG_INFO("[%d]FORWARD %s TO %s", uid, cmd, port->name)
    int body_len = message->ByteSize();
    int plen = 4 + sizeof(unsigned char) + sizeof(int) + msg_name_len + 2  + body_len;
    char *buf = Sendbuf::alloc(sockfd, plen);
    if(buf == NULL)
    {
        LOG_ERROR("alloc fail cmd:%s\n", cmd);
        return 0;
    }
    *((int *)buf) = plen - 4;
    buf += 4;

    *((unsigned char *)buf) = PROTO_MSG;
    buf += sizeof(unsigned char);

    *((int *)buf) = uid;
    buf += 4;

    *((unsigned short *)buf) = msg_name_len;
    buf += 2;
    memcpy(buf, msg_name, msg_name_len);
    buf += msg_name_len;
        
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

    LOG_INFO("[%d]FORWARD %s TO %s plen:%d usec:%d", uid, cmd, port->name, plen, time_diff(&t1, &t2))
    if(body_len < 4096)
    {
        LOG_DEBUG("%s", message->DebugString().data());
    }
    lua_pushboolean(L, true);
    return 1;
}

static int lcreate(lua_State *L)
{
    if (lua_isuserdata(L, 1))
    {
        struct aeEventLoop *loop = (struct aeEventLoop *)lua_touserdata(L, 1);
        Port::Port *port = Port::create(loop);
        port->L = L;
        Port::set_read_func(port, rmi_port_cb_packet);
        lua_pushlightuserdata(L, port);
        return 1;
    }
    return 0;
}

static luaL_Reg lua_lib[] = 
{
    {"create", lcreate},
    {NULL, NULL}
};

int luaopen_rmi_port(lua_State *L)
{

	luaL_register(L, "RMIPort", (luaL_Reg*)lua_lib);
    
    lua_pushcfunction(L, lpost);
    lua_setglobal(L, "POST");

    lua_pushcfunction(L, lget);
    lua_setglobal(L, "GET");

    lua_pushcfunction(L, lforward);
    lua_setglobal(L, "FORWARD");

    lua_pushcfunction(L, lbroadcast);
    lua_setglobal(L, "BROADCAST");

    lua_pushcfunction(L, lreply);
    lua_setglobal(L, "REPLY");

    return 0;
}
