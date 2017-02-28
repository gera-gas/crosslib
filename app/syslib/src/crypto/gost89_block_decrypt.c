/**
 *  @file    gost89_block_decrypt.c
 *  @brief   GOST 28147-89 emplementation.
 *  @author  Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "crypto/gost89.h"


/**
 * @brief
 * One data block (64-bit) decrypt.
 *
 * @param  ctx : [in] point to GOST context.
 * @param  dst : [out] buffer for output block.
 * @param  src : [in] address of input block.
 */
void gost89_block_decrypt ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src )
{
	register uint32  i;

	uint32 n1 = src[0];
	uint32 n2 = src[1];

	for( i = 0; i < 3; i++ )
	{
		__GOST_STEP_DIRECT( ctx->key, n1, n2 );
	}
	__GOST_STEP_INVERT( ctx->key, n1, n2 );

	dst[0] = n2;
	dst[1] = n1;
}
