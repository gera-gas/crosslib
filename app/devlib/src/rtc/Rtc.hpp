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
	Rtc ( hal::Port *rtc_port ) :
		Device(rtc_port)
	{
		get_time_ = reinterpret_cast<void (*)(void*, Rtc::Time*)>(dummy_loop);
		set_time_ = reinterpret_cast<void (*)(void*, const Rtc::Time*)>(dummy_loop);
		get_date_ = reinterpret_cast<void (*)(void*, Rtc::Date*)>(dummy_loop);
		set_date_ = reinterpret_cast<void (*)(void*, const Rtc::Date*)>(dummy_loop);
	}

	/**
	 * @brief
	 * Get time from RTC.
	 *
	 * @param time : [out] Point to time structure.
	 */
	void get_time ( Rtc::Time *time )
	{
		get_time_( this, time );
	}

	/**
	 * @brief
	 * Set time to RTC.
	 *
	 * @param time : [in] Point to time structure.
	 */
	void set_time ( const Rtc::Time *time )
	{
		set_time_( this, time );
	}

	/**
	 * @brief
	 * Get date from RTC.
	 *
	 * @param date : [out] Point to time structure.
	 */
	void get_date ( Rtc::Date *date )
	{
		get_date_( this, date );
	}

	/**
	 * @brief
	 * Set date to RTC.
	 *
	 * @param date : [in] Point to time structure.
	 */
	void set_date ( const Rtc::Date *date )
	{
		set_date_( this, date );
	}

	/**
	 * Convert byte from BCD to ASCII.
	 */
	uint32 bcd2ascii ( uint8 bcd_byte )
	{
		uint32 ascii_data;
	
		ascii_data  = ( (bcd_byte & 0x000000F0) ^ 0x300 ) << 20;
		ascii_data |= ( (bcd_byte & 0x0000000F) ^ 0x30 ) << 16;
	
		return ascii_data;
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
	void (*get_time_)( void *, Rtc::Time * );
	void (*set_time_)( void *, const Rtc::Time * );
	void (*get_date_)( void *, Rtc::Date * );
	void (*set_date_)( void *, const Rtc::Date * );
};

} /* namespace dev */

#endif  /* RTC_HPP_ */
