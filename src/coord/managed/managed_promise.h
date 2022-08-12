#pragma once 

#include "coord/builtin/type.h"
#include "coord/base/base_promise.h"
#include "coord/managed/managed_client.h"
#include <vector>
#include <iostream>
#include <map>

namespace coord {
    class Coord;
    namespace managed {
        class ManagedResult;
        class ManagedClient;
    }
}

namespace coord {//tolua_export
namespace managed {//tolua_export

class ManagedPromise: public base_promise<ManagedClient*, ManagedResult*>, public RcObject { //tolua_export
CC_CLASS(ManagedPromise);
friend base_managed_client;
friend ManagedClient;
private:
    ManagedPromise(Coord *coord);
    virtual ~ManagedPromise();
};//tolua_export

}//tolua_export
}//tolua_export


