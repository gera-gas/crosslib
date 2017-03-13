#ifndef DEVICE_HPP_
#define DEVICE_HPP_
/**
 * @file     Device.hpp
 * @brief    Hardware Abstraction Layer (HAL).
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
class Device : public Module {
public:
	/**
	 * Device constructor.
	 */
	Device( Port *device_port ) :
		Module(),
		port(device_port)
	{ }

protected:
	/**
	 * Pointer to connection port.
	 */
	Port *port;
};

} /* namespace hal */

#endif /* DEVICE_HPP_ */
