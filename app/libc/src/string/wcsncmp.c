/**
 *  @file     wcsncmp.c
 *  @brief    Wide char string functions.
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
int wcsncmp ( const wchar_t *s1, const wchar_t *s2, size_t size )
{
	register wchar_t  c1;
	register wchar_t  c2;


	do {
		c1 = *s1++;
		c2 = *s2++;

		if( c1 != c2 )
			return  ( c1 - c2 );
	}
	while( (c1) && (--size) );


        return 0;
}
