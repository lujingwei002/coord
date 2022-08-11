#pragma once 


#include "coord/builtin/object_pool.h"
#include "coord/builtin/ref_manager.h"
///
///
///
///
/// 1.存在于堆中的对象，有内存池，有引用计数。除非明确调用DontDestory,否则都集中在下一帧中由coord释放。调用DontDestory后，就是调用者管理对象的生命周期
/// CC_CLASS
/// CC_IMPLEMENT
/// Destoryable
///
/// 
///
///
///
///

namespace coord {//tolua_export

class Coord;

class Reflectable {
public:
    virtual const char* TypeName() const = 0;
};

template<typename TSelf>
class DestoryableRef {
public:
    DestoryableRef(TSelf* ptr) { 
        this->_ptr = ptr;
        if (nullptr != this->_ptr) {
            //this->_ptr->AddRef();
        }
    }
    DestoryableRef(std::nullptr_t) {
        this->_ptr = nullptr;
    }
    DestoryableRef(const DestoryableRef& other) {
        this->_ptr = other._ptr;
        if (nullptr != this->_ptr) {
            this->_ptr->AddRef();
        }
    }
    virtual ~DestoryableRef() {
        if (nullptr != this->_ptr) {
            this->_ptr->DecRef();
            this->_ptr = nullptr;
        }
    }
    DestoryableRef& operator=(const DestoryableRef& other) {
        if (nullptr != this->_ptr) {
            this->_ptr->DecRef();
            this->_ptr = nullptr;
        }
        this->_ptr = other._ptr;
        if (nullptr != this->_ptr) {
            this->_ptr->AddRef();
        }
        return *this;
    }
    TSelf* operator->() { return this->_ptr;}
    TSelf* Self() {return this->_ptr;}
    bool operator== (std::nullptr_t v) const {return this->_ptr == nullptr;}
    bool operator!= (std::nullptr_t v) const {return this->_ptr != nullptr;}
private:
    TSelf* _ptr;
};

template<typename T>
DestoryableRef<T> owner_move(T* ptr) {
    if (nullptr) return nullptr;
    return DestoryableRef<T>(ptr);
}

class Destoryable {//tolua_export
friend Coord;
public:
    Destoryable();
    virtual ~Destoryable();
    void AddRef();              //tolua_export
    void DecRef();              //tolua_export
protected:
    // 析构函数
    virtual void Destory();
    // 清理函数
    virtual void onDestory();
public:
    int _ref;
};//tolua_export






template<typename TSelf>
class PointerRef {
public:
    PointerRef(TSelf* ptr) { 
        this->_ptr = ptr;
        if (nullptr != this->_ptr) {
            refManager.reference(this->_ptr);
        }
    }
    PointerRef(std::nullptr_t) {
        this->_ptr = nullptr;
    }
    PointerRef(const PointerRef& other) {
        this->_ptr = other._ptr;
        if (nullptr != this->_ptr) {
            refManager.reference(this->_ptr);
        }
    }
    virtual ~PointerRef() {
        if (nullptr != this->_ptr) {
            if(refManager.release(this->_ptr) == 0){
                delete this->_ptr;
            }
            this->_ptr = nullptr;
        }
    }
    PointerRef& operator=(const PointerRef& other) {
        if (nullptr != this->_ptr) {
            if(refManager.release(this->_ptr) == 0){
                delete this->_ptr;
            }
            this->_ptr = nullptr;
        }
        this->_ptr = other._ptr;
        if (nullptr != this->_ptr) {
            refManager.reference(this->_ptr);
        }
        return *this;
    }
    TSelf* operator->() { return this->_ptr;}
    TSelf* Self() {return this->_ptr;}
    bool operator== (std::nullptr_t v) const {return this->_ptr == nullptr;}
    bool operator!= (std::nullptr_t v) const {return this->_ptr != nullptr;}
private:
    TSelf* _ptr;
};

class Type {//tolua_export
public:
    Type(const char* name);
    char name[64];
};//tolua_export

}//tolua_export


#define CC_CLASS(ClassName) \
    public:\
    static thread_local ::coord::object_pool<ClassName>* allocator;\
    static void MemTrace();\
    void operator delete(void *ptr);\
    void* operator new(size_t size);\
    virtual ::coord::Type* GetType();\
    virtual const char* TypeName() const;\
    static ::coord::Type* _type;\
    static const char* _TypeName;

#define CC_IMPLEMENT(ClassName, FullName) \
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
    const char* ClassName::_TypeName = #FullName;
