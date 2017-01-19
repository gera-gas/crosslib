/**
 *  @file     wcspbrk.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Search chars from template string 'ptmp' into target string 'pstr'.
 *
 *  @param  pstr : [in] target string.
 *  @param  ptmp : [in] template string.
 *
 *  @retval  >0 : [success] return point to address string with founded char.
 *  @retval  =0 : [failed] char don't find.
 */
wchar_t* wcspbrk ( const wchar_t *pstr, const wchar_t *ptmp )
{
	register unsigned int  i;


	while( *pstr )
	{
		for( i = 0; ptmp[i]; i++ )
		{
			if( *pstr == ptmp[i] )
				return  (wchar_t *)pstr;
		}
		pstr++;
	}

	return  (wchar_t *)0;
}
