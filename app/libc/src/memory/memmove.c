/**
 *  @file     memmove.c
 *  @brief    Standard memory LIBC functions.
 *  @author   Gerasimov A.S.
 *  @date     07.04.2012
 */
#include "memory.h"


/**
 *  @brief
 *  Move meory area to destination address.
 *
 *  @param  dst  : [out] destination address.
 *  @param  src  : [in] source address.
 *  @param  size : [in] size moved memory in bytes.
 *
 *  @return
 *  Point to destination address (dst).
 */
void* memmove ( void *pdst, const void *psrc, unsigned int size )
{
	      register char *s1 = (char *)pdst;
	register const char *s2 = (const char *)psrc;
	/* 
	 *  If destination address need locate in low address space:
	 *  
	 *  | 0x0... | ... | 0xF...| 
	 *  |        |     |       |
	 *  | psrc   | ... | pdst  |
	 */
	if( s2 >= s1 )
	{
		while( size )
		{
			*s1++ = *s2++;
			--size;
		}
	}
	else
	{
		while( size )
		{
			--size;
			s1[size] = s2[size];
		}
	}

	return  pdst;
}
