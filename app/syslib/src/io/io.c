/**
 *  @file     io.c
 *  @brief    IO service based on PT mechanisms.
 *  @author   Gerasimov A.S.
 */
#include "typedef.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "multitask/thread.h"
#include "io/io.h"

/**
 * Startup check methods.
 */
static PT_STATE( ptio_init_state )
{
	ioctx_t *io = (ioctx_t *)argin;

	if( !io->io_device )
	{
		return PT_RESET;
	}

	io->count = 0;

	return PT_NEXT;
}

/*******************************************************************************
 * PUTS
 *******************************************************************************/

static PT_STATE( ptio_txrdy_state );
static PT_STATE( ptio_tx_state );

/**
 * @brief Put string to output.
 */
PT_CREATE( pt_puts, PT_FLAG_NONE,
	ptio_init_state,
	ptio_txrdy_state,
	ptio_tx_state );


/**
 * Wait TX ready state.
 */
static PT_STATE( ptio_txrdy_state )
{
	ioctx_t *io = (ioctx_t *)argin;

	if( !IFACE_TX_READY( io->io_device ) )
	{
		return PT_HOLD;
	}

	return PT_NEXT;
}


/**
 * Put char to output device.
 */
static PT_STATE( ptio_tx_state )
{
	ioctx_t *io  = (ioctx_t *)argin;
	   char *str = io->io_buffer->addr;

	if( str[ io->count ] == '\0' )
	{
		return PT_NEXT;
	}

	IFACE_TX_CHAR( io->io_device, str[ io->count ] );

	return PT_BACK;
}


/*******************************************************************************
 * GETCH
 *******************************************************************************/

static PT_STATE( ptio_rxrdy_state );
static PT_STATE( ptio_rx_state );

/**
 * @brief Put string to output.
 */
PT_CREATE( pt_getch, PT_FLAG_NONE,
	ptio_init_state,
	ptio_rxrdy_state,
	ptio_rx_state );


/**
 * Wait RX ready state.
 */
static PT_STATE( ptio_rxrdy_state )
{
	ioctx_t *io = (ioctx_t *)argin;

	if( !IFACE_RX_READY( io->io_device ) )
	{
		return PT_HOLD;
	}

	return PT_NEXT;
}


/**
 * Read char from device.
 */
static PT_STATE( ptio_rx_state )
{
	ioctx_t *io  = (ioctx_t *)argin;
	   char *str = io->io_buffer->addr;

	str[ 0 ] = IFACE_RX_CHAR( io->io_device );

	return PT_BACK;
}
