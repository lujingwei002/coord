_package_('main')

local math = import('math')
function onAwake()
    Log("onAwake")

    -- 测试reload
    assert(math.Mutable() == 1)
    assert(math.Mutable() == 2)
    math = reload('math')
    assert(math.Mutable() == 1)

    assert(math.Immutable() == 1)
    assert(math.Immutable() == 2)
    math = reload('math')
    assert(math.Immutable() == 3)
end

function onDestory()
    Log("onDestory")
end
