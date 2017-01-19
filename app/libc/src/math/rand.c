/**
 *  @file     rand.c
 *  @brief    Mathematic fnuctions.
 *  @author   Gerasimov A.S.
 *  @date     2012.09.18
 */
#include "typedef.h"


static ulong __seed_r = 1;

/**
 *  @brief
 *  Generate pseudo random number by algorithm from ISO C standard.
 *
 *  @return
 *  Random number.
 */
ulong rand ( void )
{
	ulong next = __seed_r;
	ulong result;


	next *= 1103515245;
	next += 12345;
	result = (ulong)( next / 65536 ) % 2048;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (ulong)( next / 65536 ) % 1024;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (ulong)( next / 65536 ) % 1024;

	__seed_r = next;


	return  result;
}
