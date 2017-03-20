/**
 * @file    LedGroupInterface.cpp
 * @brief   Led common interface.
 * @author  Gerasimov A.S.
 */
#include "config.h"
#include "assert.h"
#include "led/LedGroupInterface.hpp"
#include "dummy.h"

namespace dev {

LedGroupInterface::LedGroupInterface ( void )
{
	supported_colors.data = 0;
	color.data = 0;

	blink_toggle_ = false;

	virtual_light_on  = reinterpret_cast<LightPrototype>(dummy_trap);
	virtual_light_off = reinterpret_cast<LightPrototype>(dummy_trap);
}


#if !defined(CXX_RTTI)
void LedGroupInterface::light_on ( void )
{
	if( color.red ) {
		assert( supported_colors.red );
	}
	if( color.green ) {
		assert( supported_colors.green );
	}
	if( color.blue ) {
		assert( supported_colors.blue );
	}

	virtual_light_on( this );
}


void LedGroupInterface::light_off ( void )
{
	virtual_light_off( this );
}
#endif


void LedGroupInterface::blink ( void )
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
