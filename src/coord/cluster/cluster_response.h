#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/base_response.h"
#include "coord/cluster/cluster_message.h"


namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}

namespace cluster {//tolua_export

class cluster_agent;
class Cluster;
class Request;

class Response : public BaseResponse { //tolua_export
CC_CLASS(Response);
public:
    Response(Coord* coord, Request* request);
    virtual ~Response();
public:
    virtual int flush();
public:
    Request* request;
};//tolua_export

Response* newResponse(Coord* coord, Request* request);

}//tolua_export
}//tolua_export


