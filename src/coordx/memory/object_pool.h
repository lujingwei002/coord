#pragma once 

#include <memory>
#include <cstdlib> // for exit()
#include <climits> // for UNIX_MAX
#include <cstddef>
#include <list>
#include <set>
#include <iostream>
#include "coordx/memory/object_pool_mgr.h"
#include "coordx/log/log.h"

namespace coordx {

template<class T, size_t N = 64, class Allocator = std::allocator<T>>
class object_pool : public IObjectPool {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
public:
    object_pool(const char* name){
        this->name = name;
        objectPoolMgr.createObjectPool(name, this);
    }

    ~object_pool(){
        //LOG_DEBUG("ObjectPool<%s>::~ObjectPool", this->name.c_str());
        while(this->freeList.size() > 0){
            pointer object = this->freeList.back();
            this->freeList.pop_back();
            this->allocator.deallocate(object, 1);
        }
        //for(auto object : this->allocateList){
        //    this->allocator.destroy(object);
        //}
        objectPoolMgr.destroyObjectPool(this->name.c_str(), this);
    }
    
    pointer alloc() {
        if(this->freeList.size() <= 0){
            this->growUp();
        }
        if(this->freeList.size() <= 0){
            return nullptr;
        }
        pointer object = (pointer)this->freeList.back();
        LOG_DEBUG("[ObjectPool<%s>] alloc, address=%p", this->name.c_str(), object);
        this->freeList.pop_back();
        this->allocateList.insert(object);
        return object;
    }

    pointer construct() {
        pointer object = this->alloc();
        if(object == nullptr){
            return nullptr;
        }
        LOG_DEBUG("[ObjectPool<%s>] construct", this->name.c_str());
        this->allocator.construct(object);
        return object;
    }

    bool free(pointer object) {
        auto it = this->allocateList.find(object);
        if (it == this->allocateList.end()){
            LOG_ERROR("ObjectPool<%s> free failed, address=%p", this->name.c_str(), object);
            return false;
        }
        LOG_DEBUG("ObjectPool<%s> free, address=%p, freeList:%d", this->name.c_str(), object, this->freeList.size());
        this->freeList.push_back(object);
        this->allocateList.erase(it);
        return true;
    }

    void gc(){
        size_t count = 0;
        while(this->freeList.size() > count){
            pointer object = (pointer)this->freeList.back();
            this->freeList.pop_back();
            this->allocator.deallocate(object, 1);
        }
    }

    virtual void trace() {
        if (this->allocateList.size() != 0) {
            LOG_DEBUG("ObjectPool<%50s> freeList:%02d allocateList:%02d!!!!!", this->name.c_str(), this->freeList.size(), this->allocateList.size());
        } else {
            LOG_DEBUG("ObjectPool<%50s> freeList:%02d allocateList:%02d", this->name.c_str(), this->freeList.size(), this->allocateList.size());
        }
    }

private:
    void growUp(){
        size_t count = this->allocateList.size() * 2;
        if (count <= 0)count = N;
        while(count-- > 0){
            pointer object = this->allocator.allocate(1);
            this->freeList.push_back(object);
        }
    }
private:
    std::string         name;
    Allocator           allocator;
    std::list<pointer>  freeList;
    std::set<pointer>   allocateList;
};

}