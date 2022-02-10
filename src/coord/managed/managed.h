#pragma once 

#include "coord/builtin/type.h"
#include "coord/protobuf/init.h"
#include "coord/managed/managed_config.h"
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>
namespace coord {//tolua_export
    
class Coord;

namespace managed {//tolua_export

class ManagedServer;



class Managed {//tolua_export
CC_CLASS(Managed);
public:
    Managed(Coord *coord);
    virtual ~Managed();
public:
    int start();
    //获取cluser的配置信息
    ManagedConfig* DefaultConfig();
public:

public:
    Coord*          coord;
    ManagedConfig     config;
    ManagedServer*    server;
};//tolua_export

Managed* newManaged(Coord* coord);
}//tolua_export
}//tolua_export


