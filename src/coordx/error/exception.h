#pragma once 


#include <string>

namespace coord {

class NotImplementException {
public:
    NotImplementException(const std::string& msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

class NotConfigException {
public:
    NotConfigException(const std::string& msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

class ScriptException {
public:
    ScriptException(const std::string& msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};


class ArgumentException {
public:
    ArgumentException(const std::string& msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

}


