/**
 *  @file    gost89_replace_decrypt.c
 *  @brief   GOST 28147-89 emplementation.
 *  @author  Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "crypto/gost89.h"


/**
 * @brief
 * Encypt data by simple replace algorithm.
 *
 * @param  ctx : [in] point to GOST context.
 * @param  dst : [out] buffer for output data.
 * @param  src : [in] address of input data.
 * @param  len : [in] length input data in bytes.
 */
void gost89_replace_decrypt ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len )
{
	register uint32  c0;
	

	for( c0 = ( ((len-1) >> 3) + 1 ); c0; c0-- )
	{
		gost_block_decrypt( ctx, dst, src );
		
		src += 2;
		dst += 2;
	}
}
