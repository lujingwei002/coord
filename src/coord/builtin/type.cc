#include "coord/builtin/type.h"
#include "coord/coord.h"
#include <cstring>

namespace coord {

Type::Type(const char* name) {
    strcpy(this->name, name);
}

Destoryable::Destoryable() {
    this->_ref = 1;
    coorda->insertHeapObject(this);
}

Destoryable::~Destoryable() {
    
}

void Destoryable::AddRef() {
    if(this->_ref <= 0) { //避免在destory里，又被操作ref
        return;
    }
    this->_ref++;
}
void Destoryable::DecRef() {
    this->_ref--;
    if(this->_ref != 0){ //避免循环删除，要用!=0判断。 a删除b, b删除a, 导致一直循环
        return;
    }
    this->Destory();
}

void Destoryable::Destory() {
    this->onDestory();
    delete this;
}

void Destoryable::onDestory() {
    
}

}