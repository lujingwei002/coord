#pragma once 


#include "coord/builtin/object_pool.h"

namespace coord {//tolua_export
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
