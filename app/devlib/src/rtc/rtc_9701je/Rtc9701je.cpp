/**
 * @file     Rtc9701je.cpp
 * @brief    Driver for ZFM70 optical fingerprint scanner.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "gmacro.h"
#include "hal/Module.hpp"
#include "hal/Port.hpp"
#include "hal/Device.hpp"
#include "io/InOut.hpp"
#include "rtc/RtcGroupInterface.hpp"
#include "rtc/rtc_9701je/Rtc9701je.hpp"

/* Set RTC internal registers */
#define REGS  ((Rtc9701je::RegisterTable*)0)

namespace rtc {

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
	port->snd( regnum & 0x7F );
	port->snd( databyte );
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
	port->snd( regnum | 0x80 );
	port->snd( 0 );

	return port->rcv( );
}


/**
 * @brief
 * Get time driver methods.
 */
void rtc9701je_get_time ( Rtc9701je *rtc9701je, RtcGroupInterface::Time *time )
{
	time->second = rtc9701je->byte_rcv( REGS->sec );
	time->minute = rtc9701je->byte_rcv( REGS->min );
	time->hour   = rtc9701je->byte_rcv( REGS->hour );
}


/**
 * @brief
 * Set time driver methods.
 */
void rtc9701je_set_time ( Rtc9701je *rtc9701je, const RtcGroupInterface::Time *time )
{
	rtc9701je->byte_snd( REGS->sec,  time->second );
	rtc9701je->byte_snd( REGS->min,  time->minute );
	rtc9701je->byte_snd( REGS->hour, time->hour   );
}


/**
 * @brief
 * Get date driver methods.
 */
void rtc9701je_get_date ( Rtc9701je *rtc9701je, RtcGroupInterface::Date *date )
{
	date->day   = rtc9701je->byte_rcv( REGS->day );
	date->month = rtc9701je->byte_rcv( REGS->month );
	date->year  = rtc9701je->byte_rcv( REGS->year );
}


/**
 * @brief
 * Set date driver methods.
 */
void rtc9701je_set_date ( Rtc9701je *rtc9701je, const RtcGroupInterface::Date *date )
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
	RtcGroupInterface(rtc_port)
{
	virtual_get_time = reinterpret_cast<void (*)(void*, RtcGroupInterface::Time*)>(rtc9701je_get_time);
	virtual_set_time = reinterpret_cast<void (*)(void*, const RtcGroupInterface::Time*)>(rtc9701je_set_time);
	virtual_get_date = reinterpret_cast<void (*)(void*, RtcGroupInterface::Date*)>(rtc9701je_get_date);
	virtual_set_date = reinterpret_cast<void (*)(void*, const RtcGroupInterface::Date*)>(rtc9701je_set_date);
}

} /* namespace rtc */
