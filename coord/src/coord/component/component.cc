
#include "coord/component/component.h"
#include "coord/event/event_listener.h"
#include "coord/object/object.h"
#include "coord/scene/scene.h"
#include "coord/script/script.h"
#include "coord/coord.h"
#include "coord/log/log.h"

namespace coord {
CC_IMPLEMENT(Component, "coord::Component")

Component::Component(Coord* coord){
    this->coord = coord;
    this->object = nullptr;
    this->isStart = false;
}

Component::~Component(){

}

void Component::onDestory(){
    
}

void Component::onAwake(){
    printf("aaa %p\n", this->coord);
    this->coord->coreLogError("[Component<%s>] onAwake", this->TypeName());
}

void Component::onStart(){
    this->coord->coreLogError("[Component<%s>] onStart", this->TypeName());
}

void Component::onUpdate(uint64_t cur_tick){

}

void Component::onReload() {

}

void Component::SetObject(Object* object){
    this->object = object;
    this->scene = object->scene;
}

Object* Component::GetObject(){
    return this->object;
}

int64_t Component::GetNumber(const char *fieldname){
    if (!this->coord){
        return 0;
    }
    return this->coord->Script->GetNumber(fieldname);
}

const char* Component::GetString(const char *fieldname){
    if (!this->coord){
        return 0;
    }
    return this->coord->Script->GetString(fieldname);
}

int Component::GetFunction(const char *func){
    if (!this->coord){
        return 0;
    }
    return this->coord->Script->GetFunction(func);
}

bool Component::getValue(const char *fieldName){
    if (!this->coord){
        return 0;
    }
    return this->coord->Script->getValue(fieldName);
}

int Component::TraceStack(){
    if (!this->coord){
        return 0;
    }
    return this->coord->Script->TraceStack();
} 

lua_State* Component::GetLuaState(){
    return this->coord->Script->L;
}

Scene* Component::GetScene() {
    if (!this->object){
        return NULL;
    }
    return this->object->scene;
}

int Component::GetComponent(lua_State* L) {
    if (!this->object) {
        this->coord->coreLogError("no object");
        return 0;
    }
    return this->object->GetComponent(L);
}

Component* Component::GetComponent(const char* name){
    if (!this->object) {
        this->coord->coreLogError("no object");
        return NULL;
    }
    return this->object->GetComponent(name);
}

void Component::AddHttpRouterGet(const char* pattern, const char* callback) {

}

void Component::Log(const char* str) const{;
    this->coord->Log("[%s] %s", this->TypeName(), str);
}

void Component::LogFatal(const char* str) const{;
    this->coord->LogFatal("[%s] %s", this->TypeName(), str);
}

void Component::LogError(const char* str) const{
    this->coord->LogError("[%s] %s", this->TypeName(), str);
}

void Component::LogWarn(const char* str) const{
    this->coord->LogWarn("[%s] %s", this->TypeName(), str);
}

void Component::LogInfo(const char* str) const{
    this->coord->LogDebug("[%s] %s", this->TypeName(), str);
}

void Component::LogDebug(const char* str) const{
    this->coord->LogDebug("[%s] %s", this->TypeName(), str);
}

void Component::LogMsg(const char* str) const{
    this->coord->LogMsg("[%s] %s", this->TypeName(), str);
}

void Component::coreLogFatal(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    this->coord->coreLogFatal(fmt, args);
    va_end(args);
}

void Component::coreLogError(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    this->coord->coreLogError(fmt, args);
    va_end(args);
}

void Component::coreLogWarn(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    this->coord->coreLogWarn(fmt, args);
    va_end(args);
}

void Component::coreLogInfo(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    this->coord->coreLogInfo(fmt, args);
    va_end(args);
}

void Component::coreLogDebug(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    this->coord->coreLogDebug(fmt, args);
    va_end(args);
}

void Component::coreLogMsg(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    this->coord->coreLogMsg(fmt, args);
    va_end(args);
}

}