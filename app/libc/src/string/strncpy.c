/**
 *  @file     strcpy.c
 *  @brief    Single char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Copy string from 'dst' to 'src' with chars limits in 'size'.
 *
 *  @param  pdst : [out] destination address..
 *  @param  psrc : [in] source address.
 *  @param  size : [in] char limits to copy.
 *
 *  @return
 *  Point to destination address (dst).
 */
char* strncpy ( char *pdst, const char *psrc, size_t size )
{
	register unsigned int  i;


	for( i = 0; psrc[i]; i++ )
	{
		if( i >= size )
			break;

		pdst[i] = psrc[i];
	}
	pdst[i] = '\0';

	
	return  pdst;
}
