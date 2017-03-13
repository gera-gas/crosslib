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
	base_memory(basemem)
{
#if !defined(CXX_RTTI)
	virtual_ioctl = reinterpret_cast<IoctlPrototype>(dummy_trap);

	virtual_tx_ready = reinterpret_cast<ReadyPrototype>(dummy_trap);
	virtual_rx_ready = reinterpret_cast<ReadyPrototype>(dummy_trap);

	virtual_tx = reinterpret_cast<TxPrototype>(dummy_trap);
	virtual_rx = reinterpret_cast<RxPrototype>(dummy_trap);
#endif
};

} /* namespace hal */
