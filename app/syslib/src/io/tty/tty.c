/**
 * @file     tty.c
 * @brief    Base TTY manipulation functions.
 * @author   Gerasimov A.S.
 * @note
 */
#include <stddef.h>
#include <stdbool.h>
#if defined(USE_BUILTIN_LIBC)
#include <stdio.h>
#include <string.h>
#else
#include "string/string.h"
#include "stdio/stdio.h"
#endif
#include "hal/hal.h"
#include "buffer/buffer.h"
#include "io/io.h"
#include "io/tty/tty.h"


/**
 * @brief
 * Set various cursor position for TTY devices.
 *
 * @param x : [in] new value of X coordinate.
 * @param y : [in] new value of Y coordinate.
 */
void tty_cursor_set ( tty_t *tty, size_t x, size_t y )
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
	tty->m_snd( tty, tty->esc_cursor_home, buffer );
}
