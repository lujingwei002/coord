_package_('worker')
component("WorkerHandler")


function onAwake(self)
    print('worker_handler.onAwake')

    local router = coorda.workerSlave.Router
    router:Request('aa.bb', self, 'HandleAABB')
end

function HandleAABB(self, request)
    print('HandleAABBHandleAABBHandleAABB', request:String())
    request:GetResponse():String("world")
end