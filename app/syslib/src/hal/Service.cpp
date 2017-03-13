/**
 * @file   Service.cpp
 * @author Gerasimov A.S.
 * @brief  Service layout.
 */
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"
#include "hal/Service.hpp"

namespace hal {

/**
 * Counter of Service object.
 */
int Service::object_counter_ = 0;

/**
 * @brief
 * Service layout constructor.
 *
 * @param board : [in] pointer to board implementation object.
 */
Service::Service( Board *board ) :
	Module()
{
	if( object_counter_ != 0 ) {
		dummy_trap( );
	}

	object_counter_++;

	board_ = board;
}

#if !defined(CXX_RTTI)
/**
 * Service initialize method.
 */
void Service::init ( void )
{
	board_->init( );

	virtual_init( this );
}

/**
 * Service finalize method.
 */
void Service::fini ( void )
{
	board_->fini( );

	virtual_fini( this );
}
#endif

} /* namespace hal */
