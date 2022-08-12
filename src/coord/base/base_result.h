
#pragma once 
#include "coord/base/base_reader.h"

namespace coord {//tolua_export

class Coord;

class base_result : public RcObject, public base_reader { //tolua_export
public:
    base_result(Coord* coord);
    virtual ~base_result();
public:
    virtual void onDestory(); 
public:
    int             Code;   //tolua_export  
    uint64_t        Id;
    std::string     Route;
    uint64_t        ReqTime; 
protected:
};//tolua_export

}//tolua_export
