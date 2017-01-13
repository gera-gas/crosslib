/**
 *  @file     memset.c
 *  @brief    Standard memory LIBC functions.
 *  @author   Gerasimov A.S.
 *  @date     07.04.2012
 */
#include "memory.h"


/**
 *  @brief
 *  Fill memory of parametrization value.
 *
 *  @param  s : [out] base memory address.
 *  @param  c : [in] value to fill.
 *  @param  n : [in] memory size in bytes.
 *
 *  @return
 *  Point to base memory address.
 */
void* memset ( void *s, int c, unsigned int n )
{
	register unsigned char *m = (unsigned char *)s;

	while( n )
	{
		*m++ = (unsigned char)c;
		--n;
	}

	return  s;
}
