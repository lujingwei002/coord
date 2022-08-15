#pragma once 

#include "coord/coordx.h"
#include "coord/component/script_component.h"
#include <uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <functional>
extern "C" {
#include "ccronexpr/ccronexpr.h"
}

namespace coord {//tolua_export
    
class Coord;

namespace timer {//tolua_export

typedef std::function<uint64_t ()> TimeoutFunc; 
typedef std::function<void ()> CronFunc; 

class TimerMgr;

class timer {
CC_CLASS(timer);
public:
    timer(Coord *coord, TimerMgr* timerMgr);
    virtual ~timer();
public:
    uint64_t exec();
public:
    TimeoutFunc     func;
    int             ref;
    std::string     script;
    uv_timer_t      handle;
    uint64_t        timeout;
    uint64_t        repeat;
    Coord*          coord;
    TimerMgr*       timerMgr;
    int             id;
};

class cron {
CC_CLASS(cron);
public:
    cron(Coord *coord, TimerMgr* timerMgr);
    virtual ~cron();
public:
    void exec();
    void reset();
public:
    CronFunc        func;
    int             ref;
    std::string     script;
    uv_timer_t      handle;
    uint64_t        timeout;
    uint64_t        repeat;
    Coord*          coord;
    TimerMgr*       timerMgr;
    int             id;
    cron_expr       expr;
    char            next[32];
};

///
/// #cron
/// 秒 分钟 小时 日  月  周
/// *   *    *   *  *  *
/// 1-12    指定范围
/// 1,2,3   指定固定数值
/// */1     指定间隔
///
class TimerMgr {//tolua_export
public:
    TimerMgr(Coord *coord);
    ~TimerMgr();
public:
    /// 在指定的毫秒数后调用函数或计算表达式
    int SetTimeout(uint64_t timeout, TimeoutFunc func);

    /// 可按照指定的周期（以毫秒计）来调用函数或计算表达式
    /// SetInterval() 方法会不停地调用函数，直到 ClearInterval() 被调用或窗口被关闭。由 SetInterval() 返回的 ID 值可用作 ClearInterval() 方法的参数。
    int SetInterval(uint64_t repeat, TimeoutFunc func);

    /// 在指定的间隔调用函数或计算表达式，直到 ClearCron() 被调用或窗口被关闭。由 SetCron() 返回的 ID 值可用作 ClearCron() 方法的参数。
    int SetCron(const char* expression, CronFunc func);

    int SetTimeout(lua_State* L);   //tolua_export
    int SetInterval(lua_State* L);  //tolua_export
    int SetCron(lua_State* L);      //tolua_export

    int ClearInterval(int id);
    int ClearTimeout(int id);
    int ClearCron(int id);
private:
    int setTimeout(uint64_t timeout, ScriptComponent* object, int ref);
    int setInterval(uint64_t repeat, ScriptComponent* object, int ref); 
    int setCron(const char* expression, ScriptComponent* object, int ref);
    int addTimer(uint64_t timeout, uint64_t repeat, TimeoutFunc func);
    int addTimer(uint64_t timeout, uint64_t repeat, ScriptComponent* object, int ref);
public:
    Coord*                  coord;
    int                     id;
    std::map<int, timer*>   timerDict;
    std::map<int, cron*>    cronDict;
};//tolua_export

TimerMgr* newTimerMgr(Coord *coord);

}//tolua_export
}//tolua_export


