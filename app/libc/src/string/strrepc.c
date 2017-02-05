/**
 *  @file     strrepc.c
 *  @brief    Single char string functions.
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
char* strrepc ( char *pstr, char cr, char cp )
{
	register unsigned int  i;


	for( i = 0; pstr[i]; i++ )
	{
		if( pstr[i] == cr )
			pstr[i] = cp;
	}

	
	return  pstr;
}
