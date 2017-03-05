/**
 * @file     Rtc.cpp
 * @brief    Describe base API for RTC devices.
 * @author   Gerasimov A.S.
 * @note
 */
#include "hal/Module.hpp"
#include <stddef.h>
#include "typedef.h"
#include "hal/Port.hpp"
#include "hal/Device.hpp"
#include "io/InOut.hpp"
#include "Rtc.hpp"

namespace dev {

/**
 * RTC consctructor.
 */
Rtc::Rtc ( hal::Port *rtc_port ) :
	Device(rtc_port)
{
	virtual_get_time = reinterpret_cast<void (*)(void*, Rtc::Time*)>(dummy_loop);
	virtual_set_time = reinterpret_cast<void (*)(void*, const Rtc::Time*)>(dummy_loop);
	virtual_get_date = reinterpret_cast<void (*)(void*, Rtc::Date*)>(dummy_loop);
	virtual_set_date = reinterpret_cast<void (*)(void*, const Rtc::Date*)>(dummy_loop);
}

} /* namespace dev */
