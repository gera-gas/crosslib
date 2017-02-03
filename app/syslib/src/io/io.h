#ifndef IO_H_
#define IO_H_
/**
 * @file    io.h
 * @brief   Input/Output service functions.
 * @author  Gerasimov A.S.
 */
#include <stddef.h>

typedef struct ioctx_st {
	device_t *io_device;
	buffer_t *io_buffer;
	size_t count;
} ioctx_t;

#ifdef __cplusplus
extern "C" {
#endif

extern pt_t pt_puts;
extern pt_t pt_getch;

#ifdef __cplusplus
}
#endif

#endif  /* IO_H_ */
