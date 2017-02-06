/**
 *  @file     vt100_esc.c
 *  @brief    File with ESC sequences.
 *  @author   Gerasimov A.S.
 *  @date     08.11.2012
 */
#include "typedef.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"
#include "io/tty.h"
#include "proto/vt100/vt100.h"

/*
 * Strings with VT-100 ESC sequences.
 */
const char vt100_esc_cursor_up[]    = { 0x1B, 0x5B, 0x41, '\0' };
const char vt100_esc_cursor_down[]  = { 0x1B, 0x5B, 0x42, '\0' };
const char vt100_esc_cursor_left[]  = { 0x1B, 0x5B, 0x44, '\0' };
const char vt100_esc_cursor_right[] = { 0x1B, 0x5B, 0x43, '\0' };
const char vt100_esc_cursor_home[]  = { 0x1B, 0x5B, 0x48, '\0' };
const char vt100_esc_cursor_off[]   = { 0x1B, 0x5B, 0x3F, 0x32, 0x35, 0x6C, '\0' };
const char vt100_esc_cursor_on[]    = { 0x1B, 0x5B, 0x3F, 0x32, 0x35, 0x68, '\0' };

const char vt100_esc_clear_screen[] = { 0x1B, 0x5B, 0x32, 0x4A, '\0' };
const char vt100_esc_clear_char[]   = { 0x1B, 0x5B, 0x58, '\0' };
const char vt100_esc_clear_string[] = { 0x1B, 0x5B, 0x4B, '\0' };

const char vt100_esc_outmode_normal[]    = { 0x1B, 0x5B, 0x30, 0x6D, '\0' };
const char vt100_esc_outmode_reverse[]   = { 0x1B, 0x5B, 0x37, 'm', '\0' };
const char vt100_esc_outmode_underline[] = { 0x1B, 0x5B, 0x30, 0x3B, 0x34, 0x6D, '\0' };

const char vt100_esc_status_on[]  = { 0x1B, 0x5B, 0x31, 0x61, '\0' };
const char vt100_esc_status_off[] = { 0x1B, 0x5B, 0x30, 0x61, '\0' };

const char vt100_esc_charcode[]   = { 0x1B, 0x5B, 0x67, '\0' };
