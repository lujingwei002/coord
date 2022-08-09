#pragma once 

#include "coord/base/base_request.h"
#include "coord/worker/worker_response.h"

#include "coord/worker/declare.h"
#include "coord/protobuf/declare.h"

namespace coord {
class Coord;
}

namespace coord {//tolua_export
namespace worker {//tolua_export

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
