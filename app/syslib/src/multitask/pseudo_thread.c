/**
 *  @file     pseudo_thread.c
 *  @brief    Pseudo thread main mechanism.
 *  @author   Gerasimov A.S.
 *  @date     2014-09-08 10:54:18
 */
#include "assert.h"
#include "multitask/accessor.h"
#include "multitask/thread.h"


/**
 * @brief
 * Manager of PT (Executing and controling PT objects).
 *
 * @param pt     : [in]  address of PT object.
 * @param argin  : [in]  memory address of input parameters for state handlers.
 * @param argout : [out] memory address of output parameters for state handlers.
 *
 * @retval PT_STATE_ATWORK : PT is not finish.
 * @retval PT_STATE_FINISH : PT finish (all states is walked or reset).
 */
pt_result_t pt_start ( pt_t *pt, const void *argin, void *argout )
{
	        register uint index = 0;
	register pt_result_t result = PT_STATE_ATWORK;

	
	assert( pt->numb < PT_RESET );
	/*
	 * Checking PT on free.
	 * If PT locked, check address of caller procedure.
	 * If caller address and current lock address is equal, then go to managing.
	 */
	if( pt->flags & PT_FLAG_SHARED )
	{
		critical_section.entry( );
	}

	bool lock = pt_lock( pt, PTLOCK_OWNER );

	if( pt->flags & PT_FLAG_SHARED )
	{
		critical_section.leave( );
	}

	if( lock == false )
	{
		return result;
	}

	/*
	 * Main cycle of state handling.
	 * Execute each state (if pt->flags & PT_FLAG_SHARED)
	 * and until state is not halted (not null).
	 */
	do {
		index = (*pt->state)( argin, argout );
		/*
		 * PT of forcibly completed.
		 */
		if( index == PT_RESET )
		{
			goto m_pt_finish;
		}
			
		/*
		 * Assertion control.
		 * Check to next state index on out of range.
		 */
		assert( ((ulong)(pt->state - pt->init) + index) <= pt->numb );
			
		pt->state += index;
		/*
		 * Walk all states in functions array.
		 * PT in success finished.
		 */
		if( *pt->state == 0 )
		{
		m_pt_finish:
			pt->state = pt->init;
			result = PT_STATE_FINISH;
			break;
		}
	} while( index && !(pt->flags & PT_FLAG_STEPMODE) );

	pt_unlock( pt );

	return  result;
}


/**
 * @brief
 * Try catch pseudo thread by caller function.
 *
 * @param pt     : [in/out] address of PT object.
 * @param owner  : [in] caller function uniq ID.
 *
 * @retval true  : catch is success.
 * @retval false : unable to catch.
 */
bool pt_lock ( pt_t *pt, ptlock_t owner )
{
	if( pt->owner == PTLOCK_FREE )
	{
		pt->owner = owner;
		return true;
	}

	if( pt->owner == owner )
	{
		return true;
	}

	return false;
}


/**
 * @brief
 * Free pseudo thread.
 *
 * @param pt : [in/out] address of PT object.
 */
void pt_unlock ( pt_t *pt )
{
	pt->owner = PTLOCK_FREE;
}
