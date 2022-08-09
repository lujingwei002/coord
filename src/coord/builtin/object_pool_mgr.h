#pragma once 

#include <map>
#include <string>

namespace coord {

    ///
    /// 对象池管理器
    /// 每个线程有一个管理器实例， 线程退出时自动销毁
    /// 
    ///
    ///


    class IObjectPool {
    public:
        virtual ~IObjectPool(){}
        virtual void trace() {}
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

