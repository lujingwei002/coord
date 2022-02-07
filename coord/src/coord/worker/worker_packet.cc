#include "coord/worker/worker_packet.h"
#include "coord/coord.h"

namespace coord {

namespace worker {
CC_IMPLEMENT(worker_packet, "coord::worker::worker_packet")

worker_packet* newWorkerPacket(Coord* coord) {
    worker_packet* packet = new worker_packet(coord);
    return packet;
}

worker_packet::worker_packet(Coord* coord)  {
    this->coord = coord;
}

worker_packet::~worker_packet() {
    this->coord->coreLogDebug("[worker_packet] ~worker_packet");
    
}



}
}