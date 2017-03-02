/**
 *  @file    gost89_gamming.c
 *  @brief   GOST 28147-89 emplementation.
 *  @author  Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "crypto/gost89.h"


#define MAGIC_CONSTANT_C1   0x01010104
#define MAGIC_CONSTANT_C2   0x01010101

/**
 * @brief
 * Encrypt/decrypt data by GOST gamming algorithm.
 *
 * @param  ctx : [in] point to GOST context.
 * @param  dst : [out] buffer address for output data.
 * @param  src : [in] address of input data.
 * @param  len : [in] length input data in bytes.
 */
void gost89_gamming ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len )
{
	register uint32  c0, tmp;
	         uint32  n1, n2;
	         uint32  gamma[2];
	
	
	gost89_block_encrypt( ctx, gamma, ctx->sync_message );
	
	n1 = gamma[0];
	n2 = gamma[1];
	
	for( c0 = ( ((len-1) >> 3) + 1 ); c0; c0-- )
	{
		tmp = n2;
		
		n1 += MAGIC_CONSTANT_C2;
		n2 += MAGIC_CONSTANT_C1;

		if( tmp > n2 )
			n2++;
		
		gamma[0] = n1;
		gamma[1] = n2;
		
		gost89_block_encrypt( ctx, gamma, gamma );
		
		*dst++ = gamma[0] ^ *src++;
		*dst++ = gamma[1] ^ *src++;
	}
}
