/**
 * @file   BoardLayout.cpp
 * @author Gerasimov A.S.
 * @brief  Board base API.
 */
#include "config.h"
#include "assert.h"
#include "dummy.h"
#include "system/BoardLayout.hpp"

namespace sys {

/**
 * Counter of BoardLayout object.
 */
int BoardLayout::object_counter_ = 0;

/**
 * @brief
 * Board layout constructor.
 *
 * @param udelay : [in] point to specific board delay function in microseconds.
 * @param init   : [in] point to specific board initialize function.
 */
BoardLayout::BoardLayout ( void )
{
	assert( object_counter_ == 0 );

	virtual_udelay = reinterpret_cast<udelay_t>(dummy_loop);
	virtual_init   = reinterpret_cast<method_t>(dummy_loop);
	virtual_fini   = reinterpret_cast<method_t>(dummy_loop);

	object_counter_++;
}

/**
 * Board initialize method.
 */
void BoardLayout::init ( void )
{
	virtual_init( this );
}

/**
 * Board finalize method.
 */
void BoardLayout::fini ( void )
{
	virtual_fini( this );
}

/**
 * @brief
 * Delay in microseconds.
 *
 * @note
 * Should be overrided.
 */
void BoardLayout::udelay ( size_t usec )
{
	virtual_udelay( usec );
}

/**
 * @brief
 * Delay in milliseconds.
 */
void BoardLayout::mdelay ( size_t msec )
{
	while( msec-- )
	{
		udelay( 1000 );
	}
}

/**
 * @brief
 * Delay in seconds.
 */
void BoardLayout::delay ( size_t sec )
{
	while( sec-- )
	{
		mdelay( 1000 );
	}
}

} /* namespace sys */
