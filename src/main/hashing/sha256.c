#include "sha256.h"

const uint32_t K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint8_t shb_(uint32_t x, uint32_t n) {
    return ((x >> (n & 31)) & 0xff);
}

uint32_t shw_(uint32_t x, uint32_t n) {
    return ((x << (n & 31)) & 0xffffffff);
}

uint32_t r_(uint32_t x, uint8_t n) {
    return ((x >> n) | shw_(x, 32 - n));
}

uint32_t Ch_(uint32_t x, uint32_t y, uint32_t z) {
    return ((x & y) ^ ((~x) & z));
}

uint32_t Ma_(uint32_t x, uint32_t y, uint32_t z) {
    return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t S0_(uint32_t x) {
    return (r_(x, 2) ^ r_(x, 13) ^ r_(x, 22));
}

uint32_t S1_(uint32_t x) {
    return (r_(x, 6) ^ r_(x, 11) ^ r_(x, 25));
}

uint32_t G0_(uint32_t x) {
    return (r_(x, 7) ^ r_(x, 18) ^ (x >> 3));
}

uint32_t G1_(uint32_t x) {
    return (r_(x, 17) ^ r_(x, 19) ^ (x >> 10));
}

uint32_t word_(uint8_t* c) {
    return (shw_(c[0], 24) | shw_(c[1], 16) | shw_(c[2], 8) | (c[3]));
}

static void addBits(sha256Context* context, uint32_t n) {
    if (context->bits[0] > (0xffffffff - n)) {
        context->bits[1] = (context->bits[1] + 1) & 0xFFFFFFFF;
    }
    context->bits[0] = (context->bits[0] + n) & 0xFFFFFFFF;
}

static void hash_(sha256Context* context) {
    register uint32_t a, b, c, d, e, f, g, h;
    uint32_t t[2];

    a = context->hash[0];
    b = context->hash[1];
    c = context->hash[2];
    d = context->hash[3];
    e = context->hash[4];
    f = context->hash[5];
    g = context->hash[6];
    h = context->hash[7];

    for (uint32_t i = 0; i < 64; i++) {
        if (i < 16) {
            context->W[i] = word_(&context->buf[shw_(i, 2)]);
        }
        else {
            context->W[i] = G1_(context->W[i - 2]) + context->W[i - 7] +
                G0_(context->W[i - 15]) + context->W[i - 16];
        }

        t[0] = h + S1_(e) + Ch_(e, f, g) + K[i] + context->W[i];
        t[1] = S0_(a) + Ma_(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t[0];
        d = c;
        c = b;
        b = a;
        a = t[0] + t[1];
    }

    context->hash[0] += a;
    context->hash[1] += b;
    context->hash[2] += c;
    context->hash[3] += d;
    context->hash[4] += e;
    context->hash[5] += f;
    context->hash[6] += g;
    context->hash[7] += h;
}

void sha256Init(sha256Context* context) {
    if (context != NULL) {
        context->bits[0] = context->bits[1] = context->len = 0;
        context->hash[0] = 0x6a09e667;
        context->hash[1] = 0xbb67ae85;
        context->hash[2] = 0x3c6ef372;
        context->hash[3] = 0xa54ff53a;
        context->hash[4] = 0x510e527f;
        context->hash[5] = 0x9b05688c;
        context->hash[6] = 0x1f83d9ab;
        context->hash[7] = 0x5be0cd19;
    }
}

void sha256Hash(sha256Context* context, const void* data, size_t len)
{
    const uint8_t* bytes = (const uint8_t*)data;

    if ((context != NULL) && (bytes != NULL) && (context->len < sizeof(context->buf))) {
        for (size_t i = 0; i < len; i++) {
            context->buf[context->len++] = bytes[i];
            if (context->len == sizeof(context->buf)) {
                hash_(context);
                addBits(context, sizeof(context->buf) * 8);
                context->len = 0;
            }
        }
    }
}

void sha256Final(sha256Context* context, uint8_t* hash)
{
    register uint32_t i, j;

    if (context != NULL) {
        j = context->len % sizeof(context->buf);
        context->buf[j] = 0x80;
        for (i = j + 1; i < sizeof(context->buf); i++) {
            context->buf[i] = 0x00;
        }

        if (context->len > 55) {
            hash_(context);
            for (j = 0; j < sizeof(context->buf); j++) {
                context->buf[j] = 0x00;
            }
        }

        addBits(context, context->len * 8);
        context->buf[63] = shb_(context->bits[0], 0);
        context->buf[62] = shb_(context->bits[0], 8);
        context->buf[61] = shb_(context->bits[0], 16);
        context->buf[60] = shb_(context->bits[0], 24);
        context->buf[59] = shb_(context->bits[1], 0);
        context->buf[58] = shb_(context->bits[1], 8);
        context->buf[57] = shb_(context->bits[1], 16);
        context->buf[56] = shb_(context->bits[1], 24);
        hash_(context);

        if (hash != NULL) {
            for (i = 0, j = 24; i < 4; i++, j -= 8) {
                hash[i + 0] = shb_(context->hash[0], j);
                hash[i + 4] = shb_(context->hash[1], j);
                hash[i + 8] = shb_(context->hash[2], j);
                hash[i + 12] = shb_(context->hash[3], j);
                hash[i + 16] = shb_(context->hash[4], j);
                hash[i + 20] = shb_(context->hash[5], j);
                hash[i + 24] = shb_(context->hash[6], j);
                hash[i + 28] = shb_(context->hash[7], j);
            }
        }
    }
}

void sha256(const void* data, size_t dataLen, uint8_t* hash) {
    sha256Context context;

    sha256Init(&context);
    sha256Hash(&context, data, dataLen);
    sha256Final(&context, hash);
}