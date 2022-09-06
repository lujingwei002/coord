#pragma once 

#include "coord/base/base_notify.h"

//declaration
namespace coord {
    class Coord;
    namespace managed {
        class ManagedAgent;
        class managed_server;
    }
}

namespace coord {//tolua_export
namespace managed {//tolua_export

class ManagedNotify: public base_notify { //tolua_export
RC_CLASS(ManagedNotify);
friend ManagedAgent;
private:
    ManagedNotify(Coord* coord, ManagedAgent* agent);
    virtual ~ManagedNotify();
};//tolua_export


}//tolua_export
}//tolua_export


