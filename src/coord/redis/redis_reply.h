#pragma once 

#include "coord/builtin/init.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
namespace coord {
    class Coord;
    namespace redis {
        class Client;
        class AsyncClient;
    }
}

namespace coord {//tolua_export
namespace redis {//tolua_export

class Reply : public Destoryable {//tolua_export
CC_CLASS(Reply);
friend Client;
friend AsyncClient;
    
private:
    Coord*      coord;
    redisReply* reply;
private:
    Reply(Coord *coord, redisReply* reply);



public:
    Reply(const Reply* other);
    Reply(const Reply& other);
    Reply(std::nullptr_t);
    virtual ~Reply();
public:
    Reply& operator=(const Reply& other);
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
    /// 是否错误
    bool Error() const;                       //tolua_export
    /// 是否数组
    bool Array() const;                       //tolua_export
    /// 如果是数组，返回数组的大小
    int ArrayCount() const;                   //tolua_export
    /// 是否空值
    bool Empty() const;                       //tolua_export
    bool Empty(size_t index) const;           //tolua_export
    const char* String() const;               //tolua_export
    long long Integer() const;                //tolua_export
    long long Integer(size_t index) const;    //tolua_export
    const char* String(size_t index) const;   //tolua_export
};//tolua_export

}//tolua_export
}//tolua_export


