#ifndef RTC_HPP_
#define RTC_HPP_
/**
 * @file     Rtc.hpp
 * @brief    Describe base API for RTC devices.
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
class Rtc : public hal::Device {
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
	Rtc ( hal::Port *rtc_port );

	/**
	 * @brief
	 * Get time from RTC.
	 *
	 * @param time : [out] Point to time structure.
	 */
	void get_time ( Rtc::Time *time )
	{
		virtual_get_time( this, time );
	}

	/**
	 * @brief
	 * Set time to RTC.
	 *
	 * @param time : [in] Point to time structure.
	 */
	void set_time ( const Rtc::Time *time )
	{
		virtual_set_time( this, time );
	}

	/**
	 * @brief
	 * Get date from RTC.
	 *
	 * @param date : [out] Point to time structure.
	 */
	void get_date ( Rtc::Date *date )
	{
		virtual_get_date( this, date );
	}

	/**
	 * @brief
	 * Set date to RTC.
	 *
	 * @param date : [in] Point to time structure.
	 */
	void set_date ( const Rtc::Date *date )
	{
		virtual_set_date( this, date );
	}

	/**
	 * @brief
	 * Convert byte from BCD to ASCII.
	 *
	 * @param bcd_byte : [in] input byte in bcd format.
	 * @param buffer   : [out] address of output buffer.
	 *
	 * @note
	 * Buffer size must be greater or equal 3 byte.
	 */
	void bcd2ascii ( uint8 bcd_byte, char buffer[3] )
	{
		buffer[0] = HPART8(bcd_byte) + '0';
		buffer[1] = LPART8(bcd_byte) + '0';
		buffer[2] = '\0';
	}

 	/**
	 * Convert byte from BCD to decimal format.
	 */
	int bcd2dec ( uint8 bcd_byte )
	{
		int dec_data;
	
		dec_data  = ( HPART8(bcd_byte) * 10 );
		dec_data += ( LPART8(bcd_byte) );
	
		return dec_data;
	}

protected:
	/*
	 * Overrided point to main API methods.
	 */
	void (*virtual_get_time)( void *, Rtc::Time * );
	void (*virtual_set_time)( void *, const Rtc::Time * );
	void (*virtual_get_date)( void *, Rtc::Date * );
	void (*virtual_set_date)( void *, const Rtc::Date * );
};

} /* namespace dev */

#endif  /* RTC_HPP_ */
