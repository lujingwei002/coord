#pragma once 

#include "coord/builtin/type.h"
#include "coord/base/base_notify.h"
#include "coord/cluster/cluster_message.h"


namespace coord {//tolua_export

class Coord;

namespace cluster {//tolua_export

class cluster_agent; 
class Cluster;

class GateNotify : public base_notify { //tolua_export
CC_CLASS(GateNotify);
public:
    GateNotify(Coord* coord, cluster_agent* agent);
    virtual ~GateNotify();
public:
    virtual void onDestory(); 
public:
    cluster_agent* agent; 
};//tolua_export

GateNotify* newNotify(Coord* coord, cluster_agent* agent);

}//tolua_export
}//tolua_export


