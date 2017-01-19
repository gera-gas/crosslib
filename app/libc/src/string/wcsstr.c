/**
 *  @file     wcsstr.c
 *  @brief    Wide char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Search substring 'psub', in target string 'pstr'.
 *
 *  @param  pstr : [in] target string.
 *  @param  psub : [in] substring.
 *
 *  @retval  >0 : [success] point to index of substring into target string.
 *  @retval  =0 : [failed] substring don't find.
 */
wchar_t* wcsstr ( const wchar_t *str, const wchar_t *psub )
{
	register unsigned int  i, sz;
        wchar_t  ch;
	wchar_t *pstr = (wchar_t *)str;


	ch = *psub;
	sz = wcslen(psub);

	while( (pstr = (wchar_t *)wcschr( pstr, ch )) )
	{
		for( i = 1; psub[i]; i++ )
		{
			if( psub[i] != pstr[i] )
				break;
		}
		if( i >= sz )
			break;
		pstr++;
	}

	return  (wchar_t *)pstr;
}
