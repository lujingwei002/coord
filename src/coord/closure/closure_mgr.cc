#include "coord/closure/closure_mgr.h"
#include "coord/closure/closure.h"
#include "coord/coord.h"

namespace coord {
namespace closure {

ClosureMgr* newClosureMgr(Coord* coord) {
    ClosureMgr* self = new ClosureMgr(coord);
    return self;
}

ClosureMgr::ClosureMgr(Coord* coord) {
    this->coord = coord;
}

ClosureMgr::~ClosureMgr() {
    
}


}
}