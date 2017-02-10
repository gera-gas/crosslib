/**
 * @file     vt100_menu.c
 * @brief    VT-100 menu service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 */
#include <stdbool.h>
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
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"
#include "io/tty/tty.h"
#include "ui/ui_menu.h"


/**
 * @brief
 * Calculate index of current menu item.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
size_t get_item_index ( ui_menu_t *menu_ctx )
{
	size_t i;
	ui_menuitem_t *item;

	for( i = 0, item = menu_ctx->items; item; item = item->next )
	{
		if( item == menu_ctx->current_item ) {
			break;
		}
		i++;
	}

	return i;

}


/**
 * @brief
 * Various down cursor position relative start item position (y=2).
 *
 * @param *menu_ctx : [in] point to menu context.
 * @param pos       : [in] number of down step.
 */
void down_cursor ( ui_menu_t *menu_ctx, size_t pos )
{
	char buffer[ 80 ];

	memset( buffer, 0x0, sizeof(buffer) );
	/*
	 * Convert position index to string
	 * and two lines addition.
	 */
	ultoa( pos + 2, buffer, 10 );

	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_cursor_home, NULL );
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_cursor_down, buffer );
}


/**
 * @brief
 * Indicate menu item.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
void indicate_item ( ui_menu_t *menu_ctx, const char *item_name )
{
	/*
	 * Set REVERSE output mode.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_outmode_reverse, NULL );

	/*
	 * Output item name.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, item_name, NULL );

	/*
	 * Set NORMAL output mode.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_outmode_normal, NULL );
}


/**
 * @brief
 * Display menu from parameters context.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
void display_menu ( ui_menu_t *menu_ctx )
{
	ui_menuitem_t *item;

	/*
	 * Clear screen, disable cursor and
	 * set NORMAL mode output.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_clear_screen,   NULL );
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_cursor_home,    NULL );
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_cursor_off,     NULL );
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_outmode_normal, NULL );
	
	/*
	 * Display menu title.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->title, NULL );

	/*
	 * Skip two lines.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->newline, NULL );
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->newline, NULL );

	/*
	 * Display each item.
	 */
	for( item = menu_ctx->items; item; item = item->next )
	{
		menu_ctx->tty->m_snd( menu_ctx->tty, item->name,        NULL );
		menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->newline, NULL );
	}

	/*
	 * Set cursor to current item
	 * and indicate this item position.
	 */
	down_cursor( menu_ctx, get_item_index(menu_ctx) );

	indicate_item( menu_ctx, menu_ctx->current_item->name );
}


/**
 * @brief
 * Set previous cursor position.
 *
 * @param *menu_ctx : [in/out] point to menu context.
 */
void cursor_move_up( ui_menu_t *menu_ctx )
{
	ui_menuitem_t *item;

	/*
	 * If current item top in list.
	 */
	if( menu_ctx->current_item == menu_ctx->items )
	{
		for( item = menu_ctx->items; item; item = item->next )
		{
			menu_ctx->current_item = item;
		}
		return;
	}

	/*
	 * Current item last or middle in list.
	 */
	for( item = menu_ctx->items; item; item = item->next )
	{
		if( menu_ctx->current_item == item->next )
		{
			menu_ctx->current_item = item;
			break;
		}
	}
}


/**
 * @brief
 * Set next cursor position.
 *
 * @param *menu_ctx : [in/out] point to menu context.
 */
void cursor_move_down( ui_menu_t *menu_ctx )
{
	/*
	 * If current item last in list.
	 */
	if( !menu_ctx->current_item->next )
	{
		menu_ctx->current_item = menu_ctx->items;
		return;
	}

	menu_ctx->current_item = menu_ctx->current_item->next;
}


/**
 * @brief
 * Execute cursor navigating on menu items.
 *
 * @param *menu_ctx : [in] point to menu context.
 * @param *sequence : [in] point to received ESC sequence.
 *
 * @retval ==0 : up arrow or down arrow (menu navigate keys).
 * @retval !=0 : any keys (unless menu navigate keys).
 */
void navigate_on_menu ( ui_menu_t *menu_ctx, const char *sequence )
{
	void (*move_item_point)( ui_menu_t *menu_ctx );

	/*
	 * Cursor up (up arrow).
	 */
	if( !strcmp(sequence, menu_ctx->tty->esc_cursor_up) )
	{
		move_item_point = cursor_move_up;
	}
	/*
	 * Cursor down (down arrow).
	 */
	else if( !strcmp(sequence, menu_ctx->tty->esc_cursor_down) )
	{
		move_item_point = cursor_move_down;
	}
	/*
	 * Any keys (unless menu navigate keys).
	 */
	else
	{
		return;
	}

	down_cursor( menu_ctx, get_item_index(menu_ctx) );
	/*
	 * Display current item in NORMAL mode.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->current_item->name, NULL );

	move_item_point( menu_ctx );

	down_cursor( menu_ctx, get_item_index(menu_ctx) );
	/*
	 * Indicate new item.
	 */
	indicate_item( menu_ctx, menu_ctx->current_item->name );

	return;
}


/**
 * @brief
 * Startup UI menu and manage they.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
void ui_menu_start ( ui_menu_t *menu_ctx )
{
	  char  buffer[40];
	size_t  len;

	do {
		display_menu( menu_ctx );
		/*
		 * Cycle menu handling, unless ENTER key
		 * will be not pushing.
		 */
		while( true )
		{
			len = menu_ctx->tty->m_rcv( menu_ctx->tty, buffer, sizeof(buffer) - 1 );
		
			if( !len ) {
				continue;
			}
			
			buffer[ len ] = '\0';
			/*
			 * Handling current cursor position.
			 */
			navigate_on_menu( menu_ctx, buffer );
			
			/*
			 * If put ENTER, then break cycle and goto handler item.
			 */
			if( (strlen(buffer) == 1) && (buffer[len - 1] == menu_ctx->tty->enter) ) {
				break;
			}
		}
	}
	while( menu_ctx->current_item->handler( ) != UI_MENUITEM_RESULT_EXIT );

	/*
	 * Cursor enable.
	 */
	menu_ctx->tty->m_snd( menu_ctx->tty, menu_ctx->tty->esc_cursor_on, NULL );
}
