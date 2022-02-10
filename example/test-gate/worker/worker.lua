_package_('worker')

function onAwake()
    print('worker.onAwake')
    coorda:AddScript("worker.WorkerHandler")
end

function onDestory()
    print('worker.onDestory')
end