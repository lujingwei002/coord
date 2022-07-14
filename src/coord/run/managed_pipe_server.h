#pragma once 

#include "coord/builtin/type.h"
#include "coord/pipe/pipe_listener.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;

namespace run {//tolua_export

class Running;
class Packet;
class ManagedPipeAgent;

class ManagedPipeServer : public pipe::IPipeHandler  {//tolua_export
public:
    ManagedPipeServer(Coord *coord, Running* running);
    virtual ~ManagedPipeServer();
public:
    // implement pipe::IPipeHandler begin
    virtual void recvPipeNew(pipe::PipeListener* listener, pipe::PipeAgent* pipeAgent);
    // implement pipe::IPipeHandler end
    void recvPipeClose(ManagedPipeAgent* agent);
    int start();
    void close();
public:
    Coord*                              coord;
    pipe::PipeListener*                 listener;
    Running*                            running;
    std::map<int, ManagedPipeAgent*>    agentDict;
};//tolua_export

ManagedPipeServer* newManagedPipeServer(Coord* coord, Running* running);
}//tolua_export
}//tolua_export


