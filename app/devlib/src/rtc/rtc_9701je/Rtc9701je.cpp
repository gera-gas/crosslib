/**
 * @file     Rtc9701je.cpp
 * @brief    Driver for ZFM70 optical fingerprint scanner.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "gmacro.h"
#include "hal/Port.hpp"
#include "hal/Device.hpp"
#include "io/InOut.hpp"
#include "rtc/Rtc.hpp"
#include "rtc/rtc_9701je/Rtc9701je.hpp"

/* Set RTC internal registers */
#define REGS  ((Rtc9701je::RegisterTable*)0)

namespace dev {

/**
 * @brief
 * Send byte for write to RTC device.
 *
 * @param regnum : [in] Register Table address (REGS->sec, REGS->min, etc).
 * @param regnum : [in] Data byte for write.
 */
void Rtc9701je::byte_snd ( uint8 regnum, uint8 databyte )
{
	/*
	 * Create command 16-bit word for write.
	 * bit[0] = 1 ==> read  (LSB -> MSB)
	 * bit[0] = 0 ==> write (LSB -> MSB)
	 */
	io_.putc( regnum & 0x7F );
	io_.putc( databyte );
}


/**
 * @brief
 * Send byte for write to RTC device.
 *
 * @param regnum : [in] Register Table address (REGS->sec, REGS->min, etc).
 *
 * @return
 * Data byte from RTC.
 */
uint8 Rtc9701je::byte_rcv ( uint8 regnum )
{
	/*
	 * Create command 16-bit word for read.
	 * bit[0] = 1 ==> read  (LSB -> MSB)
	 * bit[0] = 0 ==> write (LSB -> MSB)
	 */
	io_.putc( regnum | 0x80 );
	io_.putc( 0 );

	return io_.getch( );
}


/**
 * @brief
 * Get time driver methods.
 */
void rtc9701je_get_time ( Rtc9701je *rtc9701je, Rtc::Time *time )
{
	time->second = rtc9701je->byte_rcv( REGS->sec );
	time->minute = rtc9701je->byte_rcv( REGS->min );
	time->hour   = rtc9701je->byte_rcv( REGS->hour );
}


/**
 * @brief
 * Set time driver methods.
 */
void rtc9701je_set_time ( Rtc9701je *rtc9701je, const Rtc::Time *time )
{
	rtc9701je->byte_snd( REGS->sec,  time->second );
	rtc9701je->byte_snd( REGS->min,  time->minute );
	rtc9701je->byte_snd( REGS->hour, time->hour   );
}


/**
 * @brief
 * Get date driver methods.
 */
void rtc9701je_get_date ( Rtc9701je *rtc9701je, Rtc::Date *date )
{
	date->day   = rtc9701je->byte_rcv( REGS->day );
	date->month = rtc9701je->byte_rcv( REGS->month );
	date->year  = rtc9701je->byte_rcv( REGS->year );
}


/**
 * @brief
 * Set date driver methods.
 */
void rtc9701je_set_date ( Rtc9701je *rtc9701je, const Rtc::Date *date )
{
	rtc9701je->byte_snd( REGS->day,   date->day   );
	rtc9701je->byte_snd( REGS->month, date->month );
	rtc9701je->byte_snd( REGS->year,  date->year  );
}


/**
 * @brief
 * RRTC-9701JE device descriptor consctructor.
 *
 * @param fp_port        : [in] Point to device IO object.
 * @param module_address : [in] Package address (optional).
 */
Rtc9701je::Rtc9701je ( hal::Port *rtc_port ) :
	Rtc(rtc_port),
	io_(rtc_port)
{
	get_time_ = reinterpret_cast<void (*)(void*, Rtc::Time*)>(rtc9701je_get_time);
	set_time_ = reinterpret_cast<void (*)(void*, const Rtc::Time*)>(rtc9701je_set_time);
	get_date_ = reinterpret_cast<void (*)(void*, Rtc::Date*)>(rtc9701je_get_date);
	set_date_ = reinterpret_cast<void (*)(void*, const Rtc::Date*)>(rtc9701je_set_date);
}

} /* namespace dev */
