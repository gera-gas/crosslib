/**
 * @file   Board.cpp
 * @author Gerasimov A.S.
 * @brief  Board base API.
 */
#include "config.h"
#include "assert.h"
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"

namespace hal {

/**
 * Counter of Board object.
 */
int Board::object_counter_ = 0;

/**
 * Board layout constructor.
 */
Board::Board ( void ) :
	Module()
{
	assert( object_counter_ == 0 );

	object_counter_++;
}

} /* namespace hal */
