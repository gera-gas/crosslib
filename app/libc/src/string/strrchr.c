/**
 *  @file     strrchr.c
 *  @brief    Single char string functions.
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
char* strrchr ( const char *pstr, int c )
{
	unsigned int  i;


	i = strlen( pstr );

	while( i-- )
	{
		if( pstr[i] == c )
			return  (char *)&pstr[i];
	}

	return  (char *)0;
}
