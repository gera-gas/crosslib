#ifndef RTC_9701JE_HPP_
#define RTC_9701JE_HPP_
/**
 * @file     Rtc9701je.hpp
 * @brief    Driver for Epson Real Time Clock RTC-9701JE.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"

namespace rtc {

/**
 * Driver for Epson Real Time Clock RTC-9701JE.
 */
class Rtc9701je : public RtcGroupInterface {
public:
	Rtc9701je ( hal::Port * );

private:
	/*
	 * RTC Register table.
	 */
	struct RegisterTable {
		uint8 sec;         /* BCD notation */
		uint8 min;         /* BCD notation */
		uint8 hour;        /* BCD notation */
		uint8 week;        /* 2^n notation */
		uint8 day;         /* BCD notation */
		uint8 month;       /* BCD notation */
		uint8 year;        /* BCD notation */
		uint8 y100;        /* 20 is fixed (BCD) */
		uint8 alarm_min;   /* BCD notation */
		uint8 alarm_hour;  /* BCD notation */
		uint8 alarm_day;   /* WADA=0 Week, WADA=1 Day */
		uint8 reserved;
		uint8 interval_timer;
		uint8 extension_reg;
		uint8 flag_reg;
		uint8 control_reg;
	};

	/*
	 * Internal data exchange methods.
	 */ 
	void  byte_snd ( uint8 regnum, uint8 databyte );
	uint8 byte_rcv ( uint8 regnum );

	/*
	 * Device specifically methods for RTC API.
	 */
	friend void rtc9701je_get_time ( Rtc9701je *rtc9701je, RtcGroupInterface::Time *time );
	friend void rtc9701je_set_time ( Rtc9701je *rtc9701je, const RtcGroupInterface::Time *time );
	friend void rtc9701je_get_date ( Rtc9701je *rtc9701je, RtcGroupInterface::Date *date );
	friend void rtc9701je_set_date ( Rtc9701je *rtc9701je, const RtcGroupInterface::Date *date );
};

} /* namespace rtc */

#endif  /* RTC_9701JE_HPP_ */
