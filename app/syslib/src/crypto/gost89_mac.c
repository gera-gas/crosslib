/**
 *  @file    gost89_mac.c
 *  @brief   GOST 28147-89 emplementation.
 *  @author  Gerasimov A.S.
 */
#include "typedef.h"
#include "memory/memory.h"
#include "crypto/gost89.h"


/**
 * @brief
 * Calculate MAC summ by GOST algorithm.
 *
 * @param  ctx : [in] point to GOST context.
 * @param  dst : [out] buffer for output block.
 * @param  src : [in] address of input block.
 */
void gost89_mac_update ( gost89_ctx_t *ctx, const uint32 *pdata, size_t len )
{
	register uint32  c0;
	         uint32  accumul[2];

	uint32 n1 = ctx->seed[0];
	uint32 n2 = ctx->seed[1];

	for( c0 = len >> 3; c0; c0-- )
	{
		n1 ^= *pdata++;
		n2 ^= *pdata++;

		__GOST_STEP_DIRECT( ctx->key, n1, n2 );
		__GOST_STEP_DIRECT( ctx->key, n1, n2 );
	}

	if( len & 0x00000007 )
	{
		accumul[0] = 0;
		accumul[1] = 0;
		
		memcpy( accumul, pdata, len & 0x00000007 );
		
		n1 ^= accumul[0];
		n2 ^= accumul[1];
		
		__GOST_STEP_DIRECT( ctx->key, n1, n2 );
		__GOST_STEP_DIRECT( ctx->key, n1, n2 );
	}

	ctx->seed[0] = n1;
	ctx->seed[1] = n2;
}


/**
 * @brief
 * Store MAC result.
 *
 * @param  ctx : [in] point to GOST context.
 * @param  dst : [out] buffer address to store MAC.
 */
void gost89_mac_final ( gost89_ctx_t *ctx, uint32 *mac )
{
	*mac = ctx->seed[0];
}
