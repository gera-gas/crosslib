/**
 *  @file     strspn.c
 *  @brief    Single char string functions.
 *  @author   Gerasimov A.S.
 *  @date     28.07.2012
 */
#include <stddef.h>
#include "string/string.h"

/**
 *  @brief
 *  Check chars from template string 'ptmp' on apsent in target string 'pstr'.
 *
 *  @param  pstr : [in] target string.
 *  @param  ptmp : [in] template string.
 *
 *  @retval  >0 : [success] return char index start at 0.
 *  @retval  =0 : [failed] char don't find.
 *
 *  @note
 *  Reverse logic relative 'strcspn'.
 */
size_t strspn ( const char *pstr, const char *ptmp )
{
	register unsigned int  i, j;


	for( i = 0; pstr[i]; i++ )
	{
		if( !strchr( ptmp, pstr[i] ) )
			return  i;

	}

	return  i;
}
