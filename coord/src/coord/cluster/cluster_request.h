#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/base_request.h"
#include "coord/cluster/cluster_message.h"


namespace coord {//tolua_export
class Coord;


namespace cluster {//tolua_export

class cluster_agent;
class Cluster;
class Response;

class Request : public BaseRequest  { //tolua_export
CC_CLASS(Request);
public:
    Request(Coord* coord, cluster_agent* agent);
    virtual ~Request();
public:
    Response* GetResponse();//tolua_export   
public:
    virtual void onDestory();
public:
    cluster_agent*      agent; 
    Response*           response;
};//tolua_export

Request* newRequest(Coord* coord, cluster_agent* agent);

}//tolua_export
}//tolua_export


