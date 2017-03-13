/**
 * @file    Led.cpp
 * @brief   Led base API.
 * @author  Gerasimov A.S.
 */
#include "led/Led.hpp"
#include "dummy.h"

namespace dev {

Led::Led ( void )
{
	supported_colors.data = 0;
	color.data = 0;

	blink_toggle_ = false;

	virtual_light_on  = reinterpret_cast<LightPrototype>(dummy_trap);
	virtual_light_off = reinterpret_cast<LightPrototype>(dummy_trap);
}

#if !defined(CXX_RTTI)
void Led::light_on ( void )
{
	virtual_light_on( this );
}

void Led::light_off ( void )
{
	virtual_light_off( this );
}
#endif

void Led::blink ( void )
{
	/*
	 * Light on state.
	 */
	if( blink_toggle_ == false )
	{
		light_on( );

		blink_toggle_ = true;
		return;
	}

	blink_toggle_ = false;
	/*
	 * Light off state.
	 */
	light_off( );
}

} /* namespace dev */
