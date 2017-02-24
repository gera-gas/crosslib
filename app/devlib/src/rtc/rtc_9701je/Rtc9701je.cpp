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
	uint16  request;
	
	/*
	 * Create command 16-bit word for write.
	 * bit[0] = 1 ==> read  (LSB -> MSB)
	 * bit[0] = 0 ==> write (LSB -> MSB)
	 */
	request = ((regnum & 0x7F) << 8) | databyte;
	
	io_.putc( HPART16(request) );
	io_.putc( LPART16(request) );
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
	uint16  request;
	
	/*
	 * Create command 16-bit word for read.
	 * bit[0] = 1 ==> read  (LSB -> MSB)
	 * bit[0] = 0 ==> write (LSB -> MSB)
	 */
	request = ((regnum | 0x80) << 8) | 0;
	
	io_.putc( HPART16(request) );
	io_.putc( LPART16(request) );

	return io_.getch( );
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
	;
}

} /* namespace dev */
