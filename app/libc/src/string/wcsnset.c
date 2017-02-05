/**
 *  @file     wcsnset.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Set chars in 'pstr' on char value 'c'.
 *
 *  @param  pstr : [in/out] target string address.
 *  @param  c    : [in] char value.
 *  @param  numb : [in] numbers of settings char.
 *
 *  @return
 *  Point to target address of string (dst).
 */
wchar_t* wcsnset ( wchar_t *pstr, wchar_t wc, size_t size )
{
	register unsigned int  i;


	for( i = 0; i < size; i++ )
		pstr[i] = wc;

	
	return  pstr;
}
