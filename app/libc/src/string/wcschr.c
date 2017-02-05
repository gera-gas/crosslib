/**
 *  @file     wcscat.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Searching char in string start at begin.
 *
 *  @param  pstr : [in] string address.
 *  @param  c    : [in] sought char.
 *
 *  @retval >0 : [success] point to address string with sought char.
 *  @retval =0 : [failed] sought char don't searching.
 */
wchar_t* wcschr ( const wchar_t *pstr, wchar_t wc )
{
	while( *pstr )
	{
		if( *pstr == wc )
			return  (wchar_t *)pstr;
		pstr++;
	}

	return  (wchar_t *)0;
}
