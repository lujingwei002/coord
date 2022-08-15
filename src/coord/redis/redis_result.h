#pragma once 

#include "coord/coordx.h"
#include "coord/redis/declare.h"


///
///
/// 内存 RedisResult在堆中, lua用RedisResultRef来管理RedisResult, lua是RedisResult的指针，用本身的gc来管理 
/// 
/// c++ RedisResultRef -----------> RedisResult*
///
/// lua ownership-----------------------↑
///
///



namespace coord {
    class Coord;
}

namespace coord {//tolua_export
namespace redis {//tolua_export

class RedisResult : public coordx::RcObject {//tolua_export
CC_CLASS(RedisResult);
friend Client;
friend AsyncClient;
private:
    Coord*      coord;
    redisReply* reply;
private:
    RedisResult(Coord *coord, redisReply* reply);


public:
    virtual ~RedisResult();                     //tolua_export            
public:
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


