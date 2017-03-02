/**
 * @file    Agent.cpp
 * @brief   Main system application.
 * @author  Gerasimov A.S.
 */
#include "dummy.h"
#include "system/BoardLayout.hpp"
#include "system/AppLayout.hpp"

namespace sys {

/**
 * @brief
 * Board layout constructor.
 *
 * @param board : [in] point to board implementation object.
 */
AppLayout::AppLayout( BoardLayout *board ) :
	board_(board)
{
	virtual_init  = reinterpret_cast<method_t>(dummy_loop);
	virtual_start = reinterpret_cast<method_t>(dummy_loop);
	virtual_fini  = reinterpret_cast<method_t>(dummy_loop);
}


/**
 * Application initialize method.
 */
void AppLayout::init ( void )
{
	board_->init( );
	
	virtual_init( this );
}

/**
 * Application run method.
 */
void AppLayout::start ( void )
{
	virtual_start( this );
}

/**
 * Application finalize method.
 */
void AppLayout::fini ( void )
{
	virtual_fini( this );
}

} /* namespace sys */
