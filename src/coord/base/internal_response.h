#pragma once 
#include "coord/base/base_response.h"

namespace coord {//tolua_export



class internal_response : public base_response {//tolua_export
RC_CLASS(internal_response);
protected:
    internal_response(Coord* coord, internal_agent* agent, base_request* request);
    virtual ~internal_response();
public:
    virtual int Flush();
    /// ##export method
    /// 返回JSON格式的数据
    int Json();

    /// 返回protobuf格式的数据。 
    int Proto(google::protobuf::Message& message);
    protobuf::MessageRef& Proto(const char* name);         //tolua_export
    int Proto(protobuf::MessageRef& proto);                //tolua_export
    protobuf::MessageRef& Proto();                         //tolua_export

    /// 返回字符串类型的数据
    int String(const char* data, size_t len);
    int String(const char* data);                       //tolua_export

    /// 返回argument类型的数据
    Argument* Args();                                   //tolua_export
    int Pack(lua_State* L);                             //tolua_export 

    /// 返回table类型的数据
    int Table(lua_State* L);                            //tolua_export
    script::Variable& Table();
private:
    internal_agent* agent;
};//tolua_export
}//tolua_export
