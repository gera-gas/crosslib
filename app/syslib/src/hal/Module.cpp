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

Module::Module( void )
{
#if !defined(CXX_RTTI)
	virtual_init  = reinterpret_cast<module_t>(dummy_trap);
	virtual_fini  = reinterpret_cast<module_t>(dummy_trap);
#endif
};

} /* namespace hal */
