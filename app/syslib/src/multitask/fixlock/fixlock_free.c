/**
 *  @file    fixlock_free.c
 *  @brief   Access control mechanism.
 *  @author  Gerasimov A.S.
 *  @date    2014-09-08 10:54:18
 */
#include "dummy.h"
#include "multitask/accessor.h"

/**
 * @brief
 * Free fixlock object for next owner.
 *
 * @param fixlock : [in] fixlock object address.
 */
void fixlock_free ( fixlock_t *fixlock )
{
	FIXLOCK_FREE( fixlock );
}
