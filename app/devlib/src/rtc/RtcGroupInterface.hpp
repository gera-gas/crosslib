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

namespace dev {

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

	/**
	 * RTC consctructor.
	 */
	RtcGroupInterface ( hal::Port *rtc_port );

	/**
	 * @brief
	 * Get time from RTC.
	 *
	 * @param time : [out] Point to time structure.
	 */
	void get_time ( RtcGroupInterface::Time *time )
	{
		virtual_get_time( this, time );
	}

	/**
	 * @brief
	 * Set time to RTC.
	 *
	 * @param time : [in] Point to time structure.
	 */
	void set_time ( const RtcGroupInterface::Time *time )
	{
		virtual_set_time( this, time );
	}

	/**
	 * @brief
	 * Get date from RTC.
	 *
	 * @param date : [out] Point to time structure.
	 */
	void get_date ( RtcGroupInterface::Date *date )
	{
		virtual_get_date( this, date );
	}

	/**
	 * @brief
	 * Set date to RTC.
	 *
	 * @param date : [in] Point to time structure.
	 */
	void set_date ( const RtcGroupInterface::Date *date )
	{
		virtual_set_date( this, date );
	}

	void bcd2ascii ( uint8 bcd_byte, char buffer[3] );

	uint8 bcd2dec ( uint8 bcd_byte );
	uint8 dec2bcd ( uint8 dec_byte );

protected:
	/*
	 * Overrided point to main API methods.
	 */
	void (*virtual_get_time)( void *, RtcGroupInterface::Time * );
	void (*virtual_set_time)( void *, const RtcGroupInterface::Time * );
	void (*virtual_get_date)( void *, RtcGroupInterface::Date * );
	void (*virtual_set_date)( void *, const RtcGroupInterface::Date * );
};

} /* namespace dev */

#endif  /* RTC_GROUP_INTERFACE_HPP_ */
