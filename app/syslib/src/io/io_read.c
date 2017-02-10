/**
 * @file     io_read.c
 * @brief    Base IO functions to custom device.
 * @author   Gerasimov A.S.
 */
#include "typedef.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"

/**
 * @brief
 * Read data from IO device.
 *
 * @param ioctx : [in] IO context.
 * @param pdata : [in] address of destination buffer.
 * @param size  : [in] size for reading in bytes.
 *
 * @return
 * Data size wrote to device.
 */
size_t io_read ( const ioctx_t *ioctx, char *pdata, size_t size )
{
	size_t i;

	for( i = 0; i < size; i++ )
	{
		pdata[i] = (uint8)io_getch( ioctx );
	}

	return i;
}
