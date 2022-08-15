#pragma once 

#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
#include <hiredis/hiredis.h>
#include <hiredis/async.h>

namespace coord {//tolua_export
    
    namespace redis {//tolua_export

        class RedisConfig {//tolua_export
            public:
                /// 密码
                std::string     Password;       //tolua_export
                /// db
                std::string     DB;             //tolua_export
                /// 地址
                std::string     Host;           //tolua_export
                /// 端口
                uint16_t        Port;           //tolua_export
        };//tolua_export

        class RedisMgr;
        class Client;
        class AsyncClient;
        class RedisPromise;
        class RedisResult;
        typedef coordx::RcRef<coord::redis::RedisResult> RedisResultRef;//tolua_export
    }//tolua_export

} //tolua_export
