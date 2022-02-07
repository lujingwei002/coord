#include "coord/builtin/request_pipeline.h"
#include "coord/builtin/base_request.h"
#include "coord/coord.h"
namespace coord {

RequestPipeline* newRequestPipeline(Coord* coord, BaseRequest* request) {
    RequestPipeline* self = new RequestPipeline(coord, request);
    return self;
}

RequestPipeline::RequestPipeline(Coord* coord, BaseRequest* request) {
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