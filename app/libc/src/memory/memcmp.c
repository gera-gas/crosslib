/**
 *  @file     memcmp.c
 *  @brief    Standard memory LIBC functions.
 *  @author   Gerasimov A.S.
 *  @date     07.04.2012
 */
#include <stddef.h>


/**
 *  @brief
 *  Comparing two memory area.
 *
 *  @param  s1   : [in] first memory area address.
 *  @param  s2   : [in] second memory area address.
 *  @param  size : [in] size memory area in bytes.
 *
 *  @retval <0 : m1 < m2.
 *  @retval =0 : m1 = m2.
 *  @retval >0 : m1 > m2.
 */
int memcmp ( const void *s1, const void *s2, size_t size )
{
	register unsigned char  *m1 = (unsigned char *)s1;
	register unsigned char  *m2 = (unsigned char *)s2;

	while( size-- )
	{
		if( *m1 != *m2 )
			return  ( *m1 - *m2 );
		m1++;
		m2++;
        }

        return 0;
}
