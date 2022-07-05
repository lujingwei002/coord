_package_('math')

-- reload 后值会重置
local mutable = 0

-- reload 后值也不会改变
immutable = immutable or 0

function onReload()
    Log("onReload")
end

function onAwake()
    Log("OnAwake")
end

function onDestory()
    Log("OnDestory")
end

function Mutable()
    mutable = mutable + 1
    return mutable
end

function Immutable()
    immutable = immutable + 1
    return immutable
end






