/**
 *  @file    udivsi3.c
 *  @brief   32 bit software devide.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-24 01:02:20 +0400
 */
#include "typedef.h"


/**
 *  @brief
 *  32 bit software devide 'dividend' on 'divider'.
 *
 *  @param  dividend : [in] dividend.
 *  @param  divider  : [in] divider.
 *
 *  @return
 *  Return result of devide (dividend/divider).
 */
uint32 __udivsi3 ( uint32 dividend, uint32 divider )
{
	register uint32  result;
	register uint32  shiftv;


	if( !divider )
		return  0;

	if( (!dividend) || (divider > dividend) )
		return  0;

	if( dividend == divider )
		return  1;

	if( divider == 1 )
		return  dividend;

	/*
	 *  Выравниваем старшие разряды делителя и делимого,
	 *  если они не знаковые.
	 */
	for( shiftv = divider; !(dividend & shiftv & 0xFFFFFFFF); shiftv <<= 1 )
	{
		if( dividend < (shiftv << 1) )
			break;
	}

	result = 0;
	/*
	 *  Процедура деления.
	 */
	do {
		result <<= 1;

		if( shiftv <= dividend )
		{
			result += 1;
			dividend -= shiftv;
		}

		shiftv >>= 1;
	}
	while( shiftv >= divider );


	return  result;
}
