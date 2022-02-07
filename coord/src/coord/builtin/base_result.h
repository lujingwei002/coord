
#pragma once 
#include "coord/builtin/base_request.h"




namespace coord {//tolua_export

class Coord;

class BaseResult : public BaseRequest { //tolua_export
public:
    BaseResult(Coord* coord);
    virtual ~BaseResult();
public:
    int         Code;   //tolua_export  
};//tolua_export

}//tolua_export