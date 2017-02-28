#ifndef BOARD_HPP_
#define BOARD_HPP_
/**
 * @file   Board.hpp
 * @author Gerasimov A.S.
 * @brief  Board API.
 */
#include <stddef.h>

namespace sys {

/**
 * Board API class.
 */
class Board
{
public:
	/**
	 * @brief
	 * Initialize board method.
	 *
	 * @note
	 * Should be overrided.
	 */
	static void init ( void )
	{
		init_( );
	}

	/**
	 * @brief
	 * Delay in microseconds.
	 *
	 * @note
	 * Should be overrided.
	 */
	static void udelay ( size_t usec )
	{
		udelay_( usec );
	}

	static void mdelay ( size_t msec );
	static void  delay ( size_t sec );

protected:
	static void (*init_) ( void );
	static void (*udelay_) ( size_t );

};

} /* namespace sys */

#endif /* BOARD_HPP_ */
