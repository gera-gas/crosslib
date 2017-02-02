#ifndef VT100_H_
#define VT100_H_
/**
 * @file     vt100.h
 * @brief    Export VT-100 service functions.
 * @author   Gerasimov A.S.
 * @date     08.11.2012
 * @note     Implemented by PT.
 */
#include <stddef.h>
#include "typedef.h"

/**
 * VT-100 context type.
 */
typedef struct vt100_ctx_st {
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
	 * rcv/snd byte count.
	 */
	size_t count;

} vt100_ctx_t;

#ifdef __cplusplus
extern "C" {
#endif

extern pt_t pt_vt100;

#ifdef __cplusplus
}
#endif

#endif  /* VT100_H_ */
