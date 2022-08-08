#pragma once 

#include "coord/base/internal_response.h"

//declaration
namespace coord {
    class Coord;
    namespace managed {
        class ManagedRequest;
        class ManagedAgent;
}
}

namespace coord {//tolua_export
namespace managed {//tolua_export

class ManagedResponse : public internal_response { //tolua_export
CC_CLASS(ManagedResponse);
public:
    ManagedResponse(Coord* coord, ManagedAgent* agent, ManagedRequest* request);
    virtual ~ManagedResponse();
};//tolua_export


}//tolua_export
}//tolua_export


