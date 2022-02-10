#pragma once 
#include "coord/builtin/type.h"
#include "coord/builtin/slice.h"
#include <uv.h>
#include <stdint.h>

namespace coord {//tolua_export
namespace net {//tolua_export
//tolua_begin
class WriteReq {
CC_CLASS(WriteReq)
public:
    WriteReq(byte_slice& data);
    virtual ~WriteReq();
public:
    byte_slice data;
    uv_write_t req;
};//tolua_export
}//tolua_export
}//tolua_export
