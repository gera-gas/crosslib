/**
 *  @file    heap.c
 *  @brief   Functions dynamic memory allocation.
 *  @author  Gerasimov A.S.
 *  @date    2012.09.24 00:00:09 +0400
 */
#include <stddef.h>
#include "memory/memory.h"
#include "malloc/malloc.h"

memmap_t heap_map = { 0 };

/**
 *  @brief
 *  Set memory region as heap, to use for memory allocation.
 *
 *  @param  start : [in] memory address of begin region.
 *  @param  end   : [in] memory address of end region.
 */
void heap_init ( const void *start, const void *end )
{
	heap_map.cachelist = 0;
	heap_map.start     = (void *)start;
	heap_map.ptr       = (void *)start;
	heap_map.end       = (void *)end;
}


/**
 *  @brief
 *  Allocate memory area from heap.
 *
 *  @param size : [in] size memory area.
 *
 *  @retval >0 : [success] base address of allocated memory.
 *  @retval =0 : [failed] bad allocate.
 */
void* malloc ( size_t size )
{
	return  map_alloc( &heap_map, size, MF_ALIGN );
}


/**
 *  @brief
 *  Clear allocate memory area from heap.
 *
 *  @param num  : [in] block numbers.
 *  @param size : [in] block size.
 *
 *  @retval >0 : [success] base address of allocated memory.
 *  @retval =0 : [failed] bad allocate.
 *
 *  @example
 *  int *mem = (int *)calloc( 10, sizeof(int) );
 */
void* calloc ( size_t num, size_t size )
{
	register void  *mem;
	register size_t amount = num * size;

	mem =  map_alloc( &heap_map, amount, MF_ALIGN );

	if( mem )
		memset( mem, 0, amount );

	return  mem;
}
