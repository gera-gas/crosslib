/**
 *  @file     pseudo_thread.c
 *  @brief    Pseudo thread main mechanism.
 *  @author   Gerasimov A.S.
 *  @date     2014-09-08 10:54:18
 */
#include "assert.h"
#include "multitask/pseudo_thread.h"


/**
 * @brief
 * Manager of PT process (Runing and controling PT process).
 *
 * @param pt     : [in]  address of PT object.
 * @param argin  : [in]  memory address of input parameters for state handlers.
 * @param argout : [out] memory address of output parameters for state handlers.
 *
 * @retval PT_ATWORK : process is not finish.
 * @retval PT_FINISH : process finish (all states is walked or reset).
 */
pt_result_t pt_start ( pt_t *pt, const void *argin, void *argout )
{
	        register uint index = 0;
	register pt_result_t result = PT_STATE_ATWORK;
	      register uint parrent = (uint)__builtin_return_address(0);
	
	assert( pt->numb < PT_RESET );
	/*
	 * Checking pt process on free.
	 * If process locked, check address of parent.
	 * If parent address and current lock address is equal, then go to managing.
	 */
	if( (pt->lock == 0) || (pt->lock == parrent) ) {
		/*
		 * Main cycle of state handling.
		 * Execute each state (if pt->stepmode != true)
		 * until state is not halted (not null).
		 */
		do {
			index = (*pt->state)( argin, argout );
			/*
			 * The process of forcibly completed.
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
			 * Walk all states in states array.
			 * pt process in success finished.
			 */
			if( *pt->state == 0 )
			{
		m_pt_finish:
				result = PT_STATE_FINISH;
				pt->lock  = 0;
				pt->state = pt->init;
				break;
			}
		} while( index && !pt->stepmode );
		/*
		 * Set parrent address for locking process.
		 */
		if( (pt->state != pt->init) && (pt->lock == 0) )
		{
			pt->lock = parrent;
		}
	}

	return  result;
}
