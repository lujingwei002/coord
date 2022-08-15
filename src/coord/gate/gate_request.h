#pragma once 

#include "coord/coordx.h"
#include "coord/base/base_request.h"
#include "coord/gate/gate_response.h"
#include "coord/protobuf/declare.h"
namespace coord {//tolua_export
class Coord;



namespace gate {//tolua_export

class GateAgent;
class Gate;
class GateSession;

class GateRequest : public base_request  { //tolua_export
CC_CLASS(GateRequest);
public:
    GateRequest(Coord* coord, GateAgent* agent);
    virtual ~GateRequest();
public:
    void Kick(const char* reason); //tolua_export    
    GateSession* GetSession();//tolua_export
    virtual GateResponse* GetResponse();
protected:
    //virtual void onDestory();
protected:
    GateAgent*      agent; 
};//tolua_export

GateRequest* newGateRequest(Coord* coord, GateAgent* agent);

}//tolua_export
}//tolua_export


