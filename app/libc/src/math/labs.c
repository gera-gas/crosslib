/**
 *  @file     labs.c
 *  @brief    Mathematic fnuctions.
 *  @author   Gerasimov A.S.
 *  @date     2012.09.18
 */
#include "typedef.h"


/**
 *  @brief
 *  Absolute value ulong from long.
 *
 *  @param  x : [in] input value.
 *
 *  @return
 *  Return absolute value of 'x'.
 */
ulong labs ( long x )
{
	if( x < 0 )
		return  -x;

	return  x;
}
