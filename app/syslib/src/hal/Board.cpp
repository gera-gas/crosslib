/**
 * @file   Board.cpp
 * @author Gerasimov A.S.
 * @brief  Board base API.
 */
#include "dummy.h"
#include "hal/Module.hpp"
#include "hal/Board.hpp"

namespace hal {

/**
 * Counter of Board object.
 */
int Board::m_object_counter = 0;

/**
 * Board layout constructor.
 */
Board::Board ( void ) :
	Module()
{
	if( m_object_counter != 0 ) {
		dummy_trap( );
	}

#if !defined(CXX_RTTI)
	virtual_udelay = reinterpret_cast<udelay_t>(dummy_trap);
#endif
	m_object_counter++;
}

#if !defined(CXX_RTTI)
/**
 * Delay in microseconds.
 */
void Board::udelay ( size_t usec )
{
	virtual_udelay( usec );
}
#endif

} /* namespace hal */
