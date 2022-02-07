#pragma once 

#include "coord/builtin/init.h"

#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace closure {

class Wait;
class Closure;
class ClosurePromise;

typedef std::function<bool (Closure* self)> IfFunction; 
typedef std::function<void (Closure* self)> Function; 
typedef std::function<void (Closure* self, ClosurePromise* promise)> AwaitFunction; 


}
}