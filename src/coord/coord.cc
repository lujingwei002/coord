#include "coord/coord.h"
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

#if defined(__linux__)
#include <signal.h> //for kill
#include <sys/types.h> // for kill
#endif

thread_local coord::Coord* coorda;

extern int onAwake(coord::Coord* coord);
extern void onDestory(coord::Coord* coord);

namespace coord {
    std::map<uv_thread_t*, Coord*> Coord::coordDict;

    struct fork_data {
        char configFile[PATH_MAX];
        Coord* coord;
    };

    Coord *NewCoord() {
        Coord *coord = new Coord;
        return coord;
    }

    int Wait() {
        for(auto const it : Coord::coordDict){
            uv_thread_t* thread = it.first;
            uv_thread_join(thread);
        }
        return EXIT_SUCCESS;
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

    int daemon() {
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

    int Main(int argc, const char** argv) {
        if (argc < 2){
            fprintf(stderr, "not config file input\n");
            return EXIT_FAILURE;
        }
        if (argc >= 4 && strcmp(argv[2], "-s") == 0){
            coord::Init();
            coord::Coord* coorda = coord::NewCoord();
            int err = coorda->asCommand(argv[1], argv[3]);
            if(err){
                return err;
            }
            delete coorda;
            coord::Destory();
            return err;
        } else {
            if (argc >= 3 && strcmp(argv[2], "-d") == 0){
                int err = daemon();
                if (err) {
                    return err;
                }
            }
            coord::Init();
            coord::Coord* coorda = coord::NewCoord();
            int err = coorda->Main(argv[1]);
            if(err){
                return err;
            }
            delete coorda;
            coord::Destory();
            return err;
        }
    }
    
    //主线程
    static void coord_main_thread(void* arg){
        fork_data* forkData = (fork_data*)arg;
        Coord* coord = forkData->coord;
        coord->Main(forkData->configFile);
        free(forkData);
        delete coord; 
    }

    //处理中断信号
    static void coord_sigint_handler(uv_signal_t *handle, int signum) {
        fprintf(stderr, "coord_sigint_handler: %d\n", signum);
        uv_signal_stop(handle);
        Coord* coord = (Coord*)handle->data;
        coord->recvSigInt();
    }

    static void coord_sigusr1_handler(uv_signal_t *handle, int signum) {
        fprintf(stderr, "coord_sigusr1_handler: %d\n", signum);
        //uv_signal_stop(handle);
        //Coord* coord = (Coord*)handle->data;
        //coord->recvSigInt();
    }

    static void coord_sigusr2_handler(uv_signal_t *handle, int signum) {
        fprintf(stderr, "coord_sigusr2_handler: %d\n", signum);
        Coord* coord = (Coord*)handle->data;
        coord->Reload();
        //uv_signal_stop(handle);
        //Coord* coord = (Coord*)handle->data;
        //coord->recvSigInt();
    }

    Coord::Coord() {
        this->isAwake = false;
        this->coreLogger = nullptr;
        this->logger = nullptr;
        this->config = nullptr; 
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
        this->Action = nullptr;
        this->Closure = nullptr;
        this->Json = nullptr;
        this->LoggerMgr = nullptr;
        //this->requestPipelineTop = NULL;
        if(uv_loop_init(&this->loop)){
        }
        uv_loop_set_data(&this->loop, this);
        this->cacheTimeofday();
        this->exitCode = EXIT_SUCCESS;
    }

    Coord::~Coord() {
        this->coreLogDebug("[Coord] ~Coord");
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
        if(this->Json) {
            delete this->Json;
            this->Json = nullptr;
        }       
        if(this->LoggerMgr) {
            delete this->LoggerMgr;
            this->LoggerMgr = nullptr;
        }       
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
        //this->coreLogDebug("[coord] onUpdate");
        this->frame++;
        uint64_t now = this->Now();
        this->sceneMgr->onUpdate(now);
        return 0;
        //this->Gate->Update(now);
    }

    void Coord::Destory(int code) {
        this->coreLogDebug("[coord] Destory, code=%d", code);
        this->exitCode = code;
        uv_stop(&this->loop);        
    }

    uint64_t Coord::onGC() {
        return 0;
        //this->script->gc();
    }
    
    int Coord::onAwake(){   
        if (this->workerRole == worker_role_master) {   
            this->coreLogMsg("[coord] onAwake at %ld", this->Time()/1000);
        }
        this->pid = uv_os_getpid();
        this->PidPath = this->config->Basic.Pid + this->config->Basic.Name + ".pid";
        if (this->sceneMgr) {
            this->sceneMgr->onAwake();
        }
        if (this->workerRole == worker_role_master) {     
            //记录Pid
            std::ofstream outfile(this->PidPath, std::ios::trunc);
            outfile << this->pid << std::endl;
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
        if (this->config->Basic.Update > 0) {
            this->SetInterval(this->config->Basic.Update, std::bind(&Coord::onUpdate, this));
        }
        if (this->config->Basic.GC > 0) {
            this->SetInterval(this->config->Basic.GC, std::bind(&Coord::onGC, this));
        }
        this->isAwake = true;
        return 0;
    }

    void Coord::onDestory(int code) {
        this->coreLogDebug("[coord] onDestory, code=%d", code);
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
            std::ifstream pidFile;
            pidFile.open(this->PidPath.c_str(), std::ios::in);
            if(pidFile){
                uv_pid_t pid;
                pidFile >> pid;
                if(this->pid == pid) {
                    ::remove(this->PidPath.c_str());
                }
            }
            ::onDestory(this);
        }
    }

    int Coord::Fork(const char *configFile) {
        uv_thread_t* thread = (uv_thread_t*)malloc(sizeof(uv_thread_t));
        fork_data* forkData = (fork_data*)malloc(sizeof(fork_data));
        strcpy(forkData->configFile, configFile);
        forkData->coord = this;
        int err = uv_thread_create(thread, coord_main_thread, forkData);
        if (err) {
            free(forkData);
            return err;
        }
        Coord::coordDict[thread] = this;
        return 0;
    }
    
    int Coord::asCommand(const char *configFile, const char* command) {
        coorda = this;
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->config = newConfig(this); 
        this->ConfigFile = configFile;
        if (this->readConfig(configFile)) {
            return EXIT_FAILURE;
        }
        this->logger = this->LoggerMgr->GetConfigCategory("logger");
        this->coreLogger = this->LoggerMgr->GetConfigCategory("core-logger");
        if (strcmp(command, "stop") == 0) {
            std::string pidPath = this->config->Basic.Pid + this->config->Basic.Name + ".pid";
            std::ifstream ifile;
            ifile.open(pidPath.c_str(), std::ios::in);
            if(!ifile){
                fprintf(stderr, "pid file not found: %s\n", pidPath.c_str());
                return 1;
            }
            uv_pid_t pid;
            ifile >> pid;
            kill(pid, SIGINT);
        } else if (strcmp(command, "status") == 0) {

        } else if (strcmp(command, "reload") == 0) {
            std::string pidPath = this->config->Basic.Pid + this->config->Basic.Name + ".pid";
            std::ifstream ifile;
            ifile.open(pidPath.c_str(), std::ios::in);
            if(!ifile){
                fprintf(stderr, "pid file not found: %s\n", pidPath.c_str());
                return 1;
            }
            uv_pid_t pid;
            ifile >> pid;
            kill(pid, SIGUSR2);
        }
        return 0;
    }
    int Coord::Main(const char *configFile) {
        coorda = this;
        //this->coreLogger = log::newCoreLogger();
        //this->logger = log::newFileLogger();
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->config = newConfig(this); 
        this->Environment = newEnvironment(this);
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
        this->ConfigFile = configFile;
        {
            int err = this->Environment->main(configFile);
            if (err) {
                return err;
            }
        }   
        if (this->readConfig(configFile)) {
            return EXIT_FAILURE;
        }
        this->logger = this->LoggerMgr->GetConfigCategory("logger");
        this->coreLogger = this->LoggerMgr->GetConfigCategory("core-logger");

        //listen int signal
        uv_signal_init(&this->loop, &this->sigInt);
        this->sigInt.data = this;
        uv_signal_start(&this->sigInt, coord_sigint_handler, SIGINT);
        uv_signal_init(&this->loop, &this->sigUsr1);
        this->sigUsr1.data = this;
        uv_signal_start(&this->sigUsr1, coord_sigusr1_handler, SIGUSR1);
        uv_signal_init(&this->loop, &this->sigUsr2);
        this->sigUsr2.data = this;
        uv_signal_start(&this->sigUsr2, coord_sigusr2_handler, SIGUSR2);

        this->Name = this->config->Basic.Name;
        //logger
        {
            //auto config = this->logger->getConfig();
            //strcpy(config->Dir, this->config->Basic.Logger.c_str());
            //sprintf(config->Name, "%s", this->config->Basic.Name.c_str());
            //config->MaxByte = this->config->Basic.LoggerMaxByte;
            //this->logger->reload();
        }
        //core logger
        {
            //auto config = this->coreLogger->getConfig();
            //strcpy(config->Dir, this->config->Basic.CoreLogger.c_str());
            //sprintf(config->Name, "%s_core", this->config->Basic.Name.c_str());
            //config->MaxByte = this->config->Basic.CoreLoggerMaxByte;
            //this->coreLogger->reload();
        }

        this->coreLogDebug("[coord] running, cluster=%s", this->config->Basic.Registery.c_str());
        {
            int err = this->Proto->main();
            if (err) {
                return err;
            }
        }        
        //启动web服务
        if(this->config->SectionExist("WEB")) {
            this->HttpServer = http::newHttpServer(this);
            http::HttpServerConfig* config = this->HttpServer->DefaultConfig();
            config->Host = this->config->Web.Host;
            config->Port = this->config->Web.Port;
            config->Backlog = this->config->Web.Backlog;
            config->AssetDir = this->config->Web.AssetDir;
            config->RecvBufferSize = this->config->Web.RecvBuffer;
            config->SSLEncrypt = this->config->Web.SSLEncrypt;
            config->SSLPemFile = this->config->Web.SSLPemFile;
            config->SSLKeyFile = this->config->Web.SSLKeyFile;
            config->UseEtag = this->config->Web.UseEtag;
            int err = this->HttpServer->Start();
            if (err) {
                return err;
            }
        }   
        //打开cluster
        if(this->config->SectionExist("CLUSTER")) {
            this->Cluster = cluster::newCluster(this);
            cluster::ClusterConfig* config = this->Cluster->DefaultConfig();
            *config = this->config->Cluster;

           /* config->Port = this->config->Cluster.Port;
            config->Driver = this->config->Cluster.Driver;
            config->Host = this->config->Cluster.Host;
            config->Heartbeat = this->config->Cluster.Heartbeat;
            config->Expire = this->config->Cluster.Expire;
            config->Name = this->config->Cluster.Name;
            config->ReloadInterval = this->config->Cluster.ReloadInterval;
            config->ReconnectInterval = this->config->Cluster.ReconnectInterval;
            config->RegisterInterval = this->config->Cluster.RegisterInterval;
            config->RecvBuffer = this->config->Cluster.RecvBuffer;*/
            int err = this->Cluster->main();
            if (err < 0){
                return err;
            }
        }
        //启动网关
        if(this->config->SectionExist("GATE")) {
            this->Gate = gate::NewGate(this);
            gate::GateConfig* config = this->Gate->DefaultConfig();
            *config = this->config->Gate;
            /*config->ServerName = this->config->Gate.ServerName;
            config->Port = this->config->Gate.Port;
            config->Host = this->config->Gate.Host;
            config->Network = this->config->Gate.Network;
            config->RsaEncrypt = this->config->Gate.RsaEncrypt;
            config->RsaKeyFile = this->config->Gate.RsaKeyFile;
            config->Heartbeat = this->config->Gate.Heartbeat;
            config->Backlog = this->config->Gate.Backlog;
            config->RecvBuffer = this->config->Gate.RecvBuffer;
            config->SSLEncrypt = this->config->Gate.SSLEncrypt;
            config->SSLPemFile = this->config->Gate.SSLPemFile;
            config->SSLKeyFile = this->config->Gate.SSLKeyFile;
            config->MaxUser = this->config->Gate.MaxUser;
            config->MaxConnection = this->config->Gate.MaxConnection;
            config->Cluster = this->config->Gate.Cluster;
            config->RegisterExpire = this->config->Gate.RegisterExpire;
            config->RegisterInterval = this->config->Gate.RegisterInterval;
            config->UserRegisterExpire = this->config->Gate.UserRegisterExpire;
            config->UserRegisterInterval = this->config->Gate.UserRegisterInterval;*/
            int err = this->Gate->main();
            if (err) {
                return err;
            }
        }           
        //启动登录功能
        if(this->config->SectionExist("Login")) {
            this->Login = login::newLoginSvr(this);
            login::LoginConfig* config = this->Login->DefaultConfig();
            *config = this->config->Login;
            /*config->Port = this->config->Login.Port;
            config->Host = this->config->Login.Host;
            config->Backlog = this->config->Login.Backlog;
            config->RecvBufferSize = this->config->Login.RecvBuffer;
            config->SSLEncrypt = this->config->Login.SSLEncrypt;
            config->SSLPemFile = this->config->Login.SSLPemFile;
            config->SSLKeyFile = this->config->Login.SSLKeyFile;
            config->Cluster = this->config->Login.Cluster;*/
            int err = this->Login->main();
            if (err) {
                return err;
            }
        }       
        //打开cache
        if(this->config->SectionExist("CACHE")) {
            this->Cache = cache::newClient(this);
            if (this->Cache == nullptr) {
                return -1;
            }
            auto config = this->Cache->DefaultConfig();
            *config = this->config->Cache;

           /* config->Port = this->config->Cache.Port;
            config->Host = this->config->Cache.Host;
            config->DB = this->config->Cache.DB;
            config->Password = this->config->Cache.Password;
            config->ExpireTime = this->config->Cache.ExpireTime;*/
            int err = this->Cache->main();
            if (err) {
                return err;
            }
        }
         ;
        //启动managed服务
        if(this->config->SectionExist("MANAGED")) {
            this->Managed = managed::newManaged(this);
            managed::ManagedConfig* config = this->Managed->DefaultConfig();
            *config = this->config->Managed;
            /*config->Host = this->config->Managed.Host;
            config->Port = this->config->Managed.Port;
            config->User = this->config->Managed.User;
            config->Password = this->config->Managed.Password;*/
            int err = this->Managed->start();
            if (err) {
                return err;
            } 
        }
        //启动worker服务
        if(this->config->Basic.WorkerNum > 0) {
            std::string workerConfigPath = os::path::DirName(configFile);
            workerConfigPath = workerConfigPath + this->config->Basic.Worker;
            this->Worker = worker::newWorker(this);
            int err = this->Worker->start(workerConfigPath.c_str(), this->config->Basic.WorkerNum);
            if (err) {
                this->coreLogError("[Coord] worker start failed, error=%d", err);
                return err;
            }
        }
        this->workerRole = worker_role_master;
        if (this->config->Basic.Registery == "local"){
            if(this->Local()){
                return EXIT_FAILURE;
            }
        } else if (this->config->Basic.Registery == "slave"){
            if(this->slave()){
                return EXIT_FAILURE;
            }
        } else if (this->config->Basic.Registery == "master"){
            if(this->master()){
                return EXIT_FAILURE;
            }
        } else if (this->config->Basic.Registery == "client"){
            if(this->Client()){
                return EXIT_FAILURE;
            }
        }
        //异步启动的服务
        {
            this->Function()
            //启动cache
            ->Await([this](auto self, auto promise){
                if(!this->config->SectionExist("CACHE")) {
                    promise->Reslove();
                    return;
                }
                auto cache = cache::newAsyncClient(this);
                if (cache == nullptr) {
                    return;
                }
                auto config = cache->DefaultConfig();
                config->Port = this->config->Cache.Port;
                config->Host = this->config->Cache.Host;
                config->DB = this->config->Cache.DB;
                config->Password = this->config->Cache.Password;
                config->ExpireTime = this->config->Cache.ExpireTime;
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
                if (this->config->Basic.Main.length() > 0) {              
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
        uv_loop_close(&this->loop);
        this->onDestory(this->exitCode);
        return this->exitCode;
    }

    int Coord::asWorker(worker::Worker* master, const char *configFile, int index) {
        coorda = this;
        //this->coreLogger = log::newCoreLogger();
        //this->logger = log::newFileLogger();
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->config = newConfig(this); 
        this->Environment = newEnvironment(this);
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
        this->ConfigFile = configFile;
        {
            int err = this->Environment->main(configFile);
            if (err) {
                return err;
            }
        }   
        //继承配置
        this->config->Basic = master->coord->config->Basic;
        if (this->readConfig(configFile)) {
            return EXIT_FAILURE;
        }
        this->logger = this->LoggerMgr->GetConfigCategory("logger");
        this->coreLogger = this->LoggerMgr->GetConfigCategory("core-logger");
        this->Name = config->Basic.Name;
        //logger
        {
            //auto config = this->logger->getConfig();
            //strcpy(config->Dir, this->config->Basic.Logger.c_str());
            //sprintf(config->Name, "%s_worker%d", this->config->Basic.Name.c_str(), index);
            //config->MaxByte = this->config->Basic.LoggerMaxByte;
            //this->logger->reload();
        }
        //core logger
        {
            //auto config = this->coreLogger->getConfig();
            //strcpy(config->Dir, this->config->Basic.CoreLogger.c_str());
            //sprintf(config->Name, "%s_worker%d_core", this->config->Basic.Name.c_str(), index);
            //config->MaxByte = this->config->Basic.CoreLoggerMaxByte;
            //this->coreLogger->reload();
        }
        {
            int err = this->Proto->main();
            if (err) {
                return err;
            }
        }
       // this->SetLogLevel(log::ERROR);
        //启动worker slave服务
        this->WorkerSlave = worker::newWorkerSlave(this, master);
        int err = this->WorkerSlave->start();
        if (err) {
            return err;
        }
        this->workerRole = worker_role_slave;
        //加载脚本 
        if (this->config->Basic.Main.length() > 0) {
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
        this->onDestory(this->exitCode);
        return this->exitCode;
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

    int Coord::beforeTest(const char *configFile) {
        coorda = this;
        //this->coreLogger = log::newCoreLogger();
        //this->logger = log::newFileLogger();
        this->LoggerMgr = log4cc::newLoggerMgr(this);
        this->config = newConfig(this); 
        //this->coreLogError("hello");
        this->Environment = newEnvironment(this);
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
        this->ConfigFile = configFile;
        {
            int err = this->Environment->main(configFile);
            if (err) {
                return err;
            }
        }  
        if (this->readConfig(configFile)) {
            return EXIT_FAILURE;
        }
        this->logger = this->LoggerMgr->GetConfigCategory("logger");
        this->coreLogger = this->LoggerMgr->GetConfigCategory("core-logger");
        this->workerRole = worker_role_master;
        {
            int err = this->Proto->main();
            if (err) {
                return err;
            }
        }
        //加载脚本 
        if (this->config->Basic.Main.length() > 0) {              
            //加载脚本
            int err =  this->Script->main();
            if (err) {
                return err;
            }
        }
        //启动
        int err = this->onAwake();
        if (err) {
            return err;
        }
        return 0;
    }

    void Coord::loopTest() {
        uv_run(&this->loop, UV_RUN_DEFAULT);
        uv_loop_close(&this->loop);
    }

    int Coord::afterTest() {
    
        this->onDestory(this->exitCode);
        return this->exitCode;
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

    void Coord::recvSigInt() {
        this->Destory(0);
    }

    int Coord::readConfig(const char *filePath) {
        return this->config->parse(filePath);
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

    void Coord::LogCloseLevel(int level) {
        //this->logger->CloseLevel(level);
    }

    void Coord::LogOpenLevel(int level) {
        //this->logger->OpenLevel(level);
    }

    void Coord::LogSetLevel(int level) {
        //this->logger->SetLevel(level);
    }

    void Coord::coreLogFatal(const char* str) const{;
        if(this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Fatal(str);
        }
    }

    void Coord::coreLogError(const char* str) const{
        if(this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Error(str);
        }
    }

    void Coord::coreLogWarn(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Warn(str);
        }
    }

    void Coord::coreLogInfo(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Info(str);
        }
    }

    void Coord::coreLogDebug(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Debug(str);
        }
    }

    void Coord::coreLogMsg(const char* str) const{
        if (this->coreLogger == nullptr) {
            fprintf(stderr, str);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Notice(str);
        }
    }

    void Coord::coreLogFatal(const char* fmt, ...){
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

    void Coord::coreLogError(const char* fmt, ...){
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

    void Coord::coreLogWarn(const char* fmt, ...){
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

    void Coord::coreLogInfo(const char* fmt, ...){
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

    void Coord::coreLogDebug(const char* fmt, ...){
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

    void Coord::coreLogMsg(const char* fmt, ...){
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

    void Coord::coreLogFatal(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
        } else {
            this->coreLogger->Fatal(fmt, args);
        }
    }
    
    void Coord::coreLogError(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Error(fmt, args);
        }
    }

    void Coord::coreLogWarn(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Warn(fmt, args);
        }
    }

    void Coord::coreLogInfo(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Info(fmt, args);
        }
    }

    void Coord::coreLogMsg(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Notice(fmt, args);
        }
    }

    void Coord::coreLogDebug(const char* fmt, va_list args){
        if (this->coreLogger == nullptr) {
            vfprintf(stderr, fmt, args);
            fprintf(stderr, "\n");
        } else {
            this->coreLogger->Debug(fmt, args);
        }
    }

    void Coord::coreLogCloseLevel(int level) {
        //log::CloseLevel(level);
        //this->coreLogger->CloseLevel(level);
    }

    void Coord::coreLogOpenLevel(int level) {
        //log::OpenLevel(level);
        //this->coreLogger->OpenLevel(level);
    }

    void Coord::coreLogSetLevel(int level) {
        //log::SetLevel(level);
        //this->coreLogger->SetLevel(level);
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
        http::HttpServer* server = http::newHttpServer(this);
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

    void Coord::Destory(Destoryable* object) {
        object->_ref--;
        if(object->_ref != 0){ //避免循环删除，要用!=0判断。 a删除b, b删除a, 导致一直循环
            return;
        }
        object->onDestory();
        delete object;
    }

    void Coord::Destory(net::TcpClient* object) {
        object->onDestory();
    } 

    void Coord::DontDestory(Destoryable* object) {
        if(object->_ref <= 0) { //避免在destory里，又被操作ref
            return;
        }
        object->_ref++;
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

    redis::Client* Coord::RedisConfig(const char* name) {
        return this->RedisMgr->GetClient(name);
    }

    redis::AsyncClient* Coord::RedisAsyncConfig(const char* name) {
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

