/**
 *  @file     align_hi.c
 *  @brief    Mathematic fnuctions.
 *  @author   Герасимов А.С.
 *  @date     2012.09.18
 */
#include "typedef.h"


/**
 *  @brief
 *  Align up "v" up to divisible by "n".
 *
 *  @param v : [in] aligned value.
 *  @param n : [in] divisible devider.
 *
 *  @return
 *  Return aligned value.
 */
ulong align_hi ( ulong v, ulong n )
{
	return  ALIGN_HI( v, n );
}
