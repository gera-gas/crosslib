#ifndef LED_GROUP_INTERFACE_HPP_
#define LED_GROUP_INTERFACE_HPP_
/**
 * @file    LedGroupInterface.hpp
 * @brief   Led common group interface.
 * @author  Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"

namespace dev {

class LedGroupInterface {
public:
	LedGroupInterface( void );

	/**
	 * Palette describe type.
	 */
	typedef union {
		struct {
			uint8 red    : 1;
			uint8 green  : 1;
			uint8 blue   : 1;
			uint8 unused : 5;
		};
		uint8 data;
	} Palette;

	/**
	 * Currently light on colors.
	 */
	Palette color;

#if defined(CXX_RTTI)
	virtual void light_on  ( void ) = 0;
	virtual void light_off ( void ) = 0;
#else
	typedef void (*LightPrototype)( void* );

	void light_on  ( void );
	void light_off ( void );
#endif

	/**
	 * Return supported color.
	 */
	Palette get_supported_colors ( void ) const {
		return supported_colors;
	}

	/**
	 * Callback function for blink led.
	 */
	void blink ( void );

protected:
	Palette supported_colors;

#if !defined(CXX_RTTI)
	LightPrototype virtual_light_on;
	LightPrototype virtual_light_off;
#endif

private:
	bool blink_toggle_;
};

} /* namespace dev */

#endif /* LED_GROUP_INTREFACE_HPP_ */
