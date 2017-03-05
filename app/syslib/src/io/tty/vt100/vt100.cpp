/**
 * @file     Vt100.cpp
 * @brief    VT-100 IO service.
 * @author   Gerasimov A.S.
 * @note
 */
#include <stddef.h>
#include "hal/Module.hpp"
#include "hal/Port.hpp"
#include "io/InOut.hpp"
#include "io/tty/TeleType.hpp"
#include "io/tty/vt100/Vt100.hpp"

namespace tty {

/**
 * @brief 
 * Receive message by VT-100 protocol.
 *
 * @param ctx    : [in] point to self object.
 * @param buffer : [out] address of output buffer.
 * @param size   : [in] size of output buffer.
 *
 * @return
 * Received message size in bytes.
 */
size_t vt100_rcv ( Vt100 *tty, char *buffer, size_t bufsize )
{
	char   c;
	size_t len;

	for( len = 0; ; )
	{
		c = tty->io_->getch( );

		len++;

		if( len >= bufsize )
			len = 0;

		buffer[ len - 1 ] = c;

		if( len == 1 )
		{
			if( c != 0x1B ) {
				break;
			}
		}
		else if( len == 2 )
		{
			if( c != 0x5B ) {
				break;
			}
		}
		else
		{
			if( (c - 0x40) <= (0x7E - 0x40) ) {
				break;
			}
		}
	}

	return len;
}


/**
 * @brief 
 * Send message by VT-100 protocol.
 *
 * @param ctx   : [in] point to self object.
 * @param esc   : [in] string with ESC sequence.
 * @param param : [in] string with parameters for sequence or NULL.
 */
void vt100_snd ( Vt100 *tty, const char *esc, const char *param )
{
	/*
	 * Output body of ESC string.
	 *
	 * If next char is empty, thouse last char
	 * is command of ESC sequnece.
	 */
	while( (*esc != '\0') && ((*(esc+1)) != '\0') )
	{
		tty->io_->putc( *esc++ );
	}
	
	/*
	 * Otuput parameters of ESC string.
	 */
	if( param )
	{
		tty->io_->puts( param );
	}

	/*
	 * Output command of ESC sequence.
	 */
	tty->io_->putc( *esc );
}


/**
 * @brief
 * VT100 class constructor.
 *
 * @param [in] : address of IO object.
 */
Vt100::Vt100( io::InOut *io ) :
	TeleType(io)
{
	/*
	 * Redefine public ESC to VT100 ESC sequences.
	 */
	esc_cursor_up         = "\x1B\x5B\x41";
	esc_cursor_down       = "\x1B\x5B\x42";
	esc_cursor_left       = "\x1B\x5B\x44";
	esc_cursor_right      = "\x1B\x5B\x43";
	esc_cursor_home       = "\x1B\x5B\x48";
	esc_cursor_off        = "\x1B\x5B\x3F\x32\x35\x6C";
	esc_cursor_on         = "\x1B\x5B\x3F\x32\x35\x68";
	esc_clear_screen      = "\x1B\x5B\x32\x4A";
	esc_clear_char        = "\x1B\x5B\x58";
	esc_clear_string      = "\x1B\x5B\x4B";
	esc_outmode_normal    = "\x1B\x5B\x30\x6D";
	esc_outmode_reverse   = "\x1B\x5B\x37m";
	esc_outmode_underline = "\x1B\x5B\x30\x3B\x34\x6D";
	esc_status_on         = "\x1B\x5B\x31\x61";
	esc_status_off        = "\x1B\x5B\x30\x61";
	esc_charcode          = "\x1B\x5B\x67";
	/*
	 * Redefine public TTY methods to VT100 methods.
	 */
	virtual_rcv = reinterpret_cast<rcv_t>(vt100_rcv);
	virtual_snd = reinterpret_cast<snd_t>(vt100_snd);
}

} /* namespace tty */
