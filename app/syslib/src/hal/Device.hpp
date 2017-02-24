#ifndef DEVICE_HPP_
#define DEVICE_HPP_
/**
 * @file     Device.hpp
 * @brief    Hardware Abstraction Level (HAL).
 * @author   Gerasimov A.S.
 * @date     2013-08-07 15:26:14 +0400
 */
#include <stddef.h>

namespace hal {

/**
 * Class describe hardware service device.
 * In this context under service device to have in mind
 * Flash, RTC, and also external devices connected by Port.
 */
class Device {
public:
	/**
	 * Device constructor.
	 */
	Device( Port *io_port ) :
		port(io_port),
		errorcode(0)
	{ }

	/**
	 * Return device specifically error code.
	 */
	int get_error ( void ) const
	{
		return errorcode;
	}

protected:
	/*
	 * Point to port device through device connected.
	 */
	Port *port;

	/**
	 * Contain specific error code.
	 */
	int errorcode;

};

} /* namespace hal */

#endif /* DEVICE_HPP_ */
