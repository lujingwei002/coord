#pragma once 

namespace coord {//tolua_export

class Destoryable {//tolua_export
public:
    Destoryable() {
        this->_ref = 1;
    }
    virtual ~Destoryable() {
    }
public:
    virtual void onDestory() {}
public:
    int _ref;
};//tolua_export

}//tolua_export