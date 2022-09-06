#include "coord/event/event.h"
#include "coord/coord.h"
#include <limits>

namespace coord {
namespace event {

RC_IMPLEMENT(BaseEvent, "coord::event::BaseEvent")

BaseEvent::BaseEvent(const char* name, const char* arg) : name(name), arg(arg) {
}

BaseEvent::~BaseEvent() {
}

}
}