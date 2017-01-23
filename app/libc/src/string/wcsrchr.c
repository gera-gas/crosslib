/**
 *  @file     wcsrchr.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>
#include "string/string.h"

/**
 *  @brief
 *  Searching char in string start at endian (revers scan).
 *
 *  @param  pstr : [in] string address.
 *  @param  c    : [in] sought char.
 *
 *  @retval >0 : [success] point to address string with sought char.
 *  @retval =0 : [failed] sought char don't searching.
 */
wchar_t* wcsrchr ( const wchar_t *pstr, wchar_t wc )
{
	unsigned int  i;


	i = wcslen( pstr );

	while( i-- )
	{
		if( pstr[i] == wc )
			return  (wchar_t *)&pstr[i];
	}

	return  (wchar_t *)0;
}
