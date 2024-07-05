/*
   Source:
   https://homes.esat.kuleuven.be/~bosselae/ripemd160/pdf/AB-9601/AB-9601.pdf
*/

#include <stdint.h>
#include <string.h>

#include "ripemd160.h"

void ripemd160_init(RIPEMD160_CTX *ctx)
{
    memset(ctx->state, 0, sizeof(ctx->state));

    /* initialize state */
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xc3d2e1f0;

    memset(ctx->buffer, 0, sizeof(ctx->buffer));
    ctx->total[0] = ctx->total[1] = 0;
}

/* RIPEMD-160 Transformation */
void ripemd160_process(RIPEMD160_CTX *ctx, const uint8_t data[BLOCK_SIZE])
{
    uint32_t A, B, C, D, E, Ap, Bp, Cp, Dp, Ep;
    uint32_t X[16];

    /* Load words from the block into X */
    for (int i = 0; i < 16; i++) {
        X[i] = (uint32_t)data[i*4] |
               ((uint32_t)data[i*4 + 1] << 8) |
               ((uint32_t)data[i*4 + 2] << 16) |
               ((uint32_t)data[i*4 + 3] << 24);
    }

    A = Ap = ctx->state[0];
    B = Bp = ctx->state[1];
    C = Cp = ctx->state[2];
    D = Dp = ctx->state[3];
    E = Ep = ctx->state[4];

    /* Round 1 */
    #define S1(a, b, c, d, e, i) \
        a = ROL(11, (a + F1(b, c, d) + X[i])); \
        a += e; \
        c = ROL(10, c);

    /* Round 2 */
    #define S2(a, b, c, d, e, i) \
        a = ROL(11, (a + F2(b, c, d) + X[i] + 0x5a827999)); \
        a += e; \
        c = ROL(10, c);

    /* Round 3 */
    #define S3(a, b, c, d, e, i) \
        a = ROL(11, (a + F3(b, c, d) + X[i] + 0x6ed9eba1)); \
        a += e; \
        c = ROL(10, c);

    /* Round 4 */
    #define S4(a, b, c, d, e, i) \
        a = ROL(11, (a + F4(b, c, d) + X[i] + 0x8f1bbcdc)); \
        a += e; \
        c = ROL(10, c);

    /* Round 5 */
    #define S5(a, b, c, d, e, i) \
        a = ROL(11, (a + F5(b, c, d) + X[i] + 0xa953fd4e)); \
        a += e; \
        c = ROL(10, c);

    /* Round 1 */
    S1(A, B, C, D, E, 0);
    S1(E, A, B, C, D, 1);
    S1(D, E, A, B, C, 2);
    S1(C, D, E, A, B, 3);
    S1(B, C, D, E, A, 4);
    S1(A, B, C, D, E, 5);
    S1(E, A, B, C, D, 6);
    S1(D, E, A, B, C, 7);
    S1(C, D, E, A, B, 8);
    S1(B, C, D, E, A, 9);
    S1(A, B, C, D, E, 10);
    S1(E, A, B, C, D, 11);
    S1(D, E, A, B, C, 12);
    S1(C, D, E, A, B, 13);
    S1(B, C, D, E, A, 14);
    S1(A, B, C, D, E, 15);

    /* Round 2 */
    S2(E, A, B, C, D, 0);
    S2(D, E, A, B, C, 4);
    S2(C, D, E, A, B, 8);
    S2(B, C, D, E, A, 12);
    S2(A, B, C, D, E, 1);
    S2(E, A, B, C, D, 5);
    S2(D, E, A, B, C, 9);
    S2(C, D, E, A, B, 13);
    S2(B, C, D, E, A, 2);
    S2(A, B, C, D, E, 6);
    S2(E, A, B, C, D, 10);
    S2(D, E, A, B, C, 14);
    S2(C, D, E, A, B, 3);
    S2(B, C, D, E, A, 7);
    S2(A, B, C, D, E, 11);
    S2(E, A, B, C, D, 15);

    /* Round 3 */
    S3(D, E, A, B, C, 0);
    S3(C, D, E, A, B, 8);
    S3(B, C, D, E, A, 4);
    S3(A, B, C, D, E, 12);
    S3(E, A, B, C, D, 2);
    S3(D, E, A, B, C, 10);
    S3(C, D, E, A, B, 6);
    S3(B, C, D, E, A, 14);
    S3(A, B, C, D, E, 1);
    S3(E, A, B, C, D, 9);
    S3(D, E, A, B, C, 5);
    S3(C, D, E, A, B, 13);
    S3(B, C, D, E, A, 3);
    S3(A, B, C, D, E, 11);
    S3(E, A, B, C, D, 7);
    S3(D, E, A, B, C, 15);

    /* Round 4 */
    S4(C, D, E, A, B, 0);
    S4(B, C, D, E, A, 8);
    S4(A, B, C, D, E, 4);
    S4(E, A, B, C, D, 12);
    S4(D, E, A, B, C, 2);
    S4(C, D, E, A, B, 10);
    S4(B, C, D, E, A, 6);
    S4(A, B, C, D, E, 14);
    S4(E, A, B, C, D, 1);
    S4(D, E, A, B, C, 9);
    S4(C, D, E, A, B, 5);
    S4(B, C, D, E, A, 13);
    S4(A, B, C, D, E, 3);
    S4(E, A, B, C, D, 11);
    S4(D, E, A, B, C, 7);
    S4(C, D, E, A, B, 15);

    /* Round 5 */
    S5(B, C, D, E, A, 0);
    S5(A, B, C, D, E, 8);
    S5(E, A, B, C, D, 4);
    S5(D, E, A, B, C, 12);
    S5(C, D, E, A, B, 2);
    S5(B, C, D, E, A, 10);
    S5(A, B, C, D, E, 6);
    S5(E, A, B, C, D, 14);
    S5(D, E, A, B, C, 1);
    S5(C, D, E, A, B, 9);
    S5(B, C, D, E, A, 5);
    S5(A, B, C, D, E, 13);
    S5(E, A, B, C, D, 3);
    S5(D, E, A, B, C, 11);
    S5(C, D, E, A, B, 7);
    S5(B, C, D, E, A, 15);

    /* Update state */
    ctx->state[0] += Ap;
    ctx->state[1] += Bp;
    ctx->state[2] += Cp;
    ctx->state[3] += Dp;
    ctx->state[4] += Ep;
}

/* RIPEMD-160 Update */
void ripemd160_update(RIPEMD160_CTX *ctx, const uint8_t *data, uint32_t len)
{
    uint32_t left = ctx->total[0] & 0x3F;
    uint32_t fill = BLOCK_SIZE - left;

    ctx->total[0] += len;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < len)
        ctx->total[1]++;

    if (left && len >= fill) {
        memcpy((void *)(ctx->buffer + left), data, fill);
        ripemd160_process(ctx, ctx->buffer);
        data += fill;
        len -= fill;
        left = 0;
    }

    while (len >= BLOCK_SIZE) {
        ripemd160_process(ctx, data);
        data += BLOCK_SIZE;
        len -= BLOCK_SIZE;
    }

    if (len > 0) {
        memcpy((void *)(ctx->buffer + left), data, len);
    }
}

/* RIPEMD-160 Final */
void ripemd160_final(RIPEMD160_CTX *ctx, uint8_t *digest)
{
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t msglen[8];

    high = (ctx->total[0] >> 29) | (ctx->total[1] << 3);
    low = (ctx->total[0] << 3);

    PUT_UINT32_LE(low, msglen, 0);
    PUT_UINT32_LE(high, msglen, 4);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    ripemd160_update(ctx, (uint8_t *)"\x80", 1);

    while (padn > 0) {
        ripemd160_update(ctx, (uint8_t *)"\x00", 1);
        padn--;
    }

    ripemd160_update(ctx, msglen, 8);

    PUT_UINT32_LE(ctx->state[0], digest, 0);
    PUT_UINT32_LE(ctx->state[1], digest, 4);
    PUT_UINT32_LE(ctx->state[2], digest, 8);
    PUT_UINT32_LE(ctx->state[3], digest, 12);
    PUT_UINT32_LE(ctx->state[4], digest, 16);
}

/* RIPEMD-160 hash function */
void ripemd160(const uint8_t *msg, uint32_t len, uint8_t *digest)
{
    RIPEMD160_CTX ctx;

    ripemd160_init(&ctx);
    ripemd160_update(&ctx, msg, len);
    ripemd160_final(&ctx, digest);
}
