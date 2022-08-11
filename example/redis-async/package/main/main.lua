_package_('main')

function onAwake()
    Log("OnAwake")
    local client = coorda:AsyncRedisConfig("REDIS")
    assert(client)

    print('connecting')
    local ok, result = await(client:Connect())
    print('connect result', ok, result)


    local promise = client:GET("aa")

    promise:Then(function(client, result)
        print('bbbbbbbbbbbbbbaaaaaaaaaaaa1', result:String())
    end):Else(function(client, result)
        print('bbbbbbbbbbbbbbaaaaaaaaaaaa2')
    end)
end

function onDestory()
    Log("OnDestory")
end
