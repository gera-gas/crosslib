/**
 * @file   BoardLayer.cpp
 * @author Gerasimov A.S.
 * @brief  Base interface for hardware layer.
 */
#include "config.h"
#include "assert.h"
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/BoardLayer.hpp"

namespace hal {

/**
 * Counter of Board object.
 */
int BoardLayer::object_counter_ = 0;

/**
 * Board layout constructor.
 */
BoardLayer::BoardLayer ( void ) :
	Module()
{
	assert( object_counter_ == 0 );

	object_counter_++;
}

} /* namespace hal */
