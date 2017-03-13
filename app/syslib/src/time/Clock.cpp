/**
 * @file   Clock.cpp
 * @author Gerasimov A.S.
 * @brief  Service to provides clock mechanims.
 */
#include "config.h"
#include "assert.h"
#include "dummy.h"
#include "time/Clock.hpp"

namespace time {

Clock::uDelayPrototype Clock::udelay_ = reinterpret_cast<Clock::uDelayPrototype>(dummy_trap);

/**
 * @brief
 * Clock constructor.
 *
 * @param udelay_func : [in] pointer to microsecond delay function.
 */
void Clock::init ( uDelayPrototype udelay_func )
{
	udelay_ = udelay_func;
}

/**
 * Delay in microseconds.
 */
void Clock::udelay ( size_t usec )
{
	udelay_( usec );
}

/**
 * Delay in milliseconds.
 */
void Clock::mdelay ( size_t msec )
{
	while( msec-- )
	{
		udelay( 1000 );
	}
}

/**
 * Delay in seconds.
 */
void Clock::delay ( size_t sec )
{
	while( sec-- )
	{
		mdelay( 1000 );
	}
}

} /* namespace time */
