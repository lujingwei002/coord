#include "coord/cluster/cluster_node_config.h"
#include "coord/cluster/cluster.h"
#include "coord/coord.h"

namespace coord {
namespace cluster {



cluster_node::cluster_node(const char* name, const char* address, uint64_t version) {
    this->name = name;
    this->address = address;
    this->version = version;
    const char* port = strchr(address, ':');
    if (port != NULL){
        this->host.assign(address, port - address);
        this->port = atoi(port + 1);
    } else {
        this->host = address;
        this->port = 0;
    }
}

cluster_node_config::cluster_node_config(Coord *coord, Cluster* cluster) {
    this->coord = coord;
    this->cluster = cluster;
}

cluster_node_config::~cluster_node_config() {
    
}




}
}        