#include "consoled/consoled_request.h"
#include "consoled/consoled_agent.h"
#include "consoled/consoled_server.h"
#include "coord/coord.h"
#include <cctype>

namespace consoled {
CC_IMPLEMENT(ConsoledRequest, "consoled::ConsoledRequest")

ConsoledRequest* newConsoledRequest(coord::Coord* coord, ConsoledAgent* agent) {
    ConsoledRequest* request = new ConsoledRequest(coord, agent);
    return request;
}

ConsoledRequest::ConsoledRequest(coord::Coord* coord, ConsoledAgent* agent) {
    this->agent = agent;
    this->coord = coord;
    this->coord->DontDestory(this->agent);
}

ConsoledRequest::~ConsoledRequest() {
    this->coord->LogDebug("[ConsoledRequest] ~ConsoledRequest");
    this->coord->Destory(this->agent);
}

int ConsoledRequest::parse(const char* data, size_t len) {
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

const char* ConsoledRequest::Arg(size_t i) {
    if (i < 0 || i >= this->args.size()) {
        return NULL;
    }
    return this->args[i].c_str();
}

size_t ConsoledRequest::Count() {
    return this->args.size();
}


}

