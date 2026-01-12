#include "posixPortHmacmd5.h"
#include <string.h>
#include <ctype.h>
#include <stddef.h>

#define KEY_IOPAD_SIZE 64
#define MD5_DIGEST_SIZE 16
////////////////////////////////////////

void hdinitmd5(void){

}

typedef struct {
    uint32_t      total[2];   /*!< number of bytes processed  */
    uint32_t      state[4];   /*!< intermediate digest state  */
    unsigned char buffer[64]; /*!< data block being processed */
} hdmd5Context_t;

/* Implementation that should never be optimized out by the compiler */
static void hdmd5Zeroize(void *v, size_t n) {
    volatile unsigned char *p = v;
    while (n--)
        *p++ = 0;
}

/*
 * 32-bit integer manipulation macros (little endian)
 */
#ifndef HD_MD5_GET_UINT32_LE
#define HD_MD5_GET_UINT32_LE(n, b, i)                                                                                                                                                                                                                                                                                          \
    { (n) = ((uint32_t)(b)[(i)]) | ((uint32_t)(b)[(i) + 1] << 8) | ((uint32_t)(b)[(i) + 2] << 16) | ((uint32_t)(b)[(i) + 3] << 24); }
#endif

#ifndef HD_MD5_PUT_UINT32_LE
#define HD_MD5_PUT_UINT32_LE(n, b, i)                                                                                                                                                                                                                                                                                          \
    {                                                                                                                                                                                                                                                                                                                          \
        (b)[(i)] = (unsigned char)(((n)) & 0xFF);                                                                                                                                                                                                                                                                              \
        (b)[(i) + 1] = (unsigned char)(((n) >> 8) & 0xFF);                                                                                                                                                                                                                                                                     \
        (b)[(i) + 2] = (unsigned char)(((n) >> 16) & 0xFF);                                                                                                                                                                                                                                                                    \
        (b)[(i) + 3] = (unsigned char)(((n) >> 24) & 0xFF);                                                                                                                                                                                                                                                                    \
    }
#endif

static void hdmd5Init(hdmd5Context_t *ctx) {
    memset(ctx, 0, sizeof(hdmd5Context_t));
}

static void hdmd5Free(hdmd5Context_t *ctx) {
    if (ctx == NULL)
        return;

    hdmd5Zeroize(ctx, sizeof(hdmd5Context_t));
}

/*
 * MD5 context setup
 */
static void hdmd5Starts(hdmd5Context_t *ctx) {
    ctx->total[0] = 0;
    ctx->total[1] = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
}

static void hdmd5Process(hdmd5Context_t *ctx, const unsigned char data[64]) {
    uint32_t X[16], A, B, C, D;

    HD_MD5_GET_UINT32_LE(X[0], data, 0);
    HD_MD5_GET_UINT32_LE(X[1], data, 4);
    HD_MD5_GET_UINT32_LE(X[2], data, 8);
    HD_MD5_GET_UINT32_LE(X[3], data, 12);
    HD_MD5_GET_UINT32_LE(X[4], data, 16);
    HD_MD5_GET_UINT32_LE(X[5], data, 20);
    HD_MD5_GET_UINT32_LE(X[6], data, 24);
    HD_MD5_GET_UINT32_LE(X[7], data, 28);
    HD_MD5_GET_UINT32_LE(X[8], data, 32);
    HD_MD5_GET_UINT32_LE(X[9], data, 36);
    HD_MD5_GET_UINT32_LE(X[10], data, 40);
    HD_MD5_GET_UINT32_LE(X[11], data, 44);
    HD_MD5_GET_UINT32_LE(X[12], data, 48);
    HD_MD5_GET_UINT32_LE(X[13], data, 52);
    HD_MD5_GET_UINT32_LE(X[14], data, 56);
    HD_MD5_GET_UINT32_LE(X[15], data, 60);

#define S(x, n) ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n)))

#define P(a, b, c, d, k, s, t)                                                                                                                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                                                                                                                          \
        a += F(b, c, d) + X[k] + t;                                                                                                                                                                                                                                                                                            \
        a = S(a, s) + b;                                                                                                                                                                                                                                                                                                       \
    }

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];

#define F(x, y, z) (z ^ (x & (y ^ z)))

    P(A, B, C, D, 0, 7, 0xD76AA478);
    P(D, A, B, C, 1, 12, 0xE8C7B756);
    P(C, D, A, B, 2, 17, 0x242070DB);
    P(B, C, D, A, 3, 22, 0xC1BDCEEE);
    P(A, B, C, D, 4, 7, 0xF57C0FAF);
    P(D, A, B, C, 5, 12, 0x4787C62A);
    P(C, D, A, B, 6, 17, 0xA8304613);
    P(B, C, D, A, 7, 22, 0xFD469501);
    P(A, B, C, D, 8, 7, 0x698098D8);
    P(D, A, B, C, 9, 12, 0x8B44F7AF);
    P(C, D, A, B, 10, 17, 0xFFFF5BB1);
    P(B, C, D, A, 11, 22, 0x895CD7BE);
    P(A, B, C, D, 12, 7, 0x6B901122);
    P(D, A, B, C, 13, 12, 0xFD987193);
    P(C, D, A, B, 14, 17, 0xA679438E);
    P(B, C, D, A, 15, 22, 0x49B40821);

#undef F

#define F(x, y, z) (y ^ (z & (x ^ y)))

    P(A, B, C, D, 1, 5, 0xF61E2562);
    P(D, A, B, C, 6, 9, 0xC040B340);
    P(C, D, A, B, 11, 14, 0x265E5A51);
    P(B, C, D, A, 0, 20, 0xE9B6C7AA);
    P(A, B, C, D, 5, 5, 0xD62F105D);
    P(D, A, B, C, 10, 9, 0x02441453);
    P(C, D, A, B, 15, 14, 0xD8A1E681);
    P(B, C, D, A, 4, 20, 0xE7D3FBC8);
    P(A, B, C, D, 9, 5, 0x21E1CDE6);
    P(D, A, B, C, 14, 9, 0xC33707D6);
    P(C, D, A, B, 3, 14, 0xF4D50D87);
    P(B, C, D, A, 8, 20, 0x455A14ED);
    P(A, B, C, D, 13, 5, 0xA9E3E905);
    P(D, A, B, C, 2, 9, 0xFCEFA3F8);
    P(C, D, A, B, 7, 14, 0x676F02D9);
    P(B, C, D, A, 12, 20, 0x8D2A4C8A);

#undef F

#define F(x, y, z) (x ^ y ^ z)

    P(A, B, C, D, 5, 4, 0xFFFA3942);
    P(D, A, B, C, 8, 11, 0x8771F681);
    P(C, D, A, B, 11, 16, 0x6D9D6122);
    P(B, C, D, A, 14, 23, 0xFDE5380C);
    P(A, B, C, D, 1, 4, 0xA4BEEA44);
    P(D, A, B, C, 4, 11, 0x4BDECFA9);
    P(C, D, A, B, 7, 16, 0xF6BB4B60);
    P(B, C, D, A, 10, 23, 0xBEBFBC70);
    P(A, B, C, D, 13, 4, 0x289B7EC6);
    P(D, A, B, C, 0, 11, 0xEAA127FA);
    P(C, D, A, B, 3, 16, 0xD4EF3085);
    P(B, C, D, A, 6, 23, 0x04881D05);
    P(A, B, C, D, 9, 4, 0xD9D4D039);
    P(D, A, B, C, 12, 11, 0xE6DB99E5);
    P(C, D, A, B, 15, 16, 0x1FA27CF8);
    P(B, C, D, A, 2, 23, 0xC4AC5665);

#undef F

#define F(x, y, z) (y ^ (x | ~z))

    P(A, B, C, D, 0, 6, 0xF4292244);
    P(D, A, B, C, 7, 10, 0x432AFF97);
    P(C, D, A, B, 14, 15, 0xAB9423A7);
    P(B, C, D, A, 5, 21, 0xFC93A039);
    P(A, B, C, D, 12, 6, 0x655B59C3);
    P(D, A, B, C, 3, 10, 0x8F0CCC92);
    P(C, D, A, B, 10, 15, 0xFFEFF47D);
    P(B, C, D, A, 1, 21, 0x85845DD1);
    P(A, B, C, D, 8, 6, 0x6FA87E4F);
    P(D, A, B, C, 15, 10, 0xFE2CE6E0);
    P(C, D, A, B, 6, 15, 0xA3014314);
    P(B, C, D, A, 13, 21, 0x4E0811A1);
    P(A, B, C, D, 4, 6, 0xF7537E82);
    P(D, A, B, C, 11, 10, 0xBD3AF235);
    P(C, D, A, B, 2, 15, 0x2AD7D2BB);
    P(B, C, D, A, 9, 21, 0xEB86D391);

#undef F

    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
}

/*
 * MD5 process buffer
 */
static void hdmd5Update(hdmd5Context_t *ctx, const unsigned char *input, size_t ilen) {
    size_t   fill;
    uint32_t left;

    if (ilen == 0)
        return;

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += (uint32_t)ilen;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < (uint32_t)ilen)
        ctx->total[1]++;

    if (left && ilen >= fill) {
        memcpy((void *)(ctx->buffer + left), input, fill);
        hdmd5Process(ctx, ctx->buffer);
        input += fill;
        ilen -= fill;
        left = 0;
    }

    while (ilen >= 64) {
        hdmd5Process(ctx, input);
        input += 64;
        ilen -= 64;
    }

    if (ilen > 0) {
        memcpy((void *)(ctx->buffer + left), input, ilen);
    }
}

static const unsigned char _hdmd5Padding[64] = {0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
 * MD5 final digest
 */
static void hdmd5Finish(hdmd5Context_t *ctx, unsigned char output[16]) {
    uint32_t      last, padn;
    uint32_t      high, low;
    unsigned char msglen[8];

    high = (ctx->total[0] >> 29) | (ctx->total[1] << 3);
    low = (ctx->total[0] << 3);

    HD_MD5_PUT_UINT32_LE(low, msglen, 0);
    HD_MD5_PUT_UINT32_LE(high, msglen, 4);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    hdmd5Update(ctx, _hdmd5Padding, padn);
    hdmd5Update(ctx, msglen, 8);

    HD_MD5_PUT_UINT32_LE(ctx->state[0], output, 0);
    HD_MD5_PUT_UINT32_LE(ctx->state[1], output, 4);
    HD_MD5_PUT_UINT32_LE(ctx->state[2], output, 8);
    HD_MD5_PUT_UINT32_LE(ctx->state[3], output, 12);
}

/*
 * output = MD5( input buffer )
 */
void hdmd5(const void* data, uint32_t datLen, uint8_t output[16]) {
    hdmd5Context_t ctx;
    const uint8_t* input = (const uint8_t*)data;

    hdmd5Init(&ctx);
    hdmd5Starts(&ctx);
    hdmd5Update(&ctx, input, datLen);
    hdmd5Finish(&ctx, output);
    hdmd5Free(&ctx);
}

static uint8_t hdb2hex(uint8_t hb) {
    hb = hb & 0xF;
    return (uint8_t)(hb < 10 ? '0' + hb : hb - 10 + 'A');
}


void hdmd5Hex(const void* data, uint32_t datLen, uint8_t result[32]) {
    uint8_t out[16];
    const uint8_t* input = (const uint8_t*)data;

    memset(out, 0, 16);
    hdmd5(input, datLen, out);

    for (int i = 0; i < 16; ++i) {
        result[i * 2] = hdb2hex(out[i] >> 4);
        result[i * 2 + 1] = hdb2hex(out[i]);
    }
}

void hdhmacmd5(const void* data, uint32_t dataLen, const void* key, uint32_t keyLen, uint8_t out[16]) {
    hdmd5Context_t context;
    unsigned char  k_ipad[KEY_IOPAD_SIZE]; /* inner padding - key XORd with ipad  */
    unsigned char  k_opad[KEY_IOPAD_SIZE]; /* outer padding - key XORd with opad */

    const uint8_t* keyData = (const uint8_t*)key;
    const uint8_t* inputData = (const uint8_t*)data;

    /* start out by storing key in pads */
    memset(k_ipad, 0, sizeof(k_ipad));
    memset(k_opad, 0, sizeof(k_opad));

    if (keyLen > sizeof(k_opad)) {
        // When exceeding 64 bytes, take MD5
        hdmd5(keyData, keyLen, out);
        keyData = out;
        keyLen = 16;
    }

    memcpy(k_ipad, keyData, keyLen);
    memcpy(k_opad, keyData, keyLen);

    /* XOR key with ipad and opad values */
    for (int i = 0; i < KEY_IOPAD_SIZE; i++) {
        k_ipad[i] ^= 0x36;
        k_opad[i] ^= 0x5c;
    }

    /* perform inner MD5 */
    hdmd5Init(&context);                                   /* init context for 1st pass */
    hdmd5Starts(&context);                                 /* setup context for 1st pass */
    hdmd5Update(&context, k_ipad, KEY_IOPAD_SIZE);         /* start with inner pad */
    hdmd5Update(&context, inputData, dataLen);             /* then text of datagram */
    hdmd5Finish(&context, out);                            /* finish up 1st pass */

    /* perform outer MD5 */
    hdmd5Init(&context);                           /* init context for 2nd pass */
    hdmd5Starts(&context);                         /* setup context for 2nd pass */
    hdmd5Update(&context, k_opad, KEY_IOPAD_SIZE); /* start with outer pad */
    hdmd5Update(&context, out, 16);                /* then results of 1st hash */
    hdmd5Finish(&context, out);                    /* finish up 2nd pass */
}

void hdhmacmd5Hex(const void* data, uint32_t dataLen, const void* key, uint32_t keyLen, uint8_t result[32]) {
    uint8_t out[16];
    memset(out, 0, 16);

    hdhmacmd5(data, dataLen, key, keyLen, out);

    for (int i = 0; i < 16; ++i) {
        result[i * 2] = hdb2hex(out[i] >> 4);
        result[i * 2 + 1] = hdb2hex(out[i]);
    }
}
