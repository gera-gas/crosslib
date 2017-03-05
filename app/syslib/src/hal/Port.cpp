/**
 * @file     Port.cpp
 * @brief    Hardware Abstraction Layer (HAL).
 * @author   Gerasimov A.S.
 * @date     2013-08-07 15:26:14 +0400
 */
#include "hal/Module.hpp"
#include "hal/Port.hpp"
#include "dummy.h"

namespace hal {

#if !defined(CXX_RTTI)
/*
 * Public (virtual) driver methods.
 */
bool Port::ioctl ( int cmd, void *param )
{
	return virtual_ioctl( this, cmd, param );
}

bool Port::tx_ready ( void )
{
	return virtual_tx_ready( this );
}

bool Port::rx_ready ( void )
{
	return virtual_rx_ready( this );
}

void Port::tx ( size_t data )
{
	virtual_tx( this, data );
}

size_t Port::rx ( void )
{
	return virtual_rx( this );
}

void Port::irq_callback_rx ( void )
{
	virtual_rx_irq( this );
}

void Port::irq_callback_tx ( size_t data )
{
	virtual_tx_irq( this, data );
}
#endif

void Port::snd ( size_t data )
{
	while( !tx_ready() );

	tx( data );
}

size_t Port::rcv ( void )
{
	while( !rx_ready() );

	return rx( );
}


/**
 * @brief
 * Port contructor.
 *
 * @param basemem : [in] Base address of device.
 */
Port::Port( const void *basemem ) :
	Module(),
	basemem_(basemem),
	tx_buffer(NULL),
	tx_bufsize(0),
	rx_buffer(NULL),
	rx_bufsize(0)
{
#if !defined(CXX_RTTI)
	virtual_ioctl = reinterpret_cast<callback_ioctl_t>(dummy_trap);

	virtual_tx_ready = reinterpret_cast<callback_ready_t>(dummy_trap);
	virtual_rx_ready = reinterpret_cast<callback_ready_t>(dummy_trap);

	virtual_tx     = reinterpret_cast<callback_tx_t>(dummy_trap);
	virtual_tx_irq = reinterpret_cast<callback_tx_t>(dummy_trap);

	virtual_rx     = reinterpret_cast<callback_rx_t>(dummy_trap);
	virtual_rx_irq = reinterpret_cast<callback_rx_t>(dummy_trap);
#endif
};

} /* namespace hal */
