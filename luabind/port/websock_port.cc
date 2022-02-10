#include "port/websock_port.h"
#include "net/port.h"
#include "pblua/pblua.h"
#include "net/recvbuf.h"
#include "net/sendbuf.h"
#include "log/log.h"
#include "encrypt/base64.h"
#include "encrypt/md5.h"
#include "encrypt/sha1.h"
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAX_MSG_NAME_LEN 128
#define MAX_HEADER_LEN 256

static char msg_name[MAX_MSG_NAME_LEN];
static char recv_msg_name[MAX_MSG_NAME_LEN];

typedef struct FrameHeader
{
    unsigned char opcode:4;
    unsigned char rsv:3;
    unsigned char fin:1;
    unsigned char payload_len:7;
    unsigned char mask:1;
}FrameHeader;

static int time_diff(struct timeval *t1, struct timeval *t2)
{
    int usec = (t2->tv_sec - t1->tv_sec) * 1000000 + t2->tv_usec - t1->tv_usec;
    return usec;
}


static int _find_string(const char* text, size_t textlen, int start, const char* str, size_t len)
{
    for (size_t i = start; i < textlen; i++)
    {
        if (!strncmp(text + i, str, len))
        {
            return i;
        }
    }
    return -1;
}
//底层的SEND接口
static int _real_send(int sockfd, const void* data, size_t datalen)
{
    //插入到缓冲区
    char* buf= Sendbuf::alloc(sockfd, datalen);
    if (!buf)
    {
        return 0;
    }
    LOG_DEBUG("send %ld to sockfd(%d)", datalen, sockfd);
    memcpy(buf, data, datalen);
    Sendbuf::flush(sockfd, buf, datalen);
    Port::add_write_event(sockfd);
    return datalen;
}

//底层的SEND接口
static int send(int sockfd, const char* data)
{
    return _real_send(sockfd, data, strlen(data));
}


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

static int dispatch_frame(int sockfd, int opcode, const char* data, size_t datalen)
{
    Port::Sock* sock = Port::sockfromfd(sockfd);
    if (sock == NULL)
    {
        LOG_ERROR("sock is null");
        return 0;
    }
    Port::Port* port = sock->port;
    if (port == NULL)
    {
        LOG_ERROR("port is null");
        return 0;
    }
    lua_State* L = port->L;
    LOG_INFO("websocket recv a frame sockfd(%d) opcode(%d) datalen(%d)", sockfd, opcode, datalen);
    if (opcode == 8)
    {
        //分发到lua处理 lua_pushluafunction(L, port->lua_on_close);
        lua_pushnumber(L, sockfd);
        if (lua_pcall(L, 1, 0, 0) != 0)
        {
            if (lua_isstring(L, -1))
            {
                LOG_ERROR("Websocket.dispatch error %s", lua_tostring(L, -1));
            }
        }
        return 0;

    } else 
    {
        char *body = (char*)data;
        int body_len = datalen;

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

        body += msg_name_len;
        body_len -= msg_name_len;

        struct timeval t1;
        gettimeofday(&t1, NULL);

        google::protobuf::Message* message = pblua_load_msg(recv_msg_name);

        if(message == NULL){
            LOG_ERROR("can not load %d msg %s", msg_name_len, recv_msg_name);
            return 0;
        }
        google::protobuf::io::ArrayInputStream stream(body, body_len);

        if(message->ParseFromZeroCopyStream(&stream) == 0){
            delete message;
            LOG_ERROR("parse fail\n");
            return 0;
        }

        LOG_INFO("[%d]RECV %s FROM %s datalen:%d", sock->uid, recv_msg_name, port->name, datalen);

        if(message->ByteSize() < 4096)
        {
            LOG_DEBUG("%s", message->DebugString().data());
        }
        const char* func = port->lua_on_read;
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
            return 0;
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
        LOG_INFO("[%d]REC_ %s FROM %s datalen:%d usec:%d", sock->uid, recv_msg_name, port->name, datalen, time_diff(&t1, &t2));
        lua_pop(L, lua_gettop(L));

        return 0;
    }
}


static int combine_all_frame(int sockfd, const char* data , size_t datalen)
{
    char* framedata = (char*)data;
    char* combine_payload_data = (char*)data;
    unsigned long long packet_len = 0;
    unsigned long long total_len = 0;
    int opcode = 0;
    for(;;)
    {
        FrameHeader* frame_header = (FrameHeader*)framedata;
        int fin = frame_header->fin;
        opcode = frame_header->opcode;
        unsigned long long framelen = 2;
        unsigned long long real_payload_len = frame_header->payload_len;
        char *payload_data = 0;
        //解释负载长度
        if (frame_header->payload_len == 126)
        {
            framelen = 4;
        }
        else if (frame_header->payload_len == 127)
        {
            framelen = 9;
        }
        if (frame_header->mask == 1)
        {
            framelen += 4;
        }
        //负载
        payload_data = (char *)framedata + framelen;
        if (frame_header->payload_len == 126)
        {
            //2个字节的长度
            real_payload_len = ntohs(*((unsigned short*)(framedata + 2)));
        }
        else if (frame_header->payload_len == 127)
        {
            //暂时不支持8字节长度
            //8个字节的长度
            //TODO ntohl只能用于32位数
            //unsigned int* _real_len32 = (unsigned int*)(&real_payload_len);
            //_real_len32[0] = ntohl(*((unsigned int*)(framedata+ 4)));
            //_real_len32[1] = ntohl(*((unsigned int*)(framedata + 2)));
            real_payload_len = ntohl(*((unsigned long long*)(framedata+ 2)));

        }
        framelen += real_payload_len;

        //直接复制数据吧
        memcpy(combine_payload_data, payload_data, real_payload_len);
        total_len += framelen;
        packet_len += real_payload_len;
        framedata += framelen;
        combine_payload_data += real_payload_len;
        if (fin == 1)
        {
            break;
        }
    }
    *combine_payload_data = 0;
    dispatch_frame(sockfd, opcode, data, packet_len);
    return total_len;
}

static int decode_one_frame(int sockfd, const char* data, size_t datalen)
{
    if(datalen < 2)
    {
        return 0;
    }
    FrameHeader* frame_header = (FrameHeader*)data;
    LOG_DEBUG("fin(%d) rsv(%d) mask(%d) opcode(%d) payload_len(%d)", frame_header->fin, frame_header->rsv, frame_header->mask, frame_header->opcode, frame_header->payload_len);
    //LOG_DEBUG("c1 %d c2 %d", *(unsigned char *)data, *(unsigned char *)(data + 1));
    //接下来开始计算真实的长度
    unsigned long long framelen = 2;
    unsigned long long real_payload_len = frame_header->payload_len;
    //掩码
    unsigned char *mask = 0;
    //负载
    char *payload_data = 0;
    if (frame_header->payload_len == 126)
    {
        framelen = 4;
    }
    else if (frame_header->payload_len == 127)
    {
        framelen = 9;
    }
    if (frame_header->mask == 1)
    {
        mask = (unsigned char *)data + framelen;
        framelen += 4;
    }
    //负载
    payload_data = (char *)data + framelen;

    //测试数据长度
    if (datalen < framelen)
    {
        return 0;
    }

    //解释负载长度
    if (frame_header->payload_len == 126)
    {
        //2个字节的长度
        real_payload_len = ntohs(*((unsigned short*)(data + 2)));
    }
    else if (frame_header->payload_len == 127)
    {
        //暂时不支持8字节长度
        //TODO ntohl只能用于32位数
        //unsigned int* _real_len32 = (unsigned int*)(&real_payload_len);
        //_real_len32[0] = ntohl(*((unsigned int*)(data + 4)));
        //_real_len32[1] = ntohl(*((unsigned int*)(data + 2)));
        real_payload_len = ntohl(*((unsigned long long*)(data + 2)));
    }
    framelen += real_payload_len;
    //测试数据长度
    if (datalen < framelen)
    {
        return 0;
    }
    LOG_DEBUG("real_payload_len(%lld)", real_payload_len);
    //用掩码修改数据
    if (frame_header->mask == 1)
    {
        for (unsigned long long i = 0; i < real_payload_len; i++)
        {
            payload_data[i] = payload_data[i] ^ mask[i % 4];
        }
    }
    //LOG_DEBUG("%s", data);
    //LOG_DEBUG("payload %s", payload_data);
    //是否最后一帧了
    return frame_header->fin;
}

static int port_cb_accept(int sockfd)
{
    return 0;
}

static int port_cb_packet(int sockfd, const char* data, int datalen)
{
    Port::Sock* sock = Port::sockfromfd(sockfd);
    if (sock == NULL)
    {
        LOG_ERROR("sock is nil");
        return 0;
    }
    Port::Port* port = sock->port;
    if (port == NULL)
    {
        LOG_ERROR("sock is nil");
        return 0;
    }
    lua_State* L = port->L;
    //握手
    if (sock->handshake == 0)
    {
        LOG_DEBUG("%s", data);
        SHA1_CTX context; 
        SHA1Init(&context); 
        static unsigned char sha1_out[20];
        static unsigned char sec_websocket_key[128];
        static char sec_websocket_accept[128];
        static char datestr[128];
        int rnrn = _find_string(data, datalen, 0, "\r\n\r\n", 4);
        if (rnrn < 0)
        {
            LOG_ERROR("rnrn not found");
            return 0;
        }
        int key_start = _find_string(data, datalen, 0, "Sec-WebSocket-Key: ", 19);
        int key_end = _find_string(data, datalen, key_start, "\r\n", 2);
        if (key_start < 0 || key_end < 0)
        {
            LOG_ERROR("Sec-WebSocket-Key not found");
            return 0;
        }
        //计算sha1
        memcpy(sec_websocket_key, data + key_start + 19, key_end - key_start - 19);
        sec_websocket_key[key_end - key_start - 19] = 0;
        strcat((char*)sec_websocket_key, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
        SHA1Update(&context, sec_websocket_key, strlen((char *)sec_websocket_key)); 
        SHA1Final(sha1_out, &context); 

        //LOG_DEBUG("%d %d %d", rnrn, key_start, key_end);
        //LOG_DEBUG("Sec-WebSocket-Key: %s len(%d)", sec_websocket_key, strlen((char*)sec_websocket_key));
        //LOG_DEBUG("Sec-WebSocket-Key: %s", sec_websocket_key);
        //LOG_DEBUG("Sha1: %s", sha1_out);

        //计算base64
        base64_encode(sha1_out, sizeof(sha1_out), sec_websocket_accept);

        //计算日期
        time_t t = time(NULL);
        struct tm* tmp = localtime(&t);
        strftime(datestr, sizeof(datestr), "Date:%a, %d %b %Y %H:%M:%S GMT\r\n", tmp);

        //LOG_DEBUG("Sec-WebSocket-Accept: %s", sec_websocket_accept);

        send(sockfd, "HTTP/1.1 101 Switching Protocols\r\n"
                "Connection:Upgrade\r\n"
                "Server:lujingwei002@qq.com\r\n"
                "Upgrade:WebSocket\r\n"
                "Access-Control-Allow-Credentials:true\r\n"
                "Access-Control-Allow-Headers:content-type\r\n");
        send(sockfd, datestr);
        send(sockfd, "Sec-WebSocket-Accept:");
        send(sockfd, sec_websocket_accept);
        send(sockfd, "\r\n\r\n");
        sock->handshake = 1;

        //分发到lua处理
        struct sockaddr_in addr;	
        socklen_t addrlen = sizeof(addr);	
        getpeername(sockfd, (struct sockaddr *)&addr, &addrlen);
        lua_pushluafunction(L, port->lua_on_accept);
        lua_pushnumber(L, sockfd);
        lua_pushstring(L, inet_ntoa(addr.sin_addr));
        lua_pushnumber(L, ntohs(addr.sin_port));

        if (lua_pcall(L, 3, 0, 0) != 0)
        {
            if (lua_isstring(L, -1))
            {
                LOG_DEBUG("%s error %s", port->lua_on_accept, lua_tostring(L, -1));
            }
        }
        return rnrn + 4; 
    } else 
    {
        LOG_DEBUG("recv a frame");
        if(decode_one_frame(sockfd, data, datalen) == 0)
        {
            return 0;
        }
        //全部帧都到了
        return combine_all_frame(sockfd, data, datalen);
    }
    return 0;
}
/*  
static int port_cb_packet(int sockfd, const char* data, int datalen)
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
}*/

static int lcreate(lua_State *L)
{
    if (lua_isuserdata(L, 1))
    {
        struct aeEventLoop *loop = (struct aeEventLoop *)lua_touserdata(L, 1);
        Port::Port *port = Port::create(loop);
        port->L = L;
        Port::set_read_func(port, port_cb_packet);
        Port::set_accept_func(port, port_cb_accept);
        lua_pushlightuserdata(L, port);
        return 1;
    }
    return 0;
}

static int lpost(lua_State *L)
{
	if (lua_isnumber(L, 1) && lua_isuserdata(L, 2))
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
        if(Port::sock_is_close(sockfd))
        {
            LOG_ERROR("sock %d is close", sockfd);
            return 0;
        }

        int msg_name_len = strlen(cmd);
        memcpy(msg_name, cmd, msg_name_len);
        msg_name[msg_name_len] = 0;

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

        int msgdata_len = message->ByteSize();

        int plen = 0;

        //统一使用2字长长度
        FrameHeader header;
        header.fin = 1;//结束帧
        header.rsv = 0;
        header.opcode = 2;
        header.mask = 0;//没有掩码
        
        int datalen = 2 + msg_name_len + msgdata_len;
        plen += sizeof(FrameHeader);
        if (datalen >= 126)
        {
            header.payload_len = 126;
            plen = sizeof(FrameHeader) + sizeof(unsigned short) + datalen;
        } else 
        {
            header.payload_len = datalen;
            plen = sizeof(FrameHeader) + datalen;
        }

        char *buf = Sendbuf::alloc(sockfd, plen);
        if(buf == NULL)
        {
            LOG_ERROR("alloc fail cmd:%s\n", cmd);
            return 0;
        }

        if (datalen >= 126)
        {
            memcpy(buf, &header, sizeof(header));
            buf += sizeof(header);

            unsigned short real_len = htons(datalen);
            memcpy(buf, &real_len, sizeof(real_len));
            buf += sizeof(real_len);
        } else 
        {
            memcpy(buf, &header, sizeof(header));
            buf += sizeof(header);
        }

        (*(unsigned short *)buf) = msg_name_len;
        buf += sizeof(unsigned short);
        memcpy(buf, msg_name, msg_name_len);
        buf += msg_name_len;

        char * buf_end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buf);
        if(buf_end - buf != msgdata_len)
        {
            LOG_ERROR("serialize fail %d/%d cmd:%s\n", buf_end - buf, msgdata_len, cmd);
            return 0;
        }
        //加进socket的发送队列
        Sendbuf::flush(sockfd, buf, plen);

        Port::add_write_event(sockfd);

        struct timeval t2;
        gettimeofday(&t2, NULL);

        LOG_INFO("[%d]SEND %s TO %s msgdata_len(%d) plen:%d usec:%d", sock->uid, cmd, port->name, msgdata_len, plen, time_diff(&t1, &t2))
        if(datalen < 4096)
        {
            LOG_DEBUG("%s", message->DebugString().data());
        }
        lua_pushboolean(L, true);
        return 1;
	}
    lua_pushboolean(L, false);
    return 1;
}

static int lrecv_open_websock(lua_State* L)
{
	if (lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        int sockfd = (int)lua_tonumber(L, 1);

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
        int timeout_sec = (int)lua_tonumber(L, 2);
        setblock(sockfd);
        struct timeval tv;tv.tv_sec = timeout_sec; tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET,SO_RCVTIMEO, (char *)&tv,sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET,SO_SNDTIMEO, (char *)&tv,sizeof(tv));

        char c;
        int step = 1;
        //接收\r\n\r\n
        //不判断了
        for (;;)
        {
            int n = recv(sockfd, &c, sizeof(c), 0);
            if (n != sizeof(c))
            {
                LOG_ERROR("recv error");
                break;
            }
            printf("%c", c);
            switch(step)
            {
                case 1:
                    if (c == '\r')step = 2;else step = 1;
                    break;
                case 2:
                    if (c == '\n')step = 3;else step = 1;
                    break;
                case 3:
                    if (c == '\r')step = 4;else step = 1;
                    break;
                case 4:
                    if (c == '\n')goto finish_recv_open_websock;else step = 1;
                    break;
            }
        }
finish_recv_open_websock:
        LOG_DEBUG("recv_open_websock\n");

        setnonblock(sockfd);
        lua_pushboolean(L, true);
        return 1;
	}
    lua_pushboolean(L, false);
    return 1;

}

static int lsend_open_websock(lua_State* L)
{
	if (lua_isnumber(L, 1) && lua_isnumber(L, 2))
    {
        int sockfd = (int)lua_tonumber(L, 1);

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
        int timeout_sec = (int)lua_tonumber(L, 2);
        setblock(sockfd);
        struct timeval tv;tv.tv_sec = timeout_sec; tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET,SO_RCVTIMEO, (char *)&tv,sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET,SO_SNDTIMEO, (char *)&tv,sizeof(tv));

        const char* data = "GET / HTTP/1.1\r\n"
            "Accept-Encoding: gzip, deflate, sdch\r\n"
            "Accept-Language: zh-CN,zh;q=0.8\r\n"
            "Connection: Upgrade\r\n"
            "Origin: null\r\n"
            "Pragma: no-cache\r\n"
            "Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits\r\n"
            "Sec-WebSocket-Key: pk4BUV3PuqJJWfAKyvIyaw==\r\n"
            "Sec-WebSocket-Version: 13\r\n"
            "Upgrade: websocket\r\n"
            "User-Agent: Mozilla/5.0\r\n\r\n"; 
        LOG_INFO("send open websock %d\n", strlen(data));
        int n = send(sockfd, data, strlen(data), 0);
        if(n < (int)sizeof(data))
        {
            LOG_ERROR("send fail n(%d) error(%s)", n, strerror(errno));
            return 0;
        }

        setnonblock(sockfd);
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
        if(Port::sock_is_close(sockfd))
        {
            LOG_ERROR("sock %d is close", sockfd);
            return 0;
        }
        int timeout_sec = (int)lua_tonumber(L, 3);

        int msg_name_len = strlen(cmd);
        memcpy(msg_name, cmd, msg_name_len);
        msg_name[msg_name_len] = 0;

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
        setblock(sockfd);
        struct timeval tv;tv.tv_sec = timeout_sec; tv.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET,SO_RCVTIMEO, (char *)&tv,sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET,SO_SNDTIMEO, (char *)&tv,sizeof(tv));

        int msgdata_len = message->ByteSize();

        int plen = 0;

        //统一使用2字长长度
        FrameHeader header;
        header.fin = 1;//结束帧
        header.rsv = 0;
        header.opcode = 2;
        header.mask = 0;//没有掩码
        
        int datalen = 2 + msg_name_len + msgdata_len;
        plen += sizeof(FrameHeader);
        if (datalen >= 126)
        {
            header.payload_len = 126;
            plen = sizeof(FrameHeader) + sizeof(unsigned short) + datalen;
        } else 
        {
            header.payload_len = datalen;
            plen = sizeof(FrameHeader) + datalen;
        }
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

        if (datalen >= 126)
        {
            memcpy(buf, &header, sizeof(header));
            buf += sizeof(header);

            unsigned short real_len = htons(datalen);
            memcpy(buf, &real_len, sizeof(real_len));
            buf += sizeof(real_len);
        } else 
        {
            memcpy(buf, &header, sizeof(header));
            buf += sizeof(header);
        }

        (*(unsigned short *)buf) = msg_name_len;
        buf += sizeof(unsigned short);
        memcpy(buf, msg_name, msg_name_len);
        buf += msg_name_len;

        char * buf_end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buf);
        if(buf_end - buf != msgdata_len)
        {
            LOG_ERROR("serialize fail %d/%d cmd:%s\n", buf_end - buf, msgdata_len, cmd);
            return 0;
        }

        int n = send(sockfd, s_send_buf, plen, 0);
        if(n < plen){
            LOG_ERROR("send fail n(%d) error(%s)", n, strerror(errno));
            return 0;
        }

        struct timeval t2;
        gettimeofday(&t2, NULL);

        LOG_INFO("[%d]SEND %s TO %s plen:%d usec:%d", sock->uid, cmd, port->name, plen, time_diff(&t1, &t2))
        if(datalen < 4096)
        {
            LOG_DEBUG("%s", message->DebugString().data());
        }
        setnonblock(sockfd);
        lua_pushboolean(L, true);
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
        if(s_recv_len < (int)sizeof(FrameHeader))
        {
            int n = recv(sockfd, s_recv_buf + s_recv_len, sizeof(FrameHeader) - s_recv_len, 0);
            if(n <= 0)
            {
                LOG_ERROR("recv fail");
                return 0;
            }
            s_recv_len += n;
            LOG_INFO("real recv %d total %d", n, s_recv_len);
        }
        int framelen = 2;
        FrameHeader* frame_header = (FrameHeader *)s_recv_buf;
        LOG_INFO("websocket recv a frame sockfd(%d) opcode(%d) payload(%d)", sockfd, frame_header->opcode, frame_header->payload_len);
        if (frame_header->payload_len == 126)
        {
            framelen = 4;
        }
        else if (frame_header->payload_len == 127)
        {
            framelen = 9;
        }
        unsigned char* mask = NULL;
        if (frame_header->mask == 1)
        {
            mask = (unsigned char *)s_recv_buf + framelen;
            framelen += 4;
        }
        if(s_recv_len < framelen)
        {
            int n = recv(sockfd, s_recv_buf + s_recv_len, framelen - s_recv_len, 0);
            if(n <= 0)
            {
                LOG_ERROR("recv fail");
                return 0;
            }
            s_recv_len += n;
        }

        int real_len = frame_header->payload_len + framelen;

        
        if(s_recv_size < real_len)
        {
            s_recv_size = real_len;
            s_recv_buf = (char *)realloc(s_recv_buf, s_recv_size);
            if(s_recv_buf == NULL)
            {
                LOG_ERROR("relloc fail");
                s_recv_size = 0;
                s_recv_len = 0;
                return 0;
            }
        }

        if(s_recv_len < real_len)
        {
            int n = recv(sockfd, s_recv_buf + s_recv_len, real_len - s_recv_len, 0);
            if(n <= 0)
            {
                LOG_ERROR("recv fail");
                return 0;
            }
            s_recv_len += n;
        }

        char *payload_data = s_recv_buf + framelen;
        int payload_len = frame_header->payload_len;

        //用掩码修改数据
        if (frame_header->mask == 1)
        {
            for (int i = 0; i < payload_len; i++)
            {
                payload_data[i] = payload_data[i] ^ mask[i % 4];
            }
        }


        int msg_name_len = *(unsigned short *)payload_data;
        payload_data += sizeof(unsigned short);
        payload_len -= sizeof(unsigned short);
        if(msg_name_len >= MAX_MSG_NAME_LEN - 1)
        {
            LOG_ERROR("reach max msg name len %d/%d", msg_name_len, MAX_MSG_NAME_LEN);
            return 0;
        }
        memcpy(recv_msg_name, payload_data, msg_name_len);
        recv_msg_name[msg_name_len] = 0;

        payload_data += msg_name_len;
        payload_len -= msg_name_len;

        google::protobuf::Message* message = pblua_load_msg(recv_msg_name);
        if(message == NULL)
        {
            LOG_ERROR("can not load %d msg %s", msg_name_len, recv_msg_name);
            return 0;
        }
        google::protobuf::io::ArrayInputStream stream(payload_data, payload_len);
        
        if(message->ParseFromZeroCopyStream(&stream) == 0)
        {
            delete message;
            LOG_ERROR("parse fail\n");
            return 0;
        }

        LOG_INFO("[%d]RECV %s FROM %s real_len:%d", sock->uid, recv_msg_name, port->name, real_len);

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
        LOG_INFO("[%d]RECV %s FROM %s real_len:%d usec:%d", sock->uid, recv_msg_name, port->name, real_len, time_diff(&t1, &t2));
        setnonblock(sockfd);
        
        s_recv_len -= real_len;
        if(s_recv_len > 0)
        {
            memcpy(s_recv_buf, s_recv_buf + real_len, s_recv_len);
        }
        return 1;
    }

    return 0;
}

static luaL_Reg lua_lib[] = 
{
    {"create", lcreate},
    {"post", lpost},
    {"send", lsend},
    {"recv", lrecv},
    {"send_open_websock", lsend_open_websock},
    {"recv_open_websock", lrecv_open_websock},
    {NULL, NULL}
};

int luaopen_websock_port(lua_State *L)
{
    luaL_register(L, "WebSockPort", lua_lib);
    return 1;
}

