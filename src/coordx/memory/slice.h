#pragma once 
#include "coordx/memory/array.h"
#include <algorithm>
#include <cstdarg>

namespace coordx {

template<class T>
class slice {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef size_t          size_type;
    typedef ptrdiff_t       difference_type;
public:

    slice(size_type len = 0, size_type capacity = 0){
        if (len < 0)len = 0;
        if (capacity < 0) capacity = 0;
        if (capacity < len) capacity = len;
        this->arr = new array<T>(capacity);
        this->offset = 0;
        this->len = len;
        this->arr->ref++;
    }

    slice(const slice& other){
        this->arr = other.arr;
        this->offset = other.offset;
        this->len = other.len;
        this->arr->ref++;
    }

    ~slice() {
        if(this->arr == nullptr){
            return;
        }
        this->arr->ref--;
        if(this->arr->ref == 0){
            delete this->arr;
        }
        this->arr = nullptr;
    }

    slice& operator=(const slice& other) {
        if(this->arr != nullptr){
            this->arr->ref--;
            if(this->arr->ref == 0){
                delete this->arr;
            }
            this->arr = nullptr;
        }
        this->arr = other.arr;
        this->offset = other.offset;
        this->len = other.len;
        this->arr->ref++;
        return *this;
    }

    slice Slice(size_t begin, size_t end) {
        slice other(*this);
        if (begin < 0) begin = 0;
        if (end < 0) end = 0;
        if (end < begin) end = begin;
        other.offset = this->offset + begin;
        other.len = end - begin;
        other.Reserve(end - begin);
        return other;
    }

    /// 设置切片容量
    int Reserve(size_t size) {
        int err = this->arr->reserve(this->offset + size);
        if (err < 0){
            return err;
        }
        return 0;
    }

    //设置切片长度
    int Resize(size_t size) {
        if (size < 0) {
            return -1;
        }
        if(this->Capacity() < size){
            this->Reserve(size);
        }
        if(this->Capacity() < size){
            return -1;
        }
        this->len = size;
        return 0;
    }
    
    size_type Len() const {
        return this->len;
    }

    pointer Data()  const  {
        return this->arr->data() + this->offset;
    }

    size_type Capacity()  const  {
        return this->arr->capacity - this->offset;
    }

    reference operator[] (size_type index) {
        return (reference)((*this->arr)[this->offset + index]);
    }

    const_reference operator[] (size_type index) const {
        return (const_reference)((*this->arr)[this->offset + index]);
    }
public:
    array<T>*   arr;
    size_type   offset;
    size_type   len;
};

typedef slice<char> byte_slice;


template<typename T>
typename slice<T>::size_type Write(slice<T>& self, typename slice<T>::size_type offset, typename slice<T>::const_pointer v, typename slice<T>::size_type len) {
    typename slice<T>::size_type n = self.arr->write(self.offset + offset, v, len);
    self.len = std::max(offset + n, self.len);
    return n;
}

template<typename T>
typename slice<T>::size_type Append(slice<T>& self, typename slice<T>::const_pointer v, typename slice<T>::size_type len) {
    typename slice<T>::size_type n = self.arr->write(self.offset + self.len, v, len);
    self.len = std::max(self.len + n, self.len);
    return n;
}

template<typename T>
typename slice<T>::size_type Append(slice<T>& self, typename slice<T>::const_reference v) {
    return coordx::Append(self, &v, sizeof(typename slice<T>::value_type));
}

int Appendf(byte_slice& self, const char* fmt, va_list args);
int Appendf(byte_slice& self, const char* fmt, ...);

}

