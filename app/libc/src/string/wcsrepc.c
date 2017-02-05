/**
 *  @file     wcsrepc.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Replace all chars "cr" in "pstr" on new chars "cp".
 *
 *  @param  pstr : [in/out] target string.
 *  @param  cr   : [in] remove chars.
 *  @param  cp   : [out] paste chars.
 *
 *  @return
 *  Point to target string (dst).
 */
wchar_t* wcsrepc ( wchar_t *pstr, wchar_t wcr, wchar_t wcp )
{
	register unsigned int  i;


	for( i = 0; pstr[i]; i++ )
	{
		if( pstr[i] == wcr )
			pstr[i] = wcp;
	}

	
	return  pstr;
}
