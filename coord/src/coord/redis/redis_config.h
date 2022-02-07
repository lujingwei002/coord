#pragma once 

#include "coord/builtin/type.h"
#include <stdint.h>

namespace coord {//tolua_export
    
class Coord;

namespace redis {//tolua_export

class RedisConfig {//tolua_export
public:
    std::string     Password;       //tolua_export
    std::string     DB;             //tolua_export
    std::string     Host;           //tolua_export
    uint16_t        Port;           //tolua_export
};//tolua_export

}//tolua_export
}//tolua_export


