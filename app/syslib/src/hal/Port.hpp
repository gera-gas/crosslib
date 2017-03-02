#ifndef PORT_HPP_
#define PORT_HPP_
/**
 * @file     Port.hpp
 * @brief    Hardware Abstraction Level (HAL).
 * @author   Gerasimov A.S.
 * @date     2013-08-07 15:26:14 +0400
 */
#include <stddef.h>
#include "dummy.h"

namespace hal {

/**
 * Class describe hardware port device.
 * In this context under port device to have in mind
 * interaction or channel devices (UART port, SPI
 * and any IO port devices).
 */
class Port {
public:
	/**
	 * @brief
	 * Port contructor.
	 *
	 * @param basemem : [in] Base address of device.
	 */
	Port( const void *basemem );

	/*
	 * Public (virtual) driver methods.
	 */

	void init ( void )
	{
		virtual_init( this );
	};

	void fini ( void )
	{
		virtual_fini( this );
	}

	bool ioctl ( int cmd, void *param )
	{
		return virtual_ioctl( this, cmd, param );
	}

	bool tx_ready ( void )
	{
		return virtual_tx_ready( this );
	}

	bool rx_ready ( void )
	{
		return virtual_rx_ready( this );
	};

	void tx ( size_t data )
	{
		virtual_tx( this, data );
	}

	size_t rx ( void )
	{
		return virtual_rx( this );
	}

	void irq_callback_rx ( void )
	{
		virtual_irq_callback_rx( this );
	}

	void irq_callback_tx ( void )
	{
		virtual_irq_callback_tx( this );
	}

protected:
	/**
	 * Driver method for startup initializing device and configure by default.
	 */
	void (*virtual_init) ( void * );

	/**
	 * Driver method for disable and power down device method.
	 */
	void (*virtual_fini) ( void * );

	/**
	 * Driver method for device custom control.
	 */
	bool (*virtual_ioctl) ( void *, int cmd, void *param );

	/**
	 * Driver method for check to transmitter ready.
	 */
	bool (*virtual_tx_ready) ( void * );

	/**
	 * Driver method for check to receiver ready.
	 */
	bool (*virtual_rx_ready) ( void * );

	/**
	 * Driver method for write data to port.
	 */
	void (*virtual_tx) ( void *, size_t data );

	/**
	 * Driver method for read data from port.
	 */
	size_t (*virtual_rx) ( void * );

	/**
	 * Driver method for IRQ receive handler.
	 */
	void (*virtual_irq_callback_rx) ( void * );

	/**
	 * Driver method for IRQ transmit handler.
	 */
	void (*virtual_irq_callback_tx) ( void * );

	/*
	 * Device base memory address.
	 */
	const void *basemem_;

	/*
	 * Point to buffer for asynchronize access.
	 * Using for work by IRQ.
	 */
	void *tx_buffer_;
	size_t tx_bufsize_;

	void *rx_buffer_;
	size_t rx_bufsize_;
};

} /* namespace hal */

#endif /* PORT_HPP_ */
