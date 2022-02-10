#ifndef __LUA_CJSON__
#define __LUA_CJSON__

extern "C" {
int cjson_decode(lua_State *l, void* ctx, const char* data, size_t json_len);
const char* cjson_encode(lua_State *l, void* ctx, int lindex, size_t* json_len);

void* cjson_new(lua_State *l);
int cjson_destroy(void *ctx);
const char* cjson_error(lua_State *l, void *ctx);

int json_cfg_decode_invalid_numbers(lua_State *l, void *ctx, int decode_invalid_numbers);
int json_cfg_encode_invalid_numbers(lua_State *l, void *ctx, int encode_invalid_numbers);
int json_cfg_encode_keep_buffer(lua_State *l, void *ctx, int encode_keep_buffer);
int json_cfg_encode_number_precision(lua_State *l, void *ctx, int encode_number_precision);
int json_cfg_decode_max_depth(lua_State *l, void *ctx, int decode_max_depth);
int json_cfg_encode_max_depth(lua_State *l, void *ctx, int encode_max_depth);
int json_cfg_encode_sparse_array(lua_State *l, void *ctx, int encode_sparse_convert, int encode_sparse_ratio, int encode_sparse_safe);
}
#endif
