/**
 * @file     vt100_menu.c
 * @brief    VT-100 menu service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 */
#include <stdbool.h>
#include <stddef.h>
#include "config.h"
#include "typedef.h"
#include "stdio/stdio.h"
#include "memory/memory.h"
#include "string/string.h"
#include "buffer/buffer.h"
#include "hal/hal.h"
#include "io/io.h"
#include "proto/vt100/vt100.h"
#include "proto/vt100/vt100_menu.h"


/**
 * @brief
 * Calculate index of current menu item.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
size_t get_item_index ( vt100ctx_menu_t *menu_ctx )
{
	size_t i;
	vt100_menuitem_t *item;

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
 * Set cursor position into menu by Y index.
 *
 * @param *menu_ctx : [in] point to menu context.
 * @param pos       : [in] index relative to first menu item.
 */
void set_curpos ( vt100ctx_menu_t *menu_ctx, size_t pos )
{
	char buffer[ 80 ];

	memset( buffer, 0x0, sizeof(buffer) );
	/*
	 * Convert position index to string
	 * and two lines addition.
	 */
	ultoa( pos + 2, buffer, 10 );

	vt100_snd( menu_ctx->vt100ctx, esc_curhome, NULL );
	vt100_snd( menu_ctx->vt100ctx, esc_curdown, buffer );
}


/**
 * @brief
 * Display menu from parameters context.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
void display_menu ( vt100ctx_menu_t *menu_ctx )
{
	vt100_menuitem_t *item;

	/*
	 * Clear screen, disable cursor and
	 * set NORMAL mode output.
	 */
	vt100_snd( menu_ctx->vt100ctx, esc_clrscr,    NULL );
	vt100_snd( menu_ctx->vt100ctx, esc_curhome,   NULL );
	vt100_snd( menu_ctx->vt100ctx, esc_cursoroff, NULL );
	vt100_snd( menu_ctx->vt100ctx, esc_normal,    NULL );

	/*
	 * Display menu title.
	 */
	vt100_snd( menu_ctx->vt100ctx, menu_ctx->title, NULL );

	/*
	 * Skip two lines.
	 */
	vt100_println( menu_ctx->vt100ctx, menu_ctx->vt100ctx->newline );

	/*
	 * Display each item.
	 */
	for( item = menu_ctx->items; item; item = item->next )
	{
		vt100_println( menu_ctx->vt100ctx, item->name );
	}

	/*
	 * Set cursor to current item
	 * and indicate this item position.
	 */
	set_curpos( menu_ctx, get_item_index( menu_ctx ) );

	vt100_snd( menu_ctx->vt100ctx, esc_revers, NULL );
	vt100_snd( menu_ctx->vt100ctx, menu_ctx->current_item->name, NULL );
	vt100_snd( menu_ctx->vt100ctx, esc_normal, NULL );
}


/**
 * @brief
 * Set previous cursor position.
 *
 * @param *menu_ctx : [in/out] point to menu context.
 */
void cursor_move_up( vt100ctx_menu_t *menu_ctx )
{
	vt100_menuitem_t *item;

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
void cursor_move_down( vt100ctx_menu_t *menu_ctx )
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
 * @param keycode   : [in] code of putted key (ESC command).
 *
 * @retval ==0 : up arrow or down arrow (menu navigate keys).
 * @retval !=0 : any keys (unless menu navigate keys).
 */
int navigate_on_menu ( vt100ctx_menu_t *menu_ctx, char keycode )
{
#define ESCCMD( esc_ ) esc_[strlen(esc_) - 1]

	/*
	 * Cursor up (up arrow).
	 */
	if( keycode == ESCCMD(esc_curup) )
	{
		set_curpos( menu_ctx, get_item_index( menu_ctx ) );
		/*
		 * Display current item in NORMAL mode.
		 */
		vt100_snd( menu_ctx->vt100ctx, menu_ctx->current_item->name, NULL );

		cursor_move_up( menu_ctx );

		set_curpos( menu_ctx, get_item_index( menu_ctx ) );
		/*
		 * Indicate new item.
		 */
		vt100_snd( menu_ctx->vt100ctx, esc_revers, NULL );
		vt100_snd( menu_ctx->vt100ctx, menu_ctx->current_item->name, NULL );
		vt100_snd( menu_ctx->vt100ctx, esc_normal, NULL );

		return 0;
	}

	/*
	 * Cursor up (up arrow).
	 */
	if( keycode == ESCCMD(esc_curdown) )
	{
		set_curpos( menu_ctx, get_item_index( menu_ctx ) );
		/*
		 * Display current item in NORMAL mode.
		 */
		vt100_snd( menu_ctx->vt100ctx, menu_ctx->current_item->name, NULL );

		cursor_move_down( menu_ctx );

		set_curpos( menu_ctx, get_item_index( menu_ctx ) );
		/*
		 * Indicate new item.
		 */
		vt100_snd( menu_ctx->vt100ctx, esc_revers, NULL );
		vt100_snd( menu_ctx->vt100ctx, menu_ctx->current_item->name, NULL );
		vt100_snd( menu_ctx->vt100ctx, esc_normal, NULL );

		return 0;
	}

	/*
	 * Any keys (unless menu navigate keys).
	 */
	return keycode;
}


/**
 * @brief
 * VT-100 menu main manager.
 *
 * @param *menu_ctx : [in] point to menu context.
 */
void vt100_menu_start ( vt100ctx_menu_t *menu_ctx )
{
	  char  buffer[40];
	size_t  len;

#define ENTER_KEY 13

	do {
		display_menu( menu_ctx );
		/*
		 * Cycle menu handling, unless ENTER key
		 * will be not pushing.
		 */
		while( true )
		{
			len = vt100_rcv( menu_ctx->vt100ctx, buffer, sizeof(buffer) );
		
			if( !len ) {
				continue;
			}
			
			if( navigate_on_menu( menu_ctx, buffer[len-1] ) == ENTER_KEY ) {
				break;
			}
		}
	}
	while( menu_ctx->current_item->handler( ) != VT100_ITEM_RESULT_EXIT );

	/*
	 * Cursor enable.
	 */
	vt100_snd( menu_ctx->vt100ctx, esc_cursoron, NULL );
}
