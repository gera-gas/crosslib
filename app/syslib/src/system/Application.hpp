#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_
/**
 * @file   Application.hpp
 * @author Gerasimov A.S.
 * @brief  Application base API.
 */
#include <stddef.h>

namespace sys {

/**
 * Application base API class.
 */
class Application
{
public:
	static io::InOut * const stdin;
	static io::InOut * const stdout;
	static io::InOut * const stderr;

	static void init  ( void );
	static void start ( void );
	static void fini  ( void );

protected:
	static io::InOut * stream[3];

	static void (*init_)  ( void );
	static void (*start_) ( void );
	static void (*fini_)  ( void );
};

} /* namespace sys */

#endif /* APPLICATION_HPP_ */
