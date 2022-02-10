#pragma once 

#include "coord/builtin/init.h"
#include "coord/net/init.h"
#include <vector>
#include <iostream>
#include <map>

namespace coord {
class Coord;
}

namespace consoled {//tolua_export

class Consoled;
class ConsoledAgent;

class ConsoledServer : public coord::net::ITcpHandler  {//tolua_export
public:
    ConsoledServer(coord::Coord *coord, Consoled* consoled);
    virtual ~ConsoledServer();
public:
    // implement net::ITcpHandler begin
    virtual void recvTcpNew(coord::net::TcpListener* listener, coord::net::TcpAgent* tcpAgent);
    // implement net::ITcpHandler end
    void recvTcpClose(ConsoledAgent* agent);
    int start();
    void close();
public:
    coord::Coord*                   coord;
    coord::net::TcpListener*        listener;
    Consoled*                       consoled;
    std::map<int, ConsoledAgent*>   agentDict;
};//tolua_export

ConsoledServer* newConsoledServer(coord::Coord* coord, Consoled* consoled);
}//tolua_export



