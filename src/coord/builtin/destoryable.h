#pragma once 

namespace coord {//tolua_export

class Coord;
class Destoryable {//tolua_export
friend Coord;
public:
    Destoryable() {
        this->_ref = 1;
    }
    virtual ~Destoryable() {
    }
protected:
    // 析构函数
    virtual void Destory() {
        this->onDestory();
        delete this;
    }
    // 清理函数
    virtual void onDestory() {}
public:
    int _ref;
};//tolua_export

}//tolua_export
