#ifndef SHA256_H_
#define SHA256_H_

#include <stddef.h>
#include <stdint.h>

#define SHA256_SIZE_BYTES   (32)

typedef struct {
    uint8_t  buf[64];
    uint32_t hash[8];
    uint32_t bits[2];
    uint32_t len;
    uint32_t W[64];
} sha256Context;

void sha256Init(sha256Context* context);
void sha256Hash(sha256Context* context, const void* data, size_t dataLen);
void sha256Final(sha256Context* context, uint8_t* hash);

void sha256(const void* data, size_t dataLen, uint8_t* hash);

#endif