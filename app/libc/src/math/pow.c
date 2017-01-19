/**
 *  @file     pow.c
 *  @brief    Mathematic fnuctions.
 *  @author   Gerasimov A.S.
 *  @date     2012.09.18
 */
#include "typedef.h"


/**
 *  @brief
 *  Pow 'x' to 'y' (x^y).
 *
 *  @param  x : [in] target value.
 *  @param  y : [in] pow.
 *
 *  @return
 *  Result result of pow x^y.
 */
ulong pow ( ulong x, ulong y )
{
	register ulong  v;


	if( y == 0 )
		return  1;

	v = x;

	for( --y; y; y-- )
		v *= x;

	return  v;
}
