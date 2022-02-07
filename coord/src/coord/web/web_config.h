#pragma once 


#include <string>
namespace coord {//tolua_export

class Coord;

namespace web {//tolua_export



class WebConfig {//tolua_export
public:
    uint16_t        Port;       //tolua_export
    std::string     Host;       //tolua_export
    int             Backlog;    //tolua_export
    int             RecvBuffer; //tolua_export
    bool            SSLEncrypt; //tolua_export
    std::string     SSLPemFile; //tolua_export
    std::string     SSLKeyFile; //tolua_export
    std::string     AssetDir;   //tolua_export
    bool            UseEtag;    //tolua_export
};//tolua_export

}//tolua_export
}//tolua_export