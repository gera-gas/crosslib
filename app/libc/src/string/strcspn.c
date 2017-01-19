/**
 *  @file     strcspn.c
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
 *  @retval  >0 : [success] return char index start at 0.
 *  @retval  =0 : [failed] char don't find.
 */
size_t strcspn ( const char *pstr, const char *ptmp )
{
	register unsigned int  i, j;


	for( i = 0; pstr[i]; i++ )
	{
		for( j = 0; ptmp[j]; j++ )
		{
			if( pstr[i] == ptmp[j] )
				return  i;
		}
	}

	return  i;
}
