#include "coord/timer/timer.h"
#include "coord/coordx.h"
#include "coord/script/script.h"
#include "coord/coord.h"

#include <stdio.h>
#include <assert.h>
#include <iostream>

namespace coord {
namespace timer {

RC_IMPLEMENT(timer, "coord::timer::timer")
RC_IMPLEMENT(cron, "coord::timer::cron")

void uv_timer_cb (uv_timer_t *handle) {
    timer* t = (timer*)handle->data;
    uint64_t repeated = t->exec();
    if (t->repeat == 0){
        t->timerMgr->ClearInterval(t->id);
    } else if(repeated == std::numeric_limits<uint64_t>::max()) {
        t->timerMgr->ClearInterval(t->id);
    } else if(repeated > 0) {
        uv_timer_set_repeat(&t->handle, (uint64_t)repeated);
    }
}


void uv_cron_cb (uv_timer_t *handle) {
    cron* t = (cron*)handle->data;
    t->exec();
    t->reset();
}


timer::timer(Coord *coord, TimerMgr* timerMgr) {
    this->coord = coord;
    this->timerMgr = timerMgr;
    uv_timer_init(&this->coord->loop, &this->handle);
    this->handle.data = this;
    this->func = NULL;
    this->ref = 0;
} 

timer::~timer() {
    int err = uv_timer_stop(&this->handle);
    if (err < 0){
        this->coord->CoreLogError("[coord::timer] ~ failed, error=%d", err);
    }
    if (this->ref >= 0) {
        lua_unref(this->coord->Script->L, this->ref);
        this->ref = LUA_NOREF;
    }
}

uint64_t timer::exec(){
    if(!this->func){
        return 0;
    }
    return this->func();
}

cron::cron(Coord *coord, TimerMgr* timerMgr) {
    this->coord = coord;
    this->timerMgr = timerMgr;
    uv_timer_init(&this->coord->loop, &this->handle);
    this->handle.data = this;
    this->func = NULL;
    this->ref = 0;
} 

cron::~cron() {
    int err = uv_timer_stop(&this->handle);
    if (err < 0){
        this->coord->CoreLogError("[coord::cron] ~ failed, error=%d", err);
    }
    if (this->ref >= 0) {
        lua_unref(this->coord->Script->L, this->ref);
        this->ref = LUA_NOREF;
    }
}

void cron::reset() {
    time_t next = cron_next(&this->expr, this->coord->Time()/1000);
    int err = uv_timer_stop(&this->handle);
    if (err < 0){
        this->coord->CoreLogError("[coord::cron] reset failed, error=%d", uv_strerror(err));
        return;
    }
    this->timeout = next * 1000 - this->coord->Time();
    uv_timer_init(&this->coord->loop, &this->handle);
    this->handle.data = this;
    err = uv_timer_start(&this->handle, uv_cron_cb, this->timeout, this->repeat);
    if(err < 0){
        this->coord->CoreLogError("[coord::cron] reset failed, error='%s'", uv_strerror(err));
        return;
    }
    strftime(this->next, sizeof(this->next), "%Y-%m-%d_%H:%M:%S", localtime(&next));
    this->coord->CoreLogDebug("[coord::cron] reset, timeout:%ld next %s\n", this->timeout, this->next);
}

void cron::exec(){
    if(!this->func){
        return;
    }
    return this->func();
}

TimerMgr* newTimerMgr(Coord *coord) {
    TimerMgr* timerMgr = new TimerMgr(coord);
    return timerMgr;
}

TimerMgr::TimerMgr(Coord *coord) {
    this->coord = coord;
    this->id = 0;
}

TimerMgr::~TimerMgr() {
    for(auto it = this->timerDict.begin(); it != this->timerDict.end();) {
        timer* t = it->second;
        delete t;
        ++it;
    }
    this->timerDict.clear();
    for(auto it = this->cronDict.begin(); it != this->cronDict.end();) {
        cron* t = it->second;
        delete t;
        ++it;
    }
    this->cronDict.clear();
}

int TimerMgr::SetTimeout(uint64_t timeout, TimeoutFunc func) {
    return this->addTimer(timeout, 0, func);
}

int TimerMgr::SetInterval(uint64_t repeat, TimeoutFunc func) {
    return this->addTimer(repeat, repeat, func);
}


int TimerMgr::SetTimeout(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::Coord",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isnumber(L,3,0,&tolua_err) ||
        !tolua_isfunction(L,4,0,&tolua_err) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        uint64_t timeout = (uint64_t)lua_tonumber(L, 3);
        lua_pushvalue(L, 4);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'SetTimeout'.\nattempt to set a nil function", NULL);
            return 0;
        }
        int tolua_ret = (int) this->setTimeout(timeout, object, ref);
        tolua_pushnumber(L, tolua_ret);
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'SetTimeout'.",&tolua_err);
    return 0;
}

int TimerMgr::SetInterval(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::Coord",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isnumber(L,3,0,&tolua_err) ||
        !tolua_isfunction(L,4,0,&tolua_err) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        uint64_t repeat = (uint64_t)lua_tonumber(L, 3);
        lua_pushvalue(L, 4);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'SetInterval'.\nattempt to set a nil function", NULL);
            return 0;
        }
        int tolua_ret = (int) this->setInterval(repeat, object, ref);
        tolua_pushnumber(L, tolua_ret);
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'SetInterval'.",&tolua_err);
    return 0;
}

int TimerMgr::SetCron(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::Coord",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isstring(L,3,0,&tolua_err) ||
        !tolua_isfunction(L,4,0,&tolua_err) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        const char* expression = (const char* )lua_tostring(L, 3);
        lua_pushvalue(L, 4);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'SetCron'.\nattempt to set a nil function", NULL);
            return 0;
        }
        int tolua_ret = (int) this->setCron(expression, object, ref);
        tolua_pushnumber(L, tolua_ret);
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'SetCron'.",&tolua_err);
    return 0;
}

int TimerMgr::setTimeout(uint64_t timeout, ScriptComponent* object, int ref) {
    return this->addTimer(timeout, 0, object, ref);
}

int TimerMgr::setInterval(uint64_t repeat, ScriptComponent* object, int ref) {
    return this->addTimer(repeat, repeat, object, ref);
}

int TimerMgr::addTimer(uint64_t timeout, uint64_t repeat, TimeoutFunc func) {
    //this->coord->CoreLogDebug("[TimeMgr] SetTimer, timeout=%ld, repeat=%ld", timeout, repeat);
    int id = ++this->id;
    timer* t = new timer(this->coord, this);
    t->timeout = timeout;
    t->repeat = repeat;
    t->id = id;
    t->func = func;
    int err = uv_timer_start(&t->handle, uv_timer_cb, timeout, repeat);
    if(err < 0){
        this->coord->CoreLogError("[coord::TimerMgr] addTimer failed, error='%s'", uv_strerror(err));
        return -1;
    }
    this->timerDict[id] = t;
    return id;
}

int TimerMgr::addTimer(uint64_t timeout, uint64_t repeat, ScriptComponent* object, int ref) {
    //this->coord->CoreLogDebug("[TimeMgr] SetTimer, timeout=%ld, repeat=%ld", timeout, repeat);
    int id = ++this->id;
    timer* t = new timer(this->coord, this);
    t->timeout = timeout;
    t->repeat = repeat;
    t->id = id;
    t->ref = ref;
    t->func = std::bind(&ScriptComponent::recvTimer, object, "recvTimer", ref);
    int err = uv_timer_start(&t->handle, uv_timer_cb, timeout, repeat);
    if(err < 0){
        this->coord->CoreLogError("[coord::TimerMgr] addTimer failed, error='%s'", uv_strerror(err));
        return -1;
    }
    this->timerDict[id] = t;
    return id;
}

int TimerMgr::ClearInterval(int id) {
    auto it = this->timerDict.find(id);
    if(it == this->timerDict.end()){
        return ErrorInvalid;
    }
    timer* t = it->second;
    delete t;
    this->timerDict.erase(it);
    return 0;
}

int TimerMgr::ClearTimeout(int id) {
    auto it = this->timerDict.find(id);
    if(it == this->timerDict.end()){
        return ErrorInvalid;
    }
    timer* t = it->second;
    delete t;
    this->timerDict.erase(it);
    return 0;
}

int TimerMgr::ClearCron(int id) {
    auto it = this->cronDict.find(id);
    if(it == this->cronDict.end()){
        return ErrorInvalid;
    }
    cron* t = it->second;
    delete t;
    this->cronDict.erase(it);
    return 0;
}

int TimerMgr::SetCron(const char* expression, CronFunc func) {
    cron_expr expr;
    const char* error = NULL;
    memset(&expr, 0, sizeof(expr));
    cron_parse_expr(expression, &expr, &error);
    if (error) {
        this->coord->CoreLogError("[coord::TimerMgr] SetCron failed, error='%s'", error);
        return -1;
    }
    time_t next = cron_next(&expr, this->coord->Time()/1000);
    int id = ++this->id;
    cron* t = new cron(this->coord, this);
    t->timeout = next * 1000 - this->coord->Time();
    t->repeat = 0;
    t->id = id;
    t->func = func;
    t->expr = expr;
    int err = uv_timer_start(&t->handle, uv_cron_cb, t->timeout, t->repeat);
    if(err < 0){
        this->coord->CoreLogError("[coord::TimerMgr] SetCron failed, error='%s'", uv_strerror(err));
        return -1;
    }
    this->cronDict[id] = t;
    strftime(t->next, sizeof(t->next), "%Y-%m-%d_%H:%M:%S", localtime(&next));
    this->coord->CoreLogDebug("[coord::TimerMgr] SetCron, timeout:%ld next %s\n", t->timeout, t->next);
    return id;
}

int TimerMgr::setCron(const char* expression, ScriptComponent* object, int ref) {
    cron_expr expr;
    const char* error = NULL;
    memset(&expr, 0, sizeof(expr));
    cron_parse_expr(expression, &expr, &error);
    if (error) {
        this->coord->CoreLogError("[coord::TimerMgr] SetCron failed, error='%s'", error);
        return -1;
    }
    time_t next = cron_next(&expr, this->coord->Time()/1000);
    int id = ++this->id;
    cron* t = new cron(this->coord, this);
    t->timeout = next * 1000 - this->coord->Time();
    t->repeat = 0;
    t->id = id;
    t->ref = ref;
    t->func = std::bind(&ScriptComponent::recvCron, object, "recvCron", ref);
    t->expr = expr;
    int err = uv_timer_start(&t->handle, uv_cron_cb, t->timeout, t->repeat);
    if(err < 0){
        this->coord->CoreLogError("[coord::TimerMgr] SetCron failed, error='%s'", uv_strerror(err));
        return -1;
    }
    this->cronDict[id] = t;
    strftime(t->next, sizeof(t->next), "%Y-%m-%d_%H:%M:%S", localtime(&next));
    this->coord->CoreLogDebug("[coord::TimerMgr] SetCron, timeout:%ld next %s\n", t->timeout, t->next);
    return id;
}

//int uv_timer_start(uv_timer_t *handle, uv_timer_cb cb, uint64_t timeout, uint64_t repeat)
}
}