#pragma once 

#include "coord/builtin/type.h"
#include "coord/protobuf/init.h"
#include "coord/managed/managed_config.h"
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>

namespace coord {
    class Coord;
    namespace managed {
        class ManagedClient;
        class managed_server;
        class ManagedRouter;
        class ManagedRequest;
        class ManagedNotify;
        class ManagedAgent;
    }
}

namespace coord {//tolua_export
namespace managed {//tolua_export

class Managed {//tolua_export
CC_CLASS(Managed);
friend coord::Coord;
friend ManagedAgent;
private:
    Managed(Coord *coord);
    virtual ~Managed();
public:
    // 创建Client
    ManagedClient* NewClient(const std::string& path);
    // 关闭
    int Close();

private:
    int main();
    void recvRequest(ManagedRequest* request);
    void recvNotify(ManagedNotify* notify);
    void recvRequest_status(ManagedRequest* request);
    void recvRequest_stop(ManagedRequest* request);
private:
    Coord*              coord;
    ManagedConfig       config;
    managed_server*     server;
    ManagedRouter*      Router;
};//tolua_export

}//tolua_export
}//tolua_export


