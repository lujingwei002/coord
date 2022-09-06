#pragma once 

#include "coord/coordx.h"
#include "coord/base/base_request.h"
#include "coord/cluster/cluster_message.h"
#include "coord/cluster/cluster_response.h"


namespace coord {//tolua_export
class Coord;


namespace cluster {//tolua_export

class cluster_agent;
class Cluster;

class Request : public base_request  { //tolua_export
RC_CLASS(Request);
public:
    Request(Coord* coord, cluster_agent* agent);
    virtual ~Request();
public:
    virtual Response* GetResponse();//tolua_export   
public:
    virtual void onDestory();
};//tolua_export

Request* newRequest(Coord* coord, cluster_agent* agent);

}//tolua_export
}//tolua_export


