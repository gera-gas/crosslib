/**
 * @file     io_putc.c
 * @brief    Base IO functions to custom device.
 * @author   Gerasimov A.S.
 */
#include "typedef.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"

/**
 * @brief
 * Put string to output device.
 *
 * @param ioctx : [in] IO context.
 * @param pstr  : [in] string for output.
 */
void io_puts ( const ioctx_t *ioctx, const char *pstr )
{
	char c;

	while( 1 )
	{
		c = *pstr++;

		if( c == '\0' ) {
			break;
		}

		io_putc( ioctx, c );
	}
}
