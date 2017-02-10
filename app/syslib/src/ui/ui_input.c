/**
 * @file     ui_input.c
 * @brief    User interface (UI) input handlers.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include <stdbool.h>
#include "hal/hal.h"
#include "buffer/buffer.h"
#include "io/io.h"
#include "io/tty/tty.h"
#include "regexp/regexp.h"
#include "ui/ui_input.h"
#if defined(USE_BUILTIN_LIBC)
#include <memory.h>
#include <string.h>
#include <stdio.h>
#else
#include "memory/memory.h"
#include "string/string.h"
#include "stdio/stdio.h"
#endif


/**
 * @brief
 * Manager for user input.
 *
 * @param input_ctx : [in] point to input context structure.
 * @param input_num : [in] item numbers of input context structure.
 */
void ui_input ( ui_input_t *input_ctx, size_t input_num )
{
	size_t i;
	size_t len;
	char buffer[40];


	ui_inparam_t *param = input_ctx->inparam;
	/*
	 * Clear screen, enable cursor and
	 * set NORMAL mode output.
	 */
	input_ctx->tty->m_snd( input_ctx->tty, input_ctx->tty->esc_clear_screen,   NULL );
	input_ctx->tty->m_snd( input_ctx->tty, input_ctx->tty->esc_cursor_home,    NULL );
	input_ctx->tty->m_snd( input_ctx->tty, input_ctx->tty->esc_cursor_on,      NULL );
	input_ctx->tty->m_snd( input_ctx->tty, input_ctx->tty->esc_outmode_normal, NULL );

	/*
	 * Display all items.
	 */
	for( i = 0; i < input_num; i++ )
	{
		tty_cursor_set( input_ctx->tty, 1, i+1 );

		if( param[i].startinfo )
		{
			input_ctx->tty->m_snd( input_ctx->tty, param[i].startinfo, NULL );
		}
		/*
		 * If last char is not zero (buffer is dirty),
		 * clear buffer for addition security memory.
		 */
		if( param[i].buffer[ param[i].bufsize - 1 ] != '\0' )
		{
			memset( param[i].buffer, 0, param[i].bufsize );
		}

		/*
		 * If parameter already set to default value,
		 * so output this.
		 */
		len = strlen(param[i].buffer);

		if( len > 0 )
		{
			input_ctx->tty->m_snd( input_ctx->tty, param[i].buffer, NULL );
		}
	}

	/*
	 * Set cursor position to first argument.
	 */
	tty_cursor_set( input_ctx->tty, strlen(param[0].startinfo) + strlen(param[0].buffer) + 1, 1 );

	/*
	 * Handling all user inputs.
	 */
	for( i = 0; ; )
	{
		len = input_ctx->tty->m_rcv( input_ctx->tty, buffer, sizeof(buffer) - 1 );
		
		if( !len ) {
			continue;
		}
		buffer[ len ] = '\0';

		/*
		 * Cursor up (up arrow).
		 */
		if( !strcmp(buffer, input_ctx->tty->esc_cursor_up) )
		{
			if( i == 0 )
			{
				i = input_num - 1;
			}
			else
			{
				i--;
			}

			tty_cursor_set( input_ctx->tty, strlen(param[i].startinfo) + strlen(param[i].buffer) + 1, i+1 );
		}
		/*
		 * Cursor down (down arrow).
		 */
		else if( !strcmp(buffer, input_ctx->tty->esc_cursor_down) )
		{
			i++;

			if( i >= input_num )
			{
				i = 0;
			}

			tty_cursor_set( input_ctx->tty, strlen(param[i].startinfo) + strlen(param[i].buffer) + 1, i+1 );
		}
		/*
		 * Single key.
		 */
		else if( strlen(buffer) == 1 )
		{
			char keycode = buffer[len - 1];
			/*
			 * ENTER:
			 * Set end of string end goto next item.
			 */
			if( keycode == input_ctx->tty->enter )
			{
				len = strlen( param[i].buffer );

				param[i].buffer[ len ] = '\0';

				i++;

				if( i >= input_num )
				{
					return;
				}

				tty_cursor_set( input_ctx->tty, strlen(param[i].startinfo) + strlen(param[i].buffer) + 1, i+1 );
			}
			/*
			 * BACKSPACE:
			 * Delete last input char to buffer.
			 */
			else if( keycode == input_ctx->tty->backspace )
			{
				len = strlen( param[i].buffer );

				if( len )
				{
					input_ctx->tty->m_snd( input_ctx->tty, input_ctx->tty->esc_cursor_left, NULL );
					input_ctx->tty->m_snd( input_ctx->tty, input_ctx->tty->esc_clear_char,  NULL );

					param[i].buffer[ len - 1 ] = '\0';
				}
			}
			/*
			 * ANY:
			 * Save char to buffer.
			 */
			else
			{
				/*
				 * Check char on filter rules if rules was set.
				 */
				if( fstring_match_chr( &param[i].filter, keycode ) )
				{
					len = strlen( param[i].buffer );

					if( len < (param[i].bufsize - 1) )
					{
						param[i].buffer[ len+0 ] = keycode;
						param[i].buffer[ len+1 ] = '\0';

						input_ctx->tty->m_snd( input_ctx->tty, buffer, NULL );
					}

				}
			}
		}
	}
}
