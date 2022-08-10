_package_('main')

function onAwake()
    Log("OnAwake")
    local client = coorda:AsyncRedisConfig("REDIS")
    assert(client)

    print('connecting')
    local ok, result = await(client:Connect())
    print('connect result', ok, result)

    local ok, result = await(client:GET("aa"))
    print('get aa result', ok, result:String())


    local ok, result = await(client:SET("aa", "cc"))
    print('get aa result', ok, result:String())

    local ok, result = await(client:GET("aa"))
    print('get aa result', ok, result:String())

    --promise:Then(function(client, reply)
    --    print('bbbbbbbbbbbbbbaaaaaaaaaaaa1')
    --end):Else(function(client, reply)
    --    print('bbbbbbbbbbbbbbaaaaaaaaaaaa2')
    --end)
end

function onDestory()
    Log("OnDestory")
end
