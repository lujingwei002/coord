#include "coord/config/config.h"
#include "coord/log/log.h"
#include "coord/sql/sql_client.h"
#include "coord/redis/redis_client.h"
#include "coord/builtin/init.h"
#include "coord/log4cc/log4cc.h"
#include "coord/coord.h"
#include "inipp/inipp.h"
#include <fstream>
#include <iostream>
#include <regex>

namespace coord {
static const char* TAG = "Config";
static std::string DEFAULT_SECTION_NAME = "DEFAULT";
static std::string WEB_SECTION_NAME = "WEB";
static std::string LOGIN_SECTION_NAME = "Login";
static std::string GATE_SECTION_NAME = "GATE";
static std::string CACHE_SECTION_NAME = "CACHE";
static std::string CLUSTER_SECTION_NAME = "CLUSTER";
static std::string MANAGED_SECTION_NAME = "MANAGED";

#define UTF8_CODE_POINT_LENGTH(byte) ((( 0xE5000000 >> (( byte >> 3 ) & 0x1e )) & 3 ) + 1)
#define TEST_ASCII(check, byte, length) (length == 1 && check(byte))
#define IS_ASCII(v, byte, length) (length == 1 && byte == v)

static int stringEscape(const char* src, size_t srcSize, char* dest, size_t* destSize) {
    size_t j = 0;
    for (size_t i = 0; i < srcSize; i++) {
        if (src[i] == '\\' && i < srcSize - 1) {
            char c = src[i + 1];
            if (c == '"') {
                dest[j++] = '"';
            } else if (c == 'n') {
                dest[j++] = '\n';
            } else if (c == '\\') {
                dest[j++] = '\\';
            } else if (c == 'a') {
                dest[j++] = '\a';
            } else if (c == 'r') {
                dest[j++] = '\r';
            } else if (c == 'b') {
                dest[j++] = '\b';
            } else if (c == 'f') {
                dest[j++] = '\f';
            } else if (c == 'v') {
                dest[j++] = '\v';
            } else if (c == 't') {
                dest[j++] = '\t';
            } else {
                return ErrorInvalidArg;
            }
            if (j >= *destSize) {
                return ErrorInvalidArg;
            }
            i = i + 1;
        } else {
            dest[j++] = src[i];
        }
    }
    *destSize = j;
    return 0;
}

// Config *newConfig(Coord* coord) {
//     Config *config = new Config(coord);
//     return config;
// }

Config::~Config() {
}

Config::Config(Coord* coord) {
    this->coord = coord;

    this->Basic.GC = 0;
    this->Basic.Name = "coord";
    this->Basic.Update = 100;
    this->Basic.WorkerNum = 0;
    this->Basic.Pid = "./";
    this->Basic.Version = "0.0.0";
    
    this->Web.Port = 0;
    this->Web.Backlog = 1024;
    this->Web.RecvBuffer = 4096;
    this->Web.SSLEncrypt = false;
    this->Web.AssetDir = "./";
    this->Web.UseEtag = true;

    this->Gate.ServerName = "127.0.0.1";
    this->Gate.Port = 0;
    this->Gate.Network = "tcp";
    this->Gate.RsaEncrypt = false;
    this->Gate.Heartbeat = 60000;
    this->Gate.Backlog = 1024;
    this->Gate.RecvBuffer = 4096;
    this->Gate.SSLEncrypt = false;
    this->Gate.MaxUser = 10000;
    this->Gate.MaxConnection = 20000;
    this->Gate.UserRegisterExpire = 60;
    this->Gate.UserRegisterInterval = 30;
    this->Gate.RegisterExpire = 60;
    this->Gate.RegisterInterval = 30;

    this->Cache.Port = 0;

    this->Cluster.Port = 0;
    this->Cluster.Heartbeat = 30;
    this->Cluster.Expire = 60;
    this->Cluster.RegisterInterval = 60;
    this->Cluster.ReloadInterval = 60;
    this->Cluster.ReconnectInterval = 30;
    this->Cluster.RecvBuffer = 4096;

    this->Managed.Port = 0;
}

int Config::urlParse(const char* path, std::string& section, std::string& key) {
    return this->urlParse(path, strlen(path), section, key);
}

int Config::urlParse(const char* data, size_t size, std::string& section, std::string& key) {
    size_t i = 0;
    int codePointLength = 1;
    int phase = 0;
    char* sectionStart = (char*)data;
    char* keyStart = nullptr;
    
    for (; i < size;  i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (IS_ASCII('.', c, codePointLength)) {
                section.assign(sectionStart, data + i - sectionStart);
                phase = 1;
                keyStart = (char*)data + i + codePointLength;
            }
        }
    }
    if (phase == 1) {
        key.assign(keyStart, data + i - keyStart);
    } else {
        section = DEFAULT_SECTION_NAME;
        key.assign(sectionStart, data + i - sectionStart);
    }
    return 0;
}

int Config::gotConfigLineError(const std::string& configPath, int lineNum, char* data, size_t size) {
    std::string line(data, size);
    this->coord->coreLogError("parse error %s(%d): %s", configPath.c_str(), lineNum, line.c_str());
    return 0;
}

static thread_local std::map<std::string, std::string>* temp_session;
static thread_local std::string temp_key;
int Config::gotConfigKey(char* data, size_t size) {
    temp_key = std::string(data, size);
    //printf("key: %s\n", temp_key.c_str());
    return 0;
}

int Config::gotConfigSection(char* data, size_t size) {
    std::string word = std::string(data, size);
    //printf("section: %s\n", word.c_str());
    auto it = this->Sections.find(word);
    if (it == this->Sections.end()) {
        this->Sections[word] = std::map<std::string, std::string>{};
        auto it1 = this->Sections.find(word);
        if (it1 == this->Sections.end()) {
            return ErrorInvalidArg;
        }
        temp_session = &it1->second;
    }  else {
        temp_session = &it->second;
    }
    return 0;
}

int Config::gotConfigQuoteValue(char* data, size_t size) {
    if (temp_session == nullptr) {
        auto it = this->Sections.find(DEFAULT_SECTION_NAME);
        if (it == this->Sections.end()) {
            this->Sections[DEFAULT_SECTION_NAME] = std::map<std::string, std::string>{};
            auto it1 = this->Sections.find(DEFAULT_SECTION_NAME);
            if (it1 != this->Sections.end()) {
                temp_session = &it1->second;
            }
        } else {
            temp_session = &it->second;
        }
    }
    if (temp_session == nullptr) {
        return ErrorInvalidArg;
    }
    char buffer[1024];
    size_t bufferLen = sizeof(buffer);
    // scan replace {xx} with environment variable
    char* nameStart = nullptr;
    char* nameEnd = nullptr;
    char* braceStart = nullptr;

    size_t i = 0;
    size_t j = 0;
    int codePointLength = 1;
    int phase = 0;// 0=find $ 1=find { 2=find }
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (IS_ASCII('$', c, codePointLength)) {
                phase = 1;
                braceStart = data + i;
            } else {
                size_t length = codePointLength;
                if (j + length > bufferLen) return ErrorBufferNotEnough;
                memcpy(buffer + j, data + i, length);
                j = j + length;
            }
        } else if (phase == 1) {
            if (IS_ASCII('{', c, codePointLength)) {
                phase = 2;
                nameStart = data + i + codePointLength;
            } else {
                size_t length = data + i - braceStart + codePointLength;
                if (j + length > bufferLen) return ErrorBufferNotEnough;
                memcpy(buffer + j, braceStart, length);
                j = j + length;
                phase = 0;
            }
        } else if (phase == 2) {
            if (IS_ASCII('}', c, codePointLength)) {
                nameEnd = data + i;
                if (nameEnd - nameStart <= 0) return ErrorInterpret;
                // 先在 env里搜索
                std::string name = std::string(nameStart, nameEnd - nameStart);
                std::string realValue;
                //this->coord->Environment->
                if (this->coord->Environment->Get(name, realValue)) {
                    size_t length = realValue.length();
                    if (j + length > bufferLen) return ErrorBufferNotEnough;
                    memcpy(buffer + j, realValue.c_str(), length);
                    j = j + length;
                } else {
                    auto const it = this->Sections.find(DEFAULT_SECTION_NAME);
                    if (it == this->Sections.end()){
                        return ErrorInterpret;
                    }
                    if(!this->Get(name, realValue)) {
                        return ErrorInterpret;
                    }
                    size_t length = realValue.length();
                    if (j + length > bufferLen) return ErrorBufferNotEnough;
                    memcpy(buffer + j, realValue.c_str(), length);
                    j = j + length;
                }
                // 再在config里搜索
                braceStart = nullptr;
                nameStart = nullptr;
                nameEnd = nullptr;
                phase = 0;
            } else if (IS_ASCII('.', c, codePointLength)) {
            } else if (IS_ASCII('-', c, codePointLength)) {
            } else if (!TEST_ASCII(isalpha, c, codePointLength)) {
                return ErrorInterpret;
            }
        } 
    }
    if (braceStart && !nameStart) {
        size_t length = data + i - braceStart;
        if (j + length > bufferLen) return ErrorBufferNotEnough;
        memcpy(buffer + j, braceStart, length);
        j = j + length;
    } else if (nameStart && !nameEnd) {
        return ErrorInterpret;
    }
    std::string word = std::string(buffer, j);
    (*temp_session)[temp_key] = word;
    //printf("value: %s\n", word.c_str());
    return 0;
}

int Config::gotConfigValue(char* data, size_t size) {
    if (temp_session == nullptr) {
        return ErrorInvalidArg;
    }
    std::string word = std::string(data, size);
    (*temp_session)[temp_key] = word;
    //printf("value: %s\n", word.c_str());
    return 0;
}

int Config::scanConfigSectionLine(char* data, size_t size) {
    size_t i = 0;
    int codePointLength = 1;
    int phase = 0;//0=find [ 1=find word begin 2=find word end 3=find ] 4=finish
    char* valueStart = nullptr;
    char* valueEnd = nullptr;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (IS_ASCII('[', c, codePointLength)) {
                // [
                phase = 1;
            } else if (!TEST_ASCII(isspace, c, codePointLength)) {
                // x 
                return ErrorInvalidArg;
            }
        } else if(phase == 1) {
            if (TEST_ASCII(isalpha, c, codePointLength)) {
                // [ D
                phase = 2;
                valueStart = data + i;
            } else if (!TEST_ASCII(isspace, c, codePointLength)) {
                // [ &
                return ErrorInvalidArg;
            }
        } else if(phase == 2) {
            if (TEST_ASCII(isspace, c, codePointLength)) {
                // [D   
                phase = 3;
                valueEnd = data + i;
            } else if (IS_ASCII(']', c, codePointLength)) {
                // [D]
                phase = 4;
                valueEnd = data + i;
            }
        } else if(phase == 3) {
            if (IS_ASCII(']', c, codePointLength)) {
                // [DEFAULT ]
                phase = 4;
            } else if (!TEST_ASCII(isspace, c, codePointLength)) {
                // [DEFAULT xx
                return ErrorInvalidArg;
            }
        } else if(phase == 4) {
            if (!TEST_ASCII(isspace, c, codePointLength)) {
                // [DEFAULT] xx
                return ErrorInvalidArg;
            }
        }
    }
    if (!valueStart || !valueEnd) {
        return ErrorInvalidArg;
    }
    this->gotConfigSection(valueStart, valueEnd - valueStart);
    return 0;
}

int Config::scanConfigDirectiveLine(const std::string& configPath, char* data, size_t size) {
    int maxArgCount = 5;
    char* argv[maxArgCount];
    size_t argLen[maxArgCount];
    int argc = 0;
    size_t i = 0;
    int phase = 0;//0=find word begin 1=find word end
    int codePointLength = 1;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (!TEST_ASCII(isspace, c, codePointLength)) {
                if (argc > maxArgCount - 1) {return ErrorInvalidArg;}
                argv[argc] = data + i;
                phase = 1;
                if(i + codePointLength == size) {
                    argLen[argc] = data + i - argv[argc] + codePointLength;
                    argc++;
                }
            }
        } else if(phase == 1) {
            if (TEST_ASCII(isspace, c, codePointLength)) {
                argLen[argc] = data + i - argv[argc];
                phase = 0;
                argc++;
            } else if(i + codePointLength == size) {
                argLen[argc] = data + i - argv[argc] + codePointLength;
                argc++;
            }
        }
    }
    if (argc == 0) {
        return 0;
    }
    if(strncmp(argv[0], "include", argLen[0]) == 0) {
        if (argc != 2) {
            return ErrorInvalidArg;
        }
        std::string currentDir = coord::path::DirName(configPath);
        std::string fileName = std::string(argv[1], argLen[1]);
        std::string realPath = coord::path::PathJoin(currentDir, fileName);
        return this->scanConfigFile(realPath);
    }
    return ErrorInvalidArg;
}

int Config::scanConfigLine(const std::string& configPath, char* data, size_t size) {
    size_t i = 0;
    int codePointLength = 1;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (IS_ASCII(';', c, codePointLength)) {
            return 0;
        } else if (IS_ASCII('[', c, codePointLength)) {
            return this->scanConfigSectionLine(data, size);
        } else if (IS_ASCII('=', c, codePointLength)) {
            int err = this->scanConfigKey(data, i);
            if (err) return err;
            return this->scanConfigValue(data + i + 1, size - i - 1);
        }
    }
    return this->scanConfigDirectiveLine(configPath, data, size);
}

int Config::scanConfigKey(char* data, size_t size) {
    size_t i = 0;
    int codePointLength = 1;
    int phase = 0;//0=find word begin 1=find word end 2=find end
    char* wordStart = nullptr;
    char* wordEnd = nullptr;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (!TEST_ASCII(isspace, c, codePointLength)) {
                phase = 1;
                wordStart = data + i;
                wordEnd = data + i + codePointLength;
            }
        } else if(phase == 1) {
            if (!TEST_ASCII(isspace, c, codePointLength)) {
                wordEnd = data + i + codePointLength;
            } 
        }
    }
    if (wordStart && wordEnd) {
        return this->gotConfigKey(wordStart, wordEnd - wordStart);
    }
    return 1;
}

int Config::scanConfigQuoteValue(char* data, size_t size) {
    size_t i = 0;
    int codePointLength = 1;
    int phase = 0;//0=find word begin 1=find word end 2=find end 3=escape
    char* wordStart = nullptr;
    char* wordEnd = nullptr;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (IS_ASCII('"', c, codePointLength)) {
                wordStart = data + i + codePointLength;
                phase = 1;
            } else if(!isspace(c)) {
                return ErrorInvalidArg;
            }
        } else if(phase == 1) {
            if (IS_ASCII('"', c, codePointLength)) {
                phase = 2;
                wordEnd = data + i ;
            } else if (IS_ASCII('\\', c, codePointLength)) {
                phase = 3;
            }
        } else if(phase == 2){
            if (!TEST_ASCII(isspace, c, codePointLength)) {
                return ErrorInvalidArg;
            }
        } else if(phase == 3){
            phase = 1;
        }
    }
    if (!(wordStart && wordEnd)) {
        return ErrorInvalidArg;
    }
    char wordLen = wordEnd - wordStart;
    char buffer[wordLen];
    size_t realSize = wordLen;
    int err = stringEscape(wordStart, wordLen, buffer, &realSize);
    if (err) {
        return err;
    }
    return this->gotConfigQuoteValue(buffer, realSize);
}

int Config::scanConfigValue(char* data, size_t size) {
    size_t i = 0;
    int codePointLength = 1;
    int phase = 0;//0=find word begin 1=find word end 2=find end
    char* wordStart = nullptr;
    char* wordEnd = nullptr;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (IS_ASCII('"', c, codePointLength)) {
                return this->scanConfigQuoteValue(data + i, size - i);
            } else if (!TEST_ASCII(isspace, c, codePointLength)) {
                phase = 1;
                wordStart = data + i;
                wordEnd = data + i + codePointLength;
            }
        } else if(phase == 1) {
            if (!TEST_ASCII(isspace, c, codePointLength)) {
                wordEnd = data + i + codePointLength;
            } 
        }
    }
    if (wordStart && wordEnd) {
        return this->gotConfigValue(wordStart, wordEnd - wordStart);
    } else {
        return this->gotConfigValue(data, 0);
    }
}


int Config::scanConfigMultiLine(const std::string& configPath, char* data, size_t size) {
    size_t i = 0;
    int codePointLength = 1;
    int lineNum = 1;
    char* lineStart = nullptr;
    int phase = 0;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (phase == 0) {
            if (!IS_ASCII('\n', c, codePointLength) && !IS_ASCII('\r', c, codePointLength)) {
                lineStart = data + i;
                phase = 1;
            }
        } else if(phase == 1) {
            if (IS_ASCII('\r', c, codePointLength) || IS_ASCII('\n', c, codePointLength)) {
                data[i] = 0;
                int err = this->scanConfigLine(configPath, lineStart, data + i - lineStart);
                if (err) {
                    this->gotConfigLineError(configPath, lineNum, lineStart, data + i - lineStart);
                    return err;
                }
                lineNum = lineNum + 1;
                lineStart = nullptr;
                phase = 0;
            } 
        }
    }
    if (lineStart) {
        int err = this->scanConfigLine(configPath, lineStart, data + i - lineStart);
        if (err) {
            this->gotConfigLineError(configPath, lineNum, lineStart, data + i - lineStart);
            return err;
        }
        return 0;
    }
    return 0;
}

int Config::scanConfigFile(const std::string& configPath) {
    FILE* f = fopen(configPath.c_str(), "r");
    if (nullptr == f) {
        this->coord->coreLogError("no such file or directory: %s", configPath.c_str());
        return ErrorNoSuchFileOrDirectory;
    }
    fseek(f, 0, SEEK_END);
    int fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char lines[fileSize + 1];
    size_t size = sizeof(lines);
    size_t read = fread(lines, 1, size, f);
    if (read >= size) {
        return ErrorBufferNotEnough;
    }
    lines[read] = 0;
    return this->scanConfigMultiLine(configPath, lines, read);
}

void Config::DebugString(){
    this->coord->LogInfo("========================= Config =========================");
    for (auto const & it : this->Sections) {
        this->coord->LogInfo("[%s] [%s]", TAG, it.first.c_str());
        for (auto const & it1 : it.second) {
            this->coord->LogInfo("[%s] %-18s = %s", TAG, it1.first.c_str(), it1.second.c_str());
        }
    }
    this->coord->LogInfo("========================= [%s] =========================", DEFAULT_SECTION_NAME.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "env", this->Basic.Env.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "name", this->Basic.Name.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "main", this->Basic.Main.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "scene", this->Basic.Scene.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "registery", this->Basic.Registery.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "package", this->Basic.Package.c_str());
    this->coord->LogInfo("[%s] %-15s: %ld", TAG, "gc", this->Basic.GC);
    this->coord->LogInfo("[%s] %-15s: %ld", TAG, "update", this->Basic.Update);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "worker", this->Basic.Worker.c_str());
    this->coord->LogInfo("[%s] %-15s: %ld", TAG, "worker-num", this->Basic.WorkerNum);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "proto", this->Basic.Proto.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "pid", this->Basic.Pid.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "version", this->Basic.Version.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "short-version", this->Basic.ShortVersion.c_str());

    this->coord->LogInfo("========================= [%s] =========================", WEB_SECTION_NAME.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "host", this->Web.Host.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "port", this->Web.Port);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "backlog", this->Web.Backlog);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "recv-buffer", this->Web.RecvBuffer);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "ssl-encrypt", this->Web.SSLEncrypt ? "true" : "false");
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "ssl-pem", this->Web.SSLPemFile.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "ssl-key", this->Web.SSLKeyFile.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "asset-dir", this->Web.AssetDir.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "use-etag", this->Web.UseEtag? "true" : "false");

    this->coord->LogInfo("========================= [%s] =========================", GATE_SECTION_NAME.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "sever-name", this->Gate.ServerName.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "port", this->Gate.Port);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "host", this->Gate.Host.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "network", this->Gate.Network.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "rsa-encrypt", this->Gate.RsaEncrypt? "true" : "false");
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "rsa-keyfile", this->Gate.RsaKeyFile.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "heartbeat", this->Gate.Heartbeat);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "backlog", this->Gate.Backlog);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "recv-buffer", this->Gate.RecvBuffer);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "ssl-encrypt", this->Gate.SSLEncrypt ? "true" : "false");
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "ssl-pem", this->Gate.SSLPemFile.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "ssl-key", this->Gate.SSLKeyFile.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "max-user", this->Gate.MaxUser);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "max-connection", this->Gate.MaxConnection);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "cluster", this->Gate.Cluster.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "register-expire", this->Gate.RegisterExpire);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "register-interval", this->Gate.RegisterInterval);

    this->coord->LogInfo("========================= [%s] =========================", CACHE_SECTION_NAME.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "password", this->Cache.Password.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "db", this->Cache.DB.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "host", this->Cache.Host.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "port", this->Cache.Port);

    this->coord->LogInfo("========================= [%s] =========================", CLUSTER_SECTION_NAME.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "port", this->Cluster.Port);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "host", this->Cluster.Host.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "driver", this->Cluster.Driver.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "heartbeat", this->Cluster.Heartbeat);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "expire", this->Cluster.Expire);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "reload-interval", this->Cluster.ReloadInterval);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "reconnect-interval", this->Cluster.ReconnectInterval);
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "register-interval", this->Cluster.RegisterInterval);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "name", this->Cluster.Name.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "recv-buffer", this->Cluster.RecvBuffer);

    this->coord->LogInfo("========================= [%s] =========================", MANAGED_SECTION_NAME.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "host", this->Managed.Host.c_str());
    this->coord->LogInfo("[%s] %-15s: %d", TAG, "port", this->Managed.Port);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "user", this->Managed.User.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "password", this->Managed.Password.c_str());

}

int Config::parse(const char* configPath) {
    std::string realPath;
    int err = coord::path::RealPath(configPath, realPath);
    if (err) {
        this->coord->coreLogError("%s: %s", uv_strerror(err), configPath);
        return err;
    }
    err = this->scanConfigFile(realPath);
    if (err) {
        return err;
    }
    if(this->Sections.find(DEFAULT_SECTION_NAME) != this->Sections.end()) {
        auto const it = this->Sections.find(DEFAULT_SECTION_NAME);
        this->get(it->second, "env", this->Basic.Env);
        this->get(it->second, "registery", this->Basic.Registery);
        this->get(it->second, "main", this->Basic.Main);
        this->get(it->second, "scene", this->Basic.Scene);
        this->get(it->second, "package", this->Basic.Package);
        this->get(it->second, "gc", this->Basic.GC);
        this->get(it->second, "update", this->Basic.Update);
        this->get(it->second, "worker", this->Basic.Worker);
        this->get(it->second, "worker_num", this->Basic.WorkerNum);
        this->get(it->second, "proto", this->Basic.Proto);
        this->get(it->second, "name", this->Basic.Name);
        this->get(it->second, "pid", this->Basic.Pid);
        this->get(it->second, "version", this->Basic.Version);
    }

    // 处理package, 转换成绝对路径
    {
        std::string package;
        size_t begin = 0;
        while (this->Basic.Package.length() > 0) {
            size_t pos = this->Basic.Package.find(";", begin);
            if (pos == std::string::npos) {
                std::string path = this->Basic.Package.substr(begin);
                if (!coord::path::IsAbsolutePath(path.c_str())) {
                    path = coord::path::PathJoin(this->coord->Environment->ConfigDir, path);
                }
                if (package.length() == 0) {
                    package = path;
                } else {
                    package = path + ";" + package;
                }
                break;
            } else {
                std::string path = this->Basic.Package.substr(begin, pos - begin);
                if (!coord::path::IsAbsolutePath(path.c_str())) {
                    path = coord::path::PathJoin(this->coord->Environment->ConfigDir, path);
                }
                if (package.length() == 0) {
                    package = path;
                } else {
                    package = path + ";" + package;
                }
                begin = pos + 1;
            }
        }
        this->Basic.Package = package;
    }
    // 处理version
    int first = 0;
    auto it = std::find_if(this->Basic.Version.begin(), this->Basic.Version.end(), [&first](char c) {
        if (c == '.')first++;
        return first >= 2;
    });
    if (it == this->Basic.Version.end()) {
        return -1;
    }
    this->Basic.ShortVersion = this->Basic.Version.substr(0, it - this->Basic.Version.begin());

    // 读取各个模块配置
    if(this->Sections.find(WEB_SECTION_NAME) != this->Sections.end()) {
        auto const it = this->Sections.find("WEB");
        this->get(it->second, "port", this->Web.Port);
        this->get(it->second, "host", this->Web.Host);
        this->get(it->second, "backlog", this->Web.Backlog);
        this->get(it->second, "recv_buffer", this->Web.RecvBuffer);
        this->get(it->second, "ssl-encrypt", this->Web.SSLEncrypt);
        this->get(it->second, "ssl-pem", this->Web.SSLPemFile);
        this->get(it->second, "ssl-key", this->Web.SSLKeyFile);
        this->get(it->second, "asset-dir", this->Web.AssetDir);
        this->get(it->second, "use-etag", this->Web.UseEtag);
    }

    if(this->Sections.find(LOGIN_SECTION_NAME) != this->Sections.end()) {
        auto const it = this->Sections.find(LOGIN_SECTION_NAME);
        this->get(it->second, "port", this->Login.Port);
        this->get(it->second, "host", this->Login.Host);
        this->get(it->second, "backlog", this->Login.Backlog);
        this->get(it->second, "recv-buffer", this->Login.RecvBufferSize);
        this->get(it->second, "ssl-encrypt", this->Login.SSLEncrypt);
        this->get(it->second, "ssl-pem", this->Login.SSLPemFile);
        this->get(it->second, "ssl-key", this->Login.SSLKeyFile);
        this->get(it->second, "cluster", this->Login.Cluster);
    } 

    if(this->Sections.find("GATE") != this->Sections.end()) {
        auto const it = this->Sections.find("GATE");
        this->get(it->second, "server_name", this->Gate.ServerName);
        this->get(it->second, "port", this->Gate.Port);
        this->get(it->second, "host", this->Gate.Host);
        this->get(it->second, "network", this->Gate.Network);
        this->get(it->second, "rsa-encrypt", this->Gate.RsaEncrypt);
        this->get(it->second, "rsa-keyfile", this->Gate.RsaKeyFile);
        this->get(it->second, "heartbeat", this->Gate.Heartbeat);
        this->get(it->second, "backlog", this->Gate.Backlog);
        this->get(it->second, "recv-buffer", this->Gate.RecvBuffer);
        this->get(it->second, "ssl-encrypt", this->Gate.SSLEncrypt);
        this->get(it->second, "ssl-pem", this->Gate.SSLPemFile);
        this->get(it->second, "ssl-key", this->Gate.SSLKeyFile);
        this->get(it->second, "max-user", this->Gate.MaxUser);
        this->get(it->second, "max-connection", this->Gate.MaxConnection);
        this->get(it->second, "cluster", this->Gate.Cluster);
        this->get(it->second, "register-expire", this->Gate.RegisterExpire);
        this->get(it->second, "register-interval", this->Gate.RegisterInterval);
    }
    if(this->Sections.find(CACHE_SECTION_NAME) != this->Sections.end()) {
        auto const it = this->Sections.find(CACHE_SECTION_NAME);
        this->get(it->second, "password", this->Cache.Password);
        this->get(it->second, "db", this->Cache.DB);
        this->get(it->second, "port", this->Cache.Port);
        this->get(it->second, "host", this->Cache.Host);
        this->get(it->second, "expire", this->Cache.ExpireTime);
    }

    if(this->Sections.find(CLUSTER_SECTION_NAME) != this->Sections.end()) {
        auto const it = this->Sections.find(CLUSTER_SECTION_NAME);
        this->get(it->second, "port", this->Cluster.Port);
        this->get(it->second, "host", this->Cluster.Host);
        this->get(it->second, "driver", this->Cluster.Driver);
        this->get(it->second, "heartbeat", this->Cluster.Heartbeat);
        this->get(it->second, "expire", this->Cluster.Expire);
        this->get(it->second, "reload-interval", this->Cluster.ReloadInterval);
        this->get(it->second, "reconnect-interval", this->Cluster.ReconnectInterval);
        this->get(it->second, "register-interval", this->Cluster.RegisterInterval);
        this->get(it->second, "name", this->Cluster.Name);
        this->get(it->second, "recv-buffer", this->Cluster.RecvBuffer);
    }

    if(this->Sections.find(MANAGED_SECTION_NAME) != this->Sections.end()) {
        auto const it = this->Sections.find(MANAGED_SECTION_NAME);
        this->get(it->second, "host", this->Managed.Host);
        this->get(it->second, "port", this->Managed.Port);
        this->get(it->second, "user", this->Managed.User);
        this->get(it->second, "password", this->Managed.Password);
    }
    return 0;
}

bool Config::SectionExist(const std::string& section) {
    auto it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return false;
    }
    return true;
}

int Config::SQLConfig(const std::string& section, sql::SQLConfig* config) {
    if (nullptr == config) {
        return ErrorNull;
    }
    auto const it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "user", config->User)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "character-set", config->CharacterSet)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "driver", config->Driver)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

int Config::RedisConfig(const std::string& section, redis::RedisConfig* config) {
    if (nullptr == config) {
        return ErrorNull;
    }
    auto const it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!this->get(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

int Config::LoggerConfig(const std::string& section, log4cc::LoggerConfig* config) {
    if (nullptr == config) {
        return ErrorNull;
    }
    auto const it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return ErrorConfigNotExist;
    }
    this->get(it->second, "file", config->File);
    this->get(it->second, "layout", config->Layout, "basic");
    this->get(it->second, "max-line", config->MaxLine, 0);
    this->get(it->second, "max-byte", config->MaxByte, 0); 
    this->get(it->second, "console", config->Console, true);
    std::string priority;
    if(this->get(it->second, "priority", priority)) {
        config->Priority = log4cc::IntPriority(priority.c_str());
    }
    return 0;
}


}
