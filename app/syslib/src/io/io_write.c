/**
 * @file     io_write.c
 * @brief    Base IO functions to custom device.
 * @author   Gerasimov A.S.
 */
#include "typedef.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"

/**
 * @brief
 * Write data to output device.
 *
 * @param ioctx : [in] IO context.
 * @param pdata : [in] address of input buffer.
 * @param size  : [in] size for reading in bytes.
 *
 * @return
 * Data size wrote to device.
 */
size_t io_write ( const ioctx_t *ioctx, const char *pdata, size_t size )
{
	size_t i;

	for( i = 0; i < size; i++ )
	{
		io_putc( ioctx, pdata[i] );
	}

	return i;
}
