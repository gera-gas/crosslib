/**
 *  @file    heap.c
 *  @brief   ������� ������������� ������������� ������.
 *  @author  ��������� �.�.
 *  @date    2012.09.24 00:00:09 +0400
 */
#include <stddef.h>
#include "malloc.h"

memmap_t heap_map = { 0 };

/**
 *  @brief
 *  ������� ������������� ����, �.�. �������� ��� ���� ���������
 *  � ���������� �������� ������������.
 *
 *  @param  start : [in] ��������� ����� ������.
 *  @param  end   : [in] �������� ����� ������.
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
 *  ��������� ����� ������ � ����.
 */
void* malloc ( size_t size )
{
	return  map_alloc( &heap_map, size, MF_ALIGN );
}


/**
 *  @brief
 *  ��������� ����� ������ � ���� �
 *  ��������������� �������� ����� (������ ���������).
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
