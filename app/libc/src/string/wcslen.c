/**
 *  @file     wcslen.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Calculate string length.
 *
 *  @param  pstr : [in] address of string.
 *
 *  @return
 *  Numbers chars in string.
 */
size_t wcslen ( const wchar_t *pstr )
{
	register unsigned int  i;
	

	for( i = 0; pstr[i]; i++ )
		;
	
	return  i;
}
