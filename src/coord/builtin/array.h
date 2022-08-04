#pragma once 


#include "coord/log/log.h"
#include <vector>
#include <memory>
namespace coord {


template<class T>
class array {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
public:
    array(size_type capacity){
        if(capacity < 0)capacity = 0;
        this->capacity = capacity;
        this->ref = 0;
        if(capacity > 0){
            this->arr.resize(capacity);
        }
    }

    ~array(){
        //LOG_DEBUG("[Array] ~Array capacity=%d", this->capacity);
    }

    /// 返回写入的长度
    size_type write(size_type offset, const_pointer v, size_type len) {
        if(offset + len > this->capacity) {
            size_type newCapacity = 2 * this->capacity;
            if(newCapacity <= 0)newCapacity = 64;
            while(offset + len > newCapacity){
                newCapacity = 2 * newCapacity;
            }
            int err = this->reserve(newCapacity);
            if (err) {
                return 0;
            }
        }
        if(offset + len > this->capacity) {
            return 0;
        }
        auto it = this->arr.begin();
        it = it + offset;
        std::uninitialized_copy_n(v, len, it);
        return len;
    }

    pointer data(){
        return this->arr.data();
    }

    /// 设置数量容量
    int reserve(size_type capacity){
        if(this->capacity > capacity){
            return 0;
        }
        this->arr.resize(capacity);
        if (this->arr.capacity() < capacity) {
            return -1;
        }
        this->capacity = capacity;
        return 0;
    }

    //If the container size is greater than n, the function never throws exceptions (no-throw guarantee).
    //Otherwise, it causes undefined behavior.
    reference operator[] (size_type n) {
        return this->arr[n];
    }

    //If the container size is greater than n, the function never throws exceptions (no-throw guarantee).
    //Otherwise, it causes undefined behavior.
    const_reference operator[] (size_type n) const {
        return this->arr[n];
    }
public:
    std::vector<T>  arr;
    size_type       capacity;
    size_type       ref;
};

}
