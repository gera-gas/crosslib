/**
 *  @file     strrev.c
 *  @brief    Single char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Make a reverse string "123"->"321".
 *
 *  @param  pstr : [in/out] target string.
 *
 *  @return
 *  Point of target string.
 */
char* strrev ( char *pstr )
{
	register unsigned int  i;
	register unsigned int  j;
	        unsigned char  c;
	

	j = strlen( pstr ) - 1;

	for( i = 0; i < j; i++, j-- )
	{
		c = pstr[i];
		pstr[i] = pstr[j];
		pstr[j] = c;
	}

	return  pstr;
}
