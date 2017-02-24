/**
 * @file     UserInput.cpp
 * @brief    User interface (UI) input handlers.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include <stdbool.h>
#include "hal/Port.hpp"
#include "io/InOut.hpp"
#include "io/tty/TeleType.hpp"
#include "regexp/FilterString.hpp"
#include "buffer/Array.hpp"
#include "buffer/List.hpp"
#include "ui/UserInput.hpp"
#if defined(USE_BUILTIN_LIBC)
#include <memory.h>
#include <string.h>
#include <stdio.h>
#else
#include "memory/memory.h"
#include "string/string.h"
#include "stdio/stdio.h"
#endif

namespace ui {

/**
 * @brief
 * Start UI input procedure and manage
 * of users input.
 */
void UserInput::start ( void )
{
	size_t i;
	size_t len;
	char buffer[40];

	Parameter *param;
	/*
	 * Check parameters on exist.
	 */
	if( paramlist_.len() == 0 ) {
		return;
	}

	/*
	 * Clear screen, enable cursor and
	 * set NORMAL mode output.
	 */
	tty_->snd( tty_->esc_clear_screen );
	tty_->snd( tty_->esc_cursor_home );
	tty_->snd( tty_->esc_cursor_on );
	tty_->snd( tty_->esc_outmode_normal );

	i = 0;
	/*
	 * Display all items.
	 */
	list_foreach( param, paramlist_ )
	{
		tty_->cursor_set( 1, ++i );

		if( param->startinfo_ )
		{
			tty_->snd( param->startinfo_ );
		}

		/*
		 * If last char is not zero (buffer is dirty),
		 * clear buffer for addition security memory.
		 */
		if( param->buffer_[ param->bufsize_ - 1 ] != '\0' )
		{
			memset( param->buffer_, 0, param->bufsize_ );
		}

		/*
		 * If parameter already set to default value,
		 * so output this.
		 */
		len = strlen(param->buffer_);

		if( len > 0 )
		{
			tty_->snd( param->buffer_ );
		}
	}
	
	param = paramlist_.first();
	/*
	 * Set cursor position to first argument.
	 */
	tty_->cursor_set( strlen(param->startinfo_) + strlen(param->buffer_) + 1, 1 );

	/*
	 * Handling all user inputs.
	 * Variable <i> play role of Y position into cycle.
	 */
	for( i = 1; ; )
	{
		len = tty_->rcv( buffer, sizeof(buffer) - 1 );
		
		if( !len ) {
			continue;
		}
		buffer[ len ] = '\0';

		/*
		 * Cursor up (up arrow).
		 */
		if( !strcmp(buffer, tty_->esc_cursor_up) )
		{
			i--;
			param = param->prev;

			if( param == paramlist_.head() )
			{
				param = paramlist_.last();
				i = paramlist_.len();
			}

			tty_->cursor_set( strlen(param->startinfo_) + strlen(param->buffer_) + 1, i );
		}
		/*
		 * Cursor down (down arrow).
		 */
		else if( !strcmp(buffer, tty_->esc_cursor_down) )
		{
			i++;
			param = param->next;

			if( param == paramlist_.head() )
			{
				param = paramlist_.first();
				i = 1;
			}

			tty_->cursor_set( strlen(param->startinfo_) + strlen(param->buffer_) + 1, i );
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
			if( keycode == tty_->enter )
			{
				len = strlen( param->buffer_ );

				param->buffer_[ len ] = '\0';

				i++;
				param = param->next;

				if( param == paramlist_.head() )
				{
					return;
				}

				tty_->cursor_set( strlen(param->startinfo_) + strlen(param->buffer_) + 1, i );
			}
			/*
			 * BACKSPACE:
			 * Delete last input char to buffer.
			 */
			else if( keycode == tty_->backspace )
			{
				len = strlen( param->buffer_ );

				if( len )
				{
					tty_->snd( tty_->esc_cursor_left );
					tty_->snd( tty_->esc_clear_char );

					param->buffer_[ len - 1 ] = '\0';
				}
			}
			/*
			 * ANY:
			 * Save char to buffer.
			 */
			else
			{
				bool enable_input = true;
				/*
				 * Check char on filter rules if rules was set.
				 */
				if( param->filter_ )
				{
					if( !param->filter_->match(keycode) )
					{
						enable_input = false;
					}
				}

				if( enable_input )
				{
					len = strlen( param->buffer_ );

					if( len < (param->bufsize_ - 1) )
					{
						param->buffer_[ len+0 ] = keycode;
						param->buffer_[ len+1 ] = '\0';
                                        
						tty_->snd( buffer );
					}
				}
			}
		}
	} /* for */
}


/**
 * @brief
 * Create object of UI input parameters.
 *
 * @param buffer    : [out] address of output buffer.
 * @param bufsize   : [in] output buffer size in sizeof(char).
 * @param startinfo : [in] point to string with preliminary input information.
 * @param filter    : [in] point to filter object or NULL (optional).
 */
UserInput::Parameter::Parameter ( char *buffer, size_t bufsize, const char *startinfo, regexp::FilterString *filter=NULL ) :
	prev(NULL), next(NULL),
	buffer_(buffer), bufsize_(bufsize),
	startinfo_(startinfo),
	filter_(filter)
{ }

} /* namespace ui */
