#ifndef GOST_89_H_
#define GOST_89_H_
/**
 *  @file    gost89.h
 *  @brief   Export GOST 28147-89 functions.
 *  @author  Gerasimov A.S.
 */
typedef struct gost89_ctx_st {
	uint32  key[8];
	uint32  sync_message[2];
	 uint8  sblock[8][16];
	/*
	 * External s-block table.
	 */
	uint32  sblock_ext[4][256];
	/*
	 * Seed for MAC calculation.
	 */
	uint32 seed[2];
} gost89_ctx_t;


#ifdef __cplusplus
extern "C"{
#endif

void gost89_init             ( gost89_ctx_t *ctx );
void gost89_block_encrypt    ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src );
void gost89_block_decrypt    ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src );
void gost89_replace_encrypt  ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len );
void gost89_replace_decrypt  ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len );
void gost89_gamming          ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len );
void gost89_gamming_encrypt  ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len );
void gost89_gamming_decrypt  ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len );
void gost89_gammback_encrypt ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len );
void gost89_gammback_decrypt ( gost89_ctx_t *ctx, uint32 *dst, const uint32 *src, size_t len );

void gost89_mac_update       ( gost89_ctx_t *ctx, const uint32 *pdata, size_t len );
void gost89_mac_final        ( gost89_ctx_t *ctx, uint32 *mac );

#ifdef __cplusplus
}
#endif


/**
 * GOST internal macros with
 * single crypto step implementation.
 */
#define __GOST_CRYPTO_STEP( key, n1, n2 )\
{\
	uint32  result;\
	\
	result = (n1) + (key);\
	result = ctx->sblock_ext[0][result & 0xff] ^ \
		 ctx->sblock_ext[1][(result >> 8) & 0xff] ^ \
		 ctx->sblock_ext[2][(result >> 16) & 0xff] ^ \
		 ctx->sblock_ext[3][result >> 24];\
	result ^= (n2);\
	\
	(n2) = (n1);\
	(n1) = result;\
}

#define __GOST_STEP_DIRECT( k, n1, n2 )\
	__GOST_CRYPTO_STEP( k[0], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[1], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[2], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[3], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[4], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[5], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[6], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[7], n1, n2 );

#define __GOST_STEP_INVERT( k, n1, n2 )\
	__GOST_CRYPTO_STEP( k[7], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[6], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[5], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[4], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[3], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[2], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[1], n1, n2 ); \
	__GOST_CRYPTO_STEP( k[0], n1, n2 );

#endif  /*  GOST_89_H_  */
