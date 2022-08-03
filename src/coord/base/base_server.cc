#include "coord/base/base_server.h"
#include "coord/base/base_agent.h"
#include "coord/coord.h"
namespace coord {

base_server::base_server(Coord *coord) {
    this->coord = coord;
}

base_server::~base_server() {
}

} 
