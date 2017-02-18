/**
 * @file     vt100.cpp
 * @brief    VT-100 IO service.
 * @author   Gerasimov A.S.
 * @note
 */
#include <stddef.h>
#include "hal/hal.hpp"
#include "io/io.hpp"
#include "io/tty/tty.hpp"
#include "io/tty/vt100/vt100.hpp"

namespace sys {

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
size_t vt100_rcv ( void *ctx, char *buffer, size_t bufsize )
{
	char   c;
	size_t len;

	VT100 *tty = reinterpret_cast<VT100*>(ctx);

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
void vt100_snd ( void *ctx, const char *esc, const char *param )
{
	VT100 *tty = reinterpret_cast<VT100*>(ctx);

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
VT100::VT100( InOut *io ) :
	TTY(io),
	/*
	 * VT100 ESC sequences definition.
	 */
	vt100_esc_cursor_up_("\x1B\x5B\x41"),
	vt100_esc_cursor_down_("\x1B\x5B\x42"),
	vt100_esc_cursor_left_("\x1B\x5B\x44"),
	vt100_esc_cursor_right_("\x1B\x5B\x43"),
	vt100_esc_cursor_home_("\x1B\x5B\x48"),
	vt100_esc_cursor_off_("\x1B\x5B\x3F\x32\x35\x6C"),
	vt100_esc_cursor_on_("\x1B\x5B\x3F\x32\x35\x68"),
	vt100_esc_clear_screen_("\x1B\x5B\x32\x4A"),
	vt100_esc_clear_char_ ("\x1B\x5B\x58"),
	vt100_esc_clear_string_("\x1B\x5B\x4B"),
	vt100_esc_outmode_normal_("\x1B\x5B\x30\x6D"),
	vt100_esc_outmode_reverse_("\x1B\x5B\x37m"),
	vt100_esc_outmode_underline_("\x1B\x5B\x30\x3B\x34\x6D"),
	vt100_esc_status_on_("\x1B\x5B\x31\x61"),
	vt100_esc_status_off_("\x1B\x5B\x30\x61"),
	vt100_esc_charcode_ ("\x1B\x5B\x67")
{
	/*
	 * Redefine public ESC to VT100 ESC sequences.
	 */
	esc_cursor_up         = vt100_esc_cursor_up_;
	esc_cursor_down       = vt100_esc_cursor_down_;
	esc_cursor_left       = vt100_esc_cursor_left_;
	esc_cursor_right      = vt100_esc_cursor_right_;
	esc_cursor_home       = vt100_esc_cursor_home_;
	esc_cursor_off        = vt100_esc_cursor_off_;
	esc_cursor_on         = vt100_esc_cursor_on_;
	esc_clear_screen      = vt100_esc_clear_screen_;
	esc_clear_char        = vt100_esc_clear_char_;
	esc_clear_string      = vt100_esc_clear_string_;
	esc_outmode_normal    = vt100_esc_outmode_normal_;
	esc_outmode_reverse   = vt100_esc_outmode_reverse_;
	esc_outmode_underline = vt100_esc_outmode_underline_;
	esc_status_on         = vt100_esc_status_on_;
	esc_status_off        = vt100_esc_status_off_;
	esc_charcode          = vt100_esc_charcode_;

	/*
	 * Redefine public TTY methods to VT100 methods.
	 */
	rcv_ = vt100_rcv;
	snd_ = vt100_snd;
}

} /* namespace sys */
