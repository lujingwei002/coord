#pragma once 

#include "coord/builtin/type.h"
#include "coord/base/base_request.h"
#include "coord/worker/worker_response.h"

namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}
namespace worker {//tolua_export
class Worker;
class Result;

class Request : public base_request  { //tolua_export
CC_CLASS(Request);
public:
    Request(Coord* coord);
    virtual ~Request();
public:
    virtual Response* GetResponse();//tolua_export   
    virtual void onDestory();
public:
    Response* response;
};//tolua_export

Request* newRequest(Coord* coord);


}//tolua_export


}//tolua_export
