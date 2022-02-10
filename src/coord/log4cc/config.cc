#include "coord/log4cc/config.h"

namespace coord {
namespace log4cc {

LoggerConfig::LoggerConfig() {
    this->Name = "coord";
    this->Layout = "basic";
    this->Priority = ALL;
    this->Console = false;
    this->MaxByte = 2097152; //2M
    this->MaxLine = 0; 
}

}
}
