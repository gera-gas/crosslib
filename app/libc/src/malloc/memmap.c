/**
 *  @file    memmap.c
 *  @brief   Функции динамического распределения памяти.
 *  @author  Герасимов А.С.
 *  @date    2013-04-12 14:45:55 +0400
 */
#include <stddef.h>
#include "math.h"
#include "malloc.h"


/**
 *  @brief   Выделяет блок памяти из указанной в параметрах
 *           области памяти (memory map).
 *
 *  @param   map   : [in] область распределяемой памяти.
 *           size  : [in] размер запрашиваемого блока.
 *           align : [in] выравнивание адресной границы блока.
 *
 *  @return  Возвращает адрес выделенного блока.
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
