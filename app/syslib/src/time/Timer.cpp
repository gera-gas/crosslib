/**
 * @file   Timer.cpp
 * @author Gerasimov A.S.
 * @brief  Service to provides timer mechanisms.
 */
#include "dummy.h"
#include "buffer/Array.hpp"
#include "buffer/List.hpp"
#include "time/Timer.hpp"

namespace time {

Timer::Manager *Timer::manager = NULL;

Timer::Timer ( ulong value_tick, bool value_autoreload, fptr_t value_function )
{
	tick       = value_tick;
	autoreload = value_autoreload;
	function   = value_function;

	tick_initial_ = value_tick;
}


#if !defined(CXX_RTTI)
/**
 * Enable timer interrupt (event).
 */
void Timer::Manager::enable ( void )
{
	virtual_enable( this );
}


/**
 * Disable timer interrupt (event).
 */
void Timer::Manager::disable ( void )
{
	virtual_disable( this );
}


/**
 * @brief
 * Set timer execution interval.
 *
 * @param clock_interval [in] execution interval in CPU clock.
 */
void Timer::Manager::interval ( ulong clock_interval )
{
	virtual_interval( this, clock_interval );
}

/**
 * Add timer object to timer manager.
 */
void Timer::Manager::timer_add ( Timer *timer )
{
	disable( );

	timlist_.add_tail( timer );

	virtual_add( this, timer );

	enable( );
}


/**
 * Delete timer object from timer manager list.
 */
void Timer::Manager::timer_delete ( Timer *timer )
{
	disable( );

	timlist_.delete_item( timer );

	virtual_delete( this, timer );

	enable( );
}
#endif


/**
 * Monitor function of TimerManager.
 * This function should be called into interrupt handler.
 */
void Timer::Manager::start ( void )
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


/**
 * Create timer manager object.
 */
Timer::Manager::Manager ( void ) :
	timlist_()
{
	virtual_enable   = reinterpret_cast<EnablePrototype>(dummy_trap);
	virtual_disable  = reinterpret_cast<EnablePrototype>(dummy_trap);
	virtual_interval = reinterpret_cast<IntervalPrototype>(dummy_trap);

	virtual_add      = reinterpret_cast<AddPrototype>(dummy_empty);
	virtual_delete   = reinterpret_cast<AddPrototype>(dummy_empty);
}

} /* namespace time */
