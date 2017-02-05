/**
 *  @file     align_lo.c
 *  @brief    Mathematic fnuction.
 *  @author   Gerasimov A.S.
 *  @date     2012.09.18
 */
#include "typedef.h"
#include "math/math.h"

/**
 *  @brief
 *  Align down "v" up to divisible by "n".
 *
 *  @param v : [in] aligned value.
 *  @param n : [in] divisible devider.
 *
 *  @return
 *  Return aligned value.
 */
ulong align_lo ( ulong v, ulong n )
{
	return  ALIGN_LO( v, n );
}
