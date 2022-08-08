#pragma once 

#include "coord/builtin/type.h"
#include "coord/base/internal_response.h"
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

class Response : public internal_response { //tolua_export
CC_CLASS(Response);
public:
    Response(Coord* coord, cluster_agent* agent, Request* request);
    virtual ~Response();
public:
    //virtual int flush();
public:
};//tolua_export


}//tolua_export
}//tolua_export


