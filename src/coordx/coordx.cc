#include "coordx/coordx.h"
#include "coord/scene/scene_mgr.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/request_pipeline.h"
#include "coord/event/init.h"
#include "coord/component/script_component.h"
#include "coord/object/object.h"
#include "coord/script/script.h"
#include "coord/config/config.h"
#include "coord/log/log_logger.h"
#include "coord/log/log_corelogger.h"
#include "coord/log/log_filelogger.h"
#include "coord/builtin/slice.h"
#include "coord/gate/gate.h"
#include "coord/http/http_server.h"
#include "coord/http/http_request.h"
#include "coord/gate/gate_request.h"
#include "coord/gate/gate_notify.h"
#include "coord/web/web_server.h"
#include "coord/protobuf/protobuf.h"
#include "coord/timer/timer.h"
#include "coord/sql/sql_mgr.h"
#include "coord/sql/sql_client.h"
#include "coord/redis/redis_mgr.h"
#include "coord/redis/redis_client.h"
#include "coord/cache/cache_client.h"
#include "coord/cache/cache_reader.h"
#include "coord/cache/cache_promise.h"
#include "coord/cache/cache_async_client.h"
#include "coord/cluster/cluster.h"
#include "coord/net/tcp_client.h"
#include "coord/managed/managed.h"
#include "coord/worker/worker.h"
#include "coord/worker/worker_slave.h"
#include "coord/builtin/environment.h"
#include "coord/run/running.h"
#include "coord/action/action_mgr.h"
#include "coord/closure/init.h"
#include "coord/login/init.h"
#include "coord/json/json_mgr.h"
#include "coord/log4cc/log4cc.h"
#include "util/os/os.h"
#include "util/os/path.h"
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

thread_local coordx::Coordx* coorda;

extern int onAwake(coordx::Coordx* coordx);
extern void onDestory(coordx::Coordx* coordx);

namespace coordx {

    class fork_data {
    public:
        fork_data() {
            this->coordx = nullptr;
            this->exitCode = 0;
        }
    public:
        Argv    argv;
        Coordx* coordx;
        int     exitCode;
    };
    std::map<uv_thread_t*, Coordx*> Coordx::coordDict;
    static std::map<uv_thread_t*, fork_data*> forkDict;

    Coordx *NewCoordx() {
        Coordx *coordx = new Coordx;
        return coordx;
    }

    // 主线程
    static void coordx_main_thread(void* arg){
        fork_data* forkData = (fork_data*)arg;
        coordx::Coordx* coordx = coordx::NewCoord();
        forkData->coordx = coordx;
        int err = coordx->Main(forkData->argv);
        forkData->exitCode = err;
        forkData->coordx = nullptr;
        delete coordx; 
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
        err = coordx::Init();
        if (err) {
            return err;
        }
        Argv argv;
        argv.Name = name;
        argv.ConfigPath = configPath;
        Coordx* coordx = NewCoordx();
        err = coordx->Main(argv);
        coordx::Destory(); 
        return err;
    }

    static int action_fork(argparse::ArgumentParser& parser) {
        int err;
        if (parser.get<bool>("-d")) {
            err = daemon();
            if (err) {
                return err;
            }
        }
        std::string name = parser.get<std::string>("name");
        std::string configPath = parser.get<std::string>("--configure");
        err = coordx::Init();
        if (err) {
            return err;
        }
        Argv argv;
        argv.Name = name;
        argv.ConfigPath = configPath;
        err = coordx::Fork(argv);
        if(err){
            fprintf(stderr, "error: %d\n", err);
            return err;
        }
        err = coordx::Wait();
        coordx::Destory(); 
        return err;
    }

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
        int err = uv_thread_create(thread, coordx_main_thread, forkData);
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
        int err = coordx::Init();
        if (err) {
            return err;
        }
        Argv argv;
        argv.Name = name;
        argv.ConfigPath = configPath;
        printf("afaff %s\n", name.c_str());
        Coordx* coordx = NewCoordx();
        err = coordx->ActionEnv(argv);
        coordx::Destory(); 
        return err;
    }

    int Main(int argc, const char** argv) {
        argparse::ArgumentParser program("coordx", "0.0.1");
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
            .required()
            .help("unique app name");

        argparse::ArgumentParser start_parser("start");
        start_parser.add_parents(program);
        start_parser.add_description("start program");
        start_parser.add_epilog("xxxxx");
        start_parser.add_argument("name")
            .required()
            .help("unique app name");
        start_parser.add_argument("-d", "--daemon")
            .default_value(false)
            .implicit_value(true)
            .help("run daemon");

        argparse::ArgumentParser stop_parser("stop");
        stop_parser.add_parents(program);

        argparse::ArgumentParser restart_parser("restart");
        restart_parser.add_parents(program);

        argparse::ArgumentParser status_parser("status");
        status_parser.add_parents(program);

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
    
    
    Coordx::Coordx() {
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
        this->HttpServer = nullptr;
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
        //this->requestPipelineTop = NULL;
        if(uv_loop_init(&this->loop)){
        }
        uv_loop_set_data(&this->loop, this);
        this->cacheTimeofday();
        this->ExitCode = EXIT_SUCCESS;
    }

    Coordx::~Coordx() {
        this->CoreLogDebug("[Coordx] ~Coordx");
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
        if(this->HttpServer) {
            delete this->HttpServer;
            this->HttpServer = nullptr;
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
        if(this->LoggerMgr) {
            delete this->LoggerMgr;
            this->LoggerMgr = nullptr;
        }       
        coorda = nullptr;
    }

    int Coordx::master() {
        return 0;
    }

    int Coordx::slave() {
         return 0;
    }

    int Coordx::Client() {
         return 0;
    }

    int Coordx::Local() {
        return 0;
    }

    uint64_t Coordx::onUpdate(){
        //this->CoreLogDebug("[coordx] onUpdate");
        this->frame++;
        uint64_t now = this->Now();
        this->sceneMgr->onUpdate(now);
        return 0;
    }

    void Coordx::Destory(int code) {
        this->CoreLogDebug("[coordx] Destory, code=%d", code);
        this->ExitCode = code;
        uv_stop(&this->loop);        
    }

    uint64_t Coordx::onGC() {
        return 0;
        //this->script->gc();
    }
    
    int Coordx::onAwake(){   
        if (this->workerRole == worker_role_master) {   
            this->CoreLogMsg("[coordx] onAwake at %ld", this->Time()/1000);
        }
        //this->pid = uv_os_getpid();
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
            this->SetInterval(this->Config->Basic.Update, std::bind(&Coordx::onUpdate, this));
        }
        if (this->Config->Basic.GC > 0) {
            this->SetInterval(this->Config->Basic.GC, std::bind(&Coordx::onGC, this));
        }
        this->isAwake = true;
        return 0;
    }

    void Coordx::onDestory(int code) {
        this->CoreLogDebug("[coordx] onDestory, code=%d", code);
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

    int Coordx::asCommand(const char *configPath, const char* command) {
        coorda = this;
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->Config = new coord::Config(this); 
        this->ConfigPath = configPath;
        if (this->readConfig(configPath)) {
            return EXIT_FAILURE;
        }
        {
            auto logger = this->LoggerMgr->GetDefaultLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configDefaultLogger(logger);
            if (err)return err;
            this->logger = logger;
        }

        {
            auto logger = this->LoggerMgr->GetCoreLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configCoreLogger(logger);
            if (err)return err;
            this->coreLogger = logger;
        }

        if (strcmp(command, "stop") == 0) {
            std::ifstream ifile;
            ifile.open(this->Environment->PidPath.c_str(), std::ios::in);
            if(!ifile){
                fprintf(stderr, "pid file not found: %s\n", this->Environment->PidPath.c_str());
                return 1;
            }
            uv_pid_t pid;
            ifile >> pid;
            kill(pid, SIGINT);
        } else if (strcmp(command, "status") == 0) {

        } else if (strcmp(command, "reload") == 0) {
            std::ifstream ifile;
            ifile.open(this->Environment->PidPath.c_str(), std::ios::in);
            if(!ifile){
                fprintf(stderr, "pid file not found: %s\n", this->Environment->PidPath.c_str());
                return 1;
            }
            uv_pid_t pid;
            ifile >> pid;
            kill(pid, SIGUSR2);
        }
        return 0;
    }
    int Coordx::ActionStart(const char *configPath) {
        return 0;
    }
    int Coordx::ActionStop(const char *configPath) {
        return 0;
    }
    int Coordx::ActionRestart(const char *configPath) {
        return 0;
    }
    int Coordx::ActionStatus(const char *configPath) {
        return 0;
    }
    int Coordx::ActionEnv(const Argv& argv) {
        coorda = this;
        this->Config = new coord::Config(this); 
        this->Environment = new coord::Environment(this);
        this->ConfigPath = argv.ConfigPath;
        int err = this->Environment->read(argv);
        if (err) {
            return err;
        }
        if (this->readConfig(argv.ConfigPath)) {
            return EXIT_FAILURE;
        }
        this->Environment->DebugString();
        this->Config->DebugString();
        return 0;
    }
    int Coordx::Main(const Argv& argv) {
        coorda = this;
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->Config = new coord::Config(this); 
        this->Environment = new coord::Environment(this);
        this->Running = new coord::run::Running(this);
        this->sceneMgr = newSceneMgr(this);     
        this->Event = event::newEventMgr(this);        
        this->Proto = protobuf::newProtobuf(this);
        this->Timer = timer::newTimerMgr(this);
        this->sqlMgr = sql::newSQLMgr(this);
        this->RedisMgr = redis::newRedisMgr(this);
        this->Script = script::newScript(this); 
        this->Action = action::newActionMgr(this);
        this->Closure = closure::newClosureMgr(this);
        this->Json = json::newJsonMgr(this);
        this->ConfigPath = argv.ConfigPath;
        int err = this->Environment->read(argv);
        if (err) {
            return err;
        }
        if (this->readConfig(argv.ConfigPath)) {
            return EXIT_FAILURE;
        }
        err = this->Running->main();
        if (err) {
            return err;
        }
        {
            auto logger = this->LoggerMgr->GetDefaultLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configDefaultLogger(logger);
            if (err)return err;
            this->logger = logger;
        }

        {
            auto logger = this->LoggerMgr->GetCoreLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configCoreLogger(logger);
            if (err)return err;
            this->coreLogger = logger;
        }
        this->Name = this->Config->Basic.Name;
        this->CoreLogDebug("[coordx] running, cluster=%s", this->Config->Basic.Registery.c_str());
        err = this->Proto->main();
        if (err) {
            return err;
        }
        //启动web服务
        if(this->Config->SectionExist("WEB")) {
            this->HttpServer = http::newHttpServer(this);
            http::HttpServerConfig* config = this->HttpServer->DefaultConfig();
            config->Host = this->Config->Web.Host;
            config->Port = this->Config->Web.Port;
            config->Backlog = this->Config->Web.Backlog;
            config->AssetDir = this->Config->Web.AssetDir;
            config->RecvBufferSize = this->Config->Web.RecvBuffer;
            config->SSLEncrypt = this->Config->Web.SSLEncrypt;
            config->SSLPemFile = this->Config->Web.SSLPemFile;
            config->SSLKeyFile = this->Config->Web.SSLKeyFile;
            config->UseEtag = this->Config->Web.UseEtag;
            int err = this->HttpServer->Start();
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
        //启动managed服务
        if(this->Config->SectionExist("MANAGED")) {
            this->Managed = managed::newManaged(this);
            managed::ManagedConfig* config = this->Managed->DefaultConfig();
            *config = this->Config->Managed;
            int err = this->Managed->start();
            if (err) {
                return err;
            } 
        }
        //启动worker服务
        if(this->Config->Basic.WorkerNum > 0) {
            std::string workerConfigPath = coord::path::DirName(argv.ConfigPath);
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
                p->Then([this, self, promise](auto client, auto& reader) {
                    promise->Reslove();
                });
                p->Else([this, self, promise](auto client, auto& reader) {
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
            })
            ->Catch([this](auto self){
                this->Destory(-1);
            })
            ->End()
            ->Call();
        }
        uv_run(&this->loop, UV_RUN_DEFAULT);
        this->onDestory(this->ExitCode);
        uv_loop_close(&this->loop);
        return this->ExitCode;
    }

    int Coordx::workerEntryPoint(worker::Worker* master, const std::string& configPath, int index) {
        coorda = this;
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->Config = new coord::Config(this); 
        this->Environment = new coord::Environment(this);
        this->Running = new coord::run::Running(this);
        this->sceneMgr = newSceneMgr(this);     
        this->Event = event::newEventMgr(this);        
        this->Proto = protobuf::newProtobuf(this);
        this->Timer = timer::newTimerMgr(this);
        this->sqlMgr = sql::newSQLMgr(this);
        this->RedisMgr = redis::newRedisMgr(this);
        this->Script = script::newScript(this); 
        this->Action = action::newActionMgr(this);
        this->Closure = closure::newClosureMgr(this);  
        this->Json = json::newJsonMgr(this);
        this->ConfigPath = configPath;
        int err;
        // 继承master
        *this->Environment = *master->coord->Environment;
        //继承配置
        this->Config->Basic = master->coord->Config->Basic;
        if (this->readConfig(configPath)) {
            return EXIT_FAILURE;
        }
        {
            auto logger = this->LoggerMgr->GetDefaultLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configDefaultLogger(logger);
            if (err)return err;
            this->logger = logger;
        }

        {
            auto logger = this->LoggerMgr->GetCoreLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configCoreLogger(logger);
            if (err)return err;
            this->coreLogger = logger;
        }

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

    void Coordx::cacheTimeofday() {
        struct timeval curTime;
        gettimeofday(&curTime, NULL);
        this->time = curTime.tv_sec * 1000 + curTime.tv_usec / 100;
        this->nowRecord = uv_now(&this->loop);
    }

    void Coordx::Sleep(uint64_t msec) {
        uv_sleep(msec);
    }

    int Coordx::beforeTest(const Argv& argv) {
        coorda = this;
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->Config = new coord::Config(this); 
        this->Environment = new coord::Environment(this);
        this->Running = new coord::run::Running(this);
        this->sceneMgr = newSceneMgr(this);     
        this->Event = event::newEventMgr(this);        
        this->Proto = protobuf::newProtobuf(this);
        this->Timer = timer::newTimerMgr(this);
        this->sqlMgr = sql::newSQLMgr(this);
        this->RedisMgr = redis::newRedisMgr(this);
        this->Script = script::newScript(this); 
        this->Action = action::newActionMgr(this);
        this->Closure = closure::newClosureMgr(this);
        this->Json = json::newJsonMgr(this);
        this->ConfigPath = argv.ConfigPath;
        int err = this->Environment->read(argv);
        if (err) {
            return err;
        }
        if (this->readConfig(argv.ConfigPath)) {
            return EXIT_FAILURE;
        }
        err = this->Running->main();
        if (err) {
            return err;
        }
        {
            auto logger = this->LoggerMgr->GetDefaultLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configDefaultLogger(logger);
            if (err)return err;
            this->logger = logger;
        }

        {
            auto logger = this->LoggerMgr->GetCoreLogger();
            if (nullptr == logger) return ErrorOutOfMemory;
            int err = this->LoggerMgr->configCoreLogger(logger);
            if (err)return err;
            this->coreLogger = logger;
        }

        this->workerRole = worker_role_master;
        err = this->Proto->main();
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

    void Coordx::loopTest() {
        uv_run(&this->loop, UV_RUN_DEFAULT);
        uv_loop_close(&this->loop);
    }

    int Coordx::afterTest() {
        this->onDestory(this->ExitCode);
        return this->ExitCode;
    }

    int Coordx::Reload() {
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

    int Coordx::readConfig(const std::string& path) {
        return this->Config->parse(path);
    }

    Scene* Coordx::CreateScene(const char* sceneName) {
        return this->sceneMgr->CreateScene(sceneName);
    }

    int Coordx::Log(lua_State* L) {
        tolua_Error tolua_err;
        static thread_local byte_slice buffer;
        buffer.Resize(0);       
        int argc = lua_gettop(L);
        for (int i = 2; i <= argc; i++) {
            if (lua_isstring(L, i)) {
                coord::Appendf(buffer, lua_tostring(L, i));    
            } else if (lua_isnil(L, i)) {
                coord::Appendf(buffer, "nil");
            } else if (lua_istable(L, i)) {
                coord::Appendf(buffer, "table: %p", lua_topointer(L, i));
            } else if (lua_isfunction(L, i)) {
                coord::Appendf(buffer, "function: %p", lua_topointer(L, i));
            } else if(tolua_isusertype(L, i, "coord::protobuf::Reflect", 0, &tolua_err) ) {
                protobuf::Reflect* proto = ((protobuf::Reflect*) tolua_tousertype(L, i, 0));
                if(proto == nullptr) {
                    coord::Appendf(buffer, "proto: (null)");
                } else {
                    coord::Appendf(buffer, "proto: %s", proto->Name());
                }
            } else if (lua_isuserdata(L, i)) {
                coord::Appendf(buffer, "userdata: %p", lua_topointer(L, i));
            } else if (lua_isboolean(L, i)) {
                coord::Appendf(buffer, "%s", lua_toboolean(L, i) ? "true" : "false");
            } else {
                coord::Appendf(buffer, "type: %d", lua_type(L, i));
            }
            coord::Appendf(buffer, "\t");
        }
        coord::Append(buffer, 0);
        this->Log(buffer.Data());
        return 0;
    }

    void Coordx::Log(const char* fmt, ...){
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

    void Coordx::LogFatal(const char* fmt, ...){
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

    void Coordx::LogError(const char* fmt, ...){
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

    void Coordx::LogWarn(const char* fmt, ...){
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

    void Coordx::LogInfo(const char* fmt, ...){
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

    void Coordx::LogDebug(const char* fmt, ...){
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

    void Coordx::LogMsg(const char* fmt, ...){
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

    void Coordx::Log(const char* str) const{;
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Info(str);
        }
    }

    void Coordx::LogFatal(const char* str) const{;
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Fatal(str);
        }
    }

    void Coordx::LogError(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Error(str);
        }
    }

    void Coordx::LogWarn(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Warn(str);
        }
    }

    void Coordx::LogInfo(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Info(str);
        }
    }

    void Coordx::LogDebug(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->logger->Debug(str);
        }
    }

    void Coordx::LogMsg(const char* str) const{
        if(this->logger == nullptr){
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
           this->logger->Notice(str);
        }
    }

    void Coordx::LogCloseLevel(int level) {
        //this->logger->CloseLevel(level);
    }

    void Coordx::LogOpenLevel(int level) {
        //this->logger->OpenLevel(level);
    }

    void Coordx::LogSetLevel(int level) {
        //this->logger->SetLevel(level);
    }

    void Coordx::CoreLogFatal(const char* str) const{;
        if(this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Fatal(str);
        }
    }

    void Coordx::CoreLogError(const char* str) const{
        if(this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Error(str);
        }
    }

    void Coordx::CoreLogWarn(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Warn(str);
        }
    }

    void Coordx::CoreLogInfo(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Info(str);
        }
    }

    void Coordx::CoreLogDebug(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Debug(str);
        }
    }

    void Coordx::CoreLogMsg(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Notice(str);
        }
    }

    void Coordx::CoreLogFatal(const char* fmt, ...){
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

    void Coordx::CoreLogError(const char* fmt, ...){
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

    void Coordx::CoreLogWarn(const char* fmt, ...){
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

    void Coordx::CoreLogInfo(const char* fmt, ...){
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

    void Coordx::CoreLogDebug(const char* fmt, ...){
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

    void Coordx::CoreLogMsg(const char* fmt, ...){
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

    void Coordx::CoreLogFatal(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
        } else {
            this->coreLogger->Fatal(fmt, args);
        }
    }
    
    void Coordx::CoreLogError(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Error(fmt, args);
        }
    }

    void Coordx::CoreLogWarn(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Warn(fmt, args);
        }
    }

    void Coordx::CoreLogInfo(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Info(fmt, args);
        }
    }

    void Coordx::CoreLogMsg(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Notice(fmt, args);
        }
    }

    void Coordx::CoreLogDebug(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Debug(fmt, args);
        }
    }

    void Coordx::coreLogCloseLevel(int level) {
        //log::CloseLevel(level);
        //this->coreLogger->CloseLevel(level);
    }

    void Coordx::coreLogOpenLevel(int level) {
        //log::OpenLevel(level);
        //this->coreLogger->OpenLevel(level);
    }

    void Coordx::coreLogSetLevel(int level) {
        //log::SetLevel(level);
        //this->coreLogger->SetLevel(level);
    }

    uint64_t Coordx::Now() {
        return uv_now(&this->loop);
    }

    uint64_t Coordx::Time() {
        uint64_t offset = uv_now(&this->loop) - this->nowRecord;
        return this->time + offset;
    }

    uint64_t Coordx::NanoTime() {
        return uv_hrtime();
    } 

    http::HttpServer* Coordx::NewHttpServer() {
        http::HttpServer* server = http::newHttpServer(this);
        return server;
    }

    int Coordx::AddScript(lua_State* L) {
        return this->sceneMgr->mainObject->AddScript(L);
    }

    int Coordx::AddComponent(Component* component) {
        return this->sceneMgr->mainObject->AddComponent(component);
    }

    void Coordx::Emit(const char* name, event::BaseEvent* args) {
        this->Event->Emit(name, args);
    }

    void Coordx::Destory(Destoryable* object) {
        object->_ref--;
        if(object->_ref != 0){ //避免循环删除，要用!=0判断。 a删除b, b删除a, 导致一直循环
            return;
        }
        object->onDestory();
        delete object;
    }

    void Coordx::Destory(net::TcpClient* object) {
        object->onDestory();
    } 

    void Coordx::DontDestory(Destoryable* object) {
        if(object->_ref <= 0) { //避免在destory里，又被操作ref
            return;
        }
        object->_ref++;
    }

    int Coordx::SetTimeout(uint64_t timeout, timer::TimeoutFunc func) {
        return this->Timer->SetTimeout(timeout, func);
    }

    int Coordx::SetInterval(uint64_t repeat, timer::TimeoutFunc func) {
        return this->Timer->SetInterval(repeat, func);
    }

    int Coordx::SetCron(const char* expression, timer::CronFunc func) {
        return this->Timer->SetCron(expression, func);
    }

    int Coordx::SetTimeout(lua_State* L) {
        return this->Timer->SetTimeout(L);
    }

    int Coordx::SetInterval(lua_State* L) {
        return this->Timer->SetInterval(L);
    }

    int Coordx::SetCron(lua_State* L) {
        return this->Timer->SetCron(L);
    }

    void Coordx::ClearInterval(int id) {
        this->Timer->ClearInterval(id);
    }

    void Coordx::ClearTimeout(int id) {
        this->Timer->ClearTimeout(id);
    }

    void Coordx::ClearCron(int id) {
        this->Timer->ClearCron(id);
    }

    uint64_t Coordx::StopTimer() {
        return std::numeric_limits<uint64_t>::max();
    }

    sql::SQLClient* Coordx::SQLConfig(const char* name) {
        return this->sqlMgr->getClient(name);
    }

    redis::Client* Coordx::RedisConfig(const char* name) {
        return this->RedisMgr->GetClient(name);
    }

    redis::AsyncClient* Coordx::RedisAsyncConfig(const char* name) {
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
