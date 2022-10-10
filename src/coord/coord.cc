#include "coord/coord.h"
#include "coord/memory/type.h"
#include "coord/scene/init.h"
#include "coord/coordx.h"
#include "coord/event/init.h"
#include "coord/component/init.h"
#include "coord/object/init.h"
#include "coord/script/init.h"
#include "coord/config/init.h"
#include "coord/gate/init.h"
#include "coord/web/init.h"
#include "coord/http/init.h"
#include "coord/gate/init.h"
#include "coord/protobuf/init.h"
#include "coord/timer/init.h"
#include "coord/sql/init.h"
#include "coord/redis/init.h"
#include "coord/cache/init.h"
#include "coord/cluster/init.h"
#include "coord/net/init.h"
#include "coord/managed/init.h"
#include "coord/worker/init.h"
#include "coord/run/init.h"
#include "coord/action/init.h"
#include "coord/closure/init.h"
#include "coord/login/init.h"
#include "coord/json/inc.h"
#include "coord/log4cc/init.h"
#include "coord/environment/environment.h"

#include "coordx/coordx.h"
#include <uv.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <argparse/argparse.hpp>

#if defined(__linux__)
#include <signal.h> //for kill
#include <sys/types.h> // for kill
#endif

thread_local coord::Coord* coorda;

extern int onStart(coord::Coord* coord);
extern int onAwake(coord::Coord* coord);
extern void onDestory(coord::Coord* coord);

namespace coord {

    class fork_data {
    public:
        fork_data() {
            this->coord = nullptr;
            this->exitCode = 0;
        }
    public:
        Argv    argv;
        Coord*  coord;
        int     exitCode;
    };
    std::map<uv_thread_t*, Coord*> Coord::coordDict;
    static std::map<uv_thread_t*, fork_data*> forkDict;

    //处理中断信号
    static void coord_sigint_handler(uv_signal_t *handle, int signum) {
        fprintf(stderr, "coord_sigint_handler: %d\n", signum);
        uv_signal_stop(handle);
        Coord* coord = (Coord*)handle->data;
        coord->Destory(0);
    }

    Coord *NewCoord() {
        Coord *coord = new Coord;
        return coord;
    }

    // 主线程
    static void coord_main_thread(void* arg){
        fork_data* forkData = (fork_data*)arg;
        coord::Coord* coord = coord::NewCoord();
        forkData->coord = coord;
        int err = coord->Main(forkData->argv);
        forkData->exitCode = err;
        forkData->coord = nullptr;
        delete coord; 
    }

    static int daemon() {
    #if defined(__linux__)
        int pid;
        pid = fork();
        if(pid){
            exit(0);
        }else if(pid < 0){
            fprintf(stderr, "fork error");
            return -1;
        }
        setsid();
        pid = fork();
        if(pid){
            exit(0);
        }else if(pid < 0){
            fprintf(stderr, "fork error");
            return -1;
        }
        return 0;
    #elif defined(_WIN32)
        return 0;
    #endif
    }

    static int action_stop(argparse::ArgumentParser& parser) {
        int err;
        std::string name = parser.get<std::string>("name");
        err = coord::Init();
        if (err) {
            return err;
        }
        Argv argv;
        argv.Name = name;
        printf("bbbbbbb2\n");
        //Coord* coord = NewCoord();
        //err = coord->Main(argv);
        coord::Destory(); 
        return err;
    }

    static int action_status(argparse::ArgumentParser& parser) {
        int err;
        std::string name = parser.get<std::string>("name");
        err = coord::Init();
        if (err) {
            return err;
        }
        Argv argv;
        argv.Name = name;
        printf("bbbbbbb\n");
        //Coord* coord = NewCoord();
        //err = coord->Main(argv);
        coord::Destory(); 
        return err;
    }

    static int action_start(argparse::ArgumentParser& parser) {
        int err;
        if (parser.get<bool>("-d")) {
            err = daemon();
            if (err) {
                return err;
            }
        }
        std::string name = parser.get<std::string>("name");
        std::string configPath = parser.get<std::string>("--configure");
        err = coord::Init();
        if (err) {
            return err;
        }
        Argv argv;
        argv.Name = name;
        argv.ConfigPath = configPath;
        Coord* coord = NewCoord();
        err = coord->Main(argv);
        delete coord;
        coord::Destory(); 
        return err;
    }

    /* 
    static int action_fork(argparse::ArgumentParser& parser) {
        int err;
        if (parser.get<bool>("-d")) {
            err = daemon();
            if (err) {
                return err;
            }
        }
        err = coord::Init();
        if (err) {
            return err;
        }
        auto configures = parser.get<std::vector<std::string>>("--configure");
        for (auto c : configures) {
            err = coord::Fork(c.c_str());
            if(err){
                fprintf(stderr, "error: %d\n", err);
                return err;
            }
        }
        err = coord::Wait();
        coord::Destory(); 
        return err;
    }*/

    static int action_help(argparse::ArgumentParser& parser) {
        printf("help.......\n");
        return 0;
    }
    typedef std::function<int (argparse::ArgumentParser& parser)> argparser_action_func; 
    

    // 运行在主线程中
    int Fork(const Argv& argv) {
        uv_thread_t* thread = (uv_thread_t*)malloc(sizeof(uv_thread_t));
        fork_data* forkData = new fork_data();
        forkData->argv = argv;
        forkDict[thread] = forkData;
        int err = uv_thread_create(thread, coord_main_thread, forkData);
        return err;
    }

    int Wait() {
        int err = EXIT_SUCCESS;
        for(auto const it : forkDict){
            uv_thread_t* thread = it.first;
            fork_data* forkData = it.second;
            uv_thread_join(thread);
            int exitCode = it.second->exitCode;
            if (exitCode) { 
                err = exitCode;
                fprintf(stderr, "%s error:%d\n", forkData->argv.ConfigPath.c_str(), exitCode);
            }
            free(forkData);
        }
        forkDict.clear();
        return err;
    }

    int Init() {
#if defined(__linux__)
        signal(SIGHUP, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);
        signal(SIGTERM, SIG_IGN);
        signal(SIGHUP, SIG_IGN);
        //往关闭的socket写数据
        signal(SIGPIPE, SIG_IGN);
        //google protobuf出错时候会出这个
        signal(SIGABRT, SIG_IGN);
#endif
        //
        int err = coordx::coordx_init();
        if (err) {
            return err;
        }
        //初始化openssl
        SSL_library_init();             /* 为SSL加载加密和哈希算法 */                
        SSL_load_error_strings();       /* 为了更友好的报错，加载错误码的描述字符串 */
        ERR_load_BIO_strings();         /* 加载 BIO 抽象库的错误信息 */
        OpenSSL_add_all_algorithms();   /* 加载所有 加密 和 散列 函数 */
        return 0;
    }

    void Destory() {
    }

    static int action_env(argparse::ArgumentParser& parser) {
        std::string name = parser.get<std::string>("name");
        std::string configPath = parser.get<std::string>("--configure");
        int err = coord::Init();
        if (err) {
            return err;
        }
        Argv argv;
        argv.Name = name;
        argv.ConfigPath = configPath;
        Coord* coord = NewCoord();
        err = coord->ActionEnv(argv);
        coord::Destory(); 
        return err;
    }

    int Main(int argc, const char** argv) {
        argparse::ArgumentParser program("coord", "0.0.1");
        program.add_description("aaaaa");
        program.add_epilog("bbbbb");
        
        program.add_argument("--configure", "-c")
            // .default_value(std::vector<std::string>{})
            // .append()
            .help("configure file");
        program.add_argument("--verbose", "-v")
            .default_value(false)
            .implicit_value(true)
            .help("display message verbose");

        argparse::ArgumentParser env_parser("env");
        env_parser.add_parents(program);
        env_parser.add_argument("name")
            .default_value(std::string(""))
            .help("unique app name");

        argparse::ArgumentParser start_parser("start");
        start_parser.add_parents(program);
        start_parser.add_description("start program");
        start_parser.add_epilog("xxxxx");
        start_parser.add_argument("name")
            .default_value(std::string(""))
            .help("unique app name");
        start_parser.add_argument("-d", "--daemon")
            .default_value(false)
            .implicit_value(true)
            .help("run daemon");

        argparse::ArgumentParser restart_parser("restart");
        restart_parser.add_parents(program);

        argparse::ArgumentParser status_parser("status");
        status_parser.add_argument("name")
            .required()
            .help("unique app name");
        status_parser.add_parents(program);

        argparse::ArgumentParser stop_parser("stop");
        stop_parser.add_argument("name")
            .required()
            .help("unique app name");
        stop_parser.add_parents(program);


        argparse::ArgumentParser help_parser("help");
        help_parser.add_argument("command")
            .help("print command help infomation");
        help_parser.add_parents(program);

        program.add_argument("start")
            .nargs(0)
            .help("start program");

        program.add_argument("env")
            .nargs(0)
            .help("print environment");
        program.add_argument("stop")
            .nargs(0)
            .help("stop program");
        program.add_argument("restart")
            .nargs(0)
            .help("restart program");
        program.add_argument("status")
            .nargs(0)
            .help("status program");
        program.add_argument("stop")
            .nargs(0)
            .help("stop program");
        program.add_argument("help")
            .nargs(0)
            .help("help program");
        if (argc < 2) {
            std::cerr << program;
            std::exit(EXIT_FAILURE);
        }
        std::map<std::string, argparse::ArgumentParser*> parsers = {
            {"env", &env_parser},
            {"start", &start_parser},
            {"stop", &stop_parser},
            {"restart", &restart_parser},
            {"status", &status_parser},
            {"help", &help_parser},
        };
        std::map<std::string, argparser_action_func> actions = {
            {"env", action_env},
            {"start", action_start},
            {"stop", action_stop},
            {"status", action_status},
            {"help", action_help},
            {"help", [&](argparse::ArgumentParser& parser) -> int {
                std::string command = parser.get<std::string>("command");
                auto it = parsers.find(command);
                if (it == parsers.end()) {
                    std::cerr << program;
                    std::exit(EXIT_FAILURE);
                }
                auto subParser = it->second;
                std::cerr << *subParser;
                return 0;
            }},
        };

        const char* command = argv[1];
        auto it = parsers.find(command);
        if (it == parsers.end()) {
            std::cerr << "command not found" << std::endl;
            std::cerr << program;
            std::exit(EXIT_FAILURE);
        }

        for (int i = 1; i < argc - 1; i++) {
            argv[i] = argv[i + 1];
        }
        argc--;

        auto subParser = it->second;

        try {
            subParser->parse_args(argc, argv);
        } catch (const std::runtime_error& err) {
            printf("afsafsaf\n");
            std::cerr << err.what() << std::endl;
            std::cerr << *subParser;
            std::exit(EXIT_FAILURE);
        }
        auto it1 = actions.find(command);
        if (it1 == actions.end()) {
            std::cerr << "action not found" << std::endl;
            std::cerr << *subParser;
            std::exit(EXIT_FAILURE);
        }
        auto action = it1->second;
        return action(*subParser);
    }
    
    
    Coord::Coord() {
        this->isJoin = false;
        this->isAwake = false;
        this->coreLogger = nullptr;
        this->logger = nullptr;
        this->Config = nullptr; 
        this->sceneMgr = nullptr;
        this->Script = nullptr;        
        this->Event = nullptr;        
        this->Proto = nullptr;
        this->Timer = nullptr;
        this->sqlMgr = nullptr;
        this->RedisMgr = nullptr;
        this->Gate = nullptr;
        this->Login = nullptr;
        this->WebServer = nullptr;
        this->Cluster = nullptr;
        this->Cache = nullptr;
        this->AsyncCache = nullptr;
        this->Managed = nullptr;
        this->Worker = nullptr;
        this->WorkerSlave = nullptr;
        this->Environment = nullptr;
        this->Running = nullptr;
        this->Action = nullptr;
        this->Closure = nullptr;
        this->Json = nullptr;
        this->LoggerMgr = nullptr;

        coord::objectPoolMgr = new object_pool_mgr();
        //this->requestPipelineTop = NULL;
        if(uv_loop_init(&this->loop)){
        }
        uv_loop_set_data(&this->loop, this);
        this->cacheTimeofday();
        this->ExitCode = EXIT_SUCCESS;
        coorda = this;

        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->Config = new coord::Config(this); 
        this->Environment = new coord::Environment(this);
        this->Running = new coord::run::Running(this);
        this->sceneMgr = newSceneMgr(this);     
        this->Event = event::newEventMgr(this);        
        this->Proto = new protobuf::Protobuf(this);
        this->Timer = timer::newTimerMgr(this);
        this->sqlMgr = sql::newSQLMgr(this);
        this->RedisMgr = new redis::RedisMgr(this);
        this->Script = new script::Script(this); 
        this->Action = action::newActionMgr(this);
        this->Closure = closure::newClosureMgr(this);
        this->Json = new json::JsonMgr(this);
        this->Managed = new managed::Managed(this);
    }

    Coord::~Coord() {
        if(this->sceneMgr) {
            delete this->sceneMgr;
            this->sceneMgr = nullptr;
        }
        if(this->Event) {
            delete this->Event;
            this->Event = nullptr;
        }
        if(this->Gate) {
            delete this->Gate;
            this->Gate = nullptr;
        }
        if(this->Login) {
            delete this->Login;
            this->Login = nullptr;
        }
        if(this->Timer) {
            delete this->Timer;
            this->Timer = nullptr;
        }
        if(this->Cache) {
            delete this->Cache;
            this->Cache = nullptr;
        }
        if(this->AsyncCache) {
            delete this->AsyncCache;
            this->AsyncCache = nullptr;
        }
        if(this->Cluster) {
            delete this->Cluster;
            this->Cluster = nullptr;
        }
        if(this->WebServer) {
            delete this->WebServer;
            this->WebServer = nullptr;
        }
        if(this->sqlMgr) {
            delete this->sqlMgr;
            this->sqlMgr = nullptr;
        }
        if(this->RedisMgr) {
            delete this->RedisMgr;
            this->RedisMgr = nullptr;
        }
        if(this->Managed) {
            delete this->Managed;
            this->Managed = nullptr;
        }
        if(this->Script) {
            delete this->Script;
            this->Script = nullptr;
        }
        if(this->Worker) {
            delete this->Worker;
            this->Worker = nullptr;
        }  
        if(this->WorkerSlave) {
            delete this->WorkerSlave;
            this->WorkerSlave = nullptr;
        }  
        if(this->Action) {
            delete this->Action;
            this->Action = nullptr;
        }   
        if(this->Closure) {
            delete this->Closure;
            this->Closure = nullptr;
        }    
        if(this->Environment) {
            delete this->Environment;
            this->Environment = nullptr;
        }  
        if(this->Running) {
            delete this->Running;
            this->Running = nullptr;
        } 
        if(this->Json) {
            delete this->Json;
            this->Json = nullptr;
        }       
        delete coord::objectPoolMgr;
        coord::objectPoolMgr = nullptr;

        if(this->LoggerMgr) {
            delete this->LoggerMgr;
            this->LoggerMgr = nullptr;
        }       
        coorda = nullptr;
    }

    int Coord::master() {
        return 0;
    }

    int Coord::slave() {
         return 0;
    }

    int Coord::Client() {
         return 0;
    }

    int Coord::Local() {
        return 0;
    }

    uint64_t Coord::onUpdate(){
        //this->CoreLogDebug("[coord] onUpdate");
        this->frame++;
        uint64_t now = this->Now();
        this->sceneMgr->onUpdate(now);
        return 0;
    }

    void Coord::Destory(int code) {
        this->CoreLogDebug("[coord] Destory, code=%d", code);
        this->ExitCode = code;
        uv_stop(&this->loop);        
    }

    uint64_t Coord::onGC() {
        return 0;
        //this->script->gc();
    }
    
    int Coord::onStart(){   
        int err = ::onStart(this);
        if (err) {
            return err;
        }
        return err;
    }

    int Coord::onAwake(){   
        if (this->workerRole == worker_role_master) {   
            this->CoreLogMsg("[coord] onAwake at %ld", this->Time()/1000);
        }
        if (this->sceneMgr) {
            this->sceneMgr->onAwake();
        }
        if (this->workerRole == worker_role_master) {     
            int err = ::onAwake(this);
            if (err) {
                return err;
            }
        }
        if (this->Script){
            int err = this->Script->onAwake();
            if (err) {
                return err;
            }
        }
        if (this->Config->Basic.Update > 0) {
            this->SetInterval(this->Config->Basic.Update, std::bind(&Coord::onUpdate, this));
        }
        if (this->Config->Basic.GC > 0) {
            this->SetInterval(this->Config->Basic.GC, std::bind(&Coord::onGC, this));
        }
        this->isAwake = true;
        return 0;
    }

    void Coord::onDestory(int code) {
        this->CoreLogDebug("[coord] onDestory, code=%d", code);
        if(this->Gate) {
            this->Gate->onDestory();
        }
        if(this->Login) {
            this->Login->onDestory();
        }
        if(this->Worker) {
            this->Worker->onDestory();
        }  
        if (this->Script) {
            this->Script->onDestory();
        }
        if (this->workerRole == worker_role_master) { 
            ::onDestory(this);
            this->Running->onDestory();
        }
    }

    int Coord::ActionStart(const char *configPath) {
        return 0;
    }

    int Coord::ActionStop(const char *configPath) {
        return 0;
    }

    int Coord::ActionRestart(const char *configPath) {
        return 0;
    }

    int Coord::ActionStatus(const char *configPath) {
        return 0;
    }

    int Coord::ActionEnv(const Argv& argv) {
        this->ConfigPath = argv.ConfigPath;
        int err = this->Environment->main(argv);
        if (err) {
            return err;
        }
        err = this->Config->parse(argv.ConfigPath);
        if (err) {
            return err;
        }
        this->Environment->DebugString();
        this->Config->DebugString();
        return 0;
    }
    
    int Coord::Main(const Argv& argv) {
        this->ConfigPath = argv.ConfigPath;
        // 初始化环境
        int err = this->Environment->main(argv);
        if (err) {
            return err;
        }
        // 初始配置
        err = this->Config->parse(argv.ConfigPath);
        if (err) {
            return err;
        }
        // 初始化运行时
        err = this->Running->main();
        if (err) {
            return err;
        }
        // 初始化日志
        err = this->initLogger();
        // 初始化信号
        uv_signal_init(&this->loop, &this->sigInt);
        this->sigInt.data = this;
        uv_signal_start(&this->sigInt, coord_sigint_handler, SIGINT);

        this->Name = this->Config->Basic.Name;
        this->CoreLogDebug("[coord] running, cluster=%s", this->Config->Basic.Registery.c_str());
        err = this->Proto->main();
        if (err) {
            return err;
        }
        // 开启managed模块
        err = this->Managed->main();
        if (err) {
            return err;
        } 

        // 开启可选的模块
        //启动web服务
        if(this->Config->SectionExist("WEB")) {
            this->WebServer = new web::WebServer(this);
            web::WebConfig* config = this->WebServer->DefaultConfig();
            *config = this->Config->Web;
            int err = this->WebServer->Start();
            if (err) {
                return err;
            }
        }   
        //打开cluster
        if(this->Config->SectionExist("CLUSTER")) {
            this->Cluster = cluster::newCluster(this);
            cluster::ClusterConfig* config = this->Cluster->DefaultConfig();
            *config = this->Config->Cluster;
            int err = this->Cluster->main();
            if (err < 0){
                return err;
            }
        }
        //启动网关
        if(this->Config->SectionExist("GATE")) {
            this->Gate = gate::NewGate(this);
            gate::GateConfig* config = this->Gate->DefaultConfig();
            *config = this->Config->Gate;
            int err = this->Gate->main();
            if (err) {
                return err;
            }
        }           
        //启动登录功能
        if(this->Config->SectionExist("Login")) {
            this->Login = login::newLoginSvr(this);
            login::LoginConfig* config = this->Login->DefaultConfig();
            *config = this->Config->Login;
            int err = this->Login->main();
            if (err) {
                return err;
            }
        }       
        //打开cache
        if(this->Config->SectionExist("CACHE")) {
            this->Cache = cache::newClient(this);
            if (this->Cache == nullptr) {
                return -1;
            }
            auto config = this->Cache->DefaultConfig();
            *config = this->Config->Cache;
            int err = this->Cache->main();
            if (err) {
                return err;
            }
        }
         ;
        //启动worker服务
        if(this->Config->Basic.WorkerNum > 0) {
            std::string workerConfigPath = coordx::path::DirName(argv.ConfigPath);
            workerConfigPath = workerConfigPath + this->Config->Basic.Worker;
            this->Worker = worker::newWorker(this);
            int err = this->Worker->start(workerConfigPath, this->Config->Basic.WorkerNum);
            if (err) {
                this->CoreLogError("[Coord] worker start failed, error=%d", err);
                return err;
            }
        }
        this->workerRole = worker_role_master;
        if (this->Config->Basic.Registery == "local"){
            if(this->Local()){
                return EXIT_FAILURE;
            }
        } else if (this->Config->Basic.Registery == "slave"){
            if(this->slave()){
                return EXIT_FAILURE;
            }
        } else if (this->Config->Basic.Registery == "master"){
            if(this->master()){
                return EXIT_FAILURE;
            }
        } else if (this->Config->Basic.Registery == "client"){
            if(this->Client()){
                return EXIT_FAILURE;
            }
        }
        //异步启动的服务
        {
            this->Function()
            //启动cache
            ->Await([this](auto self, auto promise){
                if(!this->Config->SectionExist("CACHE")) {
                    promise->Reslove();
                    return;
                }
                auto cache = cache::newAsyncClient(this);
                if (cache == nullptr) {
                    return;
                }
                auto config = cache->DefaultConfig();
                config->Port = this->Config->Cache.Port;
                config->Host = this->Config->Cache.Host;
                config->DB = this->Config->Cache.DB;
                config->Password = this->Config->Cache.Password;
                config->ExpireTime = this->Config->Cache.ExpireTime;
                this->AsyncCache = cache;
                auto p = cache->main();
                p->Then([this, self, promise](auto client, auto reader) {
                    promise->Reslove();
                });
                p->Else([this, self, promise](auto client, auto reader) {
                    promise->Reject();
                });
            })
            ->_([this](auto self){
                //加载脚本 
                if (this->Config->Basic.Main.length() > 0) {              
                    //加载脚本
                    int err =  this->Script->main();
                    if (err) {
                        self->Abort();
                        return;
                    }
                }
                //启动
                int err = this->onAwake();
                if (err) {
                    self->Abort();
                    return;
                }
                err = this->onStart();
                if (err) {
                    self->Abort();
                    return;
                }
            })
            ->Catch([this](auto self){
                this->Destory(-1);
            })
            ->End()
            ->Call();
        }
        while(1) {
            uv_run(&this->loop, UV_RUN_DEFAULT);
        }
        this->onDestory(this->ExitCode);
        uv_loop_close(&this->loop);
        return this->ExitCode;
    }

    int Coord::workerEntryPoint(worker::Worker* master, const std::string& configPath, int index) {
        this->ConfigPath = configPath;
        int err;
        // 继承master
        *this->Environment = *master->coord->Environment;
        //继承配置
        this->Config->Basic = master->coord->Config->Basic;
        err = this->Config->parse(configPath);
        if (err) {
            return err;
        }
        err = this->initLogger();
        this->Name = this->Config->Basic.Name;
        err = this->Proto->main();
        if (err) {
            return err;
        }
       // this->SetLogLevel(log::ERROR);
        //启动worker slave服务
        this->WorkerSlave = worker::newWorkerSlave(this, master);
        err = this->WorkerSlave->start();
        if (err) {
            return err;
        }
        this->workerRole = worker_role_slave;
        //加载脚本 
        if (this->Config->Basic.Main.length() > 0) {
            //加载脚本
            int err =  this->Script->main();
            if (err) {
                return err;
            }
        }
        //启动
        err = this->onAwake();
        if (err) {
            return err;
        }
        master->recvSlaveAwake();
        //run main loop
        uv_run(&this->loop, UV_RUN_DEFAULT);
        uv_loop_close(&this->loop);
        //on exit
        this->onDestory(this->ExitCode);
        return this->ExitCode;
    }

    void Coord::cacheTimeofday() {
        struct timeval curTime;
        gettimeofday(&curTime, NULL);
        this->time = curTime.tv_sec * 1000 + curTime.tv_usec / 100;
        this->nowRecord = uv_now(&this->loop);
    }

    void Coord::Sleep(uint64_t msec) {
        uv_sleep(msec);
    }

    int Coord::initLogger() {
        int err;
        {
            auto logger = this->LoggerMgr->GetDefaultLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            err = this->LoggerMgr->configDefaultLogger(logger);
            if (err)return err;
            this->logger = logger;
        }

        {
            auto logger = this->LoggerMgr->GetCoreLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            err = this->LoggerMgr->configCoreLogger(logger);
            if (err)return err;
            this->coreLogger = logger;
        }
        return 0;
    }

    int Coord::beforeTest(const Argv& argv) {
        this->ConfigPath = argv.ConfigPath;
        int err = this->Environment->main(argv);
        if (err) {
            return err;
        }
        err = this->Config->parse(argv.ConfigPath);
        if (err) {
            return err;
        }
        err = this->Running->main();
        if (err) {
            return err;
        }
        err = this->initLogger();
        uv_signal_init(&this->loop, &this->sigInt);
        this->sigInt.data = this;
        uv_signal_start(&this->sigInt, coord_sigint_handler, SIGINT);
        this->workerRole = worker_role_master;
        err = this->Proto->main();
        if (err) {
            return err;
        }
        // managed
        err = this->Managed->main();
        if (err) {
            return err;
        } 
        //加载脚本 
        if (this->Config->Basic.Main.length() > 0) {              
            //加载脚本
            int err =  this->Script->main();
            if (err) {
                return err;
            }
        }
        //启动
        err = this->onAwake();
        if (err) {
            return err;
        }
        return 0;
    }

    int Coord::Break() {
        if (!this->isJoin) {
            return 0;
        }
        uv_stop(&this->loop);        
        return 0;
    }

    int Coord::Join() {
        this->isJoin = true;
        uv_stop(&this->loop);        
        uv_run(&this->loop, UV_RUN_DEFAULT);
        this->isJoin = false;
        return 0;
    }

    int Coord::afterTest() {
        this->onDestory(this->ExitCode);
        return this->ExitCode;
    }

    int Coord::Reload() {
        //刷新LUA
        if (this->Script) {
            int err = this->Script->onReload();
            if (err) {
                return err;
            }
        }
        if (this->Worker) {
            this->Worker->onReload();
        }
        if (this->sceneMgr) {
            this->sceneMgr->onReload();
        }
        return 0;
    }

    Scene* Coord::CreateScene(const char* sceneName) {
        return this->sceneMgr->CreateScene(sceneName);
    }

    int Coord::Log(lua_State* L) {
        tolua_Error tolua_err;
        static thread_local byte_slice buffer;
        buffer.Resize(0);       
        int argc = lua_gettop(L);
        for (int i = 2; i <= argc; i++) {
            if (lua_isstring(L, i)) {
                coordx::Appendf(buffer, lua_tostring(L, i));    
            } else if (lua_isnil(L, i)) {
                coordx::Appendf(buffer, "nil");
            } else if (lua_istable(L, i)) {
                coordx::Appendf(buffer, "table: %p", lua_topointer(L, i));
            } else if (lua_isfunction(L, i)) {
                coordx::Appendf(buffer, "function: %p", lua_topointer(L, i));
            } else if(tolua_isusertype(L, i, protobuf::Message::_TypeName, 0, &tolua_err) ) {
                protobuf::Message* message = ((protobuf::Message*) tolua_tousertype(L, i, 0));
                if(message == nullptr) {
                    coordx::Appendf(buffer, "proto: (null)");
                } else {
                    coordx::Appendf(buffer, "proto: %s", message->Name());
                }
            } else if (lua_isuserdata(L, i)) {
                coordx::Appendf(buffer, "userdata: %p", lua_topointer(L, i));
            } else if (lua_isboolean(L, i)) {
                coordx::Appendf(buffer, "%s", lua_toboolean(L, i) ? "true" : "false");
            } else {
                coordx::Appendf(buffer, "type: %d", lua_type(L, i));
            }
            coordx::Appendf(buffer, "\t");
        }
        coordx::Append(buffer, 0);
        this->Log(buffer.Data());
        return 0;
    }

    void Coord::Log(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Info(fmt, args);
        }
        va_end(args);
    }

    void Coord::LogFatal(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Fatal(fmt, args);
        }
        va_end(args);
    }

    void Coord::LogError(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Error(fmt, args);
        }
        va_end(args);
    }

    void Coord::LogWarn(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Warn(fmt, args);
        }
        va_end(args);
    }

    void Coord::LogInfo(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Info(fmt, args);
        }
        va_end(args);
    }

    void Coord::LogDebug(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Debug(fmt, args);
        }
        va_end(args);
    }

    void Coord::LogMsg(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Notice(fmt, args);
        }
        va_end(args);
    }

    void Coord::LogFatal(const char* fmt, va_list args){
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Fatal(fmt, args);
        }
    }

    void Coord::LogError(const char* fmt, va_list args){
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Error(fmt, args);
        }
    }

    void Coord::LogWarn(const char* fmt, va_list args){
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Warn(fmt, args);
        }
    }

    void Coord::LogInfo(const char* fmt, va_list args){
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Info(fmt, args);
        }
    }

    void Coord::LogDebug(const char* fmt, va_list args){
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Debug(fmt, args);
        }
    }

    void Coord::LogMsg(const char* fmt, va_list args){
        if(this->logger == nullptr){
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->logger->Notice(fmt, args);
        }
    }


    void Coord::Log(const char* str) const{;
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Info(str);
        }
    }

    void Coord::LogFatal(const char* str) const{;
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Fatal(str);
        }
    }

    void Coord::LogError(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Error(str);
        }
    }

    void Coord::LogWarn(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Warn(str);
        }
    }

    void Coord::LogInfo(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Info(str);
        }
    }

    void Coord::LogDebug(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Debug(str);
        }
    }

    void Coord::LogMsg(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
           this->logger->Notice(str);
        }
    }

    void Coord::LogSetPriority(log4cc::PriorityLevel priority) {
        if (nullptr == this->logger) {
            return;
        }
        this->logger->SetPriority(priority);
    }

    void Coord::CoreLogFatal(const char* str) const{;
        if(this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Fatal(str);
        }
    }

    void Coord::CoreLogError(const char* str) const{
        if(this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Error(str);
        }
    }

    void Coord::CoreLogWarn(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Warn(str);
        }
    }

    void Coord::CoreLogInfo(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Info(str);
        }
    }

    void Coord::CoreLogDebug(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Debug(str);
        }
    }

    void Coord::CoreLogMsg(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Notice(str);
        }
    }

    void Coord::CoreLogFatal(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);

        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Fatal(fmt, args);
        }

        va_end(args);

    }

    void Coord::CoreLogError(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);

        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Error(fmt, args);
        }

        va_end(args);
    }

    void Coord::CoreLogWarn(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);

        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Warn(fmt, args);
        }

        va_end(args);
    }

    void Coord::CoreLogInfo(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);

        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Info(fmt, args);
        }

        va_end(args);
    }

    void Coord::CoreLogDebug(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);

        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Debug(fmt, args);
        }

        va_end(args);
    }

    void Coord::CoreLogMsg(const char* fmt, ...){
        va_list args;
        va_start(args, fmt);
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Notice(fmt, args);
        }

        va_end(args);

    }

    void Coord::CoreLogFatal(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
        } else {
            this->coreLogger->Fatal(fmt, args);
        }
    }
    
    void Coord::CoreLogError(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Error(fmt, args);
        }
    }

    void Coord::CoreLogWarn(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Warn(fmt, args);
        }
    }

    void Coord::CoreLogInfo(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Info(fmt, args);
        }
    }

    void Coord::CoreLogMsg(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Notice(fmt, args);
        }
    }

    void Coord::CoreLogDebug(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Debug(fmt, args);
        }
    }

    void Coord::CoreLogSetPriority(log4cc::PriorityLevel priority) {
        if (nullptr == this->coreLogger) {
            return;
        }
        this->coreLogger->SetPriority(priority);
    }

    uint64_t Coord::Now() {
        return uv_now(&this->loop);
    }

    uint64_t Coord::Time() {
        uint64_t offset = uv_now(&this->loop) - this->nowRecord;
        return this->time + offset;
    }

    uint64_t Coord::NanoTime() {
        return uv_hrtime();
    } 

    http::HttpServer* Coord::NewHttpServer() {
        http::HttpServer* server = new http::HttpServer(this);
        return server;
    }

    int Coord::AddScript(lua_State* L) {
        return this->sceneMgr->mainObject->AddScript(L);
    }

    int Coord::AddComponent(Component* component) {
        return this->sceneMgr->mainObject->AddComponent(component);
    }

    void Coord::Emit(const char* name, event::BaseEvent* args) {
        this->Event->Emit(name, args);
    }

    void Coord::Destory(coord::RcObject* object) {
        object->DecRef();
    }

    void Coord::Destory(net::TcpClient* object) {
        object->onDestory();
    } 

    void Coord::DontDestory(coord::RcObject* object) {
        object->AddRef();
    }

    int Coord::SetTimeout(uint64_t timeout, timer::TimeoutFunc func) {
        return this->Timer->SetTimeout(timeout, func);
    }

    int Coord::SetInterval(uint64_t repeat, timer::TimeoutFunc func) {
        return this->Timer->SetInterval(repeat, func);
    }

    int Coord::SetCron(const char* expression, timer::CronFunc func) {
        return this->Timer->SetCron(expression, func);
    }

    int Coord::SetTimeout(lua_State* L) {
        return this->Timer->SetTimeout(L);
    }

    int Coord::SetInterval(lua_State* L) {
        return this->Timer->SetInterval(L);
    }

    int Coord::SetCron(lua_State* L) {
        return this->Timer->SetCron(L);
    }

    void Coord::ClearInterval(int id) {
        this->Timer->ClearInterval(id);
    }

    void Coord::ClearTimeout(int id) {
        this->Timer->ClearTimeout(id);
    }

    void Coord::ClearCron(int id) {
        this->Timer->ClearCron(id);
    }

    uint64_t Coord::StopTimer() {
        return std::numeric_limits<uint64_t>::max();
    }

    sql::SQLClient* Coord::SQLConfig(const char* name) {
        return this->sqlMgr->getClient(name);
    }

    redis::Client* Coord::NewRedisClient() {
        return this->RedisMgr->NewClient();
    }
    redis::Client* Coord::RedisConfig(const char* name) {
        return this->RedisMgr->GetClient(name);
    }
    redis::AsyncClient* Coord::NewAsyncRedisClient() {
        return this->RedisMgr->NewAsyncClient();
    }
    redis::AsyncClient* Coord::AsyncRedisConfig(const char* name) {
        return this->RedisMgr->GetAsyncClient(name);
    }
    

    /*int Coord::Cache(const char* name, const char* data, size_t expire) {
        if (data == NULL){
            int err = this->cache->Delete(name);
            return err;
        } else {
            int err = this->cache->Set(name, data, expire);
            return err;
        }
    }

    cache::CacheReader Coord::Cache(const char* name) {
        return this->cache->Get(name);
    }*/

   /* void Coord::pushRequestPipeline(BaseRequest* request) {
        if (request == NULL) {
            return;
        }
        if (this->requestPipelineTop) {
            RequestPipeline* pipeline = newRequestPipeline(this, this->requestPipelineTop);
            this->requestPipelineArr.push_back(pipeline);
            this->requestPipelineTop = NULL;
        }
        this->requestPipelineTop = request;
    }

    void Coord::recoverRequestPipeline(RequestPipeline* pipeline) {
        if (pipeline == NULL) {
            return;
        }
        if (this->requestPipelineTop) {
            RequestPipeline* pipeline = newRequestPipeline(this, this->requestPipelineTop);
            this->requestPipelineArr.push_back(pipeline);
            this->requestPipelineTop = NULL;
        }
        this->requestPipelineArr.push_back(pipeline);
    }

    void Coord::popRequestPipeline() {
        if (this->requestPipelineTop) {
            this->Destory(this->requestPipelineTop);
            this->requestPipelineTop = NULL;
            return;
        }
        if (this->requestPipelineArr.size() > 0) {
            RequestPipeline* pipeline = this->requestPipelineArr.back();
            this->requestPipelineArr.pop_back();
            this->Destory(pipeline);
        }
    }

    RequestPipeline* Coord::refRequestPipeline(BaseRequest* request){
        if (this->requestPipelineTop) {
            RequestPipeline* pipeline = newRequestPipeline(this, this->requestPipelineTop);
            this->requestPipelineArr.push_back(pipeline);
            this->requestPipelineTop = NULL;
        }
        if (this->requestPipelineArr.size() > 0) {
            RequestPipeline* pipeline = this->requestPipelineArr.back();
            this->DontDestory(pipeline);
            return pipeline;
        } else {
            return NULL;
        }
    }*/

} 

