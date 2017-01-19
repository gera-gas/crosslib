/**
 *  @file     strcat.c
 *  @brief    Single char string functions.
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
char* strncat ( char *pdst, const char *psrc, size_t size )
{
	register unsigned int  id, is;


	id = strlen( pdst );

	for( is = 0; psrc[is]; is++, id++ )
	{
		if( is >= size )
			break;

		pdst[id] = psrc[is];
	}
	pdst[id] = '\0';

	
	return  pdst;
}
