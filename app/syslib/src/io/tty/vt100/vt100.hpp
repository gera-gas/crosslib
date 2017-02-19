#ifndef VT100_HPP_
#define VT100_HPP_
/**
 * @file     vt100.hpp
 * @brief    VT-100 IO service.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "tty.h"
 */
#include <stddef.h>

namespace sys {

/**
 * General TTY type.
 */
class VT100 : public TTY {
public:
	/**
	 * @brief
	 * VT100 class constructor.
	 *
	 * @param [in] : address of IO object.
	 */
	VT100( InOut *io );

private:
	/*
	 * VT100 ESC sequences.
	 */
	const char *vt100_esc_cursor_up_;
	const char *vt100_esc_cursor_down_;
	const char *vt100_esc_cursor_left_;
	const char *vt100_esc_cursor_right_;
	const char *vt100_esc_cursor_home_;
	const char *vt100_esc_cursor_off_;
	const char *vt100_esc_cursor_on_;
	const char *vt100_esc_clear_screen_;
	const char *vt100_esc_clear_char_;
	const char *vt100_esc_clear_string_;
	const char *vt100_esc_outmode_normal_;
	const char *vt100_esc_outmode_reverse_;
	const char *vt100_esc_outmode_underline_;
	const char *vt100_esc_status_on_;
	const char *vt100_esc_status_off_;
	const char *vt100_esc_charcode_;

	/*
	 * VT100 Emplementation SND/RCV methods.
	 */
	friend size_t vt100_rcv ( void *ctx, char *buffer, size_t bufsize );
	friend void   vt100_snd ( void *ctx, const char *esc, const char *param );
};

} /* namespace sys */

#endif  /* VT100_HPP_ */
