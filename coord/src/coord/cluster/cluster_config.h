
#pragma once 


#include <string>

namespace coord {//tolua_export
    


namespace cluster {//tolua_export



class ClusterConfig {//tolua_export
public:
    /// 节点地址的保存方式，目录仅支持redis
    std::string     Driver;             //tolua_export  
    /// 节点地址
    std::string     Host;               //tolua_export  
    /// 节点端口
    uint16_t        Port;               //tolua_export  
    /// 节点间的心跳间隔
    uint16_t        Heartbeat;          //tolua_export  
    /// 节点位置的过期时间
    uint32_t        Expire;             //tolua_export  
    /// 节点名字
    std::string     Name;               //tolua_export  
    /// 节点注册间隔
    uint16_t        RegisterInterval;   //tolua_export  
    /// 节点位置更新间隔
    uint16_t        ReloadInterval;     //tolua_export  
    /// 节点间的重连间隔
    uint16_t        ReconnectInterval;  //tolua_export  
    int             RecvBuffer;         //tolua_export

};//tolua_export

}//tolua_export
}//tolua_export