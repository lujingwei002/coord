#include "coord/run/managed_pipe_request.h"
#include "coord/run/managed_pipe_agent.h"
#include "coord/coord.h"
#include "coord/run/managed_pipe_server.h"
#include <cctype>

namespace coord {

namespace run {
CC_IMPLEMENT(ManagedPipeRequest, "coord::run::ManagedPipeRequest")

ManagedPipeRequest* newManagedPipeRequest(Coord* coord, ManagedPipeAgent* agent) {
    ManagedPipeRequest* request = new ManagedPipeRequest(coord, agent);
    return request;
}

ManagedPipeRequest::ManagedPipeRequest(Coord* coord, ManagedPipeAgent* agent) {
    this->agent = agent;
    this->coord = coord;
    this->coord->DontDestory(this->agent);
}

ManagedPipeRequest::~ManagedPipeRequest() {
    this->coord->CoreLogDebug("[ManagedPipeRequest] ~ManagedPipeRequest");
    this->coord->Destory(this->agent);
}

int ManagedPipeRequest::parse(const char* data, size_t len) {
    this->args.clear();
    const char* start = data;
    for (size_t i = 0; i < len; i++) {
        if (start) {
            if (isspace(data[i])) {
                this->args.push_back(std::string(start, data + i - start));
                start = NULL;
            }
        } else {
            if(!isspace(data[i])) {
                start = data + i;
            }
        }
    }
    if (start && len > 0) {
        this->args.push_back(std::string(start, data + len - start));
    }
    return 0;
}

const char* ManagedPipeRequest::Arg(size_t i) {
    if (i < 0 || i >= this->args.size()) {
        return NULL;
    }
    return this->args[i].c_str();
}

size_t ManagedPipeRequest::Count() {
    return this->args.size();
}


}

}