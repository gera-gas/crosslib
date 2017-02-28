/**
 *  @file    gost89_gamming_encrypt.c
 *  @brief   GOST 28147-89 emplementation.
 *  @author  Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "crypto/gost89.h"


/**
 * @brief
 * Encrypt data by GOST gamming algorithm.
 *
 * @param  ctx : [in] point to GOST context.
 * @param  dst : [out] buffer address for output data.
 * @param  src : [in] address of input data.
 * @param  len : [in] length input data in bytes.
 */
void gost89_gamming_encrypt ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len )
{
	gost89_gamming( ctx, dst, src, len );
}
