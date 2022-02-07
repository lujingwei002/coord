#include "coord/closure/closure.h"
#include "coord/closure/closure_sequence.h"
#include "coord/closure/closure_function.h"
#include "coord/closure/closure_await.h"
#include "coord/closure/closure_wait.h"
#include "coord/closure/closure_if.h"
#include "coord/coord.h"

namespace coord {
namespace closure {

Closure* newClosure(Coord* coord) {
    Closure* self = new Closure(coord);
    return self;
}

Closure::Closure(Coord* coord) : closure_action(coord, this) {
    //this->coord = coord;
    this->deferFunc = nullptr;
    this->catchFunc = nullptr;
    auto sequence = new closure_sequence(coord, this);
    sequence->parent = this;
    this->sequence = sequence;
    this->sequenceArr.push_back(sequence);
    this->action = this->sequence;
}

Closure::~Closure() {
    if (this->action != nullptr) {
        this->coord->Destory(this->action);
        this->action = nullptr;
    }
}

Closure* Closure::End() {
    if (this->sequence == nullptr) {
        return this;
    }
    this->sequenceArr.pop_back();
    this->sequence = this->sequenceArr.back();
    return this;
}

Closure* Closure::_(Function func) {
    if (this->sequence == nullptr) {
        return this;
    }
    auto action = new closure_function(this->coord, this, func);
    this->sequence->addInstruction(action);
    return this;
}

void Closure::call(size_t index) {
    this->action->execute();
}

Closure* Closure::Await(AwaitFunction func, Function thenFunc, Function catchFunc) {
    if (this->sequence == nullptr) {
        return this;
    }
    auto action = new closure_await(this->coord, this, func, thenFunc, catchFunc);
    this->sequence->addInstruction(action);
    return this;
}

Closure* Closure::Wait(uint64_t msec) {
    if (this->sequence == nullptr) {
        return this;
    }
    auto action = new closure_wait(this->coord, this, msec);
    this->sequence->addInstruction(action);
    return this;
}

Closure* Closure::If(IfFunction func) {
    if (this->sequence == nullptr) {
        return this;
    }
    auto action = new closure_if(this->coord, this, func);
    this->sequence->addInstruction(action);
    this->sequenceArr.push_back(action);
    this->sequence = action;
    return this;
}

Closure* Closure::ElseIf(IfFunction func) {
    if (this->sequence == nullptr) {
        return this;
    }
    auto ifInstruction = dynamic_cast<closure_if*>(this->sequence);
    if (ifInstruction == nullptr) {
        return this;
    }
    ifInstruction->addElseIf(func);
    return this;
}

Closure* Closure::Else() {
    if (this->sequence == nullptr) {
        return this;
    }
    auto ifInstruction = dynamic_cast<closure_if*>(this->sequence);
    if (ifInstruction == nullptr) {
        return this;
    }
    ifInstruction->addElse();
    return this;
}

Closure* Closure::Defer(Function func) {
    this->deferFunc = func;
    return this;
}

Closure* Closure::Catch(Function func) {
    this->catchFunc = func;
    return this;
}

void Closure::onComplete(closure_action* action) {
    if (this->deferFunc) this->deferFunc(this);
}

void Closure::Abort() {
    this->action->onAbort();
    if (this->catchFunc) this->catchFunc(this);
    if (this->deferFunc) this->deferFunc(this);
    
}

}

}