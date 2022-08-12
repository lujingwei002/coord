#pragma once 

#include "coord/builtin/type.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor_database.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>


namespace coord {//tolua_export
   
   
    namespace protobuf {//tolua_export
        class Protobuf;
        class Reflect;
        class Array;
        class my_multi_file_error_collector;
        class Message;                                                
        class RepeatMessage;                                          
        typedef coord::RcRef<coord::protobuf::Message> MessageRef;               //tolua_export                
        typedef coord::RcRef<coord::protobuf::RepeatMessage> RepeatMessageRef;   //tolua_export
    } //tolua_export
} //tolua_export
