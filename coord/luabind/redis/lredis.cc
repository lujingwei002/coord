#include "redis/lredis.h"
#include "log/log.h"
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

static void getCallback_push_reply(lua_State *L, redisReply *reply)
{
    unsigned int i;
    lua_newtable(L);

    lua_pushstring(L, "type");
    if(reply->type == REDIS_REPLY_NIL)
    {
        lua_pushstring(L, "null");
    }else if(reply->type == REDIS_REPLY_INTEGER)
    {
        lua_pushstring(L, "integer");
    }else if(reply->type == REDIS_REPLY_STRING)
    {
        lua_pushstring(L, "string");
    }else if(reply->type == REDIS_REPLY_ERROR)
    {
        lua_pushstring(L, "error");
    }else if(reply->type == REDIS_REPLY_STATUS)
    {
        lua_pushstring(L, "status");
    }else if(reply->type == REDIS_REPLY_ARRAY)
    {
        lua_pushstring(L, "array");
    }

    lua_settable(L, -3);

    lua_pushstring(L, "value");
    if (reply->type == REDIS_REPLY_NIL) 
    {
        lua_pushnil(L);
    }else if (reply->type == REDIS_REPLY_INTEGER) 
    {
        lua_pushnumber(L, reply->integer);
    }else if (reply->type == REDIS_REPLY_STRING) 
    {
        lua_pushlstring(L, reply->str, reply->len);
    }else if (reply->type == REDIS_REPLY_ERROR) 
    {
        lua_pushstring(L, reply->str);
    }else if (reply->type == REDIS_REPLY_STATUS) 
    {
        lua_pushstring(L, reply->str);
    }else if (reply->type == REDIS_REPLY_ARRAY) 
    {
        lua_newtable(L);
        redisReply **elements = reply->element;
        for(i = 0; i < reply->elements; i++)
        {
           redisReply *reply = elements[i];
           lua_pushnumber(L, i + 1);
           getCallback_push_reply(L, reply);
           lua_settable(L, -3);
        }  
    }
    lua_settable(L, -3);
} 

static int lconnect(lua_State *L)
{
    if(lua_gettop(L) == 2 && lua_isstring(L, 1) && lua_isnumber(L, 2))
    {
        const char *ip = (const char *)lua_tostring(L, 1);
        unsigned short port = (unsigned short)lua_tonumber(L, 2);
        redisContext *c = redisConnect(ip, port);
        if(c == NULL)
        {
            LOG_ERROR("connect error");
            return 0;
        }
        if(!(c->flags & REDIS_CONNECTED))
        {
            redisFree(c);
            LOG_ERROR("connect error");
            return 0;
        }
        lua_pushlightuserdata(L, c);
        return 1;
    }
    return 0;
}

static int lclose(lua_State *L){
    if (lua_gettop(L) == 1 && lua_isuserdata(L, 1)) {
        struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
        redisFree(c);
        return 0;
    }
    return 0;
}

static int lzrevrank(lua_State *L){
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L, 3)) {
        LOG_ERROR("arg error");
        return 0;
    }
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    const char *key = (const char *)lua_tostring(L, 2);

    size_t str_len;
    const char *value = (const char *)lua_tolstring(L, 3, &str_len);
    if(value == NULL){
        LOG_ERROR("value fail");
        return 0;
    }
    redisReply * reply = (redisReply *)redisCommand(c, "ZREVRANK %s %b", key, value, str_len);
    if(reply == NULL){
        LOG_ERROR("Set:redisCommand fail key:%s value:%s", key, value);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}


static int lzrem(lua_State *L){
   
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L, 3)) {
        LOG_ERROR("arg error");
        return 0;
    }
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    const char *key = (const char *)lua_tostring(L, 2);


    size_t str_len;
    const char *value = (const char *)lua_tolstring(L, 3, &str_len);
    if(value == NULL){
        LOG_ERROR("value fail");
        return 0;
    }
    redisReply * reply = (redisReply *)redisCommand(c, "ZREM %s %b", key, value, str_len);
    if(reply == NULL){
        LOG_ERROR("Set:redisCommand fail key:%s value:%s", key, value);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}


static int lzrank(lua_State *L){
   
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L, 3)) {
        LOG_ERROR("arg error");
        return 0;
    }
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    const char *key = (const char *)lua_tostring(L, 2);


    size_t str_len;
    const char *value = (const char *)lua_tolstring(L, 3, &str_len);
    if(value == NULL){
        LOG_ERROR("value fail");
        return 0;
    }
    redisReply * reply = (redisReply *)redisCommand(c, "ZRANK %s %b", key, value, str_len);
    if(reply == NULL){
        LOG_ERROR("Set:redisCommand fail key:%s value:%s", key, value);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}


static int lzadd(lua_State *L){
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2) || !lua_isnumber(L ,3) || !lua_isstring(L, 4)) {
        LOG_ERROR("arg error");
        return 0;
    }
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    const char *key = (const char *)lua_tostring(L, 2);

    float score = (float)lua_tonumber(L, 3);

    size_t str_len;
    const char *value = (const char *)lua_tolstring(L, 4, &str_len);
    if(value == NULL){
        LOG_ERROR("value fail");
        return 0;
    }
    redisReply * reply = (redisReply *)redisCommand(c, "ZADD %s %f %b", key, score, value, str_len);
    if(reply == NULL){
        LOG_ERROR("Set:redisCommand fail key:%s value:%s", key, value);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}

static int lset(lua_State *L){
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L ,3)) {
        LOG_ERROR("arg error");
        return 0;
    }
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    const char *key = (const char *)lua_tostring(L, 2);
    size_t str_len;
    const char *value = (const char *)lua_tolstring(L, 3, &str_len);
    if(value == NULL){
        LOG_ERROR("value fail");
        return 0;
    }
    redisReply * reply = (redisReply *)redisCommand(c, "set %s %b", key, value, str_len);
    if(reply == NULL){
        LOG_ERROR("Set:redisCommand fail key:%s value:%s", key, value);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}

static int llpush(lua_State *L){
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L ,3)) {
        LOG_ERROR("arg error");
        return 0;
    }
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if (c == NULL) {
        LOG_ERROR("userdata is null");
        return 0;
    }
    const char *key = (const char *)lua_tostring(L, 2);
    size_t str_len;
    const char *str = (const char *)lua_tolstring(L, 3, &str_len);
    redisReply * reply = (redisReply *)redisCommand(c, "LPUSH %s %b", key, str, str_len);
    if (reply == NULL) {
        LOG_ERROR("lpush fail key:%s value:%s", key, str);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}


static int lhset(lua_State *L)
{
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L ,3) || !lua_isstring(L ,4)) {
        LOG_ERROR("arg error");
        return 0;
    }
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if (c == NULL) {
        LOG_ERROR("userdata is null");
        return 0;
    }
    const char *table = (const char *)lua_tostring(L, 2);
    const char *key = (const char *)lua_tostring(L, 3);
    const char *value = (const char *)lua_tostring(L, 4);
    redisReply * reply = (redisReply *)redisCommand(c, "hset %s %s %s", table, key, value);
    if (reply == NULL) {
        LOG_ERROR("hset fail table:%s key:%s value:%s", table, key, value);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}

static char **redis_argv;
static size_t *redis_argvlen;
static int redis_argc;
static char s_hmset_cmd[] = "HMSET";
static char s_mset_cmd[] = "MSET";

static int lmset(lua_State *L){
    int i;
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    int argc = lua_gettop(L);
    if(redis_argc < argc){
        if(redis_argv != NULL){
            redis_argc = 0;
            free(redis_argv);
        }
        if(redis_argvlen != NULL){
            redis_argc = 0;
            free(redis_argvlen);
        }
        redis_argv = (char **)malloc(argc * sizeof(char *));
        redis_argvlen = (size_t *)malloc(argc * sizeof(size_t));
        if(!redis_argv || !redis_argvlen){
            redis_argv = 0;
            if(redis_argv)free(redis_argv);
            if(redis_argvlen)free(redis_argvlen);
            LOG_ERROR("malloc fail");
            return 0;
        }
        redis_argc = argc;
    }
    redis_argv[0] = s_mset_cmd;
    redis_argvlen[0] = 4;
    for(i = 0; i < (argc - 1)/2; i++){
        size_t k_len = 0;
        size_t v_len = 0;
        const char *k = (const char *)lua_tolstring(L, (i*2) + 2, &k_len);
        const char *v = (const char *)lua_tolstring(L, (i*2) + 3, &v_len);
        redis_argv[(2*i)+1] = (char *)k;
        redis_argvlen[(2*i)+1] = k_len;
        redis_argv[(2*i)+2] = (char *)v;
        redis_argvlen[(2*i)+2] = v_len;
    }
    redisReply * reply = (redisReply *)redisCommandArgv(c, argc, (const char **)redis_argv, redis_argvlen);
    if(reply == NULL){
        LOG_ERROR("MSET FAIL");
        return 0;
    }

    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}

static int lhmset(lua_State *L){
    int i;
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    int argc = lua_gettop(L);
    if(argc % 2 != 0){
        LOG_ERROR("expect even but %d", argc);
        return 0;
    }
    if(redis_argc < argc){
        if(redis_argv != NULL){
            redis_argc = 0;
            free(redis_argv);
        }
        if(redis_argvlen != NULL){
            redis_argc = 0;
            free(redis_argvlen);
        }
        redis_argv = (char **)malloc(argc * sizeof(char *));
        redis_argvlen = (size_t *)malloc(argc * sizeof(size_t));
        if(!redis_argv || !redis_argvlen){
            redis_argv = 0;
            if(redis_argv)free(redis_argv);
            if(redis_argvlen)free(redis_argvlen);
            LOG_ERROR("malloc fail");
            return 0;
        }
        redis_argc = argc;
    }
    size_t key_len;
    const char *key = (const char *)lua_tolstring(L, 2, &key_len);
    if(key == NULL){
        LOG_ERROR("tolstring FAIL");
        return 0;
    }
    redis_argv[0] = s_hmset_cmd;
    redis_argvlen[0] = 5;
    redis_argv[1] = (char *)key;
    redis_argvlen[1] = key_len;

    for(i = 0; i < (argc - 1)/2; i++){
        size_t k_len = 0;
        size_t v_len = 0;
        const char *k = (const char *)lua_tolstring(L, (i * 2) + 3, &k_len);
        const char *v = (const char *)lua_tolstring(L, (i * 2) + 4, &v_len);
        redis_argv[2*i + 2] = (char *)k;
        redis_argvlen[2*i + 2] = k_len;
        redis_argv[2*i + 3] = (char *)v;
        redis_argvlen[2*i + 3] = v_len;
    }
    redisReply * reply = (redisReply *)redisCommandArgv(c, argc, (const char **)redis_argv, redis_argvlen);
    if(reply == NULL){
        LOG_ERROR("MSET FAIL");
        return 0;
    }

    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}

static int ltest(lua_State *L) {
    printf("test ok!!\n");
    return 0;
}

static int lcommand(lua_State *L) {
    if (!lua_isuserdata(L, 1) || !lua_isstring(L, 2)) {
        LOG_ERROR("arg error");
        return 0;
    }
    size_t str_len = 0;
    struct redisContext *c = (struct redisContext *)lua_touserdata(L, 1);
    const char *command = (const char *)lua_tolstring(L, 2, &str_len);
    if(c == NULL){
        LOG_ERROR("userdata is null");
        return 0;
    }
    redisReply * reply = (redisReply *)redisCommand(c, command);
    if(reply == NULL){
        LOG_ERROR("Command:redisCommand fail command:%s", command);
        return 0;
    }
    getCallback_push_reply(L, reply);
    freeReplyObject(reply);
    return 1;
}

static luaL_Reg lua_lib[] = {
    {"connect", lconnect},
    {"command", lcommand},
    {"mset", lmset},
    {"hmset", lhmset},
    {"set", lset},
    {"zadd", lzadd},
    {"zrank", lzrank},
    {"zrevrank", lzrevrank},
    {"zrem", lzrem},
    {"hset", lhset},
    {"lpush", llpush},
    {"close", lclose},
    {"test", ltest},
    {NULL, NULL}
};

int luaopen_redis(lua_State *L){
	luaL_register(L, "Redis", (luaL_Reg*)lua_lib);
    return 1;
}

