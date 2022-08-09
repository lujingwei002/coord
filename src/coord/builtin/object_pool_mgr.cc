#include "coord/builtin/object_pool_mgr.h"
#include "coord/builtin/object_pool.h"
#include "coord/log/log.h"
#include <uv.h>
#include <vector>

namespace coord {
    thread_local object_pool_mgr objectPoolMgr;

    object_pool_mgr::~object_pool_mgr() {
        this->destory();
    }
    
    void object_pool_mgr::createObjectPool(const char* name, IObjectPool* pool){
        auto it = this->poolDict.find(name);
        if(it != this->poolDict.end()){
            LOG_ERROR("[object_pool_mgr<%x>] create object pool fail, name=%s, error='pool name conflict'", uv_thread_self(), name);
            return;
        }
        LOG_DEBUG("[object_pool_mgr<%x>] create object pool, name=%s", uv_thread_self(), name);
        this->poolDict[name] = pool;
    }

    void object_pool_mgr::destroyObjectPool(const char* name, IObjectPool* pool){
        auto it = this->poolDict.find(name);
        if(it == this->poolDict.end()){
            LOG_ERROR("[object_pool_mgr<%x>] destory object pool fail, name=%s, error='pool not found'", uv_thread_self(), name);
            return;
        }
        if(it->second != pool){
            LOG_ERROR("[object_pool_mgr<%x>] destory object pool fail, name=%s, error='pool name conflict'", uv_thread_self(), name);
            return;
        }
        LOG_DEBUG("[object_pool_mgr<%x>] destory object pool, name=%s", uv_thread_self(), name);
        this->poolDict.erase(it);
    }

    void object_pool_mgr::trace(){
        LOG_DEBUG("=====================object_pool_mgr<%x>::Trace %d=====================", uv_thread_self(), object_pool_mgr::poolDict.size());
        for(auto &v : this->poolDict) {
            v.second->trace();
        }
        LOG_DEBUG("=====================object_pool_mgr<%x>::Trace %d=====================", uv_thread_self(), object_pool_mgr::poolDict.size());
    }

    void object_pool_mgr::destory(){
        std::vector<IObjectPool*> poolArr;
        // 销毁前打印对象池信息
        for(auto const& it : this->poolDict) {
            it.second->trace();
            poolArr.push_back(it.second);
        }
        while(poolArr.size() > 0){
            IObjectPool* pool = poolArr.back();
            poolArr.pop_back();
            delete pool;
        }
    }
}  
