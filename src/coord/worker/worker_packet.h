#pragma once 

#include "coord/builtin/type.h"

#include "coord/builtin/slice.h"
#include <string>
namespace coord {
class Coord;


namespace worker {

class Worker;
class WorkerResponse;
class WorkerResult;

enum worker_packet_type {
    worker_packet_request = 1,
    worker_packet_response = 2,
    worker_packet_notify = 3,
};

class worker_packet : public RcObject  { 
CC_CLASS(worker_packet);
public:
    worker_packet(Coord* coord);
    virtual ~worker_packet();
public:
   
public:
    Coord*      coord;
    Coord*       slave;
    std::string route;
    int         type;
    uint64_t    id;
    int         code;
    byte_slice  payload;
};//tolua_export

worker_packet* newWorkerPacket(Coord* coord);


}


}
