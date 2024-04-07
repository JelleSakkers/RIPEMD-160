/* Naam: Jelle SAakkers
 * UvAnetID: 14619946
 * Opleiding: Bachelor Informatica
 */

#include <stdlib.h>
#include <stdint.h>

#define RIPEMD160_BLOCK_LENGTH 64
#define RIPEMD160_DIGEST_LENGTH 20

/* RIPEMD-160 DEFINITIONS */

 #define A(x, y, z) ((x) ^ (y) ^ (z))
 #define B(x, y, z) (((x) & (y)) | (~(x) & (z)))
 #define C(x, y, z) (((x) | ~(y)) ^ (z))
 #define D(x, y, z) (((x) & (z)) | ((y) & ~(z)))
 #define E(x, y, z) ((x) ^ ((y) | ~(z)))

typedef struct _RIPEMD160_CTX {
	uint32_t total[2];
	uint32_t state[5];
	uint32_t buffer[RIPEMD160_BLOCK_LENGTH];
} RIPEMD160_CTX;


