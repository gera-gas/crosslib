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
	init_  = reinterpret_cast<void (*)(void*)>(dummy_loop);
	fini_  = reinterpret_cast<void (*)(void*)>(dummy_loop);
	ioctl_ = reinterpret_cast<bool (*)(void*,int,void*)>(dummy_loop);

	tx_ready_ = reinterpret_cast<bool (*)(void*)>(dummy_loop);
	rx_ready_ = reinterpret_cast<bool (*)(void*)>(dummy_loop);

	tx_ = reinterpret_cast<void (*)(void*,size_t)>(dummy_loop);
	rx_ = reinterpret_cast<size_t (*)(void*)>(dummy_loop);

	irq_callback_rx_ = reinterpret_cast<void (*)(void*)>(dummy_loop);
	irq_callback_tx_ = reinterpret_cast<void (*)(void*)>(dummy_loop);
};

} /* namespace hal */
