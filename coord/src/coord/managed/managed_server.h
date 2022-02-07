#pragma once 

#include "coord/builtin/type.h"
#include "coord/net/tcp_listener.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;

namespace managed {//tolua_export

class Managed;
class Packet;
class ManagedAgent;

class ManagedServer : public net::ITcpHandler  {//tolua_export
public:
    ManagedServer(Coord *coord, Managed* managed);
    virtual ~ManagedServer();
public:
    // implement net::ITcpHandler begin
    virtual void recvTcpNew(net::TcpListener* listener, net::TcpAgent* tcpAgent);
    // implement net::ITcpHandler end
    void recvTcpClose(ManagedAgent* agent);
    int start();
    void close();
public:
    Coord* coord;
    net::TcpListener* listener;
    Managed* managed;
    std::map<int, ManagedAgent*> agentDict;
};//tolua_export

ManagedServer* newManagedServer(Coord* coord, Managed* managed);
}//tolua_export
}//tolua_export


