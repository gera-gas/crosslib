/**
 * @file   Application.cpp
 * @author Gerasimov A.S.
 * @brief  Application lyout.
 */
#include "config.h"
#include "assert.h"
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"
#include "hal/ServiceLayer.hpp"
#include "hal/Application.hpp"

namespace hal {

/**
 * Counter of Application object.
 */
int Application::object_counter_ = 0;

/**
 * @brief
 * Application layout constructor.
 *
 * @param board : [in] pointer to service implementation object.
 */
Application::Application ( ServiceLayer *service ) :
	Module()
{
	assert( object_counter_ == 0 );

	object_counter_++;
	service_ = service;

#if !defined(CXX_RTTI)
	virtual_start = reinterpret_cast<ModulePrototype>(dummy_trap);
#endif
}

#if !defined(CXX_RTTI)
/**
 * Application initialize method.
 */
void Application::init ( void )
{
	service_->init( );

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
	service_->fini( );

	virtual_fini( this );
}
#endif

} /* namespace hal */
