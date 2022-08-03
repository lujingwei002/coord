#pragma once 

#include "coord/base/base_result.h"

//declaration
namespace coord {
class Coord;
}

namespace coord {//tolua_export
namespace managed {//tolua_export

class ManagedResult : public base_result { //tolua_export
CC_CLASS(ManagedResult);
public:
    ManagedResult(Coord* coord);
    virtual ~ManagedResult();
};//tolua_export

}//tolua_export
}//tolua_export


