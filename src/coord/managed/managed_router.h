#pragma once 

#include "coord/coordx.h"
#include "coord/base/base_router.h"
#include "coord/managed/managed_response.h"
#include "coord/managed/managed_request.h"
#include <vector>
#include <iostream>
#include <map>

//declaration
namespace coord {
    class Coord;
    namespace managed {
        class Managed;
        class ManagedRequest;
        class ManagedNotify;
    }
}

namespace coord {//tolua_export
namespace managed {//tolua_export

class ManagedRouter : public base_router<ManagedRequest, ManagedNotify, ManagedResponse> { //tolua_export
RC_CLASS(ManagedRouter);
friend managed::Managed;
private:
    ManagedRouter(Coord *coord, Managed* managed);
    virtual ~ManagedRouter();
private:
    Managed* managed;
};//tolua_export

}//tolua_export
}//tolua_export


