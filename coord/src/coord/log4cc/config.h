#pragma once 

#include "coord/log4cc/layout.h"
#include "coord/log4cc/priority.h"

#include <map>
#include <vector>

namespace coord { //tolua_export
namespace log4cc { //tolua_export

class LoggerConfig { //tolua_export
public:
    LoggerConfig();
public:
    std::string                 Name;       //tolua_export
    std::string                 Layout;     //tolua_export
    uint32_t                    MaxByte;    //tolua_export
    uint32_t                    MaxLine;    //tolua_export
    PriorityLevel               Priority;
    bool                        Console;
    std::string                 File;       //tolua_export

};//tolua_export

}//tolua_export
}//tolua_export

