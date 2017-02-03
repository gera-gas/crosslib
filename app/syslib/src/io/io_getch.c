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
 * Get char from IO device.
 *
 * @param devio : [in] IO context.
 */
char io_getch ( const ioctx_t *ioctx )
{
	device_t *devio = ioctx->io_device;

	while( !IFACE_RX_READY( devio ) );

	return IFACE_RX_CHAR( devio );
}
