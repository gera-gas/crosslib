/**
 *  @file     bsearch.c
 *  @brief    �������� �����.
 *  @author   ����� �.
 *  @date     28.07.2012
 */
#include <stddef.h>
#include "stdlib.h"

/**
 * bsearch - ��������� �������� ����� � ��������������� �������
 *
 * @param key	 ������� �������
 * @param base0	 ����� �������
 * @param nmemb	 ����� ��������� � �������
 * @param size	 ������ ��������
 * @param compar ������� ��� ��������� ���������
 *
 * @return
 *	����� �������� �������� ��� NULL ���� �� �� ������.
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
