_package_('main')

local math = import('math')
function OnAwake()
    Log("OnAwake")

    -- 测试reload
    Log(math.Mutable() == 1 and 'true' or 'false')
    Log(math.Mutable() == 2 and 'true' or 'false')
    math = reload('math')
    Log(math.Mutable() == 1 and 'true' or 'false')

    Log(math.Immutable() == 1 and 'true' or 'false')
    Log(math.Immutable() == 2 and 'true' or 'false')
    math = reload('math')
    Log(math.Immutable() == 3 and 'true' or 'false')
end

function OnDestory()
    Log("OnDestory")
end
