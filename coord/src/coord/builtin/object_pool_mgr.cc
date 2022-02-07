#include "coord/builtin/object_pool_mgr.h"
#include "coord/builtin/object_pool.h"
#include "coord/log/log.h"
#include <libuv/uv.h>
#include <vector>

namespace coord {
    thread_local object_pool_mgr objectPoolMgr;

    object_pool_mgr::~object_pool_mgr() {
        this->destory();
    }
    
    void object_pool_mgr::createObjectPool(const char* name, IObjectPool* pool){
        LOG_DEBUG("object_pool_mgr<%x>::CreateObjectPool %s", uv_thread_self(), name);
        this->poolDict[name] = pool;
    }

    void object_pool_mgr::destroyObjectPool(const char* name, IObjectPool* pool){
        LOG_DEBUG("object_pool_mgr<%x>::DestroyObjectPool %s", uv_thread_self(), name);
        auto it = this->poolDict.find(name);
        if(it == this->poolDict.end()){
            return;
        }
        if(it->second != pool){
            return;
        }
        this->poolDict.erase(it);
    }

    void object_pool_mgr::trace(){
        LOG_DEBUG("=====================object_pool_mgr<%x>::Trace %d=====================", uv_thread_self(), object_pool_mgr::poolDict.size());
        for(auto &v : this->poolDict) {
            v.second->Trace();
        }
        LOG_DEBUG("=====================object_pool_mgr<%x>::Trace %d=====================", uv_thread_self(), object_pool_mgr::poolDict.size());
    }

    void object_pool_mgr::destory(){
        std::vector<IObjectPool*> poolArr;
        for(auto const it : this->poolDict) {
            it.second->Trace();
            poolArr.push_back(it.second);
        }
        while(poolArr.size() > 0){
            IObjectPool* pool = poolArr.back();
            poolArr.pop_back();
            delete pool;
        }
    }
}  