#pragma once 


#include "coord/builtin/object_pool.h"

namespace coord {//tolua_export

class Reflectable {
public:
    virtual const char* TypeName() const = 0;
};

/// 存在于堆中的对象，有内存池，有引用计数
/// 
///
/// 管理堆中的对象，C++中是存在于栈中，离开作用域后释放。LUA中是存在于堆中，LUA的GC负责释放。
/// 
///
///
///
///
///
///
///
///



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
    static ::coord::Type* _type;

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
    }
