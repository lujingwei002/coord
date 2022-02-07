#include "coord/action/action_mgr.h"
#include "coord/action/action.h"
#include "coord/action/action_animation.h"
#include "coord/coord.h"

namespace coord {
namespace action {

ActionMgr* newActionMgr(Coord* coord) {
    ActionMgr* self = new ActionMgr(coord);
    return self;
}

ActionMgr::ActionMgr(Coord* coord) {
    this->coord = coord;
}

ActionMgr::~ActionMgr() {
    
}

Animation* ActionMgr::Begin() {
    return newAnimation(this->coord);
}

}
}