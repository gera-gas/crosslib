#ifndef BUFFER_H_
#define BUFFER_H_
/**
 *  @file     buffer.h
 *  @brief    Export data structure implementation mechanisms.
 *  @author   Gerasimov A.S.
 */
#include <stddef.h>

/**
 * Type describes simple buffer.
 */
typedef struct buffer_st {
	 void *addr;
	size_t size;
} buffer_t;

#endif  /* BUFFER_H_ */
