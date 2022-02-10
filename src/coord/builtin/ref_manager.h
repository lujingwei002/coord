#pragma once 

#include <map>

namespace coord {//tolua_export

class ref_manager {
public:
    ref_manager() {
        
    }
    ~ref_manager() {
    }
public:
    void reference(void* ptr);
    int release(void* ptr);
private:
    std::map<void*, int> refDict;
};

extern thread_local ref_manager refManager;
}