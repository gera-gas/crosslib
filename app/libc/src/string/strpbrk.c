/**
 *  @file     strpbrk.c
 *  @brief    Single char string functions.
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
char* strpbrk ( const char *pstr, const char *ptmp )
{
	register unsigned int  i;


	while( *pstr )
	{
		for( i = 0; ptmp[i]; i++ )
		{
			if( *pstr == ptmp[i] )
				return  (char *)pstr;
		}
		pstr++;
	}

	return  (char *)0;
}
