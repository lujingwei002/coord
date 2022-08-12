#pragma once 

#include "coord/builtin/type.h"
#include "coord/redis/declare.h"


///
///
/// RedisMgr负责管理Client的内存
///
///
///

namespace coord {
    class Coord;
}

namespace coord {//tolua_export
namespace redis {//tolua_export

class RedisMgr {//tolua_export
friend Coord;
friend Client;
friend AsyncClient;
private:
    RedisMgr(Coord *coord);
    virtual ~RedisMgr();
private:
    // 释放redis client
    void free(Client* conn);
    // 释放redis client
    void free(AsyncClient* conn);
private:
    std::map<std::string, Client*>      clientDict;
    std::set<Client*>                   clientSet;
    std::map<std::string, AsyncClient*> asyncClientDict;
    std::set<AsyncClient*>              asyncClientSet;
    Coord*                              coord;




public:
    /// 创建redis client
    Client* NewClient();
    /// 创建async redis client
    AsyncClient* NewAsyncClient();

    /// 根据配置创建redis client
    Client* GetClient(const char* name);

    /// 根据配置创建async redis client
    AsyncClient* GetAsyncClient(const char* name);
};//tolua_export


}//tolua_export
}//tolua_export


