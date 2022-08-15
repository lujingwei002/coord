#pragma once 


#include "coord/coordx.h"

#include <uv.h>
namespace coord {

namespace net {
/*

|----------|------|---------|
begin    front   back      end
*/
class RecvBuffer  {
public:
    static RecvBuffer* New(size_t capacity);
public:
    RecvBuffer(size_t capacity);
    ~RecvBuffer();
public:
    size_t Len(){
        return this->back - this->front;
    }
    char* Front() {
        return this->front;
    }
    char* Begin() {
        return this->begin;
    }
    char* Back() {
        return this->back;
    }
    void PopFront(size_t size){
        this->front += size;
    }
    void PushBack(size_t size){
        this->back += size;
    }
    size_t Available(){
        return this->end - this->back;
    }
    size_t Capacity(){
        return this->end - this->begin;
    }
    size_t Unused(){
        return this->front - this->begin;
    }
    bool Reserve(size_t size);
    void Reset();
    void Truncate();
public:
    char* data;
    size_t capacity;
    char* front;
    char* back;
    char* begin;
    char* end;
};

}

}


