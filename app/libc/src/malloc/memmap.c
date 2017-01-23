/**
 *  @file    memmap.c
 *  @brief   Functions dynamic memory allocation.
 *  @author  Gerasimov A.S., Sudak I.
 *  @date    2013-04-12 14:45:55 +0400
 */
#include <stddef.h>
#include "typedef.h"
#include "math/math.h"
#include "malloc/malloc.h"


/**
 *  @brief   �������� ���� ������ �� ��������� � ����������
 *           ������� ������ (memory map).
 *
 *  @param   map   : [in] ������� �������������� ������.
 *           size  : [in] ������ �������������� �����.
 *           align : [in] ������������ �������� ������� �����.
 *
 *  @return  ���������� ����� ����������� �����.
 */
void* memmap_block ( memmap_t *mmap, size_t size, unsigned int align )
{
	void  *m;
	void  *e;

	m = (void *)(ALIGNe_HI( mmap->ptr, align ));
	e = (void *)(m + size);

	if( (e > mmap->start) && (e <= mmap->end) )
	{
		mmap->ptr = e;
		return  m;
	}

	return  (void *)0;
}
