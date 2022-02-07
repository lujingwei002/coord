#pragma once 



#include <vector>
#include <string>
#include <iostream>
#include <map>

namespace coord {//tolua_export
    
class Coord;

namespace cache {//tolua_export

class CacheConfig {//tolua_export
public:
    std::string     Password;       //tolua_export   
    std::string     DB;             //tolua_export   
    std::string     Host;           //tolua_export
    int16_t         Port;           //tolua_export        
    int             ExpireTime;     //tolua_export  
};//tolua_export

}//tolua_export
}//tolua_export


