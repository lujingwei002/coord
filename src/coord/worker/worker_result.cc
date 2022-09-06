#include "coord/worker/worker_result.h"
#include "coord/worker/worker_request.h"
#include "coord/coord.h"
#include "coord/worker/worker.h"
#include "coord/protobuf/init.h"
#include "coord/coordx.h"

namespace coord {

namespace worker {
RC_IMPLEMENT(Result, "coord::worker::Result")

Result* newResult(Coord* coord) {
    Result* result = new Result(coord);
    return result;
}

Result::Result(Coord* coord) : base_result(coord) {

}

Result::~Result() {
    this->coord->CoreLogDebug("[worker::Result] ~");
}

}
}
