#pragma once 


#include "coord/base/base_notify.h"
#include "coord/protobuf/declare.h"
namespace coord {//tolua_export
class Coord;


namespace worker {//tolua_export
class Worker;
class Response;
class Result;

class Notify : public base_notify { //tolua_export
CC_CLASS(Notify);
public:
    Notify(Coord* coord);
    virtual ~Notify();   
    virtual void onDestory();
public:
};//tolua_export

Notify* newNotify(Coord* coord);


}//tolua_export


}//tolua_export
