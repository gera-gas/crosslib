#ifndef PORT_HPP_
#define PORT_HPP_
/**
 * @file     Port.hpp
 * @brief    Hardware Abstraction Layer (HAL).
 * @author   Gerasimov A.S.
 * @date     2013-08-07 15:26:14 +0400
 */
#include <stddef.h>

namespace hal {

/**
 * Class describe hardware port device.
 * In this context under port device to have in mind
 * interaction or channel devices (UART port, SPI
 * and any IO port devices).
 */
class Port : public hal::Module {
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
#if defined(CXX_RTTI)
	virtual bool ioctl ( int, void * ) = 0;
	virtual bool tx_ready ( void ) = 0;
	virtual bool rx_ready ( void ) = 0;
	virtual void tx ( size_t ) = 0;
	virtual size_t rx ( void ) = 0;
	virtual void irq_callback_rx ( void ) = 0;
	virtual void irq_callback_tx ( size_t ) = 0;
#else
	bool ioctl ( int, void * );
	bool tx_ready ( void );
	bool rx_ready ( void );
	void tx ( size_t  );
	size_t rx ( void );
	void irq_callback_rx ( void );
	void irq_callback_tx ( size_t );
	/*
	 * Define types for virtual methods.
	 */
	typedef bool   (*callback_ioctl_t) ( void*, int, void* );
	typedef bool   (*callback_ready_t) ( void* );
	typedef void   (*callback_tx_t)    ( void*, size_t );
	typedef size_t (*callback_rx_t)    ( void* );
#endif

	/*
	 * Port data exchange methods.
	 * These functions do not return until fully worked out.
	 */
	void snd ( size_t );
	size_t rcv ( void );

protected:

#if !defined(CXX_RTTI)
	/**
	 * Driver method for device custom control.
	 */
	callback_ioctl_t virtual_ioctl;

	/**
	 * Driver method for check to transmitter ready.
	 */
	callback_ready_t virtual_tx_ready;

	/**
	 * Driver method for check to receiver ready.
	 */
	callback_ready_t virtual_rx_ready;

	/**
	 * Driver method for write data to port.
	 */
	callback_tx_t virtual_tx;

	/**
	 * Driver method for IRQ transmit handler.
	 */
	callback_tx_t virtual_tx_irq;

	/**
	 * Driver method for read data from port.
	 */
	callback_rx_t virtual_rx;

	/**
	 * Driver method for IRQ receive handler.
	 */
	callback_rx_t virtual_rx_irq;
#endif

	/*
	 * Device base memory address.
	 */
	const void *basemem_;

	/*
	 * Pointer to buffer used for asynchronous access.
	 * Using for work by IRQ.
	 */
	void *tx_buffer;
	size_t tx_bufsize;

	void *rx_buffer;
	size_t rx_bufsize;
};

} /* namespace hal */

#endif /* PORT_HPP_ */
