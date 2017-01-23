/**
 *  @file     clz.c
 *  @brief    Mathematic functions.
 *  @author   Purykin S.
 *  @date     2012.09.18
 */
#include "typedef.h"


/**
 * @brief   Counts the number of leading zeros in value parameter.
 *
 * @param   value : The 32-bits value.
 *
 * @retval  Number between 0 and 32 of leading zeros in value parameter starting from the
 *          most significant bit. The result in rD is 32 when rA is 0, and it is 0 if
 *          rA is 0xFFFFFFFF.
 */
int clz ( uint32 value )
{
	register uint32  i;

	for (i = 0; i < 32;) {
		if (value & 0x80000000)
			break;
		value <<= 1;
		i++;
	}

	return i;
}
