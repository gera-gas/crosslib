/**
 * @file     ui_menu.cpp
 * @brief    VT-100 menu service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 */
#include <stddef.h>
#if defined(USE_BUILTIN_LIBC)
#include <memory.h>
#include <string.h>
#include <stdio.h>
#else
#include "memory/memory.h"
#include "string/string.h"
#include "stdio/stdio.h"
#endif
#include "buffer/buffer.hpp"
#include "regexp/regexp.hpp"
#include "hal/hal.hpp"
#include "io/io.hpp"
#include "io/tty/tty.hpp"
#include "ui/ui.hpp"

namespace sys {

#if 0
/**
 * @brief
 * Calculate index of current menu item.
 */
size_t UI_Menu::get_item_index ( void )
{
	size_t i;
	Item *item;

	i = 0;

	list_foreach( item, itemlist_ )
	{
		if( item == current_item_ ) {
			break;
		}
		i++;
	}

	return i;
}
#endif

/**
 * @brief
 * Various down cursor position relative start item position (y=2).
 *
 * @param pos : [in] number of down step.
 */
void UI_Menu::down_cursor ( size_t pos )
{
	char buffer[ 40 ];

	memset( buffer, 0x0, sizeof(buffer) );
	/*
	 * Convert position index to string
	 * and two lines addition.
	 */
	ultoa( pos + 2, buffer, 10 );

	tty_->snd( tty_->esc_cursor_home );
	tty_->snd( tty_->esc_cursor_down, buffer );
}


/**
 * @brief
 * Indicate menu item.
 *
 * @param item_name : [in] point to string with item name.
 */
void UI_Menu::indicate_item ( const char *item_name )
{
	/*
	 * Set REVERSE output mode.
	 */
	tty_->snd( tty_->esc_outmode_reverse );

	/*
	 * Output item name.
	 */
	tty_->snd( item_name );

	/*
	 * Set NORMAL output mode.
	 */
	tty_->snd( tty_->esc_outmode_normal );
}


/**
 * @brief
 * Display menu from parameters context.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
void UI_Menu::display_menu ( void )
{
	Item *item;

	/*
	 * Clear screen, disable cursor and
	 * set NORMAL mode output.
	 */
	tty_->snd( tty_->esc_clear_screen );
	tty_->snd( tty_->esc_cursor_home );
	tty_->snd( tty_->esc_cursor_off );
	tty_->snd( tty_->esc_outmode_normal );
	
	/*
	 * Display menu title.
	 */
	tty_->snd( title_ );

	/*
	 * Skip two lines.
	 */
	tty_->snd( tty_->newline );
	tty_->snd( tty_->newline );

	/*
	 * Display each item.
	 */
	list_foreach( item, itemlist_ )
	{
		tty_->snd( item->name );
		tty_->snd( tty_->newline );
	}

	/*
	 * Set cursor to current item
	 * and indicate this item position.
	 */
	down_cursor( current_item_idx_ );

	indicate_item( current_item_->name );
}


/**
 * @brief
 * Set previous cursor position on menu items.
 */
void item_point_move_up ( UI_Menu *pmenu )
{
	pmenu->current_item_idx_--;
	pmenu->current_item_ = pmenu->current_item_->prev;
	/*
	 * If current item top in list.
	 */
	if( pmenu->current_item_ == pmenu->itemlist_.head() )
	{
		pmenu->current_item_ = pmenu->itemlist_.last();
		pmenu->current_item_idx_ = pmenu->itemlist_.size() - 1;
	}
}


/**
 * @brief
 * Set next cursor position on menu items.
 */
void item_point_move_down ( UI_Menu *pmenu )
{
	pmenu->current_item_idx_++;
	pmenu->current_item_ = pmenu->current_item_->next;
	/*
	 * If current item top in list.
	 */
	if( pmenu->current_item_ == pmenu->itemlist_.head() )
	{
		pmenu->current_item_ = pmenu->itemlist_.first();
		pmenu->current_item_idx_ = 0;
	}
}


/**
 * @brief
 * Execute cursor navigating on menu items.
 *
 * @param *sequence : [in] point to received ESC sequence.
 */
void UI_Menu::navigate_on_menu ( const char *sequence )
{
	void (*move_item_point)( UI_Menu* );

	/*
	 * Cursor up (up arrow).
	 */
	if( !strcmp(sequence, tty_->esc_cursor_up) )
	{
		move_item_point = item_point_move_up;
	}
	/*
	 * Cursor down (down arrow).
	 */
	else if( !strcmp(sequence, tty_->esc_cursor_down) )
	{
		move_item_point = item_point_move_down;
	}
	/*
	 * Any keys (unless menu navigate keys).
	 */
	else
	{
		return;
	}

	down_cursor( current_item_idx_ );
	/*
	 * Display current item in NORMAL mode.
	 */
	tty_->snd( current_item_->name );

	move_item_point( this );

	down_cursor( current_item_idx_ );
	/*
	 * Indicate new item.
	 */
	indicate_item( current_item_->name );
}


/**
 * @brief
 * Start and manage UI menu.
 */
void UI_Menu::start ( void )
{
	  char  buffer[40];
	size_t  len;

	/*
	 * Check parameters on exist.
	 */
	if( itemlist_.size() == 0 ) {
		return;
	}

	/*
	 * Set item point to first menu item.
	 */
	if( !current_item_ )
	{
		current_item_ = itemlist_.first();
	}

	do {
		display_menu( );
		/*
		 * Cycle menu handling, unless ENTER key
		 * will be not pushing.
		 */
		while( true )
		{
			len = tty_->rcv( buffer, sizeof(buffer) - 1 );
		
			if( !len ) {
				continue;
			}
			
			buffer[ len ] = '\0';
			/*
			 * Handling current cursor position.
			 */
			navigate_on_menu( buffer );
			
			/*
			 * If put ENTER, then break cycle and goto handler item.
			 */
			if( (strlen(buffer) == 1) && (buffer[len - 1] == tty_->enter) ) {
				break;
			}
		}
	}
	while( current_item_->handler( ) != Item::HANDLER_RESULT_EXIT );

	/*
	 * Cursor enable.
	 */
	tty_->snd( tty_->esc_cursor_on );
}

} /* namespace sys */
