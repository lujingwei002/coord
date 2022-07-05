__COMPONENTS = 1
__CHILDREN = 2

function instantiate(conf)
    local object = GameObject:new()
    for k, v in pairs(conf) do
        if k == __COMPONENTS then
            for class, component_conf in pairs(v) do
                if component_conf.__script then
                    local component = object:add_script(component_conf.__script)
                    for varname, value in pairs(component_conf) do
                        component[varname] = value
                    end
                else
                    local component_class = _G[class]
                    if not component_class then
                        print(string.format('%s not found', class))
                    end
                    local component = component_class:new()
                    object:add_component(component)
                    for varname, value in pairs(component_conf) do
                        component[varname] = value
                    end
                end
            end
        elseif k == __CHILDREN then
            for k2, v2 in pairs(v) do
                local child = instantiate(v2)
                child.name = k2
                object:add_child(child)
            end
        else
            object[k] = v
        end
    end
    return object 
end

NEW_POST = function(srvid)
    local srvid = srvid
    local modname = nil
    local funname = nil
    local mt = {
        __index = function(self, k)
            if not modname then 
                modname = k 
            else
                funcname = k
            end
            return self
        end,
        __call = function(self, ...)
            modname = nil
            funcname = nil
            mynode:post(srvid, modname, funcname, ...)
        end
    }
    local stub  = {}
    setmetatable(stub, mt)
    return stub
end

--兼容以前的协议
POST = function(...)
    mynode:post(...)
end

function import_proto(dir)
    Pblua.mappath('', dir)
    local files = File.listdir(dir)
    for _, file in pairs(files) do
        if file.type == File.TYPE_FILE and string.find(file.name, '.proto$') then
            logdebug(string.format('load proto(%s)', file.name))
            Pblua.import(file.name)
        end
    end
end



-------------------------------------------------------------
function _package_(name)

end

local function Log(str)
    local env = getfenv(2)
    coorda:Log(string.format('[%s] %s', env.__PACKAGE or 'aa', str or ''))
end
local function LogFatal(str)
    local env = getfenv(2)
    coorda:LogFatal(string.format('[%s] %s', env.__PACKAGE, str or ''))
end
local function LogError(str)
    local env = getfenv(2)
    coorda:LogError(string.format('[%s] %s', env.__PACKAGE, str or ''))
end
local function LogWarn(str)
    local env = getfenv(2)
    coorda:LogWarn(string.format('[%s] %s', env.__PACKAGE, str or ''))
end
local function LogInfo(str)
    local env = getfenv(2)
    coorda:LogInfo(string.format('[%s] %s', env.__PACKAGE, str or ''))
end
local function LogDebug(str)
    local env = getfenv(2)
    coorda:LogDebug(string.format('[%s] %s', env.__PACKAGE, str or ''))
end
local function LogMsg(str)
    local env = getfenv(2)
    coorda:LogMsg(string.format('[%s] %s', env.__PACKAGE, str or ''))
end

local script = {}
local function _import_(searchDir, packagePath, exportName)
    local fullDir = searchDir..'/'..packagePath
    if not os.path.IsDir(fullDir) then
        return false
    end
    local packageName = os.path.BaseName(packagePath)
    local env = script.package[packagePath]
    if not env then
        env = {__NAME = exportName, __PACKAGE = packagePath, __PATH = fullDir, Log = Log, LogFatal = LogFatal, LogError = LogError, LogWarn = LogWarn, LogInfo = LogInfo, LogDebug = LogDebug, LogMsg = LogMsg}
        --env.static = env
        env.package = env
        setmetatable(env, {__index = _G})
        --_G[exportName] = env
    end
    local fileArr, dirArr = os.ListDir(fullDir)    
    for _, fileName in pairs(fileArr) do
        if string.find(fileName, '.lua$') then
            local fullPath = fullDir..'/'..fileName
            local packageNameReal = nil
            for line in io.lines(fullPath) do 
                for k, _ in string.gmatch(line, "_package_%([\"\']([%w\.#\/-]+)[\"\']") do
                    packageNameReal = k
                    break
                end
                if packageNameReal then
                    break
                end
            end
            if packageNameReal == packageName or packageNameReal == 'main' then             
                coorda:coreLogDebug(string.format('require %s', fullPath))
                local f, err = loadfile(fullPath)
                if not f then
                    error(err)
                end
                setfenv(f, env)
                f()
            else
                print('ignore', fullPath, 'a', packageNameReal, 'b', packageName)
            end
        end
    end 
    script.package[packagePath] = env
    script.export[exportName] = env
    if script.reloading then
        script.reload[packagePath] = env
        if type(env.onReload) == 'function' then
            env.onReload()
        end
    else
        if type(env.onAwake) == 'function' then
            env.onAwake()
        end
    end
    return env
end

function import(packagePath, exportName)
    if not exportName then
        exportName = os.path.BaseName(packagePath)
    end
    --环境变量名冲突
    -- if _G[exportName] and not script.export[exportName] then
    --     error(string.format("environment %s conflict", exportName))
    --     return
    -- end
    --检查导出包名冲突
    local package = script.export[exportName]
    if package and package.__PACKAGE ~= packagePath then
        error(string.format("package %s conflict with %s", packagePath, package.__PACKAGE))
    end
    --是否已经导入过了
    local package = script.package[packagePath]
    if package then
        if not script.reloading then
            return package
        elseif script.reload[packagePath] then
            return package
        end
    end
    --搜索导入
    for searchDir, _ in string.gmatch(coorda.Script.Path, "[^;]+") do
        local package = _import_(searchDir, packagePath, exportName)
        if package then
            return package
        end
    end
end

function component(name)
    local package = getfenv(2)
    local env = package[name]
    if not env then
        env = {__COMPONENT = package.__PACKAGE..'.'..name, package = package, __INTERFACE = {}}
        setmetatable(env, {__index = _G})
        package[name] = env
    end
    setfenv(2, env)
end

function implement(name)
    local env = getfenv(2)
    table.insert(env.__INTERFACE, name)
end

local function traceG()
    for k, v in pairs(_G) do
        print(k)
    end
end

local lastPrint = print
function print(...)
    coorda:Log(...)
end

function _main_()
    --coorda:coreLogDebug(coorda.Script.Path)
    --环境初始化
    script.package = {}
    script.export = {}
end

function _onAwake_() 
    --导入启动包
    --local exportName = os.path.BaseName(coorda.script.Main)
    local package = import(coorda.Script.Main, 'main')
    if not package then
        error("import main package failed")
    end
end

function _onDestory_()
    if not coorda then
        return
    end
    --local exportName = os.path.BaseName(coorda.Script.Main)
    if not script.export.main then
        return
    end
    script.export.main.onDestory()
end

function _onReload_()
    script.reloading = true
    script.reload = {}
    local package = import(coorda.Script.Main, 'main')
    script.reloading = false
    script.reload = {}
    if not package then
        error("import main package failed")
    end
end

function reload(packagePath, exportName)
    script.reloading = true
    script.reload = {}
    local package = import(packagePath, exportName)
    script.reloading = false
    script.reload = {}
    return package
end

function _REQUEST(self, args)
    print(self)
    print("gggggg", args)
end
