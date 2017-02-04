#ifndef VT100_H_
#define VT100_H_
/**
 * @file     vt100.h
 * @brief    Export VT-100 IO service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 */
#include <stddef.h>

/**
 * VT-100 context type.
 */
typedef struct vt100ctx_st {
	ioctx_t *ioctx;
	   char *newline;
} vt100ctx_t;

/*
 * Strings with ESC sequences.
 */
extern char esc_curup[];      /**  cursor up     */
extern char esc_curdown[];    /**  cursor down   */
extern char esc_curleft[];    /**  cursor left   */
extern char esc_curright[];   /**  cursor right  */

extern char esc_curhome[];    /**  set cursor to start position of screen  */
extern char esc_clrscr[];     /**  clear screen  */
extern char esc_clrchar[];    /**  clear char    */
extern char esc_clrstr[];     /**  clear string  */

extern char esc_statuson[];   /**  enable output status string  */
extern char esc_statusoff[];  /**  disable output status string */

extern char esc_cursoron[];   /**  cursor enable  */
extern char esc_cursoroff[];  /**  cursor disable */

extern char esc_charcode[];   /**  out char by code          */
extern char esc_normal[];     /**  set output with underline */
extern char esc_linedown[];   /**  set string reverse mode   */
extern char esc_revers[];     /**  set a normal output       */

#ifdef __cplusplus
extern "C" {
#endif

size_t vt100_rcv     ( const vt100ctx_t *, char *, size_t );
  void vt100_snd     ( const vt100ctx_t *, const char *, const char * );
  void vt100_println ( const vt100ctx_t *, const char * );

#ifdef __cplusplus
}
#endif

#endif  /* VT100_H_ */
