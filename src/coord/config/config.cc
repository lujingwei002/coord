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

#define UTF8_CODE_POINT_LENGTH(byte) ((( 0xE5000000 >> (( byte >> 3 ) & 0x1e )) & 3 ) + 1)
#define TEST_ASCII(check, byte, length) (length == 1 && check(byte))
#define IS_ASCII(v, byte, length) (length == 1 && byte == v)

template <typename CharT, typename T>
static inline bool extract(const std::basic_string<CharT> & value, T & dst) {
	CharT c;
	std::basic_istringstream<CharT> is{ value };
	T result;
	if ((is >> std::boolalpha >> result) && !(is >> c)) {
		dst = result;
		return true;
	}
	else {
		return false;
	}
}

template <typename CharT>
static inline bool extract(const std::basic_string<CharT> & value, std::basic_string<CharT> & dst) {
	dst = value;
	return true;
}

template <typename CharT, typename T>
static inline bool get_value(const std::map<std::basic_string<CharT>, std::basic_string<CharT>>& sec, const std::basic_string<CharT>& key, T& dst) {
    const auto it = sec.find(key);
    if (it == sec.end()) return false;
    return extract(it->second, dst);
}

template <typename CharT, typename T>
static inline bool get_value(const std::map<std::basic_string<CharT>, std::basic_string<CharT>>& sec, const char* key, T& dst) {
    return get_value(sec, std::string(key), dst);
}

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


Config *newConfig(Coord* coord) {
    Config *config = new Config(coord);
    return config;
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

    this->Cluster.Heartbeat = 30;
    this->Cluster.Expire = 60;
    this->Cluster.RegisterInterval = 60;
    this->Cluster.ReloadInterval = 60;
    this->Cluster.ReconnectInterval = 30;
    this->Cluster.RecvBuffer = 4096;
}

int Config::gotConfigLineError(const std::string& configFilePath, int lineNum, char* data, size_t size) {
    std::string line(data, size);
    this->coord->coreLogError("parse error %s(%d): %s", configFilePath.c_str(), lineNum, line.c_str());
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
                std::string name = std::string(nameStart, nameEnd - nameStart);
                auto opt = this->coord->Environment->GetString(name.c_str());
                if (opt.has_value()) {
                    size_t length = opt.value().length();
                    if (j + length > bufferLen) return ErrorBufferNotEnough;
                    memcpy(buffer + j, opt.value().c_str(), length);
                    j = j + length;
                } else {
                    return ErrorInterpret;
                }
                braceStart = nullptr;
                nameStart = nullptr;
                nameEnd = nullptr;
                phase = 0;
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

int Config::scanConfigDirectiveLine(const std::string& configFilePath, char* data, size_t size) {
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
        std::string currentDir = coord::path::DirName(configFilePath);
        std::string fileName = std::string(argv[1], argLen[1]);
        std::string realPath = coord::path::PathJoin(currentDir, fileName);
        return this->scanConfigFile(realPath);
    }
    return ErrorInvalidArg;
}

int Config::scanConfigLine(const std::string& configFilePath, char* data, size_t size) {
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
    return this->scanConfigDirectiveLine(configFilePath, data, size);
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


int Config::scanConfigMultiLine(const std::string& configFilePath, char* data, size_t size) {
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
                int err = this->scanConfigLine(configFilePath, lineStart, data + i - lineStart);
                if (err) {
                    this->gotConfigLineError(configFilePath, lineNum, lineStart, data + i - lineStart);
                    return err;
                }
                lineNum = lineNum + 1;
                lineStart = nullptr;
                phase = 0;
            } 
        }
    }
    if (lineStart) {
        int err = this->scanConfigLine(configFilePath, lineStart, data + i - lineStart);
        if (err) {
            this->gotConfigLineError(configFilePath, lineNum, lineStart, data + i - lineStart);
            return err;
        }
        return 0;
    }
    return 0;
}

int Config::scanConfigFile(const std::string& configFilePath) {
    FILE* f = fopen(configFilePath.c_str(), "r");
    if (nullptr == f) {
        this->coord->coreLogError("no such file or directory: %s", configFilePath.c_str());
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
    return this->scanConfigMultiLine(configFilePath, lines, read);
}

void Config::DebugString(){
    for (auto const & it : this->Sections) {
        this->coord->LogInfo("[%s] [%s]", TAG, it.first.c_str());
        for (auto const & it1 : it.second) {
            this->coord->LogInfo("[%s] %-18s = %s", TAG, it1.first.c_str(), it1.second.c_str());
        }
    }
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Env", this->Basic.Env.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Name", this->Basic.Name.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Main", this->Basic.Main.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Scene", this->Basic.Scene.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Registery", this->Basic.Registery.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Package", this->Basic.Package.c_str());
    this->coord->LogInfo("[%s] %-15s: %ld", TAG, "GC", this->Basic.GC);
    this->coord->LogInfo("[%s] %-15s: %ld", TAG, "Update", this->Basic.Update);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Worker", this->Basic.Worker.c_str());
    this->coord->LogInfo("[%s] %-15s: %ld", TAG, "WorkerNum", this->Basic.WorkerNum);
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Proto", this->Basic.Proto.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Pid", this->Basic.Pid.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "Version", this->Basic.Version.c_str());
    this->coord->LogInfo("[%s] %-15s: %s", TAG, "ShortVersion", this->Basic.ShortVersion.c_str());
}

int Config::parse(const char* configFilePath) {
    std::string realPath;
    int err = coord::path::RealPath(configFilePath, realPath);
    if (err) {
        this->coord->coreLogError("%s: %s", uv_strerror(err), configFilePath);
        return err;
    }
    err = this->scanConfigFile(realPath);
    if (err) {
        return err;
    }
    get_value(this->Sections["DEFAULT"], "env", this->Basic.Env);
    get_value(this->Sections["DEFAULT"], "registery", this->Basic.Registery);
    get_value(this->Sections["DEFAULT"], "main", this->Basic.Main);
    get_value(this->Sections["DEFAULT"], "scene", this->Basic.Scene);
    get_value(this->Sections["DEFAULT"], "package", this->Basic.Package);
    get_value(this->Sections["DEFAULT"], "gc", this->Basic.GC);
    get_value(this->Sections["DEFAULT"], "update", this->Basic.Update);
    get_value(this->Sections["DEFAULT"], "worker", this->Basic.Worker);
    get_value(this->Sections["DEFAULT"], "worker_num", this->Basic.WorkerNum);
    get_value(this->Sections["DEFAULT"], "proto", this->Basic.Proto);
    get_value(this->Sections["DEFAULT"], "name", this->Basic.Name);
    get_value(this->Sections["DEFAULT"], "pid", this->Basic.Pid);
    get_value(this->Sections["DEFAULT"], "version", this->Basic.Version);

    {
        size_t begin = 0;
        while (this->Basic.Package.length() > 0) {
            size_t pos = this->Basic.Package.find(";", begin);
            if (pos == std::string::npos) {
                std::string path = this->Basic.Package.substr(begin);
                if (!coord::path::IsAbsolutePath(path.c_str())) {
                    path = coord::path::PathJoin(this->coord->Environment->ConfigFileDir, path);
                }
                this->coord->Environment->Package = path + ";" + this->coord->Environment->Package;
                break;
            } else {
                std::string path = this->Basic.Package.substr(begin, pos - begin);
                if (!coord::path::IsAbsolutePath(path.c_str())) {
                    path = coord::path::PathJoin(this->coord->Environment->ConfigFileDir, path);
                }
                this->coord->Environment->Package = path + ";" + this->coord->Environment->Package;
                begin = pos + 1;
            }
        }
    }
    int first = 0;
    auto it = std::find_if(this->Basic.Version.begin(), this->Basic.Version.end(), [&first](char c) {
        if (c == '.')first++;
        return first >= 2;
    });
    if (it == this->Basic.Version.end()) {
        return -1;
    }
    this->Basic.ShortVersion = this->Basic.Version.substr(0, it - this->Basic.Version.begin());


    if(this->Sections.find("WEB") != this->Sections.end()) {
        auto const it = this->Sections.find("WEB");
        get_value(it->second, "port", this->Web.Port);
        get_value(it->second, "host", this->Web.Host);
        get_value(it->second, "backlog", this->Web.Backlog);
        get_value(it->second, "recv_buffer", this->Web.RecvBuffer);
        get_value(it->second, "ssl_encrypt", this->Web.SSLEncrypt);
        get_value(it->second, "ssl_pem", this->Web.SSLPemFile);
        get_value(it->second, "ssl_key", this->Web.SSLKeyFile);
        get_value(it->second, "asset_dir", this->Web.AssetDir);
        get_value(it->second, "use_etag", this->Web.UseEtag);
    }

    if(this->Sections.find("Login") != this->Sections.end()) {
        auto const it = this->Sections.find("Login");
        get_value(it->second, "port", this->Login.Port);
        get_value(it->second, "host", this->Login.Host);
        get_value(it->second, "backlog", this->Login.Backlog);
        get_value(it->second, "recv_buffer", this->Login.RecvBufferSize);
        get_value(it->second, "ssl_encrypt", this->Login.SSLEncrypt);
        get_value(it->second, "ssl_pem", this->Login.SSLPemFile);
        get_value(it->second, "ssl_key", this->Login.SSLKeyFile);
        get_value(it->second, "cluster", this->Login.Cluster);
    } 

    if(this->Sections.find("GATE") != this->Sections.end()) {
        auto const it = this->Sections.find("GATE");
        get_value(it->second, "server_name", this->Gate.ServerName);
        get_value(it->second, "port", this->Gate.Port);
        get_value(it->second, "host", this->Gate.Host);
        get_value(it->second, "network", this->Gate.Network);
        get_value(it->second, "rsa_encrypt", this->Gate.RsaEncrypt);
        get_value(it->second, "rsa_keyfile", this->Gate.RsaKeyFile);
        get_value(it->second, "heartbeat", this->Gate.Heartbeat);
        get_value(it->second, "backlog", this->Gate.Backlog);
        get_value(it->second, "recv_buffer", this->Gate.RecvBuffer);
        get_value(it->second, "ssl_encrypt", this->Gate.SSLEncrypt);
        get_value(it->second, "ssl_pem", this->Gate.SSLPemFile);
        get_value(it->second, "ssl_key", this->Gate.SSLKeyFile);
        get_value(it->second, "max_user", this->Gate.MaxUser);
        get_value(it->second, "max_connection", this->Gate.MaxConnection);
        get_value(it->second, "cluster", this->Gate.Cluster);
        get_value(it->second, "register_expire", this->Gate.RegisterExpire);
        get_value(it->second, "register_interval", this->Gate.RegisterInterval);
    }
    if(this->Sections.find("CACHE") != this->Sections.end()) {
        auto const it = this->Sections.find("CACHE");
        get_value(it->second, "password", this->Cache.Password);
        get_value(it->second, "db", this->Cache.DB);
        get_value(it->second, "port", this->Cache.Port);
        get_value(it->second, "host", this->Cache.Host);
        get_value(it->second, "expire", this->Cache.ExpireTime);
    }

    if(this->Sections.find("CLUSTER") != this->Sections.end()) {
        auto const it = this->Sections.find("CLUSTER");
        get_value(it->second, "port", this->Cluster.Port);
        get_value(it->second, "host", this->Cluster.Host);
        get_value(it->second, "driver", this->Cluster.Driver);
        get_value(it->second, "heartbeat", this->Cluster.Heartbeat);
        get_value(it->second, "expire", this->Cluster.Expire);
        get_value(it->second, "reload_interval", this->Cluster.ReloadInterval);
        get_value(it->second, "reconnect_interval", this->Cluster.ReconnectInterval);
        get_value(it->second, "register_interval", this->Cluster.RegisterInterval);
        get_value(it->second, "name", this->Cluster.Name);
        get_value(it->second, "recv_buffer", this->Cluster.RecvBuffer);
    }

    if(this->Sections.find("MANAGED") != this->Sections.end()) {
        auto const it = this->Sections.find("MANAGED");
        get_value(it->second, "port", this->Managed.Port);
        get_value(it->second, "port", this->Managed.Port);
        get_value(it->second, "user", this->Managed.User);
        get_value(it->second, "password", this->Managed.Password);
    }
    
    //std::cout << "bitbucket.org compression level: " << this->Role << std::endl;
    return 0;
}

bool Config::SectionExist(const char* section) {
    auto it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return false;
    }
    return true;
}

int Config::SQLConfig(const char* section, sql::SQLConfig* config) {
    auto const it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "user", config->User)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "character_set", config->CharacterSet)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "driver", config->Driver)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

int Config::RedisConfig(const char* section, redis::RedisConfig* config) {
    auto const it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

int Config::LoggerConfig(const char* section, log4cc::LoggerConfig* config) {
    auto const it = this->Sections.find(section);
    if (it == this->Sections.end()){
        return ErrorConfigNotExist;
    }
    get_value(it->second, "file", config->File);
    get_value(it->second, "layout", config->Layout);
    get_value(it->second, "max-line", config->MaxLine);
    if(get_value(it->second, "max-byte", config->MaxByte)) {
    }

    std::string console;
    if(get_value(it->second, "console", console)) {
        if(console == "true") {
            config->Console = true;
        }
    }
    std::string priority;
    if(get_value(it->second, "priority", priority)) {
        config->Priority = log4cc::IntPriority(priority.c_str());
    }
    return 0;
}


}
