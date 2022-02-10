#pragma once 

#include <cstdint>

namespace coord {
namespace encrypt {
namespace sha1 {

typedef struct{
    uint32_t        state[5];
    uint32_t        count[2];
    unsigned char   buffer[64];
} Context;

void Transform(uint32_t state[5], const unsigned char buffer[64]);
void Init(Context* context);
void Update(Context* context, const unsigned char* data, uint32_t len);
void Final(unsigned char digest[20], Context* context);
void Encode(char* out, const char* input, int len);

}
}
}