/**
 * @file   Service.cpp
 * @author Gerasimov A.S.
 * @brief  Service layout.
 */
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"
#include "hal/Service.hpp"
#include "hal/clock/Clock.hpp"

namespace hal {

/**
 * Counter of Service object.
 */
int Service::m_object_counter = 0;

/**
 * @brief
 * Service layout constructor.
 *
 * @param board : [in] pointer to board implementation object.
 */
Service::Service( Board *board ) :
	Module()
{
	if( m_object_counter != 0 ) {
		dummy_trap( );
	}

	m_object_counter++;

	m_board = board;
}

#if !defined(CXX_RTTI)
/**
 * Service initialize method.
 */
void Service::init ( void )
{
	m_board->init( );

	Clock::init( m_board );

	virtual_init( this );
}

/**
 * Service finalize method.
 */
void Service::fini ( void )
{
	m_board->fini( );

	virtual_fini( this );
}
#endif

} /* namespace hal */
