/**
 * @file     Port.cpp
 * @brief    Hardware Abstraction Level (HAL).
 * @author   Gerasimov A.S.
 * @date     2013-08-07 15:26:14 +0400
 */
#include "hal/Port.hpp"

namespace hal {

/**
 * @brief
 * Port contructor.
 *
 * @param basemem : [in] Base address of device.
 */
Port::Port( const void *basemem ) :
	basemem_(basemem),
	tx_buffer_(NULL),
	tx_bufsize_(0),
	rx_buffer_(NULL),
	rx_bufsize_(0) {
	/*
	 * Set driver methods to loop function,
	 * spcial for catch by debugger.
	 */
	virtual_init  = reinterpret_cast<void (*)(void*)>(dummy_loop);
	virtual_fini  = reinterpret_cast<void (*)(void*)>(dummy_loop);
	virtual_ioctl = reinterpret_cast<bool (*)(void*,int,void*)>(dummy_loop);

	virtual_tx_ready = reinterpret_cast<bool (*)(void*)>(dummy_loop);
	virtual_rx_ready = reinterpret_cast<bool (*)(void*)>(dummy_loop);

	virtual_tx = reinterpret_cast<void (*)(void*,size_t)>(dummy_loop);
	virtual_rx = reinterpret_cast<size_t (*)(void*)>(dummy_loop);

	virtual_irq_callback_rx = reinterpret_cast<void (*)(void*)>(dummy_loop);
	virtual_irq_callback_tx = reinterpret_cast<void (*)(void*)>(dummy_loop);
};

} /* namespace hal */
