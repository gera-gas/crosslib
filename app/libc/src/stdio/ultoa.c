/**
 * @file	ultoa.c
 * @brief	Formatted input/output routines
 * @author	Gerasimov A.S.
 * @date	13.02.2013
 */
#include "typedef.h"
#include "ctype/ctype.h"
#include "string/string.h"
#include "stdio/stdio.h"


/**
 *  @brief
 *  Converting long integer to string.
 *
 *  @param d     : [in] long integer.
 *  @param str   : [out] address of output buffer.
 *  @param radix : [in] the base of a system of numeration (2,10,16).
 *
 *  @return
 *  Return point to result string <str>.
 */
char* ultoa ( unsigned long d, char *str, int radix )
{
	size_t  i;
	size_t  ch;

	switch( radix )
	{
		case 2:
			for( i = 0; i < (sizeof(long) * 8); i++ )
			{
				str[i] = ascii_tochar( (d >> 31) & 0x1 );
				d <<= 1;
			}
			str[i] = '\0';
		break;

		case 10:
			for( i = 0; d >= 10; i++ )
			{
				str[i] = ascii_tochar( d % 10 );
				d /= 10;
			}
			str[i] = ascii_tochar( d ); i++;
			str[i] = '\0';

			strrev( str );
		break;

		case 16:
			for( i = 0; i < (sizeof(long) * 2); i++ )
			{
				ch = d >> 28;

				if( ch < 0xA )
					ch = ascii_tochar( ch );
				else
					ch = ch + ('A' - 0xA);

				str[i] = ch;

				d <<= 4;
			}
			str[i] = '\0';
		break;

		default:
			return  (char *)0;
	}

	return  str;
}
