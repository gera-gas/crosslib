/**
 *  @file     wcsnumc.c
 *  @brief    Wide char string functions.
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
size_t wcsnumc ( const wchar_t *pstr, wchar_t wc )
{
	register unsigned int  i;


	for( i = 0; *pstr; pstr++ )
	{
		if( *pstr == wc )
			i++;
	}

	return  i;
}
