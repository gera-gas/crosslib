/**
 * @file     TeleType.c
 * @brief    Base TTY manipulation functions.
 * @author   Gerasimov A.S.
 * @note
 */
#include <stddef.h>
#if defined(USE_BUILTIN_LIBC)
#include <stdio.h>
#include <string.h>
#else
#include "string/string.h"
#include "stdio/stdio.h"
#endif
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Port.hpp"
#include "io/InOut.hpp"
#include "io/tty/TeleType.hpp"

namespace tty {

/**
 * @brief
 * TTY class constructor.
 *
 * @param [in] : address of IO object.
 */
TeleType::TeleType( io::InOut *io ) :
	newline("\n\r"),
	/*
	 * Single char control keys.
	 */
	esc(27),
	enter(13),
	tab(9),
	backspace(8),
	/*
	 * ESC control sequences.
	 */
	esc_cursor_up(NULL),
	esc_cursor_down(NULL),
	esc_cursor_left(NULL),
	esc_cursor_right(NULL),
	esc_cursor_home(NULL),
	esc_cursor_off(NULL),
	esc_cursor_on(NULL),
	esc_clear_screen(NULL),
	esc_clear_char(NULL),
	esc_clear_string(NULL),
	esc_outmode_normal(NULL),
	esc_outmode_reverse(NULL),
	esc_outmode_underline(NULL),
	esc_status_on(NULL),
	esc_status_off(NULL),
	esc_charcode(NULL),
	/*
	 * Set IO context.
	 */
	io_(io)
{
	virtual_snd = reinterpret_cast<snd_t>(dummy_loop);
	virtual_rcv = reinterpret_cast<rcv_t>(dummy_loop);
}


/**
 * @brief
 * Set various cursor position for TTY devices.
 *
 * @param x : [in] new value of X coordinate.
 * @param y : [in] new value of Y coordinate.
 */
void TeleType::cursor_set ( size_t x=1, size_t y=1 )
{
	size_t i;
	char buffer[80];

	if( !esc_cursor_home ) {
		return;
	}

	/*
	 * Set Y position.
	 */
	ultoa( y, buffer, 10 );

	i = strlen(buffer);
	buffer[ i ] = ';';
	/*
	 * Set Y position.
	 */
	ultoa( x, &buffer[ i + 1 ], 10 );

	/*
	 * Send command to TTY with cursor position settings.
	 */
	snd( esc_cursor_home, buffer );
}

} /* namespace tty */
