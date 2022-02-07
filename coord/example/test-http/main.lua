_package_('test-http')

print('aa', import('example/test-http/http'))

function main()
    
    --local httpServer = coorda:NewHttpServer()
    --local config = httpServer:DefaultConfig()
    --config.host = "0.0.0.0"
    --config.port = 3333
    --httpServer:Start()

    --local route
    --route:Get('xx', http.HttpHandler.xxx)
    coorda:AddScript("http.HttpHandler")

    --coorda:CloseAllLog()
    --coorda:OpenLog(3)
end

function exit()
    static:LogMsg("exit")
end 