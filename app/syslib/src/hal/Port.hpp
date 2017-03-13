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
class Port : public Module {
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
#else
	bool ioctl ( int, void * );
	bool tx_ready ( void );
	bool rx_ready ( void );
	void tx ( size_t  );
	size_t rx ( void );
	/*
	 * Define types for virtual methods.
	 */
	typedef bool   (*IoctlPrototype) ( void*, int, void* );
	typedef bool   (*ReadyPrototype) ( void* );
	typedef void   (*TxPrototype)    ( void*, size_t );
	typedef size_t (*RxPrototype)    ( void* );
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
	IoctlPrototype virtual_ioctl;

	/**
	 * Driver method for check to transmitter ready.
	 */
	ReadyPrototype virtual_tx_ready;

	/**
	 * Driver method for check to receiver ready.
	 */
	ReadyPrototype virtual_rx_ready;

	/**
	 * Driver method for write data to port.
	 */
	TxPrototype virtual_tx;

	/**
	 * Driver method for read data from port.
	 */
	RxPrototype virtual_rx;
#endif

	/*
	 * Device base memory address.
	 */
	const void *base_memory;
};

} /* namespace hal */

#endif /* PORT_HPP_ */
