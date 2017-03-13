/**
 * @file     Module.cpp
 * @brief    Hardware Abstraction Layer (HAL).
 * @author   Gerasimov A.S.
 */
#include "hal/Module.hpp"
#include "dummy.h"

namespace hal {

#if !defined(CXX_RTTI)
/*
 * Public (virtual) driver methods.
 */
void Module::init ( void )
{
	virtual_init( this );
}

void Module::fini ( void )
{
	virtual_fini( this );
}
#endif

Module::Module( void ) :
	errorcode(0)
{
#if !defined(CXX_RTTI)
	virtual_init  = reinterpret_cast<ModulePrototype>(dummy_empty);
	virtual_fini  = reinterpret_cast<ModulePrototype>(dummy_empty);
#endif
};

} /* namespace hal */
