#pragma once 

#include <map>
#include <string>

namespace coord {

    class IObjectPool {
    public:
        virtual ~IObjectPool(){}
        virtual void Trace() {}
    };

    class object_pool_mgr {
    public:
        object_pool_mgr(){}
        ~object_pool_mgr();
        void createObjectPool(const char* name, IObjectPool* pool);
        void destroyObjectPool(const char* name, IObjectPool* pool);
        void trace();
        void destory();
    private:
        std::map<std::string, IObjectPool*> poolDict;
    };

    thread_local extern object_pool_mgr objectPoolMgr;

}

