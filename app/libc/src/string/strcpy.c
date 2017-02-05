/**
 *  @file     strcpy.c
 *  @brief    Single char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Copy string from 'dst' to 'src'.
 *
 *  @param  pdst : [out] destination address..
 *  @param  psrc : [in] source address.
 *
 *  @return
 *  Point to destination address (dst).
 */
char* strcpy ( char *pdst, const char *psrc )
{
	register unsigned int  i;


	for( i = 0; psrc[i]; i++ )
		pdst[i] = psrc[i];

	pdst[i] = '\0';

	
	return  pdst;
}
