#pragma once 

namespace coord {
   
   
    
    namespace timer {
        class TimerMgr;
        class timer;
        class cron;
        typedef std::function<uint64_t ()> TimeoutFunc; 
        typedef std::function<void ()> CronFunc; 
    }
} 
