#ifndef HAL_HPP_
#define HAL_HPP_
/**
 * @file     hal.hpp
 * @brief    Hardware Abstraction Level (HAL).
 * @author   Gerasimov A.S.
 * @date     2013-08-07 15:26:14 +0400
 */
#include <stdbool.h>
#include <stddef.h>
#include "dummy.h"

namespace sys {

/**
 * Class describe hardware port device.
 * In this context under port device to have in mind
 * interaction or channel devices (UART port, SPI
 * and any IO port devices).
 */
class DevicePort {
public:
	/**
	 * @brief
	 * Device contructor.
	 *
	 * @param basemem : [in] Base address of device.
	 */
	DevicePort( const void *basemem );

	~DevicePort( ) { };

	/*
	 * Public (virtual) driver methods.
	 */

	void init ( void )
	{
		init_( this );
	};

	void fini ( void )
	{
		fini_( this );
	}

	bool ioctl ( int cmd, void *param )
	{
		return ioctl_( this, cmd, param );
	}

	bool tx_ready ( void )
	{
		return tx_ready_( this );
	}

	bool rx_ready ( void )
	{
		return rx_ready_( this );
	};

	void tx ( size_t data )
	{
		tx_( this, data );
	}

	size_t rx ( void )
	{
		return rx_( this );
	}

	void irq_callback_rx ( void )
	{
		irq_callback_rx_( this );
	}

	void irq_callback_tx ( void )
	{
		irq_callback_tx_ ( this );
	}

protected:
	/**
	 * Driver method for startup initializing device and configure by default.
	 */
	void (*init_) ( void * );

	/**
	 * Driver method for disable and power down device method.
	 */
	void (*fini_) ( void * );

	/**
	 * Driver method for device custom control.
	 */
	bool (*ioctl_) ( void *, int cmd, void *param );

	/**
	 * Driver method for check to transmitter ready.
	 */
	bool (*tx_ready_) ( void * );

	/**
	 * Driver method for check to receiver ready.
	 */
	bool (*rx_ready_) ( void * );

	/**
	 * Driver method for write data to port.
	 */
	void (*tx_) ( void *, size_t data );

	/**
	 * Driver method for read data from port.
	 */
	size_t (*rx_) ( void * );

	/**
	 * Driver method for IRQ receive handler.
	 */
	void (*irq_callback_rx_) ( void * );

	/**
	 * Driver method for IRQ transmit handler.
	 */
	void (*irq_callback_tx_) ( void * );

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

} /* namespace sys */

#endif /* HAL_HPP_ */
