#pragma once 

#include "coord/coordx.h"
#include "coord/coordx.h"
#include <uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export
class Coord;
namespace event {//tolua_export

class BaseEvent  {//tolua_export
CC_CLASS(BaseEvent);
public:
    BaseEvent(const char* name, const char* arg);
    virtual ~BaseEvent();
public:
    Coord*          coord;
    std::string     name;   //tolua_export
    std::string     arg;    //tolua_export
};//tolua_export

}//tolua_export
}//tolua_export


