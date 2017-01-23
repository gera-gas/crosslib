#ifndef _MD5_H
#define _MD5_H
/**
 *  @file     md5.h
 *  @brief    MD5 hash algorythm implementaion.
 *  @author   Gerasimov A.S.
 *  @date     2015-11-06 13:39:51 +0400
 */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8   buffer[64];
    uint32  count[2];
    uint32  state[4];
} MD5_ctx;

bool md5_init   ( MD5_ctx *pctx );
bool md5_update ( MD5_ctx *pctx, const void *data, size_t len );
bool md5_final  ( MD5_ctx *pctx, void *md );

#ifdef __cplusplus
}
#endif

#endif  /*  _MD5_H  */
