#include "coord/memory/type.h"
#include <cstring>

namespace coord {

Type::Type(const char* name) {
    strcpy(this->name, name);
}

RcObject::RcObject() {
    this->_ref = 1;
}

RcObject::~RcObject() {
    
}

void RcObject::AddRef() {
    if(this->_ref <= 0) { //避免在destory里，又被操作ref
        return;
    }
    this->_ref++;
}

void RcObject::Gc() {
    this->DecRef();
}

void RcObject::DecRef() {
    this->_ref--;
    if(this->_ref != 0){ //避免循环删除，要用!=0判断。 a删除b, b删除a, 导致一直循环
        return;
    }
    this->Destory();
}

void RcObject::Destory() {
    this->onDestory();
    delete this;
}

void RcObject::onDestory() {
    
}

}
