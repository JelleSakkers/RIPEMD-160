#ifndef RIPEMD160_H
#define RIPEMD160_H

#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 64
#define RIPEMD160_DIGEST_SIZE 20

/* boolean functions */
#define F1(x, y, z) ((x) ^ (y) ^ (z))
#define F2(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define F3(x, y, z) (((x) | ~(y)) ^ (z))
#define F4(x, y, z) (((x) & (z)) | ((y) & ~(z)))
#define F5(x, y, z) ((x) ^ ((y) | ~(z)))

/* cyclic left-shift the 32-bit word n left by s bits */
#define ROL(s, n) (((n) << (s)) | ((n) >> (32-(s))))

/* store a 32-bit unsigned integer in little-endian byte order */
#define PUT_UINT32_LE(n, dst, i)                    \
    do {                                            \
        (dst)[(i) + 0] = (uint8_t)((n)      );      \
        (dst)[(i) + 1] = (uint8_t)((n) >>  8);      \
        (dst)[(i) + 2] = (uint8_t)((n) >> 16);      \
        (dst)[(i) + 3] = (uint8_t)((n) >> 24);      \
    } while (0)

typedef struct _RIPEMD160_CTX {
    uint32_t total[2];
    uint32_t state[5];
    uint8_t buffer[BLOCK_SIZE];
} RIPEMD160_CTX;

void ripemd160_init(RIPEMD160_CTX *ctx);
void ripemd160_process(RIPEMD160_CTX *ctx, const uint8_t data[BLOCK_SIZE]);
void ripemd160_update(RIPEMD160_CTX *ctx, const uint8_t *data, uint32_t len);
void ripemd160_final(RIPEMD160_CTX *ctx, uint8_t *digest);
void ripemd160(const uint8_t *msg, uint32_t len, uint8_t *digest);

#endif /* RIPEMD160_H */

