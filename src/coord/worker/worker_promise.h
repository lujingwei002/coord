#pragma once 

#include "coord/base/base_promise.h"


namespace coord {//tolua_export

class Coord;

namespace worker {//tolua_export

class Result;
class Worker;

typedef base_promise<Worker*, Result*> base_worker_promise;
class Promise: public base_worker_promise, public RcObject { //tolua_export
CC_CLASS(Promise);
public:
    Promise(Coord *coord);
    virtual ~Promise();
private:
};//tolua_export

}//tolua_export

}//tolua_export
