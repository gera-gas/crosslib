#ifndef RTC_GROUP_INTERFACE_HPP_
#define RTC_GROUP_INTERFACE_HPP_
/**
 * @file     RtcGroupInterface.hpp
 * @brief    RTC common group interface.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "hal/Port.hpp"
 * #include "hal/Device.hpp"
 */
#include <stddef.h>
#include "typedef.h"
#include "gmacro.h"
#include "dummy.h"

namespace rtc {

/**
 * API class for RTC devices.
 */
class RtcGroupInterface : public hal::Device {
public:

	/*
	 * Type describe of time and date.
	 */
	struct Time {
		uint8  second;
		uint8  minute;
		uint8  hour;
	};

	struct Date {
		uint8  day;
		uint8  month;
		uint8  year;
	};

	RtcGroupInterface ( hal::Port *rtc_port );

	void get_time ( RtcGroupInterface::Time *time );
	void set_time ( const RtcGroupInterface::Time *time );
	void get_date ( RtcGroupInterface::Date *date );
	void set_date ( const RtcGroupInterface::Date *date );

	void bcd_tostr ( uint8 bcd_byte, char buffer[3] );

	uint8 bcd_todec ( uint8 bcd_byte );
	uint8 dec_tobcd ( uint8 dec_byte );

protected:
	/*
	 * Overrided point to main API methods.
	 */
	void (*virtual_get_time)( void *, RtcGroupInterface::Time * );
	void (*virtual_set_time)( void *, const RtcGroupInterface::Time * );
	void (*virtual_get_date)( void *, RtcGroupInterface::Date * );
	void (*virtual_set_date)( void *, const RtcGroupInterface::Date * );
};

} /* namespace rtc */

#endif  /* RTC_GROUP_INTERFACE_HPP_ */
