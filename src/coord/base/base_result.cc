#include "coord/base/base_result.h"
#include "coord/coord.h"
#include "coord/coordx.h"

namespace coord {

base_result::base_result(Coord* coord) : base_reader(coord) {
    this->Code = 0;
}

base_result::~base_result() {
}

void base_result::onDestory() {
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s|%10s| RESULT | %3d |\t%s", this->TypeName(), coordx::date::FormatNano(duration), this->Code, this->Route.c_str());
}


}
