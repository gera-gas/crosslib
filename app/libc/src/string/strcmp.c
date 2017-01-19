/**
 *  @file     strcmp.c
 *  @brief    Single char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Comparing two strings.
 *
 *  @param  s1 : [in] first string address.
 *  @param  s2 : [in] second string address.
 *
 *  @retval <0 : s1 < s2;
 *  @retval =0 : s1 = s2;
 *  @retval >0 : s1 > s2.
 */
int strcmp ( const char *s1, const char *s2 )
{
	register char  c1;
	register char  c2;


	do {
		c1 = *s1++;
		c2 = *s2++;

		if( c1 != c2 )
			return  ( c1 - c2 );
	}
	while( c1 );


        return 0;
}
