#pragma once 

#include "coord/coordx.h"
#include "coord/net/tcp_listener.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;

namespace cluster {//tolua_export

class Cluster;
class cluster_packet;
class cluster_agent;

class cluster_server : public net::ITcpHandler  {//tolua_export
public:
    cluster_server(Coord *coord, Cluster* cluster);
    virtual ~cluster_server();
public:
    // implement net::ITcpHandler begin
    virtual void recvTcpNew(net::TcpListener* listener, net::TcpAgent* tcpAgent);
    // implement net::ITcpHandler end
    void recvTcpClose(cluster_agent* agent);
    int main();
    void heartbeat();
    void close();
public:
    Coord*                          coord;
    net::TcpListener*               listener;
    Cluster*                        cluster;
    std::map<int, cluster_agent*>   agentDict;
};//tolua_export

cluster_server* newClusterServer(Coord* coord, Cluster* cluster);
}//tolua_export
}//tolua_export


