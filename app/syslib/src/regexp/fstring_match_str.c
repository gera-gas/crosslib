/**
 *  @file     fstring_match_str.c
 *  @brief    Export data structure implementation mechanisms.
 *  @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "regexp/regexp.h"


/**
 * @brief
 * Check input string to tempalte matching.
 *
 * @param pstr : [in] input string for identification.
 * @param ptmp : [in] point to etalon template.
 *
 * @retval true  : [success] input string matching to etalon template.
 * @retval false : [failed] not matching.
 */
bool fstring_match_str ( const fstring_t *etalon, const char *pstr )
{
	bool result = true;

	while( *pstr )
	{
		if( !regexp_match_szc( etalon, *pstr++ ) )
		{
			result = false;
			break;
		}
	}

	return result;
}
