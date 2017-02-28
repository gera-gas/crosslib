/**
 * @file   Board.cpp
 * @author Gerasimov A.S.
 * @brief  Board base API.
 */
#include "dummy.h"
#include "system/Board.hpp"

namespace sys {

void (*Board::init_)( void ) = reinterpret_cast<void (*)()>(dummy_loop);
void (*Board::udelay_)( size_t ) = reinterpret_cast<void (*)(size_t)>(dummy_loop);

/**
 * @brief
 * Delay in milliseconds.
 */
void Board::mdelay ( size_t msec )
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
void Board::delay ( size_t sec )
{
	while( sec-- )
	{
		mdelay( 1000 );
	}
}

} /* namespace sys */
