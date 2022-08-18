#pragma once 


#include <string>

namespace coord {

class NotImplementException {
public:
    NotImplementException(const char* msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

class NotConfigException {
public:
    NotConfigException(const char* msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

class ScriptException {
public:
    ScriptException(const char* msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};


class ArgumentException {
public:
    ArgumentException(const char* msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

}

