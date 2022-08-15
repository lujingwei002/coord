#pragma once 

#include "coord/coordx.h"
#include "coord/base/internal_response.h"
#include "coord/protobuf/declare.h"

namespace coord {//tolua_export
class Coord;



namespace gate {//tolua_export

class GateAgent;
class Gate;
class GateRequest;

class GateResponse : public internal_response { //tolua_export
CC_CLASS(GateResponse);
public:
    GateResponse(Coord* coord, GateAgent* agent, GateRequest* request);
    virtual ~GateResponse();
public:
    virtual int flush();
public:
    GateRequest*    request;
};//tolua_export


}//tolua_export
}//tolua_export


