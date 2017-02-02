#ifndef BUFFER_H_
#define BUFFER_H_
/**
 *  @file     buffer.h
 *  @brief    Export data structure implementation mechnisms.
 *  @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"

/**
 * Type describes simple buffer.
 */
typedef struct buffer_st {
	 void *addr;
	size_t size;
} buffer_t;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif  /* BUFFER_H_ */
