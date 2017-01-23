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
 *  @brief   ¬ыдел€ет блок пам€ти из указанной в параметрах
 *           области пам€ти (memory map).
 *
 *  @param   map   : [in] область распредел€емой пам€ти.
 *           size  : [in] размер запрашиваемого блока.
 *           align : [in] выравнивание адресной границы блока.
 *
 *  @return  ¬озвращает адрес выделенного блока.
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
