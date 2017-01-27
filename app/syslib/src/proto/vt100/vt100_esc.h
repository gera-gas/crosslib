#ifndef  VT100_ESC_H_
#define  VT100_ESC_H_

#ifdef __cplusplus
extern "C" {
#endif

extern char esc_curup[];
extern char esc_curdown[];
extern char esc_curleft[];
extern char esc_curright[];

extern char esc_curhome[];
extern char esc_clrscr[];
extern char esc_clrchar[];
extern char esc_clrstr[];

extern char esc_statuson[];
extern char esc_statusoff[];

extern char esc_cursoron[];
extern char esc_cursoroff[];

extern char esc_charcode[];
extern char esc_normal[];
extern char esc_linedown[];
extern char esc_revers[];

#ifdef __cplusplus
}
#endif

#endif  /*  VT100_ESC_H_  */
