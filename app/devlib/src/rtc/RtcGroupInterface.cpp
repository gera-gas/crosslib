/**
 * @file     RtcGroupInterface.cpp
 * @brief    RTC common group interface (CGI).
 * @author   Gerasimov A.S.
 * @note
 */
#include "hal/Module.hpp"
#include <stddef.h>
#include "typedef.h"
#include "hal/Port.hpp"
#include "hal/Device.hpp"
#include "io/InOut.hpp"
#include "rtc/RtcGroupInterface.hpp"

namespace dev {

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
void RtcGroupInterface::bcd2ascii ( uint8 bcd_byte, char buffer[3] )
{
	buffer[0] = HPART8(bcd_byte) + '0';
	buffer[1] = LPART8(bcd_byte) + '0';
	buffer[2] = '\0';
}


/**
 * Convert byte from BCD to decimal format.
 */
uint8 RtcGroupInterface::bcd2dec ( uint8 bcd_byte )
{
	uint8 dec_data;
	
	dec_data  = ( HPART8(bcd_byte) * 10 );
	dec_data += ( LPART8(bcd_byte) );
	
	return dec_data;
}


/**
 * Convert decimal byte to BCD format.
 */
uint8 RtcGroupInterface::dec2bcd ( uint8 dec_byte )
{
	uint8 bcd_data;

	bcd_data  = ( (( dec_byte / 10 ) << 4 ) & 0xF0 );
	bcd_data += ( (( dec_byte % 10 ) << 0 ) & 0x0F );
	
	return bcd_data;
}


/**
 * RTC consctructor.
 */
RtcGroupInterface::RtcGroupInterface ( hal::Port *rtc_port ) :
	Device(rtc_port)
{
	virtual_get_time = reinterpret_cast<void (*)(void*, RtcGroupInterface::Time*)>(dummy_trap);
	virtual_set_time = reinterpret_cast<void (*)(void*, const RtcGroupInterface::Time*)>(dummy_trap);
	virtual_get_date = reinterpret_cast<void (*)(void*, RtcGroupInterface::Date*)>(dummy_trap);
	virtual_set_date = reinterpret_cast<void (*)(void*, const RtcGroupInterface::Date*)>(dummy_trap);
}

} /* namespace dev */
