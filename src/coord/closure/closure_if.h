#pragma once 

#include "coord/builtin/inc.h"
#include "coord/closure/closure_sequence.h"
#include "coord/closure/closure_base.h"
#include <functional>
#include <vector>
#include <map>

namespace coord {
class Coord;

namespace closure {

class closure_action;

class closure_if : public closure_sequence {
CC_CLASS(closure_if);    
public:
    closure_if(Coord* coord, Closure* closure, IfFunction func);
    virtual ~closure_if();
public:
    void addElseIf(IfFunction func);
    void addElse();
public:
    // implement closure_action
    virtual void execute();
    virtual void onComplete(closure_action* action);
    /// implement closure_sequence
    virtual void addInstruction(closure_action* action);
public:
    int                                     status;
    IfFunction                              ifFunc;
    closure_sequence*                       ifSequence;
    std::vector<IfFunction>                 elseIfFuncArr;
    std::vector<closure_sequence*>          elseIfSequenceArr;
    closure_sequence*                       elseSequence;
    closure_sequence*                       sequence;

};


}
}