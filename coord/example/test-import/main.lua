_package_('test-import')

function main()
    coorda:LogMsg("hello")
    static:LogMsg("fffaaaaaaaaaaa")
    --coorda:Exit(0)
end

function exit()
    static:LogMsg("exit")
end