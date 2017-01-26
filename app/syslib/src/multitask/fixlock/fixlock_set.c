/**
 *  @file    fixlock_set.c
 *  @brief   Access control mechanism.
 *  @author  Gerasimov A.S.
 *  @date    2014-09-08 10:54:18
 */
#include "dummy.h"
#include "multitask/accessor.h"

/**
 * @brief
 * Set fixlock state by ID.
 *
 * @param fixlock : [in] fixlock object address.
 * @param own_id  : [in] owner preset procedure ID.
 * @param new_id  : [in] new preset procedure ID.
 *
 * @retval true  : success set.
 * @retval false : failed set.
 */
bool fixlock_set ( fixlock_t *fixlock, uint own_id, uint new_id )
{
	register bool result = FIXLOCK_TRY( fixlock, own_id );

	if( result )
	{
		fixlock->state = new_id;
	}

	return result;
}
