#pragma once 

#include "coord/builtin/type.h"
#include "coord/base/base_result.h"

namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}

namespace worker {//tolua_export
class Worker;
class Request;

class Result : public base_result  { //tolua_export
CC_CLASS(Result);
public:
    Result(Coord* coord);
    virtual ~Result();
public:
public:
    Request*  request;
};//tolua_export

Result* newResult(Coord* coord);


}//tolua_export
}//tolua_export
