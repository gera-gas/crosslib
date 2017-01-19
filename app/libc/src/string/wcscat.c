/**
 *  @file     wcscat.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Concatinate "pdst" with "psrc" and save to "pdst".
 *
 *  @param  pdst : [in/out] destination address.
 *  @param  psrc : [in] source address.
 *
 *  @return
 *  Point to destination address (pdst).
 */
wchar_t* wcscat ( wchar_t *pdst, const wchar_t *psrc )
{
	register unsigned int  id, is;


	id = wcslen( pdst );

	for( is = 0; psrc[is]; is++, id++ )
		pdst[id] = psrc[is];

	pdst[id] = '\0';

	
	return  pdst;
}
