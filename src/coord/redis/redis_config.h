#pragma once 

#include "coord/builtin/type.h"
#include <stdint.h>

namespace coord {//tolua_export
    
class Coord;

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

}//tolua_export
}//tolua_export


