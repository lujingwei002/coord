#pragma once

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
#include <uv.h>
#include <array>
#include <map>
#include <vector>
#include "lua-cjson/lua_cjson.h"

#include "coord/coord.h"
#include "coord/coordx.h"
#include "coord/environment/inc.h"
#include "coord/config/init.h"
#include "coord/log4cc/init.h"
#include "coord/script/init.h"
#include "coord/action/init.h"
#include "coord/cache/init.h"
#include "coord/redis/init.h"
#include "coord/closure/init.h"
#include "coord/cluster/init.h"
#include "coord/encrypt/init.h"
#include "coord/event/init.h"
#include "coord/http/init.h"
#include "coord/json/init.h"
#include "coord/managed/init.h"
#include "coord/sql/init.h"
#include "coord/sql/mysql/init.h"
#include "coord/timer/init.h"
