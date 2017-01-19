/**
 *  @file    umodsi3.c
 *  @brief   32 bit software umod devide.
 *  @author  Герасимов А.С.
 *  @date    2013-03-24 14:11:13 +0400
 */
#include "typedef.h"

/**
 *  @brief
 *  32 bit software umod devide.
 *
 *  @param  dividend : [in] dividend.
 *  @param  divider  : [in] divider.
 *
 *  @return
 *  Return 
 *  Возвращает mod of devide (dividend/divider).
 */
uint32 __umodsi3 ( uint32 dividend, uint32 divider )
{
	return  ( dividend - __udivsi3( dividend, divider ) * divider );
}
