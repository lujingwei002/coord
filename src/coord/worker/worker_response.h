#pragma once 


#include "coord/base/internal_response.h"
#include "coord/protobuf/declare.h"
namespace coord {//tolua_export
class Coord;


namespace worker {//tolua_export
class Worker;
class Request;

class Response : public internal_response { //tolua_export
CC_CLASS(Response);
public:
    Response(Coord* coord, Request* request);
    virtual ~Response();
public:
    Request*  request;
};//tolua_export

Response* newResponse(Coord* coord, Request* request);


}//tolua_export
}//tolua_export

