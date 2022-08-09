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
local function _import_(searchDir, packagePath)
    local fullDir = searchDir..'/'..packagePath
    if not os.path.IsDir(fullDir) then
        return false
    end
    local packageName = os.path.BaseName(packagePath)

    --是否已经导入过了
    local package = script.package[fullDir]
    if package then
        if not script.reloading then
            return package
        elseif script.reload[fullDir] then
            return package
        end
    end

    if not package then
        package = {__NAME = packageName, __PACKAGE = packagePath, __PATH = fullDir, Log = Log, LogFatal = LogFatal, LogError = LogError, LogWarn = LogWarn, LogInfo = LogInfo, LogDebug = LogDebug, LogMsg = LogMsg}
        package.package = package 
        setmetatable(package, {__index = _G})
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
                --coorda:CoreLogDebug(string.format('require %s', fullPath))
                local f, err = loadfile(fullPath)
                if not f then
                    error(err)
                end
                setfenv(f, package)
                f()
            else
                print('ignore', fullPath, 'a', packageNameReal, 'b', packageName)
            end
        end
    end 
    script.package[fullDir] = package 
    if script.reloading then
        script.reload[fullDir] = package 
        if type(package.onReload) == 'function' then
            package.onReload()
        end
    else
        if type(package.onAwake) == 'function' then
            package.onAwake()
        end
    end
    return package
end

function import(packagePath)
    --搜索导入
    for searchDir, _ in string.gmatch(coorda.Script.Path, "[^;]+") do
        local package = _import_(searchDir, packagePath)
        if package then
            return package
        end
    end
end

-- 组件的日志接口
local function ComponentLog(str)
    local env = getfenv(2)
    coorda:Log(string.format('[%s] %s', env.__COMPONENT, str or ''))
end
local function ComponentLogFatal(str)
    local env = getfenv(2)
    coorda:LogFatal(string.format('[%s] %s', env.__COMPONENT, str or ''))
end
local function ComponentLogError(str)
    local env = getfenv(2)
    coorda:LogError(string.format('[%s] %s', env.__COMPONENT, str or ''))
end
local function ComponentLogWarn(str)
    local env = getfenv(2)
    coorda:LogWarn(string.format('[%s] %s', env.__COMPONENT, str or ''))
end
local function ComponentLogInfo(str)
    local env = getfenv(2)
    coorda:LogInfo(string.format('[%s] %s', env.__COMPONENT, str or ''))
end
local function ComponentLogDebug(str)
    local env = getfenv(2)
    coorda:LogDebug(string.format('[%s] %s', env.__COMPONENT, str or ''))
end
local function ComponentLogMsg(str)
    local env = getfenv(2)
    coorda:LogMsg(string.format('[%s] %s', env.__COMPONENT, str or ''))
end

function component(name)
    local package = getfenv(2)
    local env = package[name]
    if not env then
        env = {
            __COMPONENT = package.__PACKAGE..'.'..name, 
            package = package, 
            __INTERFACE = {},
            Log = ComponentLog,
            LogFatal = ComponentLogFatal,
            LogError = ComponentLogError,
            LogWarn = ComponentLogWarn,
            LogInfo = ComponentLogInfo,
            LogDebug = ComponentLogDebug,
            LogMsg = ComponentLogMsg,
        }
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
    --coorda:CoreLogDebug(coorda.Script.Path)
    --环境初始化
    script.package = {}
    -- 入口模块
    script.main = nil
end

function _onAwake_() 
    --导入启动包
    local package = import(coorda.Script.Main, 'main')
    if not package then
        error("import main package failed")
    end
    script.main = package
end

function _onDestory_()
    if not coorda then
        return
    end
    if not script.main then
        return
    end
    script.main.onDestory()
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

function reload(packagePath)
    script.reloading = true
    script.reload = {}
    local package = import(packagePath)
    script.reloading = false
    script.reload = {}
    return package
end

function _REQUEST(self, args)
end
