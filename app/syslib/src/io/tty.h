#ifndef TTY_H_
#define TTY_H_
/**
 * @file     tty.h
 * @brief    Base display manipulation functions.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "io.h"
 */
#include <stddef.h>

/**
 * Describe X,Y coordinate position.
 */
typedef struct coord_st {
	size_t x;
	size_t y;
} coord_t;

/**
 * Base display manipulation functions.
 */
typedef struct tty_st {
	/*
	 * Point to IO context.
	 */
	ioctx_t *ioctx;

	/*
	 * New line chars, for example: "\n" or "\n\r".
	 */
	const char *newline;

	/*
	 * Single char control keys.
	 */
	int enter;
	int tab;
	int backspace;

	/*
	 * ESC control sequences.
	 */
	const char *esc_cursor_up;
	const char *esc_cursor_down;
	const char *esc_cursor_left;
	const char *esc_cursor_right;
	const char *esc_cursor_home;
	const char *esc_cursor_off;
	const char *esc_cursor_on;

	const char *esc_clear_screen;
	const char *esc_clear_char;
	const char *esc_clear_string;

	const char *esc_outmode_normal;
	const char *esc_outmode_reverse;
	const char *esc_outmode_underline;

	const char *esc_status_on;
	const char *esc_status_off;

	const char *esc_charcode;

	/*
	 * Point to send/receive methods.
	 */
	size_t (*m_rcv) ( const struct tty_st *, char *, size_t );
	void   (*m_snd) ( const struct tty_st *, const char *, const char * );

} tty_t;

#endif  /* TTY_H_ */
