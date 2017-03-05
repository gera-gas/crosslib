#ifndef MODULE_HPP_
#define MODULE_HPP_
/**
 * @file     Module.hpp
 * @brief    Hardware Abstraction Layer (HAL).
 * @author   Gerasimov A.S.
 */
#include <stddef.h>

namespace hal {

/**
 * Class describe base module structure.
 */
class Module {
public:
	Module ( void );

#if defined(CXX_RTTI)
	virtual void init ( void ) = 0;
	virtual void fini ( void ) = 0;
#else
	void init ( void );
	void fini ( void );

	typedef void (*module_t) (void*);
#endif

protected:

#if !defined(CXX_RTTI)
	/**
	 * Method for startup initializing and configure by default.
	 */
	module_t virtual_init;

	/**
	 * Shutdown method.
	 */
	module_t virtual_fini;
#endif
};

} /* namespace hal */

#endif /* MODULE_HPP_ */
