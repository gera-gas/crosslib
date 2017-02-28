/**
 * @file   Application.cpp
 * @author Gerasimov A.S.
 * @brief  Application base API.
 */
#include <stddef.h>
#include "dummy.h"
#include "hal/Port.hpp"
#include "io/InOut.hpp"
#include "system/Application.hpp"

namespace sys {

io::InOut * Application::stream[3] = { NULL, NULL, NULL };

io::InOut * const Application::stdin  = stream[0];
io::InOut * const Application::stdout = stream[1];
io::InOut * const Application::stderr = stream[2];

void (*Application::init_)( void )  = reinterpret_cast<void (*)()>(dummy_loop);
void (*Application::start_)( void ) = reinterpret_cast<void (*)()>(dummy_loop);
void (*Application::fini_)( void )  = reinterpret_cast<void (*)()>(dummy_loop);

void Application::init ( void )
{
	init_( );
}

void Application::start ( void )
{
	start_( );
}

void Application::fini ( void )
{
	fini_( );
}

} /* namespace sys */
