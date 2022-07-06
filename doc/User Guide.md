
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
                ${COORD_ROOT}
        搜索顺序 /usr/coord
                 /usr/local/coord
                 ${HomeDir}/coord
    project-dir      : 工程目录
    package         : 包路径, 以;号分隔
                        ${coord-dir}/package
                        ${working-dir}/package
                        ${config-dir}/package
                        ${config-dir}

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

