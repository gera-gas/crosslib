/**
 * @file   Application.cpp
 * @author Gerasimov A.S.
 * @brief  Application lyout.
 */
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"
#include "hal/Service.hpp"
#include "hal/Application.hpp"

namespace hal {

/**
 * Counter of Application object.
 */
int Application::m_object_counter = 0;

/**
 * @brief
 * Application layout constructor.
 *
 * @param board : [in] pointer to service implementation object.
 */
Application::Application ( Service *service ) :
	Module()
{
	if( m_object_counter != 0 ) {
		dummy_trap( );
	}
	m_object_counter++;
	m_service = service;

#if !defined(CXX_RTTI)
	virtual_start = reinterpret_cast<module_t>(dummy_trap);
#endif
}

#if !defined(CXX_RTTI)
/**
 * Application initialize method.
 */
void Application::init ( void )
{
	m_service->init( );

	virtual_init( this );
}

/**
 * Application finalize method.
 */
void Application::start ( void )
{
	virtual_start( this );
}

/**
 * Application finalize method.
 */
void Application::fini ( void )
{
	m_service->fini( );

	virtual_fini( this );
}
#endif

} /* namespace hal */
