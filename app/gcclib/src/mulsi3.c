/**
 *  @file    mulsi3.c
 *  @brief   software mull 32x32.
 *  @author  Gerasimov A.S.
 */
#include "typedef.h"


/**
 *  @brief
 *  32 bit mull 'a' and 'b'.
 *
 *  @param  a [in] : multiplier 'a'.
 *  @param  b [in] : multiplier 'b'.
 *
 *  @return
 *  Return result of mull.
 */
uint32 __mulsi3 ( uint32 a, uint32 b )
{
	register uint32 result;

	for( result = 0; a; )
	{
		if( a & 1 )
			result += b;

		a >>= 1;
		b <<= 1;
	}

	return  result;
}
