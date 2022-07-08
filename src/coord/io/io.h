#pragma once 


#include "coord/builtin/slice.h"
#include <uv.h>

namespace coord {//tolua_export
namespace io {


int ReadFile(const char* path, byte_slice& buffer);

uv_stat_t* FileStat(const char* path);

int FileLock(const char* path);
}
}