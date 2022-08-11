#pragma once 

namespace coord {//tolua_export
   
   
    
    namespace log4cc {//tolua_export
        class LoggerMgr;
        class Category;

        //tolua_begin
        typedef enum {
            EMERG = 0,
            FATAL = 0,
            ALERT = 100,
            CRIT = 200,
            ERROR = 300,
            WARN = 400,
            NOTICE = 500,
            INFO = 600,
            DEBUG = 700,
            NOTSET = 800,
            ALL = 1000,
        } PriorityLevel;
        //tolua_end


    }//tolua_export
} //tolua_export
