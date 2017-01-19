/**
 *  @file     memcpy.c
 *  @brief    Standard memory LIBC functions.
 *  @author   Gerasimov A.S.
 *  @date     07.04.2012
 */
#include <stddef.h>
 

/**
 *  @brief
 *  Copy memory from 'dst' to 'src'.
 *
 *  @param  dst  : [out] destination address.
 *  @param  src  : [in] source address.
 *  @param  size : [in] size copied memory in bytes.
 *
 *  @return
 *  Point to destination address (dst).
 */
void* memcpy ( void *dst, const void *src, size_t size )
{
	      register char *s1 = (char *)dst;
	register const char *s2 = (const char *)src;

	while( size )
	{
		*s1++ = *s2++;
		--size;
	}

	return  dst;
}
