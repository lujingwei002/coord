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

class Request : public BaseRequest  { //tolua_export
CC_CLASS(Request);
public:
    Request(Coord* coord);
    virtual ~Request();
public:
    Response* GetResponse();//tolua_export   
    virtual void onDestory();
public:
    Response* response;
};//tolua_export

Request* newRequest(Coord* coord);


}//tolua_export


}//tolua_export
