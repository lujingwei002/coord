#pragma once 

#include "coord/coordx.h"
#include "coord/closure/closure_function.h"
#include "coord/closure/closure_action.h"
#include "coord/closure/closure_base.h"
#include <functional>
#include <vector>
#include <map>
#include <any>
namespace coord {
class Coord;

namespace closure {

class Closure;
class closure_action;
class closure_sequence;

typedef std::function<void (Closure*)> Code; 

class Closure : public closure_action {
public:
    Closure(Coord*  coord);
    virtual ~Closure();
public:

    void createArg() {}
    template<class T, class... Args>
    void createArg(T arg, Args... args) {
        this->argumentArr.push_back(arg);
        this->argumentDict[arg] = nullptr;
        createArg(args...);
    }
    
    std::any Arg(const char* name) {
        auto it = this->argumentDict.find(name);
        if (it == this->argumentDict.end()) {
            return NULL;
        }
        return it->second;
    }

    void Args(const char* name, std::any value) {
        this->argumentDict[name] = value;
    }

    std::any Value(const char* name) {
        auto it = this->valueDict.find(name);
        if (it == this->valueDict.end()) {
            return NULL;
        }
        return it->second;
    }

    void Value(const char* name, std::any value) {
        this->valueDict[name] = value;
    }

    void call(size_t index);
    template<class T, class... Args>
    void call(size_t index, T value, Args... args) {
        if (index >= this->argumentArr.size()) {
            this->call(index + 1);
            return;
        }
        std::string& key = this->argumentArr[index];
        this->argumentDict[key] = value;
        this->call(index + 1, args...);
    }
    template<class... Args>
    void Call(Args... args) {
        this->call(0, args...);
    }

    Closure* End();
    
    void Abort();
    Closure* _(Function func);
    Closure* Defer(Function func);
    Closure* Catch(Function func);
    Closure* If(IfFunction func);
    Closure* ElseIf(IfFunction func);
    Closure* Else();
    Closure* Wait(uint64_t msec);
    Closure* Await(AwaitFunction func, Function thenFunc = nullptr, Function catchFunc = nullptr);
public:
    virtual void onComplete(closure_action* action);
public:
    std::map<std::string, std::any>     argumentDict;
    std::vector<std::string>            argumentArr;
    closure_action*                     action;
    closure_sequence*                   sequence;
    std::vector<closure_sequence*>      sequenceArr;
    Function                            deferFunc;
    Function                            catchFunc;
    std::map<std::string, std::any>     valueDict;
};

Closure* newClosure(Coord* coord);
}
}