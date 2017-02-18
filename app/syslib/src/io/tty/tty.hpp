#ifndef TTY_HPP_
#define TTY_HPP_
/**
 * @file     tty.hpp
 * @brief    Base type for TTY devices.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "io.h"
 */
#include <stddef.h>

namespace sys {

/**
 * TTY API type.
 * Base (general) class for any tty specific emplementation.
 */
class TTY {
public:
	/*
	 * New line chars, for example: "\n" or "\n\r".
	 */
	const char *newline;

	/*
	 * Single char control keys.
	 */
	const int esc;
	const int enter;
	const int tab;
	const int backspace;

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

	/**
	 * @brief
	 * TTY class constructor.
	 *
	 * @param [in] : address of IO object.
	 */
	TTY( InOut *io );

	/**
	 * @brief
	 * Set various cursor position for TTY devices.
	 *
	 * @param x : [in] new value of X coordinate.
	 * @param y : [in] new value of Y coordinate.
	 *
	 * @note
	 * Without parameters cursor set to home (x=1,y=1).
	 */
	void cursor_set ( size_t, size_t );

	/*
	 * Public (virtual) TTY methods.
	 */

	size_t rcv ( char *s, size_t n )
	{
		return rcv_( this, s, n );
	}

	void snd ( const char *s, const char *p=NULL )
	{
		snd_( this, s, p );
	}

protected:
	InOut *io_;
	/*
	 * Points to TTY IO methods.
	 */
	size_t (*rcv_) ( void *, char *, size_t );
	void   (*snd_) ( void *, const char *, const char * );
};

} /* namespace sys */

#endif  /* TTY_HPP_ */
