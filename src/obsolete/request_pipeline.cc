#include "coord/builtin/request_pipeline.h"
#include "coord/base/base_request.h"
#include "coord/coord.h"
namespace coord {

RequestPipeline* newRequestPipeline(Coord* coord, IRequest* request) {
    RequestPipeline* self = new RequestPipeline(coord, request);
    return self;
}

RequestPipeline::RequestPipeline(Coord* coord, IRequest* request) {
    this->coord = coord;
    this->request = request;
    //this->coord->DontDestory(this->request);
}

RequestPipeline::~RequestPipeline() {
    if(this->request) {
        this->coord->Destory(this->request);
        this->request = NULL;
    }
}


}
