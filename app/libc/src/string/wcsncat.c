/**
 *  @file     wcsncat.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Concatinate n (size) chars in "pdst" string with "psrc" and save to "pdst".
 *
 *  @param  pdst : [in/out] destination address.
 *  @param  psrc : [in] source address.
 *  @param  size : [in] chars limit to concatinate.
 *
 *  @return
 *  Point to destination address (pdst).
 */
wchar_t* wcsncat ( wchar_t *pdst, const wchar_t *psrc, size_t size )
{
	register unsigned int  id, is;


	id = wcslen( pdst );

	for( is = 0; psrc[is]; is++, id++ )
	{
		if( is >= size )
			break;

		pdst[id] = psrc[is];
	}
	pdst[id] = '\0';

	
	return  pdst;
}
