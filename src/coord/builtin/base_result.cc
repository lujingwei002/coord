#include "coord/builtin/base_result.h"
#include "coord/coord.h"

namespace coord {

BaseResult::BaseResult(Coord* coord) : BaseRequest(coord) {
    this->Code = 0;
}

BaseResult::~BaseResult() {

}


}