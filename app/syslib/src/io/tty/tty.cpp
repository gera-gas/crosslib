/**
 * @file     tty.c
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
#include "hal/hal.hpp"
#include "io/io.hpp"
#include "io/tty/tty.hpp"

namespace sys {

/**
 * @brief
 * TTY class constructor.
 *
 * @param [in] : address of IO object.
 */
TTY::TTY( InOut *io ) :
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
	snd_ = reinterpret_cast<void (*)(void *, const char *, const char *)>(dummy_loop);
	rcv_ = reinterpret_cast<size_t (*)(void *, char *, size_t)>(dummy_loop);
}


/**
 * @brief
 * Set various cursor position for TTY devices.
 *
 * @param x : [in] new value of X coordinate.
 * @param y : [in] new value of Y coordinate.
 */
void TTY::cursor_set ( size_t x=1, size_t y=1 )
{
	size_t i;
	char buffer[80];

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

} /* namespace sys */
