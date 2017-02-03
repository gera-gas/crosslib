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

void io_putc  ( const ioctx_t *, char );
void io_puts  ( const ioctx_t *, const char * );
char io_getch ( const ioctx_t * );

#ifdef THREAD_H_
extern pt_t pt_puts;
extern pt_t pt_getch;
#endif

#ifdef __cplusplus
}
#endif

#endif  /* IO_H_ */
