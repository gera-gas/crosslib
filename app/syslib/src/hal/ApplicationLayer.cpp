/**
 * @file   ApplicationLayer.cpp
 * @author Gerasimov A.S.
 * @brief  Application (top) layer.
 */
#include "config.h"
#include "assert.h"
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/BoardLayer.hpp"
#include "hal/ServiceLayer.hpp"
#include "hal/ApplicationLayer.hpp"

namespace hal {

/**
 * Counter of Application object.
 */
int ApplicationLayer::object_counter_ = 0;

/**
 * @brief
 * Application layout constructor.
 *
 * @param board : [in] pointer to service implementation object.
 */
ApplicationLayer::ApplicationLayer ( ServiceLayer *service ) :
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
void ApplicationLayer::init ( void )
{
	service_->init( );

	virtual_init( this );
}

/**
 * Application finalize method.
 */
void ApplicationLayer::start ( void )
{
	virtual_start( this );
}

/**
 * Application finalize method.
 */
void ApplicationLayer::fini ( void )
{
	service_->fini( );

	virtual_fini( this );
}
#endif

} /* namespace hal */
