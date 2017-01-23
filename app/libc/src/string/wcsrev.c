/**
 *  @file     wcsrev.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>
#include "string/string.h"

/**
 *  @brief
 *  Make a reverse string "123"->"321".
 *
 *  @param  pstr : [in/out] target string.
 *
 *  @return
 *  Point of target string.
 */
wchar_t* wcsrev ( wchar_t *pstr )
{
	register unsigned int  i;
	register unsigned int  j;
			wchar_t  c;
	

	j = wcslen( pstr ) - 1;

	for( i = 0; i < j; i++, j-- )
	{
		c = pstr[i];
		pstr[i] = pstr[j];
		pstr[j] = c;
	}

	return  pstr;
}
