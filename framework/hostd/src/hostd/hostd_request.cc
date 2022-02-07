#include "hostd/hostd_request.h"
#include "hostd/hostd_agent.h"
#include "hostd/hostd_server.h"
#include "coord/coord.h"
#include <cctype>

namespace hostd {
CC_IMPLEMENT(HostdRequest, "hostd::HostdRequest")

HostdRequest* newHostdRequest(coord::Coord* coord, HostdAgent* agent) {
    HostdRequest* request = new HostdRequest(coord, agent);
    return request;
}

HostdRequest::HostdRequest(coord::Coord* coord, HostdAgent* agent) {
    this->agent = agent;
    this->coord = coord;
    this->coord->DontDestory(this->agent);
}

HostdRequest::~HostdRequest() {
    this->coord->LogDebug("[HostdRequest] ~HostdRequest");
    this->coord->Destory(this->agent);
}

int HostdRequest::parse(const char* data, size_t len) {
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

const char* HostdRequest::Arg(size_t i) {
    if (i < 0 || i >= this->args.size()) {
        return NULL;
    }
    return this->args[i].c_str();
}

size_t HostdRequest::Count() {
    return this->args.size();
}


}

