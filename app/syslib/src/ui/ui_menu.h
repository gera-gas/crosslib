#ifndef UI_MENU_H_
#define UI_MENU_H_
/**
 * @file     ui_menu.h
 * @brief    Export UI menu service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 *
 * @note
 * Header dependencies:
 *
 * #include "tty.h"
 *
 * @example
 *
 * // Create IO descriptor and set device for IO.
 * ioctx_t ioctx = {
 * 	.io_device = &device_X3
 * };
 * 
 * // Create VT-100 TTY descriptor and connect IO for them.
 * VT100_TTY( iotty, &ioctx );
 * 
 * // Create handler for ITEM-1.
 * UI_MENUITEM_FUNC( item1func )
 * {
 * 	io_puts( &ioctx, " I am ITEM-1!");
 * 	io_getch( &ioctx );
 * 
 * 	return UI_MENUITEM_RESULT_STAY;
 * }
 * 
 * // Create handler for ITEM-2.
 * UI_MENUITEM_FUNC( item2func )
 * {
 * 	return UI_MENUITEM_RESULT_EXIT;
 * }
 * 
 * //Create descriptor for each item.
 * ui_menuitem_t item2 = { .next = NULL,   .name = " ITEM-2 (Exit)  ", .handler = item2func };
 * ui_menuitem_t item1 = { .next = &item2, .name = " ITEM-1 (Hello) ", .handler = item1func };
 * 
 * //Create main menu descriptor.
 * ui_menu_t mainmenu = {
 * 	.tty = &iotty,
 * 	.title = "VT-100 DEMO MENU.",
 * 	.items = &item1,
 * 	.current_item = &item1
 * };
 *
 * ui_menu_start( &mainmenu );
 */
#include <stddef.h>

/**
 * UI menu handler result type.
 */
typedef enum {
	UI_MENUITEM_RESULT_STAY,
	UI_MENUITEM_RESULT_EXIT
} ui_menuitem_result_t;

/**
 * UI Menu item type.
 */
typedef struct ui_menuitem_st {
	struct ui_menuitem_st *next;
	/*
	 * Item name.
	 */
	const char  *name;

	/*
	 * Item handler function.
	 */
	ui_menuitem_result_t (*handler)( void );

} ui_menuitem_t;

/**
 * @brief 
 * Create handler function for menu item.
 *
 * @param name_ : [in] function name.
 */
#define UI_MENUITEM_FUNC( name_ )  ui_menuitem_result_t name_ ( void )

/**
 * UI Menu context type.
 */
typedef struct {
	/*
	 * TTY context object.
	 */
	tty_t *tty;

	/*
	 *  String with menu title.
	 */
	const char *title;

	/*
	 * Point to array with menu items.
	 * Array should be endian of zero.
	 */
	ui_menuitem_t *items;

	/*
	 * Point to current item.
	 */
	ui_menuitem_t *current_item;

} ui_menu_t;

#ifdef __cplusplus
extern "C" {
#endif

void ui_menu_start ( ui_menu_t *menu_ctx );

#ifdef __cplusplus
}
#endif

#endif  /* UI_MENU_H_ */
