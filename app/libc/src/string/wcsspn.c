/**
 *  @file     wcsspn.c
 *  @brief    Wide char string functions.
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
size_t wcsspn ( const wchar_t *pstr, const wchar_t *ptmp )
{
	register unsigned int  i;


	for( i = 0; pstr[i]; i++ )
	{
		if( !wcschr( ptmp, pstr[i] ) )
			return  i;

	}

	return  i;
}
