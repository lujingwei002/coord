#include "coordx/coordx.h"
#include "coordx/reactor/reactor.h"

namespace coordx {
    int coordx_init() {
        uv_loop_init(&uvloop);
        return 0;
    }
} 

