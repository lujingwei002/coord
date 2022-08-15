#pragma once 

#include "coord/coordx.h"
#include "coord/base/base_notify.h"
#include "coord/protobuf/declare.h"

namespace coord {//tolua_export
class Coord;


namespace gate {//tolua_export

class GateAgent; 
class Gate;
class GateResponse;

class GateNotify : public base_notify { //tolua_export
CC_CLASS(GateNotify);
public:
    GateNotify(Coord* coord, GateAgent* agent);
    virtual ~GateNotify();
public:
    virtual void onDestory(); 
public:
    GateAgent*   agent; 
    uint64_t    sessionId;//tolua_export
};//tolua_export

GateNotify* newGateNotify(Coord* coord, GateAgent* agent);

}//tolua_export
}//tolua_export


