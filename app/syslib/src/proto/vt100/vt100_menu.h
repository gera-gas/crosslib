#ifndef VT100_MENU_H_
#define VT100_MENU_H_
/**
 * @file     vt100_menu.h
 * @brief    Export VT-100 menu service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 */
#include <stddef.h>

/**
 * VT-100 menu handler result type.
 */
typedef enum {
	VT100_ITEM_RESULT_STAY,
	VT100_ITEM_RESULT_EXIT
} vt100_item_result_t;

/**
 * VT-100 Menu item type.
 */
typedef struct vt100_menuitem_st {
	struct vt100_menuitem_st *next;
	/*
	 * Item name.
	 */
	char  *name;

	/*
	 * Item handler function.
	 */
	vt100_item_result_t (*handler)( void );

} vt100_menuitem_t;

/**
 * @brief 
 * Create handler function for menu item.
 *
 * @param name_ : [in] function name.
 */
#define VT100_MENUITEM_FUNC( name_ )  vt100_item_result_t name_ ( void )

/**
 * VT-100 Menu context type.
 */
typedef struct {
	/*
	 * VT-100 context structure.
	 */
	vt100ctx_t *vt100ctx;

	/*
	 *  String with menu title.
	 */
	char *title;

	/*
	 * Point to array with menu items.
	 * Array should be endian of zero.
	 */
	vt100_menuitem_t *items;

	/*
	 * Point to current item.
	 */
	vt100_menuitem_t *current_item;

} vt100ctx_menu_t;

#ifdef __cplusplus
extern "C" {
#endif

void vt100_menu_start ( vt100ctx_menu_t *menu_ctx );

#ifdef __cplusplus
}
#endif

#endif  /* VT100_MENU_H_ */
