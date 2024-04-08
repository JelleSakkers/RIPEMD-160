/*
 *  - RIPEMD-160-
 * 
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 64
#define RIPEMD160_DIGEST_SIZE 20

/* boolean functions  */
 #define F1(x, y, z) ((x) ^ (y) ^ (z))
 #define F2(x, y, z) (((x) & (y)) | (~(x) & (z)))
 #define F3(x, y, z) (((x) | ~(y)) ^ (z))
 #define F4(x, y, z) (((x) & (z)) | ((y) & ~(z)))
 #define F5(x, y, z) ((x) ^ ((y) | ~(z)))

/* cyclic left-shift the 32-bit word n left by s bits */
#define ROL(s, n) (((n) << (s)) | ((n) >> (32-(s))))

typedef struct _RIPEMD160_CTX {
	uint32_t total[2];
	uint32_t state[5];
	uint32_t buffer[BLOCK_SIZE];
} RIPEMD160_CTX;

void ripemd160_init(RIPEMD160_CTX *ctx)
{
	memset(ctx->state, 0, sizeof(ctx->state));

	/* initialize state */
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
	ctx->state[4] = 0xc3d2e1f0;
}

