#pragma once 
#include "coord/component/component.h"
#include "coord/display/vector3.h"
#include <map>

namespace coord {//tolua_export
class Coord;
class Transform : public Component {//tolua_export
CC_CLASS(Transform);

    public:
        Transform(Coord* coord);
        virtual ~Transform();
    public:
        Vector3 position;//tolua_export
        Vector3 scale;//tolua_export
        Vector3 rotation;//tolua_export
};//tolua_export
}//tolua_export
