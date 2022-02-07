#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/base_request.h"
#include "coord/cluster/cluster_message.h"


namespace coord {//tolua_export

class Coord;

namespace cluster {//tolua_export

class cluster_agent; 
class Cluster;

class Notify : public BaseRequest { //tolua_export
CC_CLASS(Notify);
public:
    Notify(Coord* coord, cluster_agent* agent);
    virtual ~Notify();
public:
    virtual void onDestory(); 
public:
    cluster_agent* agent; 
};//tolua_export

Notify* newNotify(Coord* coord, cluster_agent* agent);

}//tolua_export
}//tolua_export


