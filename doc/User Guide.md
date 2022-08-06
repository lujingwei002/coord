
coordx:         基础库
coord-service:  节点服务
coord:          命令行工具


##### Environment
    ### 预定义环境变量
    version         : Coord版本
    config-dir   : 配置文件所有的目录
    Config-path  : 配置文件的绝对路径
    working-dir     : 工作目录
    exec-path       : 执行文件路径
    exec-dir        : 执行文件目录
    coord-dir       : Coord目录
    home-dir        : Home目录
    proc-dir        : proc目录
    run-dir         : proc/${name}
    pid-path        : proc/${name}/pid
                ${COORD_ROOT}
        搜索顺序 /usr/coord
                 /usr/local/coord
                 ${HomeDir}/coord
    project-dir      : 工程目录
    package          : 包路径, 以;号分隔
                        ${coord-dir}/package
                        ${working-dir}/package
                        ${config-dir}/package
                        ${config-dir}
    managed-sock-path   : managed的unix socket路径
    ### 自定义环境变量
    查找路径 ${config-dir}/.env


#### Config
    [DEFAULT]
    env         环境 [dev|qa|prd]
    main        入口模块
    scene       场景文件
    registery   注册表

    [WEB]
    port    端口
    host    IP

    [Login] 登录服
    [GATE]  网关服
    [CACHE] 缓存
    [CLUSTER] 集群
    [MANAGED] 管理


Logger 配置

file: 文件路径
    日志文件达到滚动大小时,命名格式为 日志名.年月日_时分秒
    
layout: 输出格式
    basic: 年-月-日 时:分:秒 毫秒 线程id 级别 : 日志
max-line: 最大行数, 当file非空时有效
max-byte: 最大字节数, 当file非空时有效
console: [true|false] 输出到控制台
priority: 级别
    emerg 
    fatal
    alert
    crit
    error
    warn
    notice
    info
    debug
    all


预定义logger
core-logger
   file: ${CoordDir}/log/${Name}-core.log 

logger
    默认输出到控制台
    file: ${ConfigFileDir}/log/${Name}.log 

## 脚本
    脚本组织架构是包(package)和component

    定义入口包，修改脚本文件的main字段，默认是main

### 包(package)
    包的声明方法是_package_('包名')
    ```
    -- 包名必须和文件夹名字一致, 不相同的会被忽略
    _package_('main')
    function onAwake()
        print('hello')        
    end
    ```
    生命周期方法
    ```
    -- 模块唤醒时调用
    function onAwake()
    end
    -- 模块重载时调用
    function onReload()
    end
    -- 模块销毁时调用, main包才有会有回调
    function onDestory()
    end
    ```
    -- 模块self
    ```
    function onAwake()
        -- package代表本模块
        print(package)
        -- 环境中预定义的函数
        -- 这些打印函数会带上模块名
        Log
        LogFatal
        LogError
        LogWarn
        LogInfo
        LogDebug
        LogMsg
        -- 包路径
        __PACKAGE 
        -- 包的完整路径
        __PATH
        -- 包名
        __NAME
    end
    ```

    # 导入包
    ```
    local controller = import('web/controller')
    ```
    # 包重载
    ```
    reload('web/controller')
    ```

### 组件(component)
    组件定义在包内
    ```
    _package_("controller")
    component("AccountController")
    function onAwake(self)
    end
    function onDestory(self)
    end
    function onUpdate(self)
    end
    ```
    使用组件的方法
    ```
    -- 先导入模块
    local controller = import('web/controller')
    -- 添加到Object上
    coorda:AddScript(controller.AccountController)
    ```




