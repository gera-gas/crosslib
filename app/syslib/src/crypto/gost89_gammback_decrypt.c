/**
 *  @file    gost89_gammback_decrypt.c
 *  @brief   GOST 28147-89 emplementation.
 *  @author  Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "crypto/gost89.h"


/**
 * @brief
 * Decrypt data by GOST gamming algorithm with feed back.
 *
 * @param  ctx : [in] point to GOST context.
 * @param  dst : [out] buffer address for output data.
 * @param  src : [in] address of input data.
 * @param  len : [in] length input data in bytes.
 */
void gost89_gammback_decrypt ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len )
{
	register uint32  c0;
	         uint32  gamma[2];
	         uint32  accumul[2];
	
	
	accumul[0] = src[0];
	accumul[1] = src[1];

	gost89_block_encrypt( ctx, gamma, ctx->sync_message );
	
	*dst++ = gamma[0] ^ *src++;
	*dst++ = gamma[1] ^ *src++;
	
	for( c0 = ( ((len-1) >> 3) + 1 ); c0; c0-- )
	{
		gost89_block_encrypt( ctx, gamma, accumul );
		
		accumul[0] = src[0];
		accumul[1] = src[1];
		
		*dst++ = gamma[0] ^ *src++;
		*dst++ = gamma[1] ^ *src++;
	}
}
