/**
 *  @file     esc.c
 *  @brief    File with ESC sequences.
 *  @author   Gerasimov A.S.
 *  @date     08.11.2012
 */
char esc_curup[]    = { 0x1B, 0x5B, 0x41, '\0' };  /**  cursor up     */
char esc_curdown[]  = { 0x1B, 0x5B, 0x42, '\0' };  /**  cursor down   */
char esc_curleft[]  = { 0x1B, 0x5B, 0x44, '\0' };  /**  cursor left   */
char esc_curright[] = { 0x1B, 0x5B, 0x43, '\0' };  /**  cursor right  */

char esc_curhome[] = { 0x1B, 0x5B, 0x48, '\0' };        /**  set cursor to start position of screen  */
char esc_clrscr[]  = { 0x1B, 0x5B, 0x32, 0x4A, '\0' };  /**  clear screen  */
char esc_clrchar[] = { 0x1B, 0x5B, 0x58, '\0' };        /**  clear char    */
char esc_clrstr[]  = { 0x1B, 0x5B, 0x4B, '\0' };        /**  clear string  */

char esc_statuson[]  = { 0x1B, 0x5B, 0x31, 0x61, '\0' };  /**  enable output status string  */
char esc_statusoff[] = { 0x1B, 0x5B, 0x30, 0x61, '\0' };  /**  disable output status string */

char esc_cursoron[]  = { 0x1B, 0x5B, 0x3F, 0x32, 0x35, 0x68, '\0' };  /**  cursor enable  */
char esc_cursoroff[] = { 0x1B, 0x5B, 0x3F, 0x32, 0x35, 0x6C, '\0' };  /**  cursor disable */

char esc_charcode[] = { 0x1B, 0x5B, 0x67, '\0' };                    /**  out char by code          */
char esc_linedown[] = { 0x1B, 0x5B, 0x30, 0x3B, 0x34, 0x6D, '\0' };  /**  set output with underline */
char esc_revers[]   = { 0x1B, 0x5B, 0x37, 'm', '\0' };               /**  set string reverse mode   */
char esc_normal[]   = { 0x1B, 0x5B, 0x30, 0x6D, '\0' };              /**  set a normal output       */
