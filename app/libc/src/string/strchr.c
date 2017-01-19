/**
 *  @file     strchr.c
 *  @brief    Single char string functions.
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
char* strchr ( const char *pstr, char c )
{
	while( *pstr )
	{
		if( *pstr == c )
			return  (char *)pstr;
		pstr++;
	}

	return  (char *)0;
}
