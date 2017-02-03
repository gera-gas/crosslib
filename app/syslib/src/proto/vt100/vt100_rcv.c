/**
 * @file     vt100_rcv.c
 * @brief    VT-100 data exchange functions.
 * @author   Gerasimov A.S.
 */
#include "typedef.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"
#include "proto/vt100/vt100.h"

/**
 * @brief 
 * Receive message by VT-100 protocol.
 *
 * @param ctx    : [in] point module context object.
 * @param buffer : [out] address of output buffer.
 * @param size   : [in] size of output buffer.
 *
 * @return
 * Received message size in bytes.
 */
size_t vt100_rcv ( const vt100ctx_t *ctx, char *buffer, size_t bufsize )
{
	ioctx_t *ioctx = ctx->ioctx;

	char   c;
	size_t len;

	for( len = 0; ; )
	{
		c = io_getch( ioctx );

		len++;

		if( len >= bufsize )
			len = 0;

		buffer[ len - 1 ] = c;

		if( len == 1 )
		{
			if( c != 0x1B ) {
				break;
			}
		}
		else if( len == 2 )
		{
			if( c != 0x5B ) {
				break;
			}
		}
		else
		{
			if( (c - 0x40) <= (0x7E - 0x40) ) {
				break;
			}
		}
	}

	return len;
}
