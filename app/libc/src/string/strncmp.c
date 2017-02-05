/**
 *  @file     strcmp.c
 *  @brief    Single char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Comparing two strings by char size limit.
 *
 *  @param  s1   : [in] first string address.
 *  @param  s2   : [in] second string address.
 *  @param  size : [in] char limits to compare.
 *
 *  @retval <0 : s1 < s2;
 *  @retval =0 : s1 = s2;
 *  @retval >0 : s1 > s2.
 */
int strncmp ( const char *s1, const char *s2, size_t size )
{
	register char  c1;
	register char  c2;


	do {
		c1 = *s1++;
		c2 = *s2++;

		if( c1 != c2 )
			return  ( c1 - c2 );
	}
	while( (c1) && (--size) );


        return 0;
}
