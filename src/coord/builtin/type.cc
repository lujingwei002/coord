#include "coord/builtin/type.h"
#include <cstring>

namespace coord {

Type::Type(const char* name) {
    strcpy(this->name, name);
}

}