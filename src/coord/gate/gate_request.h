#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/base_request.h"

namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}

namespace gate {//tolua_export

class GateAgent;
class Gate;
class GateResponse;
class GateSession;
class GateRequest : public BaseRequest  { //tolua_export
CC_CLASS(GateRequest);
public:
    GateRequest(Coord* coord, GateAgent* agent);
    virtual ~GateRequest();
public:
    GateResponse* GetResponse();//tolua_export    
    void Kick(const char* reason); //tolua_export    
    GateSession* GetSession();//tolua_export
public:
    virtual void onDestory();
public:
    GateAgent*      agent; 
    GateResponse*   response;
    uint64_t        sessionId;//tolua_export
};//tolua_export

GateRequest* newGateRequest(Coord* coord, GateAgent* agent);

}//tolua_export
}//tolua_export


