#include "coord/net/write_req.h"
#include <memory.h>
#include <stdlib.h>

namespace coord {
namespace net {
RC_IMPLEMENT(WriteReq, "coord::net::WriteReq")

WriteReq::WriteReq(byte_slice& data) : data(data){
    this->req.data = this;
}

WriteReq::~WriteReq(){

}


}
}