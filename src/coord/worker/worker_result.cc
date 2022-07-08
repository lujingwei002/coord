#include "coord/worker/worker_result.h"
#include "coord/worker/worker_request.h"
#include "coord/coord.h"
#include "coord/worker/worker.h"
#include "coord/protobuf/init.h"
#include "util/date/date.h"

namespace coord {

namespace worker {
CC_IMPLEMENT(Result, "coord::worker::Result")

Result* newResult(Coord* coord) {
    Result* result = new Result(coord);
    return result;
}

Result::Result(Coord* coord) : BaseResult(coord) {

}

Result::~Result() {
    this->coord->CoreLogDebug("[worker::Result] ~");
}

}
}