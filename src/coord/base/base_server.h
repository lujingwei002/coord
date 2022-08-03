#pragma once 

#include "coord/builtin/type.h"
#include "coord/net/tcp_listener.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;


class base_server {//tolua_export
public:
    base_server(Coord *coord);
    virtual ~base_server();
public:
    Coord*                          coord;
};//tolua_export

}//tolua_export


