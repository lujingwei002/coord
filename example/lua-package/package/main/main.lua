_package_('main')

local math = import('math')
function onAwake()
    Log("onAwake")
    print('onAwake')
    print('包名', __NAME)
    print('包的导入路径', __PACKAGE)
    print('包的完整路径', __PATH)

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
