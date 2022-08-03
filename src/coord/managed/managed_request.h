#pragma once 

#include "coord/base/base_request.h"
#include "coord/managed/managed_response.h"

//declaration
namespace coord {
    class Coord;
    namespace managed {
        class managed_server;
        class ManagedAgent;
        class ManagedResponse;
    }
}


namespace coord {//tolua_export
namespace managed {//tolua_export

class ManagedRequest : public base_request { //tolua_export
CC_CLASS(ManagedRequest);
friend ManagedAgent;
private:
    ManagedRequest(Coord* coord, ManagedAgent* agent);
    virtual ~ManagedRequest();
public:
    virtual ManagedResponse* GetResponse();
};//tolua_export

}//tolua_export
}//tolua_export


