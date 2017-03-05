/**
 * @file   Clock.cpp
 * @author Gerasimov A.S.
 * @brief  Service to provides clock mechanims.
 */
#include "config.h"
#include "assert.h"
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"
#include "hal/clock/Clock.hpp"

namespace hal {

Board *Clock::m_board = NULL;

/**
 * @brief
 * Board layout constructor.
 *
 * @param board : [in] pointer to board implementation object.
 */
void Clock::init ( Board *board )
{
	m_board = board;
}

/**
 * Delay in microseconds.
 */
void Clock::udelay ( size_t usec )
{
	assert(m_board != NULL);

	m_board->udelay( usec );
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

} /* namespace sys */
