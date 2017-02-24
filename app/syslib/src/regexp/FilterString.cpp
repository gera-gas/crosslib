/**
 *  @file     FilterString.cpp
 *  @brief    Methods for simple filter string.
 *  @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "config.h"
#ifndef USE_BUILTIN_LIBC
#include "ctype/ctype.h"
#include "string/string.h"
#else
#include <ctype.h>
#include <string.h>
#endif
#include "regexp/FilterString.hpp"

namespace regexp {

/**
 * @brief
 * Check input char to template matching.
 *
 * @param c : [in] input char for identification.
 *
 * @retval true  : [success] input char matching to etalon template.
 * @retval false : [failed] not matching.
 */
bool FilterString::match ( char c )
{
	bool result = true;

	switch( filter_type_ )
	{
	case TYPE_BINCHAR:
		if( !ascii_isbdigit( c ) )
		{
			result = false;
		}

	break;

	case TYPE_DECCHAR:
		if( !ascii_isdigit( c ) )
		{
			result = false;
		}

	break;

	case TYPE_HEXCHAR:
		if( !ascii_isxdigit( c ) )
		{
			result = false;
		}

	break;

	case TYPE_LETTERS:
#if ( defined(USE_BUILTIN_LIBC) || defined(USE_REGEXP_LOCALE) )
		if( !isalpha( c ) )
#else
		if( !ascii_isalpha( c ) )
#endif
		{
			result = false;
		}

	break;

	case TYPE_CUSTOM:
		if( !strchr( custom_filter_string_, c ) )
		{
			result = false;
		}

	break;

	case TYPE_NONE:
		result = true;
	break;
	}

	return result;
}


/**
 * @brief
 * Check input string to tempalte matching.
 *
 * @param pstr : [in] input string for identification.
 *
 * @retval true  : [success] input string matching to etalon template.
 * @retval false : [failed] not matching.
 */
bool FilterString::match ( const char *pstr )
{
	bool result = true;

	while( *pstr )
	{
		if( !match( *pstr++ ) )
		{
			result = false;
			break;
		}
	}

	return result;
}

} /* namespace regexp */
