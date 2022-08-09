#include "coord/net/recv_buffer.h"
#include <cstring>


namespace coord {
namespace net {
RecvBuffer* RecvBuffer::New(size_t capacity) {
    RecvBuffer* self = new RecvBuffer(capacity);
    return self;
}

RecvBuffer::RecvBuffer(size_t capacity) {
    char *ptr = (char*)malloc(capacity);
    if(ptr == NULL){
        capacity = 0;
    }
    this->data = ptr;
    this->capacity = capacity;
    this->begin = ptr;
    this->front = ptr;
    this->back = ptr;
    this->end = ptr + capacity;
}

RecvBuffer::~RecvBuffer() {
   if(this->data == NULL){
       return;
   }
   free(this->data);
   this->data = NULL;
   this->capacity = 0;
}

bool RecvBuffer::Reserve(size_t size){
    if(this->end - this->back >= (int)size){
        return true;
    }  
    size_t newCapacity = this->capacity + size;
    char* ptr = (char*)realloc(this->data, newCapacity);
    if(ptr == NULL){
        return false;
    }
    this->begin = ptr;
    this->end = ptr + newCapacity;
    this->front = (this->front - this->data) + ptr;
    this->back = (this->back - this->data) + ptr;
    this->capacity = newCapacity;
    this->data = ptr;
    return true;
}

void RecvBuffer::Truncate(){
    size_t len = this->back - this->front;
    if(len <= 0){
        this->back = this->begin;
        this->front = this->begin;
    } else {
        memmove(this->data, this->front, len);
        this->front = this->begin;
        this->back = this->front + len;
    }
}

void RecvBuffer::Reset(){
    this->front = this->begin;
    this->back = this->begin;
}

}
}