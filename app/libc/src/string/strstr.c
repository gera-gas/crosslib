/**
 *  @file     strstr.c
 *  @brief    Single char string functions.
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
char* strstr ( const char *str, const char *psub )
{
	register unsigned int  i, sz;
	char  ch;
	char *pstr = (char *)str;


	ch = *psub;
	sz = strlen(psub);

	while( (pstr = (char *)strchr( pstr, ch )) )
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

	return  (char *)pstr;
}
