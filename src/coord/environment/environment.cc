#include "coord/environment/environment.h"
#include "coord/builtin/init.h"
#include "coord/coord.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <uv.h>
#include <ctype.h>
#include "coord/builtin/string.h"
#include "coord/builtin/error.h"

namespace coord {
static const char* TAG = "Environment";
static const char* env_file_name = ".env";

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

/*
Environment* newEnvironment(Coord* coord) {
    Environment* self = new Environment(coord);
    return self;
}
*/

int Environment::scanEnvDirectiveLine(const std::string& envFilePath, char* data, size_t size) {
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
        std::string currentDir = coord::path::DirName(envFilePath);
        std::string fileName = std::string(argv[1], argLen[1]);
        std::string envFilePath = coord::path::PathJoin(currentDir, fileName);
        return this->scanEnvFile(envFilePath);
    }
    return ErrorInvalidArg;
}

int Environment::scanEnvLine(const std::string& envFilePath, char* data, size_t size) {
    size_t i = 0;
    int codePointLength = 1;
    for (; i < size; i += codePointLength) {
        char c = data[i];
        codePointLength = UTF8_CODE_POINT_LENGTH(c);
        if (IS_ASCII('#', c, codePointLength)) {
            return 0;
        } else if (IS_ASCII('=', c, codePointLength)) {
            int err = this->scanEnvKey(data, i);
            if (err) return err;
            return this->scanEnvValue(data + i + 1, size - i - 1);
        }
    }
    return this->scanEnvDirectiveLine(envFilePath, data, size);
}

int Environment::gotEnvLineError(const std::string& envFilePath, int lineNum, char* data, size_t size) {
    std::string line(data, size);
    this->coord->CoreLogError("parse error %s(%d): %s", envFilePath.c_str(), lineNum, line);
    return 0;
}

static thread_local std::string temp_env_key;
int Environment::gotEnvKey(char* data, size_t size) {
    temp_env_key = std::string(data, size);
    //printf("key: %s\n", temp_env_key.c_str());
    return 0;
}
int Environment::gotEnvValue(char* data, size_t size) {
    std::string word = std::string(data, size);
    //printf("value: %s\n", word.c_str());
    this->Variables[temp_env_key] = word;
    return 0;
}

int Environment::scanEnvKey(char* data, size_t size) {
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
        return this->gotEnvKey(wordStart, wordEnd - wordStart);
    }
    return 1;
}

int Environment::scanEnvQuoteValue(char* data, size_t size) {
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
    return this->gotEnvValue(buffer, realSize);
}

int Environment::scanEnvValue(char* data, size_t size) {
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
                return this->scanEnvQuoteValue(data + i, size - i);
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
        return this->gotEnvValue(wordStart, wordEnd - wordStart);
    } else {
        return this->gotEnvValue(data, 0);
    }
}

int Environment::scanEnvMultiLine(const std::string& envFilePath, char* data, size_t size) {
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
                int err = this->scanEnvLine(envFilePath, lineStart, data + i - lineStart);
                if (err) {
                    this->gotEnvLineError(envFilePath, lineNum, lineStart, data + i - lineStart);
                    return err;
                }
                lineNum = lineNum + 1;
                lineStart = nullptr;
                phase = 0;
            } 
        }
    }
    if (lineStart) {
        int err = this->scanEnvLine(envFilePath, lineStart, data + i - lineStart);
        if (err) {
            this->gotEnvLineError(envFilePath, lineNum, lineStart, data + i - lineStart);
            return err;
        }
        return 0;
    }
    return 0;

}

int Environment::scanEnvFile(const std::string& envFilePath) {
    FILE* f = fopen(envFilePath.c_str(), "r");
    if (nullptr == f) {
        this->coord->CoreLogError("No such file or directory: %s", envFilePath.c_str());
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
    return this->scanEnvMultiLine(envFilePath, lines, read);
}

int Environment::main(const Argv& argv) {
    char buffer[PATH_MAX];
    size_t len = sizeof(buffer);

    this->Pid = uv_os_getpid();
    if (argv.Name.length() > 0) {
        this->Name = argv.Name;
    } else {
        uv_pid_t pid = this->Pid;
        this->Name = std::to_string(pid);
    }

    len = sizeof(buffer);
    // 配置文件绝对路径
    uv_fs_t req;
    int err = uv_fs_realpath(&this->coord->loop, &req, argv.ConfigPath.c_str(), nullptr);
    if (err) {
        this->coord->CoreLogError("%s %s", uv_strerror(err), argv.ConfigPath.c_str());
        return err;
    }
    this->ConfigPath = (char*)req.ptr;

    // 执行文件所在目录
    len = sizeof(buffer);
    err = uv_exepath(buffer, &len);
    if (err) {
        return err;
    }
    this->ExecPath = buffer;

    // 工作目录
    len = sizeof(buffer);
    err = uv_cwd(buffer, &len);
    if (err) {
        return err;
    }
    this->WorkingDir = buffer;

    // 用户home目录
    len = sizeof(buffer);
    err = uv_os_homedir(buffer, &len);
    if (err) {
        return err;
    }
    this->HomeDir = buffer;

    // coord 目录
    err = this->searchCoordDir(this->CoordDir);
    if (err) {
        return err;
    }
    // 配置文件所在的目录
    this->ConfigDir = coord::path::DirName(this->ConfigPath);
    // 工作目录
    this->WorkingDir = this->ConfigDir;

    // 执行文件所在的目录
    this->ExecDir = coord::path::DirName(this->ExecPath);
    // 工程目录
    this->ProjectDir = coord::path::DirName(this->ExecDir);
    
    this->ProcDir = coord::path::PathJoin(this->CoordDir, "proc");
    this->RunDir = coord::path::PathJoin(this->ProcDir, this->Name);
    this->PidPath = coord::path::PathJoin(this->RunDir, "pid");
    this->ManagedSockPath = coord::path::PathJoin(this->RunDir, "managed.sock");
    this->Package = this->CoordDir + "/package";                        // 引擎目录
    this->Package = this->WorkingDir + "/package;" + this->Package;     // 工作目录
    this->Package = this->ConfigDir + "/package;" + this->Package;  // 配置文件目录
    this->Package = this->ConfigDir + ";" + this->Package;          // 配置文件目录

    this->Variables["name"] = this->Name;
    this->Variables["version"] = this->Version;
    this->Variables["config-dir"] = this->ConfigDir;
    this->Variables["config-path"] = this->ConfigPath;
    this->Variables["working-dir"] = this->WorkingDir;
    this->Variables["exec-path"] = this->ExecPath;
    this->Variables["exec-dir"] = this->ExecDir;
    this->Variables["coord-dir"] = this->CoordDir;
    this->Variables["project-dir"] = this->ProjectDir;
    this->Variables["home-dir"] = this->HomeDir;
    this->Variables["proc-dir"] = this->ProcDir;
    this->Variables["run-dir"] = this->RunDir;
    this->Variables["pid-path"] = this->PidPath;
    this->Variables["package"] = this->Package;
    this->Variables["managed-sock-path"] = this->ManagedSockPath;

    std::string envFilePath = coord::path::PathJoin(this->ConfigDir, env_file_name);
    if (!coord::path::Exists(envFilePath)) {
        return 0;
    }
    err = this->scanEnvFile(envFilePath);
    if (err) {
        return err;
    }
    /* 
    this->coord->LogInfo(R"(
/---------------------------/
/                           /       
/                           /       
/       coord               /       
/                           /       
/                           /       
/-------------------------- /)");
*/

    return 0;
}

void Environment::DebugString() {
    this->coord->LogInfo("========================= Environment =========================");
    for (auto const & it : this->Variables) {
        this->coord->LogInfo("[%s] %-18s = %s", TAG, it.first.c_str(), it.second.c_str());
    }
}

int Environment::searchCoordDir(std::string& coordDir) {
    char buffer[PATH_MAX];
    size_t len = sizeof(buffer);
    int err = uv_os_getenv("COORD_ROOT", buffer, &len);
    if(err == 0) {
        coordDir.assign(buffer, len);
        err = coord::path::RealPath(coordDir, coordDir);
        if (err) {
            return err;
        }
        return 0;
    }
    std::vector<std::string> searchDirArr;
    searchDirArr.push_back("/usr");
    searchDirArr.push_back("/usr/local");
    searchDirArr.push_back(this->HomeDir);
    for (auto searchDir : searchDirArr) {
        auto dir = coord::path::PathJoin(searchDir, "coord");
        if (coord::path::Exists(dir)) {
            coordDir = dir;
            return 0;
        }
    }
    return -1;
}

int Environment::Get(lua_State* L) {
    const char* name = lua_tostring(L, 2);
    auto it = this->Variables.find(name);
    if (it == this->Variables.end()) {
        return 0;
    }
    lua_pushlstring(L, it->second.c_str(), it->second.length());
    return 1;
}

}
