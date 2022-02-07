#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/base_request.h"

namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}
namespace worker {//tolua_export
class Worker;
class Response;
class Result;

class Notify : public BaseRequest  { //tolua_export
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
