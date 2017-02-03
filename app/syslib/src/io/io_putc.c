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
 * Put char to output device.
 *
 * @param devio : [in] IO context.
 * @param c     : [in] char for output.
 */
void io_putc ( const ioctx_t *ioctx, char c )
{
	device_t *devio = ioctx->io_device;

	while( !IFACE_TX_READY( devio ) );

	IFACE_TX_CHAR( devio, c );
}
