/**
 *  @file    heap.c
 *  @brief   Функции динамического распределения памяти.
 *  @author  Герасимов А.С.
 *  @date    2012.09.24 00:00:09 +0400
 */
#include <stddef.h>
#include "malloc.h"

memmap_t heap_map = { 0 };

/**
 *  @brief
 *  Функция инициализации кучи, т.е. выделяет под кучу указанное
 *  в параметрах адресное пространство.
 *
 *  @param  start : [in] начальный адрес памяти.
 *  @param  end   : [in] конечный адрес памяти.
 */
void heap_init ( void *start, void *end )
{
	heap_map.cachelist = 0;
	heap_map.start     = start;
	heap_map.ptr       = start;
	heap_map.end       = end;
}


/**
 *  @brief
 *  Выделение блока памяти в куче.
 */
void* malloc ( size_t size )
{
	return  map_alloc( &heap_map, size, MF_ALIGN );
}


/**
 *  @brief
 *  Выделение блока памяти в куче с
 *  предварительной очичткой блока (чистое выделение).
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
