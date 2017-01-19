/**
 *  @file     strnumc.c
 *  @brief    Single char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Search char 'c' in string.
 *
 *  @param  pstr : [in] target string.
 *  @param  c    : [in] char.
 *
 *  @return
 *  Numbers of repeat char in string.
 */
size_t strnumc ( const char *pstr, char c )
{
	register unsigned int  i;


	for( i = 0; *pstr; pstr++ )
	{
		if( *pstr == c )
			i++;
	}

	return  i;
}
