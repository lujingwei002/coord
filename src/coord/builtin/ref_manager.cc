#include "coord/builtin/ref_manager.h"
#include "coord/coord.h"

namespace coord {

thread_local ref_manager refManager;

void ref_manager::reference(void* ptr) {
    auto it = this->refDict.find(ptr);
    if (it == this->refDict.end()) {
        this->refDict[ptr] = 1;
    } else {
        this->refDict[ptr] = it->second + 1;
    }
}

int ref_manager::release(void* ptr) {
    auto it = this->refDict.find(ptr);
    if (it == this->refDict.end()) {
       // LOG_ERROR("[ref_manager] release failed'");
        return 0;
    } else if (it->second <= 0) {
        // LOG_ERROR("[ref_manager] release failed'");
        return 0;
    } else if (it->second == 1) {
        this->refDict.erase(it);
        return 0;
    } else {
        this->refDict[ptr] = it->second - 1;
        return it->second;
    }
}

}