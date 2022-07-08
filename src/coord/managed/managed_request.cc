#include "coord/managed/managed_request.h"
#include "coord/managed/managed_agent.h"
#include "coord/coord.h"
#include "coord/managed/managed_server.h"
#include <cctype>

namespace coord {

namespace managed {
CC_IMPLEMENT(ManagedRequest, "coord::managed::ManagedRequest")

ManagedRequest* newManagedRequest(Coord* coord, ManagedAgent* agent) {
    ManagedRequest* request = new ManagedRequest(coord, agent);
    return request;
}

ManagedRequest::ManagedRequest(Coord* coord, ManagedAgent* agent) {
    this->agent = agent;
    this->coord = coord;
    this->coord->DontDestory(this->agent);
}

ManagedRequest::~ManagedRequest() {
    this->coord->CoreLogDebug("[ManagedRequest] ~ManagedRequest");
    this->coord->Destory(this->agent);
}

int ManagedRequest::parse(const char* data, size_t len) {
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

const char* ManagedRequest::Arg(size_t i) {
    if (i < 0 || i >= this->args.size()) {
        return NULL;
    }
    return this->args[i].c_str();
}

size_t ManagedRequest::Count() {
    return this->args.size();
}


}

}