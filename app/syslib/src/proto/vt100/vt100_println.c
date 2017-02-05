/**
 * @file     vt100_println.c
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
 * Print line to VT-100 terminal.
 *
 * @param ctx  : [in] point to VT-100 context object.
 * @param line : [in] string for output.
 */
void vt100_println ( const vt100ctx_t *ctx, const char *line )
{
	if( line )
	{
		io_puts( ctx->ioctx, line );
	}

	if( ctx->newline )
	{
		io_puts( ctx->ioctx, ctx->newline );
		return;
	}

	io_puts( ctx->ioctx, "\n\r" );
}
