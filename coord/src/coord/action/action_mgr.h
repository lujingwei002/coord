#pragma once 

namespace coord {
class Coord;
namespace action {

class Action;
class Animation;

class ActionMgr {
public:
    ActionMgr(Coord*  coord);
    ~ActionMgr();
public:
    Animation* Begin();
public:
    Coord*  coord;
};

ActionMgr* newActionMgr(Coord* coord);
}
}