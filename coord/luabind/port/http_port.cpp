

#include "port/http_port.h"
#include "net/port.h"
#include "net/sendbuf.h"
#include "net/port.h"
#include "net/recvbuf.h"
#include <ctype.h>

#define CRLF2 "\r\n\r\n"
#define CRLF "\r\n"

static int http_port_cb_packet(int portfd, int linefd, int bodyfd){
    Port *port = port_from_fd(portfd);
    Line *line = line_from_fd(linefd);
    if(port == NULL){
        LOG_ERROR("port is null");
        return 0;
    }
    if(line == NULL){
        LOG_ERROR("line is null");
        return 0;
    }
    int buffd = line->buf_read;
    char *body = ar_ptr(bodyfd);
    int body_len = ar_remain(bodyfd);

    //读消息体
    if(line->content_length > 0){
        const char *func = port->lua_cb_packet;
        if(func[0] != 0){
            luas_pushluafunction(func);
            //sock 
            lua_pushnumber(L, linefd);
            lua_pushlstring(L, body, body_len);
            if(lua_pcall(L, 2, 0, 0) != 0){
                LOG_ERROR("error running function %s: %s", func, lua_tostring(L, -1));
            }
            lua_pop(L, lua_gettop(L));
        }
        //跳过这个数据包
        rbuf_rskip(buffd, body_len);
        line->content_length -= body_len;
        line->content_length = max(0, line->content_length);
        return 0;
    }
    //数据不够
    if(body_len < 4){
        return 0;
    }
    //搜索\r\n\r\n
    int msg_len = 0;
    for(int i = 0; i < body_len - 3; i++){
        if(strncmp(body + i, CRLF2, 4) == 0){
            //找到
            msg_len = i + 4;
            break;
        }
    }
    //不够一个数据包
    if(msg_len == 0){
        return 0;
    }
    //跳过这个数据包
    rbuf_rskip(buffd, msg_len);
    
    const char *func = port->lua_cb_packet;
    if(func[0] != 0){
        luas_pushluafunction(func);
        //sock 
        lua_pushnumber(L, linefd);
        lua_pushlstring(L, body, msg_len);
        if (lua_pcall(L, 2, 0, 0) != 0){
            LOG_ERROR("error running function %s: %s", func, lua_tostring(L, -1));
        }
        lua_pop(L, lua_gettop(L));
    }
    return 0;
}

static int lcreate(lua_State *L){
    if (lua_gettop(L) == 0){
        int portfd = port_new();
        if(portfd > 0){
            port_set_raw(portfd);
            port_set_cb_packet(portfd, http_port_cb_packet);
            lua_pushnumber(L, portfd);
            return 1;
        }
    }
    lua_pushboolean(L, false);
    return 1;
}
static int lcontent_length_mode(lua_State *L){
	if (lua_isnumber(L, 1) && lua_isnumber(L, 2)){
        int linefd = (int)lua_tonumber(L, 1);
        int content_length = (int)lua_tonumber(L, 2);
        Line *line = line_from_fd(linefd);
        line->content_length = content_length;
        lua_pushboolean(L, true);
        return 1;
    }
    return 0;
}
static int lsplit_string(lua_State *L){
	if (lua_isstring(L, 1) && lua_isstring(L, 2)){
        size_t str_len = 0;
        const char *str = lua_tolstring(L, 1, &str_len);
        size_t sep_len = 0;
        const char *sep = lua_tolstring(L, 2, &sep_len);
        char *last_acc = (char *)str;
        char *acc = (char *)str;
        lua_newtable(L);
        int idx = 1;
        for(size_t i = 0; i < str_len; i++){
            if(strncmp(acc, sep, sep_len) == 0){
                char c = *acc;
                *acc = 0;
                if(last_acc != acc){
                    lua_pushnumber(L, idx++);
                    lua_pushlstring(L, last_acc, acc - last_acc);
                    lua_settable(L, -3);
                }
                *acc = c;
                last_acc = acc + sep_len;
            }
            acc++;
        }
        if(last_acc != acc){
            lua_pushnumber(L, idx++);
            lua_pushlstring(L, last_acc, acc - last_acc);
            lua_settable(L, -3);
        }
        return 1;
    }
    return 0;
}

static int ldecode_form_data(lua_State *L){
	if (lua_isstring(L, 1) && lua_isstring(L, 2)){
        size_t str_len = 0;
        const char *str = lua_tolstring(L, 1, &str_len);
        size_t sep_len = 0;
        const char *sep = lua_tolstring(L, 2, &sep_len);
        char *acc = (char *)str;
        char *last_acc = (char *)str;
        int mode = 0;
        int idx = 1;
        lua_newtable(L);
        for(size_t i = 0; i < str_len; i++){
            if(mode == 0){
                //寻找boundary
                if(strncmp(acc, sep, sep_len) == 0){
                    acc = acc + sep_len + 2;//\r\n长度是2
                    mode = 1;
                }
            }else if(mode == 1){
                //Content-Disposition: form-data; name="name"; filename="1212.png"
                if(strncmp(acc, "name=\"", 6) == 0){
                    acc += 6;
                    mode = 2;
                    last_acc = acc;
                }else{
                    acc++;
                }
            }
            else if(mode == 2){
                //Content-Disposition: form-data; name="name"; filename="1212.png"
                if(*acc == '\"'){
                    lua_pushnumber(L, idx++);
                    lua_newtable(L);

                    lua_pushstring(L, "name");
                    lua_pushlstring(L, last_acc, acc - last_acc);
                    lua_settable(L, -3);
                    mode = 3;
                 }
                 acc++;
            }
            else if(mode == 3){
                //Content-Disposition: form-data; name="name"; filename="1212.png"
                if(strncmp(acc, CRLF, 2) == 0){
                    acc += 2;
                    mode = 4;
                 }
                 else{
                    acc++;
                 }
            }else if(mode == 4){
                //Content-Type: image/png
                if(*acc == ':'){
                    acc += 2;
                    mode = 5;
                    last_acc = acc;
                }else{
                    acc++;
                }
            }else if(mode == 5){
                //Content-Type: image/png
                if(strncmp(acc, CRLF, 2) == 0){
                    lua_pushstring(L, "type");
                    lua_pushlstring(L, last_acc, acc - last_acc);
                    lua_settable(L, -3);
                    acc += 4;
                    mode = 6;
                    last_acc = acc;
                 }
                 else{
                    acc++;
                 }
            }else if(mode == 6){
                //寻找boundary
                if(strncmp(acc, sep, sep_len) == 0){
                    int size = acc - last_acc - 2;//\r\n
                    lua_pushstring(L, "size");
                    lua_pushnumber(L, size);
                    lua_settable(L, -3);
                    lua_pushstring(L, "body");
                    lua_pushlstring(L, last_acc, size);
                    lua_settable(L, -3);
                    acc = acc + sep_len;
                    mode = 2;
                    
                    //最外层的table
                    lua_settable(L, -3);
                }else{
                    acc++;
                }
            }else{
                acc++;
            }
        }
    }
    return 1;
}
static int ldecode_query_string(lua_State *L){
	if(lua_isstring(L, 1)){
        size_t str_len = 0;
        const char *str = (const char *)lua_tolstring(L, 1, &str_len);
        lua_newtable(L);
        int start = 0;
        int key = 0;
        for(size_t i = 0; i < str_len; i++){
            char c = str[i];
            if(c == '='){
                lua_pushlstring(L, str + start, i - start);
                start = i + 1;
                key = 1;
            }else if(c == '&'){
                lua_pushlstring(L, str + start, i - start);
                lua_settable(L, -3);
                start = i + 1;
                key = 0;
            }
        }
        if(key == 1){
            lua_pushlstring(L, str + start, str_len - start);
            lua_settable(L, -3);
        }
        return 1;
    }
    return 0;
}
static int lsend(lua_State *L){

	if (lua_isnumber(L, 1) && lua_isstring(L, 2)){
        int linefd = (int)lua_tonumber(L, 1);
        size_t str_len;
        char *str = (char *)lua_tolstring(L, 2, &str_len);
        Line *line = line_from_fd(linefd);
        int buffd = line->buf_write;

        char *buf = bbuf_alloc(buffd, str_len);
        if(buf == NULL){
            LOG_ERROR("alloc fail");
            return 0;
        }
        memcpy(buf, str, str_len);
        //加进socket的发送队列
        bbuf_append(buffd, buf, str_len);

        line_notify_writable(linefd);

        lua_pushboolean(L, true);
        return 1;
	}
    lua_pushboolean(L, false);
    return 1;
}

#define NON_NUM '0'

static int hex2num(char c){
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return NON_NUM;
}

static int urldecode(const char *str, const int str_len, char *result, const int result_len){
    char ch, ch1, ch2;
    int i;
    int j = 0;
    if ((str == NULL) || (result == NULL) || (str_len <= 0) || (result_len <= 0)) {
        return 0;
    }
    for (i = 0; i < str_len && j < result_len; ++i) {
        ch = str[i];
        switch (ch) {
            case '+':
                result[j++] = ' ';
                break;
            case '%':
                if (i + 2 < str_len) {
                    ch1 = hex2num(str[i + 1]);
                    ch2 = hex2num(str[i + 2]);
                    if ((ch1 != NON_NUM) && (ch2 != NON_NUM)) {
                        result[j++] = (char)((ch1 << 4) | ch2);
                    }
                    i += 2;
                    break;
                } else {
                    break;
                }
            default:
                result[j++] = ch;
                break;
        }
    }
    result[j] = 0;
    return j;
}
static int urlencode(const char *str, const int str_len, char *result, const int result_len){
    int i;
    int j = 0;
    char ch;

    if ((str == NULL) || (result == NULL) || (str_len <= 0) || (result_len <= 0)) {
        return 0;
    }
    for (i = 0; i < str_len && j < result_len; ++i) {
        ch = str[i];
        if (((ch >= 'A') && (ch < 'Z')) ||
            ((ch >= 'a') && (ch < 'z')) ||
            ((ch >= '0') && (ch < '9'))) {
                result[j++] = ch;
         } else if (ch == ' '){
            result[j++] = '+';
         } else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
            result[j++] = ch;
         } else {
            if (j + 3 < result_len) {
                sprintf(result + j, "%%%02X", (unsigned char)ch);
                j += 3;
            } else {
                return 0;
            }
         }
    }
    result[j] = '\0';
    return j;
}

static int lurldecode(lua_State *L){
	if(lua_isstring(L, 1)){
        size_t str_len = 0;
        const char *str = (const char *)lua_tolstring(L, 1, &str_len);
        char result[1024];
        int result_len = urldecode(str, str_len, result, 1024);
        lua_pushlstring(L, result, result_len);
        return 1;
    }
    return 0;
}

static int lurlencode(lua_State *L){
	if(lua_isstring(L, 1)){
        size_t str_len = 0;
        const char *str = (const char *)lua_tolstring(L, 1, &str_len);
        char result[1024];
        int result_len = urlencode(str, str_len, result, 1024);
        lua_pushlstring(L, result, result_len);
        return 1;
    }
    return 0;
}
static char s_cookie_key[64];
//Set-Cookie: sid=b418382051cf500f65dddac4674ae897; Domain=taocpp.com; Path=/; Expires=Wed, 30-Oct-2013 18:10:50 CST
static int lset_cookie_parse(lua_State *L){
	if(lua_isstring(L, 1)){
        size_t str_len = 0;
        const char *str = (const char *)lua_tolstring(L, 1, &str_len);
        int kstart = 0;
        int vstart = 0;
        int mode = 0;
        lua_newtable(L);
        for (size_t i = 0; i < str_len; i++){
            char c = str[i];
            if(mode == 0 && c == ':'){
                kstart = i + 1;
                mode = 1;
            }else if(mode == 2 && c == '='){
                vstart = i + 1;
                mode = 3;
            }else if(mode == 3 && (c == ';' || i == str_len - 1)){
                char *key = (char *)(str + kstart);
                int key_len = vstart - kstart - 1;
                if(key_len >= sizeof(s_cookie_key)){
                    return 1;
                }
                for(int k = 0; k < key_len; k++){
                    s_cookie_key[k] = tolower(key[k]);
                }
                s_cookie_key[key_len] = 0;
                char *val = (char *)str + vstart;
                int val_len = 0;
                if(c == ';'){
                    val_len = i - vstart;
                }else{
                    val_len = i - vstart + 1;
                }
                lua_pushlstring(L, s_cookie_key, key_len);
                lua_pushlstring(L, val, val_len);
                lua_settable(L, -3);

                if(strncmp(s_cookie_key, "expires", key_len) == 0){
                    struct tm tm;
                    char *s = val;
                    char oc = s[val_len];
                    s[val_len] = 0;
                    strptime(s, "%a, %d-%b-%Y %H:%m:%S %Z", &tm);
                    s[val_len] = oc;
                    time_t t = mktime(&tm);
                    lua_pushlstring(L, s_cookie_key, key_len);
                    lua_pushnumber(L, t);
                    lua_settable(L, -3);
                }
                if(strncmp(s_cookie_key, "expires", key_len) == 0 || strncmp(s_cookie_key, "domain", key_len) == 0 || strncmp(s_cookie_key, "path", key_len) == 0){
                }else{
                    lua_pushstring(L, "cookie");
                    if(c == ';'){
                        lua_pushlstring(L, str + kstart, i - kstart);
                    }else{
                        lua_pushlstring(L, str + kstart, i - kstart + 1);
                    }
                    lua_settable(L, -3);
                }
                mode = 1;
            }else if(mode == 1 && c != ' '){
                kstart = i;
                mode = 2;
            }
        }
        return 1;
    }
    return 0;
}

static int lkvparse(lua_State *L){
	if(lua_isstring(L, 1)){
        size_t str_len = 0;
        const char *str = (const char *)lua_tolstring(L, 1, &str_len);
        int kstart = 0;
        int vstart = 0;
        int mode = 1;
        lua_newtable(L);
        for (size_t i = 0; i < str_len; i++){
            char c = str[i];
            if(mode == 2 && c == '='){
                vstart = i + 1;
                mode = 3;
            }else if(mode == 3 && (c == ';' || i == str_len - 1)){
                char *key = (char *)(str + kstart);
                int key_len = vstart - kstart - 1;
                char *val = (char *)str + vstart;
                int val_len = 0;
                if(c == ';'){
                    val_len = i - vstart;
                }else{
                    val_len = i - vstart + 1;
                }
                lua_pushlstring(L, key, key_len);
                lua_pushlstring(L, val, val_len);
                lua_settable(L, -3);
                mode = 1;
            }else if(mode == 1 && c != ' '){
                kstart = i;
                mode = 2;
            }
        }
        return 1;
    }
    return 0;

}
// 0 [http://] 1 xxx 2 [:9090] 3 /xxxx 4 ?xxxx
static int lurlparse(lua_State *L){
	if(lua_isstring(L, 1)){
        size_t str_len = 0;
        const char *str = (const char *)lua_tolstring(L, 1, &str_len);
        lua_newtable(L);
        int start = 0;
        int mode = 0;
        for (size_t i = 0; i < str_len; i++) {
            char ch = str[i];
            if (ch == ':' && i + 2 < str_len && str[i + 1] == '/' && str[i + 2] == '/' && mode == 0) {
               lua_pushstring(L, "protocol");
               lua_pushlstring(L, str + start, i - start);
               lua_settable(L, -3);
               mode = 1;
               i += 3;
               start = i;
            }else if (i == str_len - 1 && mode <= 1) {
                lua_pushstring(L, "host");
                lua_pushlstring(L, str + start, i - start + 1);
                lua_settable(L, -3);
            }else if (ch == ':' && mode <= 1) {
                lua_pushstring(L, "host");
                lua_pushlstring(L, str + start, i - start);
                lua_settable(L, -3);
                start = i + 1;
                mode = 2;
            }else if (ch == '/' && mode <= 1) {
                lua_pushstring(L, "host");
                lua_pushlstring(L, str + start, i - start);
                lua_settable(L, -3);
                start = i;
                mode = 3;
            }else if (ch == '/' && mode <= 2) {
                lua_pushstring(L, "port");
                lua_pushlstring(L, str + start, i - start);
                lua_settable(L, -3);
                start = i;
                mode = 3;
            }else if (i == str_len - 1 && mode <= 2) {
                lua_pushstring(L, "port");
                lua_pushlstring(L, str + start, i - start + 1);
                lua_settable(L, -3);
            }else if (ch == '?' && mode == 3) {
                lua_pushstring(L, "path");
                lua_pushlstring(L, str + start, i - start);
                lua_settable(L, -3);
                start = i + 1;
                mode = 4;
            }else if (i == str_len - 1 && mode == 3) {
                lua_pushstring(L, "path");
                lua_pushlstring(L, str + start, i - start + 1);
                lua_settable(L, -3);
                start = i + 1;
                mode = 4;
            }else if (i == str_len - 1 && mode == 4) {
                lua_pushstring(L, "query_string");
                lua_pushlstring(L, str + start, i - start + 1);
                lua_settable(L, -3);
            }
        }
    }
    return 1;
}
static luaL_Reg lua_lib[] = {
    {"create", lcreate},
    {"send", lsend},
    {"content_length_mode", lcontent_length_mode},
    {"decode_query_string", ldecode_query_string},
    {"split_string", lsplit_string},
    {"decode_form_data", ldecode_form_data},
    {"urldecode", lurldecode},
    {"urlencode", lurlencode},
    {"urlparse", lurlparse},
    {"kvparse", lkvparse},
    {"set_cookie_parse", lset_cookie_parse},
    {NULL, NULL}
};

int luaopen_http_port(lua_State *L){
    luaL_register(L, "HttpPort", lua_lib);
    return 0;
}

