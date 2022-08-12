#pragma once 

#include "coord/pipe/pipe_listener.h"
#include "coord/base/base_server.h"
#include <map>

//declaration
namespace coord {
    class Coord;
namespace managed {
    class Managed;
    class ManagedAgent;
}
}

namespace coord {
namespace managed {

class managed_server : public RcObject, public pipe::IPipeHandler  {
CC_CLASS(managed_server);
friend managed::Managed;
friend managed::ManagedAgent;
private:
    managed_server(Coord *coord, Managed* managed);
    virtual ~managed_server();
protected:
    // implement pipe::IPipeHandler begin
    virtual void EvConnection(pipe::PipeListener* listener, pipe::PipeAgent* pipeAgent);
    virtual void EvClose(pipe::PipeListener* listener);
    // implement pipe::IPipeHandler end
private:
    // 启动
    int start();
    // 主动关闭
    int close();
    // agent关闭
    void recvAgentClose(ManagedAgent* agent);
private:
    Coord*                              coord;
    pipe::PipeListener*                 listener;
    Managed*                            managed;
    std::map<int, ManagedAgent*>        agentDict;
};

}
}


