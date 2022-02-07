
#pragma once 
#include <map>
#include <string>

namespace coord {//tolua_export

namespace gate {//tolua_export



class GateConfig {//tolua_export
public:
    std::string     ServerName;       //tolua_export
    std::string     Host;       //tolua_export
    std::string     Network;    //tolua_export
    unsigned short  Port;    //tolua_export
    bool            RsaEncrypt;        //tolua_export
    std::string     RsaKeyFile; //tolua_export
    int             Heartbeat;          //tolua_export
    int             Backlog;            //tolua_export
    int             RecvBuffer;         //tolua_export
    bool            SSLEncrypt;        //tolua_export
    std::string     SSLPemFile; //tolua_export
    std::string     SSLKeyFile; //tolua_export
    int             MaxUser;            //tolua_export
    int             MaxConnection;      //tolua_export
    std::string     Cluster;    //tolua_export
    uint32_t        UserRegisterExpire;     //tolua_export  agent注册的过期时间
    uint16_t        UserRegisterInterval;   //tolua_export  agent注册间隔
    uint32_t        RegisterExpire;     //tolua_export  gate注册的过期时间
    uint16_t        RegisterInterval;   //tolua_export  gate注册间隔
};//tolua_export

}//tolua_export

}//tolua_export
