#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_
/**
 * @file   Application.hpp
 * @author Gerasimov A.S.
 * @brief  Service API.
 * @note   Application (top) layer.
 */
#include <stddef.h>

namespace hal {

/**
 * Application layout.
 */
class Application : public Module
{
public:
	Application( ServiceLayer* );

	void init  ( void );
	void start ( void );
	void fini  ( void );

protected:
	ModulePrototype virtual_start;

private:
	static int object_counter_;
	ServiceLayer *service_;
};

} /* namespace hal */

#endif /* APPLICATION */
