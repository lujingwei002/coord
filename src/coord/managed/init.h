
#pragma once
#include "coord/managed/managed.h"
#include "coord/managed/managed_client.h"
#include "coord/managed/managed_promise.h"
#include "coord/managed/managed_agent.h"
#include "coord/managed/managed_result.h"

namespace cood {
namespace managed {
    typedef coord::managed::ManagedAgent Agent;
    typedef coord::managed::ManagedRequest Request;
    typedef coord::managed::ManagedNotify Notify;
    typedef coord::managed::ManagedResponse Response;
    typedef coord::managed::ManagedResult Result;
}
typedef coord::managed::ManagedAgent ManagedAgent;
typedef coord::managed::ManagedRequest ManagedRequest;
typedef coord::managed::ManagedNotify ManagedNotify;
typedef coord::managed::ManagedResponse ManagedResponse;
typedef coord::managed::ManagedResult ManagedResult;

}
