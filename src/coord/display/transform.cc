
#include "coord/display/transform.h"

namespace coord {

RC_IMPLEMENT(Transform, "coord::Transform")

Transform::Transform(Coord* coord) : Component(coord) {

}

Transform::~Transform() {

}

}
