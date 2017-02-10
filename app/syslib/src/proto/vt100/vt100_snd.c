/**
 * @file     vt100_rcv.c
 * @brief    VT-100 data exchange functions.
 * @author   Gerasimov A.S.
 */
#include "typedef.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"
#include "io/tty/tty.h"
#include "proto/vt100/vt100.h"

/**
 * @brief 
 * Send message by VT-100 protocol.
 *
 * @param ctx   : [in] point to IO context object.
 * @param esc   : [in] string with ESC sequence.
 * @param param : [in] string with parameters for sequence or 0.
 */
void vt100_snd ( const tty_t *tty, const char *esc, const char *param )
{
	/*
	 * Output body of ESC string.
	 *
	 * If next char is empty, thouse last char
	 * is command of ESC sequnece.
	 */
	while( (*esc != '\0') && ((*(esc+1)) != '\0') )
	{
		io_putc( tty->ioctx, *esc++ );
	}
	
	/*
	 * Otuput parameters of ESC string.
	 */
	if( param )
	{
		io_puts( tty->ioctx, param );
	}

	/*
	 * Output command of ESC sequence.
	 */
	io_putc( tty->ioctx, *esc );
}
