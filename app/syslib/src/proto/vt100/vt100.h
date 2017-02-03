#ifndef VT100_H_
#define VT100_H_
/**
 * @file     vt100.h
 * @brief    Export VT-100 service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 * @note     Implemented by PT.
 */
#include <stdbool.h>
#include <stddef.h>
#include "typedef.h"

#if 0
/**
 * VT-100 context type.
 */
typedef struct vt100_ioctx_st {
	/*
	 * Point to input/output device
	 * for data exchange.
	 */
	device_t *io_device;

	/*
	 * Point snd/rcv data buffer.
	 */
	buffer_t *io_buffer;

	/*
	 * Using for send addition parameters.
	 */
	char *io_param;

	/*
	 * rcv/snd byte count.
	 */
	size_t count;

} vt100_ctx_t;


/**
 * VT-100 menu single item type.
 */
typedef struct vt100_menuitem_st {
	/*
	 * String with item name.
	 */
	char *name;

	/*
	 * Point to menu PT handler.
	 */
	pt_t *handler;

} vt100_menuitem_t;

/**
 * @brief
 * Create array with menu items.
 *
 * @param name_: [in] name of item list.
 * @param ...  : [in] list of menuitem_t objects.
 */
#define VT100_MENU_ITEMS( name_, ... )\
	vt100_menuitem_t *name_[] = { __VA_ARGS__, (vt100_menuitem_t *)0 };


/**
 * VT-100 menu describe type.
 */
typedef struct vt100_menu_st {
	/*
	 * VT-100 context structure.
	 */
	vt100_ctx_t ctx;

	/*
	 * Menu current pointer. Contain offset
	 * of array item list.
	 */
	size_t current_item;

	/*
	 *  String with menu title.
	 */
	char *title;

	/*
	 * Point to array with menu items.
	 * Array should be endian of zero.
	 */
	vt100_menuitem_t *items;

} vt100_menu_t;
#endif

/**
 * VT-100 context type.
 */
typedef struct vt100ctx_st {
	ioctx_t *ioctx;
} vt100ctx_t;

#ifdef __cplusplus
extern "C" {
#endif

size_t vt100_rcv ( const vt100ctx_t *, char *, size_t );
  void vt100_snd ( const vt100ctx_t *, const char *, const char * );

#if 0
extern pt_t vt100_rcv;
extern pt_t vt100_snd;
#endif

#ifdef __cplusplus
}
#endif

/**
 * @brief
 * Receive VT-100 message.
 *
 * @param ctx_    : [in] VT-100 context (vt100_ctx_t).
 * @param buffer_ : [out] address of output (receive) buffer.
 * @param size_   : [in] size of receive buffer.
 *
 * @note
 * VT-100 context must be have a device address.
 */
#define VT100_RCV( ctx_, buffer_, size_ ) do {\
	ctx_.io_buffer->addr = (void *)(buffer_);\
	ctx_.io_buffer->size = (size_);\
	PT_WAIT( vt100_rcv, &ctx_, NULL );\
} while( 0 );

/**
 * @brief
 * Send VT-100 message.
 *
 * @param ctx_   : [in] VT-100 context (vt100_ctx_t).
 * @param esc_   : [in] String with ESC sequence.
 * @param param_ : [in] (optionally) String with parameters for ESC or <0>.
 *
 * @note
 * VT-100 context must be have a device address.
 */
#define VT100_SND( ctx_, esc_, param_ ) do {\
	ctx_.io_buffer->addr = (void *)(esc_);\
	ctx_.io_param = (param_);\
	PT_WAIT( vt100_snd, &ctx_, NULL );\
} while( 0 );

#endif  /* VT100_H_ */
