/**
 * @file   TimerManager.cpp
 * @author Gerasimov A.S.
 * @brief  Service to provides timer mechanisms.
 */
#include "dummy.h"
#include "buffer/Array.hpp"
#include "buffer/List.hpp"
#include "time/Timer.hpp"
#include "time/TimerManager.hpp"

namespace time {

#if !defined(CXX_RTTI)
/**
 * Enable timer interrupt (event).
 */
void TimerManager::enable ( void )
{
	virtual_enable( this );
}


/**
 * Disable timer interrupt (event).
 */
void TimerManager::disable ( void )
{
	virtual_disable( this );
}


/**
 * @brief
 * Set timer execution interval.
 *
 * @param clock_interval [in] execution interval in CPU clock.
 */
void TimerManager::interval ( ulong clock_interval )
{
	virtual_interval( this, clock_interval );
}
#endif


/**
 * Create timer manager object.
 */
TimerManager::TimerManager ( void ) :
	timlist_()
{
	virtual_enable   = reinterpret_cast<TimerManagerEnablePrototype>(dummy_trap);
	virtual_disable  = reinterpret_cast<TimerManagerEnablePrototype>(dummy_trap);
	virtual_interval = reinterpret_cast<TimerManagerIntervalPrototype>(dummy_trap);
}


/**
 * Add timer object to timer manager.
 */
void TimerManager::add_timer ( Timer *timer )
{
	timlist_.add_tail( timer );
}


/**
 * Add timer object to timer manager.
 */
void TimerManager::del_timer ( Timer *timer )
{
	;
}


/**
 * Monitor function of TimerManager.
 * This function should be called into interrupt handler.
 */
void TimerManager::start ( void )
{
	Timer *timer;

	list_foreach( timer, timlist_ )
	{
		if( timer->tick )
		{
			timer->tick--;
		}
		else
		{
			if( timer->function )
			{
				timer->function( );
			}

			if( timer->autoreload )
			{
				timer->reload( );
			}
		}
	}
}

} /* namespace time */
