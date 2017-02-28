/**
 *  @file    gost89.c
 *  @brief   GOST 28147-89 emplementation.
 *  @author  Gerasimov A.S.
 */
#include "typedef.h"
#include "crypto/gost89.h"


/**
 * @brief
 * GOST initialization.
 *
 * @param ctx : [in/out] point to GOST context.
 */
void gost89_init ( gost89_ctx_t *ctx )
{
	uint32 i;
	uint32 j;
	uint32 k;
	uint32 row1, row2, row3, row4;
	
	k = 0;
	/*
	 * Extending s-block table with barrel shift already.
	 */
	for( i = 0; i < 16; i++ )
	{
		row1 = ( (uint32)ctx->sblock[1][i] << 15 );
		row2 = ( (uint32)ctx->sblock[3][i] << 23 );
		row3 = ( (uint32)ctx->sblock[5][i] );
		row3 = (row3 >> 1) | (row3 << 31);
		row4 = ( (uint32)ctx->sblock[7][i] << 7 );

		for( j = 0; j < 16; j++, k++ )
		{
			ctx->sblock_ext[0][k] = row1 | ( (uint32)ctx->sblock[0][j] << 11 );
			ctx->sblock_ext[1][k] = row2 | ( (uint32)ctx->sblock[2][j] << 19 );
			ctx->sblock_ext[2][k] = row3 | ( (uint32)ctx->sblock[4][j] << 27 );
			ctx->sblock_ext[3][k] = row4 | ( (uint32)ctx->sblock[6][j] << 3  );
		}
	}

	/*
	 * Clear seed for MAC calculation.
	 */
	ctx->seed[0] = 0;
	ctx->seed[1] = 0;
}
