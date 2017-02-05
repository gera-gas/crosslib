/**
 *  @file    fixlock_try.c
 *  @brief   Access control mechanism.
 *  @author  Gerasimov A.S.
 *  @date    2014-09-08 10:54:18
 */
#include "dummy.h"
#include "multitask/accessor.h"

/**
 * @brief
 * Try catch of fixlock object by ID.
 *
 * @param fixlock : [in] fixlock object address.
 * @param id      : [in] preset procedure ID.
 *
 * @retval true  : success catch.
 * @retval false : failed catch.
 */
bool fixlock_try ( fixlock_t *fixlock, uint id )
{
	return FIXLOCK_TRY( fixlock, id );
}
