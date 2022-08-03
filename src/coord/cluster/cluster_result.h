#pragma once 

#include "coord/builtin/type.h"
#include "coord/base/base_result.h"
#include "coord/cluster/cluster_message.h"


namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}

namespace cluster {//tolua_export

class Cluster;
class Request;
class cluster_client;

class Result : public base_result  { //tolua_export
CC_CLASS(Result);
public:
    Result(Coord* coord, cluster_client* client);
    virtual ~Result();
public:
    virtual void onDestory(); 

public:
    cluster_client*  client;  
};//tolua_export

Result* newResult(Coord* coord, cluster_client* client);

}//tolua_export
}//tolua_export


