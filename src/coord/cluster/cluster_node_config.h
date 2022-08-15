#pragma once 

#include "coord/coordx.h"
#include <vector>
#include <iostream>
#include <map>
namespace coord {//tolua_export
    
class Coord;


namespace cluster {//tolua_export

class Cluster;

class cluster_node {
public:
    cluster_node(const char* name, const char* address, uint64_t version);
    ~cluster_node() {}
public:
    std::string name;
    std::string address;
    uint64_t version;
    std::string host;
    int16_t port;
};

class cluster_node_config  {//tolua_export
public:
    cluster_node_config(Coord *coord, Cluster* cluster);
    virtual ~cluster_node_config();
public:
    virtual int main() {return 0;}
    virtual int reload() {return 0;}
    virtual int reload(const char* node, uint64_t version) {return 0;}
    virtual int heartbeat() {return 0;}
public:
    Coord*      coord;
    Cluster*    cluster;
    std::string name;
    std::string fullName;
    uint64_t    version;
};//tolua_export


}//tolua_export
}//tolua_export


