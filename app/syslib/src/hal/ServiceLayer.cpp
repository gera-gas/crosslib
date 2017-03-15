/**
 * @file   ServiceLayer.cpp
 * @author Gerasimov A.S.
 * @brief  Service Layer intreface.
 */
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"
#include "hal/ServiceLayer.hpp"

namespace hal {

/**
 * Counter of Service object.
 */
int ServiceLayer::object_counter_ = 0;

/**
 * @brief
 * Service layout constructor.
 *
 * @param board : [in] pointer to board implementation object.
 */
ServiceLayer::ServiceLayer( Board *board ) :
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
void ServiceLayer::init ( void )
{
	board_->init( );

	virtual_init( this );
}

/**
 * Service finalize method.
 */
void ServiceLayer::fini ( void )
{
	board_->fini( );

	virtual_fini( this );
}
#endif

} /* namespace hal */