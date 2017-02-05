/**
 *  @file     strnset.c
 *  @brief    Single char string functions.
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
char* strnset ( char *pstr, char c, size_t numb )
{
	register unsigned int  i;


	for( i = 0; i < numb; i++ )
		pstr[i] = c;

	
	return  pstr;
}
