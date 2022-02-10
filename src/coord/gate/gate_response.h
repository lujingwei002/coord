#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/base_response.h"

namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}

namespace gate {//tolua_export

class GateAgent;
class Gate;
class GateRequest;

class GateResponse : BaseResponse { //tolua_export
CC_CLASS(GateResponse);
public:
    GateResponse(Coord* coord, GateRequest* request);
    virtual ~GateResponse();
public:
    virtual int flush();
public:
    GateRequest* request;
};//tolua_export

GateResponse* newGateResponse(Coord* coord, GateRequest* request);

}//tolua_export
}//tolua_export


