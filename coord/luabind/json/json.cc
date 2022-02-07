#include "json/json.h"
#include "json/cJSON.h"
#include "log/log.h"


namespace Json 
{

static int is_digit(char str)
{
    if(str >= 48 && str <= 57)
    {
        return 1;
    }
    return 0;
}

static cJSON* json_encode_tree(lua_State *L);
static void json_decode_tree(lua_State* L, cJSON *json);

char *encode(lua_State *L)
{
    cJSON *json = json_encode_tree(L);
    if(json == NULL)
    {
        LOG_INFO("null");
        return NULL;
    }
    char *str = cJSON_Print(json);
    cJSON_Delete(json);
    return str;
}

int decode(lua_State* L, char *str)
{
    cJSON *json = cJSON_Parse(str);
    if(json == NULL)
    {
        LOG_INFO("null");
        return 0;
    }
    json_decode_tree(L, json);
    cJSON_Delete(json);
    return 1;
}

static cJSON* json_encode_tree(lua_State *L)
{
    int type = lua_type(L, -1);
    if(type == LUA_TNIL)
    {
        cJSON *json = cJSON_CreateNull();
        return json;
    }else if(type == LUA_TBOOLEAN)
    {
        int b = lua_toboolean(L, -1);
        cJSON* json = cJSON_CreateBool(b);
        return json;
    }else if(type == LUA_TNUMBER)
    {
        double num = lua_tonumber(L, -1);
        cJSON* json = cJSON_CreateNumber(num);
        return json;
    }else if(type == LUA_TSTRING)
    {
        size_t str_len;
        const char *string = lua_tolstring(L, -1, &str_len);
        cJSON* json = cJSON_CreateString(string);
        return json;
    }else if(type == LUA_TTABLE)
    {
        cJSON *json = cJSON_CreateObject();
        if(json == NULL)
        {
            LOG_INFO("null");
            return NULL;
        }
        lua_pushnil(L);
        while(lua_next(L, -2) != 0)
        {
            if(lua_type(L, -2) == LUA_TSTRING)
            {
                size_t str_len = 0;
                const char *k = lua_tolstring(L, -2, &str_len);
                cJSON *cjson = json_encode_tree(L);
                if(cjson == NULL)
                {
                    LOG_INFO("null");
                    break;
                }
                cJSON_AddItemToObject(json, k, cjson);
            }else if(lua_type(L, -2) == LUA_TNUMBER)
            {
                int k = (int)lua_tonumber(L, -2);
                cJSON *cjson = json_encode_tree(L);
                if(cjson == NULL)
                {
                    LOG_INFO("null");
                    break;
                }
                char kname[32];
                sprintf(kname, "%d", k);
                cJSON_AddItemToObject(json, kname, cjson);
            }
            lua_pop(L, 1);
        }
        return json;
    }
    LOG_ERROR("unspport type\n");
    return NULL;
}

static void json_decode_tree(lua_State* L, cJSON* json)
{
    int i;
    if(json == NULL)
    {
        lua_pushnil(L);
    }
    if(json->type == cJSON_Number)
    {
        if(json->valuedouble != 0)
        {
            lua_pushnumber(L, json->valuedouble);
        }else
        {
            lua_pushnumber(L, json->valueint);
        }
    }else if(json->type == cJSON_String)
    {
        lua_pushstring(L, json->valuestring);
    }else if(json->type == cJSON_NULL)
    {
        lua_pushnil(L);
    }else if(json->type == cJSON_True)
    {
        lua_pushboolean(L, 1);
    
    }else if(json->type == cJSON_False){
        lua_pushboolean(L, 0);
    }else if(json->type == cJSON_Array)
    {//cJSON_Array
        lua_newtable(L);
        int size = cJSON_GetArraySize(json);
        for(i = 0; i < size; i++)
        {
            lua_pushnumber(L, i + 1);
            cJSON *cjson = cJSON_GetArrayItem(json, i);
            json_decode_tree(L, cjson);
            lua_settable(L, -3);
        }
    }else if(json->type == cJSON_Object)
    {//cJSON_Object
        lua_newtable(L);
        int size = cJSON_GetArraySize(json);
        for(i = 0; i < size; i++)
        {
            cJSON *cjson = cJSON_GetArrayItem(json, i);
            if(is_digit(cjson->string[0]))
            {
                int intval = atoi(cjson->string);
                lua_pushinteger(L, intval);
            }else
            {
                lua_pushstring(L, cjson->string);
            }
            json_decode_tree(L, cjson);
            lua_settable(L, -3);
        }
    }
}


};
