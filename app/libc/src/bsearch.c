/**
 *  @file     bsearch.c
 *  @brief    Двоичный поиск.
 *  @author   Судак И.
 *  @date     28.07.2012
 */
#include <stddef.h>
#include "stdlib.h"

/**
 * bsearch - выполняет двоичный поиск в отсортированном массиве
 *
 * @param key	 искомый элемент
 * @param base0	 адрес массива
 * @param nmemb	 число элементов в массиве
 * @param size	 размер элемента
 * @param compar функция для сравнения элементов
 *
 * @return
 *	Адрес искомого элемента или NULL если он не найден.
 */
void *bsearch ( const void *key, const void *base0, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *) )
{
	const char *base = base0;
	int lim, cmp;
	const void *p;

	for (lim = nmemb; lim != 0; lim >>= 1) {
		p = base + (lim >> 1) * size;
		cmp = (*compar)(key, p);
		if (cmp == 0)
			return (void *)p;
		if (cmp > 0) {  /* key > p: move right */
			base = (char *)p + size;
			lim--;
		} /* else move left */
	}

	return NULL;
}
