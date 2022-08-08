#include "coord/base/base_agent.h"
#include "coord/coord.h"
namespace coord {

CC_IMPLEMENT(base_agent, "coord::base_agent")


base_agent::base_agent(Coord *coord) {
    this->coord = coord;
}

base_agent::~base_agent() {
}


}  
