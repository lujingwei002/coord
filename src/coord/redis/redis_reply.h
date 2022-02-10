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
namespace coord {//tolua_export
    
class Coord;

namespace redis {//tolua_export

class Reply : public Destoryable {//tolua_export
CC_CLASS(Reply);
public:
    Reply(std::nullptr_t);
    Reply(Coord *coord, redisReply* reply, bool owner = true);
    Reply(const Reply& other);
    virtual ~Reply();
public:
    Reply& operator=(const Reply& other);
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
    /// 是否错误
    bool Error();                       //tolua_export
    /// 是否数组
    bool Array();                       //tolua_export
    /// 如果是数组，返回数组的大小
    int ArrayCount();                   //tolua_export
    /// 是否空值
    bool Empty();                       //tolua_export
    bool Empty(size_t index);           //tolua_export
    const char* String();               //tolua_export
    long long Integer();                //tolua_export
    long long Integer(size_t index);    //tolua_export
    const char* String(size_t index);   //tolua_export
public:
    Coord*      coord;
    redisReply* reply;
    bool        owner;
};//tolua_export

}//tolua_export
}//tolua_export


