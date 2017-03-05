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
	Application( Service* );

	void init  ( void );
	void start ( void );
	void fini  ( void );

protected:
	module_t virtual_start;

private:
	static int m_object_counter;

	Service *m_service;
};

} /* namespace hal */

#endif /* APPLICATION */
