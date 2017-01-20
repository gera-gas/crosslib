/**
 *  @file     umoddi3.c
 *  @brief    64 bit software devide.
 *  @author   Purykin S.
 *  @date     2013-07-19 11:03:01 +0400
 */
#include "typedef.h"
#include "math.h"


/**
 *  @brief
 *  64 bit software umod devide.
 *
 *  @param  A : [in] dividend.
 *  @param  B : [in] divider.
 *
 *  @return
 *  Return mod of devide (dividend/divider).
 */
uint64 __umoddi3 ( uint64 A, uint64 B )
{
	unsigned short dividend[4] = {
		((unsigned short *)&A)[3],
		((unsigned short *)&A)[2],
		((unsigned short *)&A)[1],
		((unsigned short *)&A)[0]
	};
	unsigned short divisor[4] = {
		((unsigned short *)&B)[3],
		((unsigned short *)&B)[2],
		((unsigned short *)&B)[1],
		((unsigned short *)&B)[0]
	};

	unsigned short quotient[4];
	unsigned short remainder[4];
	unsigned int n = 4;

	if (divisor[0] == 0) return 0;
	else if (divisor[1] == 0) n = 1;
	else if (divisor[2] == 0) n = 2;
	else if (divisor[3] == 0) n = 3;

	if( divmnu(quotient, remainder, dividend, divisor, 4, n))
		return 0;

	dividend[0] = remainder[0]; remainder[0] = remainder[3]; remainder[3] = dividend[0];
	dividend[0] = remainder[1]; remainder[1] = remainder[2]; remainder[2] = dividend[0];

	return *(uint64 *)remainder;
}
