#pragma once 
 
#include "coord/memory/object_pool.h"
///
///
///
///
/// 1.Rc对象
/// 类型存在于堆中的对象，有内存池，有引用计数。
/// RC_CLASS
/// RC_IMPLEMENT
/// RcObject
///
/// 2.RefRc对象
/// 负责管理Rc对象
/// C++时，对象存在于栈中，用作用域管理Rc,
/// lua时，lua指定的是Rc对象， 用lua的gc管理Rc, 释放时调用Rc的DecRef
/// 构造rc时，引用计算不加1
///
///
///

namespace coord {//tolua_export


class Reflectable {
public:
    virtual const char* TypeName() const = 0;
};


template<typename TSelf>
class RcRef {
public:
    RcRef(TSelf* ptr) { 
        this->_ptr = ptr;
        if (nullptr != this->_ptr) {
            /// 不加1， 因为如果从函数里函数，rc对象无法释放自身
            ///
            /// ```
            ///   MessageRef NewMessage() {
            ///      auto message = new message();
            ///      return message;//如果构造ref时引用计算是1+1的话，message对象无法释放自身
            ///  }
            /// ```
            //}
            ///
            ////
            //this->_ptr->AddRef();
        }
    }
    RcRef() {
    }
    RcRef(std::nullptr_t) {
        this->_ptr = nullptr;
    }
    RcRef(const RcRef& other) {
        this->_ptr = other._ptr;
        if (nullptr != this->_ptr) {
            this->_ptr->AddRef();
        }
    }
    virtual ~RcRef() {
        if (nullptr != this->_ptr) {
            this->_ptr->DecRef();
            this->_ptr = nullptr;
        }
    }
    RcRef& operator=(const RcRef& other) {
        if (nullptr != this->_ptr) {
            // 原来的减1
            this->_ptr->DecRef();
            this->_ptr = nullptr;
        }
        this->_ptr = other._ptr;
        if (nullptr != this->_ptr) {
            this->_ptr->AddRef();
        }
        return *this;
    }
    TSelf* operator->() const { return this->_ptr;}
    TSelf* Self() {return this->_ptr;}
    // 返回一个推入的lua的指针
    TSelf* TakeOwnerShip() const {
        if (nullptr == this->_ptr) {
            return nullptr;
        }
        this->_ptr->AddRef();
        return this->_ptr;
    }
    bool operator== (std::nullptr_t v) const {return this->_ptr == nullptr;}
    bool operator!= (std::nullptr_t v) const {return this->_ptr != nullptr;}
private:
    TSelf* _ptr;
public:
    static RcRef NullPtr;
};


template<typename TSelf>
RcRef<TSelf> RcRef<TSelf>::NullPtr;

template<typename T>
RcRef<T> owner_move(T* ptr) {
    if (nullptr) return nullptr;
    return RcRef<T>(ptr);
}

class RcObject {//tolua_export
public:
    RcObject();
    virtual ~RcObject();
    void AddRef();              //tolua_export
    void DecRef();              //tolua_export
    // lua调用gc
    void Gc();                  //tolua_export
protected:
    // 析构函数
    virtual void Destory();
    // 清理函数
    virtual void onDestory();
public:
    int _ref;
};//tolua_export

class Type {//tolua_export
public:
    Type(const char* name);
    char name[64];
};//tolua_export

}//tolua_export


class CoordObject {
public:
    CoordObject();
    ~CoordObject();
};

#define RC_CLASS(ClassName) \
    public:\
    static thread_local ::coord::object_pool<ClassName>* allocator;\
    static void MemTrace();\
    void operator delete(void *ptr);\
    void* operator new(size_t size);\
    virtual ::coord::Type* GetType();\
    virtual const char* TypeName() const;\
    static ::coord::Type* _type;\
    static const char* _TypeName;

#define RC_IMPLEMENT(ClassName, FullName) \
    thread_local ::coord::object_pool<ClassName>* ClassName::allocator = new ::coord::object_pool<ClassName>(FullName);\
    void ClassName::MemTrace() {\
        ClassName::allocator->trace();\
    }\
    void ClassName::operator delete(void *ptr) {\
        ClassName::allocator->free((ClassName*)ptr);\
    }\
    void* ClassName::operator new(size_t size) {\
        return ClassName::allocator->alloc();\
    }\
    ::coord::Type* ClassName::_type = new ::coord::Type(FullName);\
    ::coord::Type* ClassName::GetType()\
    {\
        return ClassName::_type;\
    }\
    const char* ClassName::TypeName() const \
    {\
        return ClassName::_type->name;\
    }\
    const char* ClassName::_TypeName = FullName;


#define COORD_CLASS(ClassName) \
    public:\
    virtual ::coord::Type* GetType();\
    virtual const char* TypeName() const;\
    static ::coord::Type* _type;\
    static const char* _TypeName;


#define COORD_IMPLEMENT(ClassName, FullName) \
    ::coord::Type* ClassName::_type = new ::coord::Type(FullName);\
    ::coord::Type* ClassName::GetType()\
    {\
        return ClassName::_type;\
    }\
    const char* ClassName::TypeName() const \
    {\
        return ClassName::_type->name;\
    }\
    const char* ClassName::_TypeName = FullName;

