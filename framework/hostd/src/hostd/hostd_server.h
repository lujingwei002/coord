#pragma once 

#include "coord/builtin/init.h"
#include "coord/net/init.h"
#include <vector>
#include <iostream>
#include <map>

namespace coord {
class Coord;
}

namespace hostd {//tolua_export

class Hostd;
class HostdAgent;

class HostdServer : public coord::net::ITcpHandler  {//tolua_export
public:
    HostdServer(coord::Coord *coord, Hostd* hostd);
    virtual ~HostdServer();
public:
    // implement net::ITcpHandler begin
    virtual void recvTcpNew(coord::net::TcpListener* listener, coord::net::TcpAgent* tcpAgent);
    // implement net::ITcpHandler end
    void recvTcpClose(HostdAgent* agent);
    int start();
    void close();
public:
    coord::Coord* coord;
    coord::net::TcpListener* listener;
    Hostd* hostd;
    std::map<int, HostdAgent*> agentDict;
};//tolua_export

HostdServer* newHostdServer(coord::Coord* coord, Hostd* hostd);
}//tolua_export



