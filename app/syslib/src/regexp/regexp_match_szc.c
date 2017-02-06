/**
 *  @file     regexp_match_szc.c
 *  @brief    Export data structure implementation mechanisms.
 *  @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "regexp/regexp.h"
#ifndef USE_BUILTIN_LIBC
#include "ctype/ctype.h"
#include "string/string.h"
#else
#include <ctype.h>
#include <string.h>
#endif


/**
 * @brief
 * Check input char to template matching.
 *
 * @param c    : [in] input char for identification.
 * @param ptmp : [in] point to etalon template.
 *
 * @retval true  : [success] input char matching to etalon template.
 * @retval false : [failed] not matching.
 */
bool regexp_match_szc ( const regexp_sz_t *etalon, char c )
{
	bool result = true;

	switch( etalon->type )
	{
	case REGEXP_TYPE_BINCHAR:
		if( !ascii_isbdigit( c ) )
		{
			result = false;
		}

	break;

	case REGEXP_TYPE_DECCHAR:
		if( !ascii_isdigit( c ) )
		{
			result = false;
		}

	break;

	case REGEXP_TYPE_HEXCHAR:
		if( !ascii_isxdigit( c ) )
		{
			result = false;
		}

	break;

	case REGEXP_TYPE_LETTERS:
#if ( defined(USE_BUILTIN_LIBC) || defined(USE_REGEXP_LOCALE) )
		if( !isalpha( c ) )
#else
		if( !ascii_isalpha( c ) )
#endif
		{
			result = false;
		}

	break;

	case REGEXP_TYPE_CUSTOM:
		if( !strchr( etalon->custom, c ) )
		{
			result = false;
		}

	break;
	}

	return result;
}
