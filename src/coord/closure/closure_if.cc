#include "coord/closure/closure_if.h"
#include "coord/closure/closure_action.h"
#include "coord/closure/closure.h"
#include "coord/coordx.h"
#include "coord/coord.h"

namespace coord {

namespace closure {
RC_IMPLEMENT(closure_if, "coord::closure::closure_if")

closure_if::closure_if(Coord* coord, Closure* closure, IfFunction func) : closure_sequence(coord, closure) {
    this->ifFunc = func;
    this->status = 0;
    this->ifSequence = nullptr;
    this->elseSequence = nullptr;
}

closure_if::~closure_if() {
    if (this->ifSequence != nullptr) {
        this->coord->Destory(this->ifSequence);
        this->ifSequence = nullptr;
    }
    if (this->elseSequence != nullptr) {
        this->coord->Destory(this->elseSequence);
        this->elseSequence = nullptr;
    }
    for (const auto it : this->elseIfSequenceArr) {
        this->coord->Destory(it);
    }
    this->elseIfSequenceArr.clear();
    this->elseIfFuncArr.clear();
}

void closure_if::execute() {
    if (!this->ifFunc) {
        if (this->parent)this->parent->onComplete(this);
        return;
    }
    /// 执行if分支
    bool result = this->ifFunc(this->closure);
    if (result) {
        if (this->ifSequence)this->ifSequence->execute();
        return;
    }
    /// 执行elseif分支
    for (size_t index = 0; index < this->elseIfFuncArr.size(); index++) {
        bool result = this->elseIfFuncArr[index](this->closure);
        if (result) {
            this->elseIfSequenceArr[index]->execute();
            return;
        }
    }
    /// 执行else分支
    if (this->elseSequence) {
        this->elseSequence->execute();
        return;
    }
}

void closure_if::addElseIf(IfFunction func) {
    if (this->status != 0) {
        return;
    }
    this->elseIfFuncArr.push_back(func);
    auto sequence = new closure_sequence(this->coord, this->closure);
    sequence->parent = this;
    this->elseIfSequenceArr.push_back(sequence);
    this->sequence = sequence;
}

void closure_if::addElse() {
    if (this->status != 0) {
        return;
    }
    this->status = 1;
    auto sequence = new closure_sequence(this->coord, this->closure);
    sequence->parent = this;
    this->elseSequence = sequence;
    this->sequence = sequence;
}

void closure_if::addInstruction(closure_action* action) {
    if (this->sequence == nullptr) {
        auto sequence = new closure_sequence(this->coord, this->closure);
        sequence->parent = this;
        this->ifSequence = sequence;
        this->sequence = sequence;
    } 
    this->sequence->addInstruction(action);
}

void closure_if::onComplete(closure_action* action) {
    if (this->isAbort) return;
    if (this->parent) this->parent->onComplete(this);
}


}
}