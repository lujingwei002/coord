#include "coord/builtin/init.h"
#include "coord/builtin/platform.h"

namespace coord {
    int builtinInit() {
        uv_loop_init(&uvloop);
        return 0;
    }
}
