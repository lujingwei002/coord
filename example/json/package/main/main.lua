_package_('main')

function onAwake()
    Log("OnAwake11")
    local json = coorda.Json:NewString("hello world")
    print(json:ToString())
    -- 数组
    local user = coorda.Json:NewObject()
    user.name = 'cc'
    user.score = 1.2
    -- 值是对象，对象里有字典
    user.lang = {name = 'lua', versoin = 51, owner = {"aa", "bb"}}
    print('ff')
    -- 值是数组，数组里有对象， 字典部分被忽略
    user.book = {'lua', 1, {a = 'b'}, ignore = '这个字典会被忽略'}
    user[1] = '设置失败，因为user是字典'
    print(user.name)
    print(user:ToString())

    -- 对象
    local heroArr = coorda.Json:NewArray()
   -- heroArr:AddNumber(3)
    heroArr[10] = 3
    print(heroArr:ToString())

    -- 值是jsonref
    heroArr[1] = user
    heroArr[2] = {user}
    print(heroArr:ToString())
end

function onDestory()
    Log("OnDestory")
end
