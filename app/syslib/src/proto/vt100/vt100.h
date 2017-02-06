#ifndef VT100_H_
#define VT100_H_
/**
 * @file     vt100.h
 * @brief    Export VT-100 IO service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 * @note
 * Header dependencies:
 *
 * #include "tty.h"
 */
#include <stddef.h>

/*
 * Export strings with VT-100 ESC sequences.
 */
extern const char vt100_esc_cursor_up[];          /**  cursor up     */
extern const char vt100_esc_cursor_down[];        /**  cursor down   */
extern const char vt100_esc_cursor_left[];        /**  cursor left   */
extern const char vt100_esc_cursor_right[];       /**  cursor right  */
extern const char vt100_esc_cursor_home[];        /**  set cursor to start position of screen  */
extern const char vt100_esc_cursor_off[];         /**  cursor disable */
extern const char vt100_esc_cursor_on[];          /**  cursor enable  */

extern const char vt100_esc_clear_screen[];       /**  clear screen  */
extern const char vt100_esc_clear_char[];         /**  clear char    */
extern const char vt100_esc_clear_string[];       /**  clear string  */

extern const char vt100_esc_outmode_normal[];     /**  set a normal output       */
extern const char vt100_esc_outmode_reverse[];    /**  set string reverse mode   */
extern const char vt100_esc_outmode_underline[];  /**  set output with underline */

extern const char vt100_esc_status_on[];          /**  enable output status string  */
extern const char vt100_esc_status_off[];         /**  disable output status string */

extern const char vt100_esc_charcode[];           /**  out char by code          */

#ifdef __cplusplus
extern "C" {
#endif

size_t vt100_rcv ( const tty_t *, char *, size_t );
  void vt100_snd ( const tty_t *, const char *, const char * );

#ifdef __cplusplus
}
#endif

/**
 * @brief
 * Create VT-100 tty descriptor.
 * 
 * @param name_  : [in] descriptor name.
 * @param ioctx_ : [in] point to IO context object.
 */
#define VT100_TTY( name_, ioctx_ )\
tty_t name_ = {\
	/*\
	 * Set general values.\
	 */\
	.ioctx      = (ioctx_t *)(ioctx_),\
	.newline    = "\n\r",\
	/*\
	 * Set single code control key.\
	 */\
	.enter     = 13,\
	.tab       = 9,\
	.backspace = 8,\
	/*\
	 * Set ESC sequences.\
	 */\
	.esc_cursor_up         = vt100_esc_cursor_up,\
	.esc_cursor_down       = vt100_esc_cursor_down,\
	.esc_cursor_left       = vt100_esc_cursor_left,\
	.esc_cursor_right      = vt100_esc_cursor_right,\
	.esc_cursor_home       = vt100_esc_cursor_home,\
	.esc_cursor_off        = vt100_esc_cursor_off,\
	.esc_cursor_on         = vt100_esc_cursor_on,\
	.esc_clear_screen      = vt100_esc_clear_screen,\
	.esc_clear_char        = vt100_esc_clear_char,\
	.esc_clear_string      = vt100_esc_clear_string,\
	.esc_outmode_normal    = vt100_esc_outmode_normal,\
	.esc_outmode_reverse   = vt100_esc_outmode_reverse,\
	.esc_outmode_underline = vt100_esc_outmode_underline,\
	.esc_status_on         = vt100_esc_status_on,\
	.esc_status_off        = vt100_esc_status_off,\
	.esc_charcode          = vt100_esc_charcode,\
	/*\
	 * Set methods.\
	 */\
	.m_rcv = vt100_rcv,\
	.m_snd = vt100_snd\
};

#endif  /* VT100_H_ */
