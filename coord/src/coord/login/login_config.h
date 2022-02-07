#pragma once 


#include <map>
#include <string>

namespace coord {//tolua_export

class Coord;

namespace login {//tolua_export

class LoginConfig {//tolua_export
public:
    std::string     Host;           //tolua_export
    unsigned short  Port;           //tolua_export
    int             Backlog;        //tolua_export
    int             RecvBufferSize; //tolua_export
    bool            SSLEncrypt;     //tolua_export
    std::string     SSLPemFile;     //tolua_export
    std::string     SSLKeyFile;     //tolua_export
    std::string     Cluster;        //tolua_export
};//tolua_export 




}//tolua_export
}//tolua_export