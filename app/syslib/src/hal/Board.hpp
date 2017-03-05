#ifndef BOARD_HPP_
#define BOARD_HPP_
/**
 * @file   Board.hpp
 * @author Gerasimov A.S.
 * @brief  Base board API.
 * @note   This is end point API of hardware layer.
 */
#include <stddef.h>

namespace hal {

/**
 * Board API class.
 */
class Board : public Module
{
public:
	Board ( void );

#if defined(CXX_RTTI)
	virtual void udelay ( size_t usec ) = 0;
#else
	void udelay ( size_t usec );
#endif

protected:
#if !defined(CXX_RTTI)
	typedef void (*udelay_t) ( size_t );

	udelay_t virtual_udelay;
#endif

private:
	static int m_object_counter;
};

} /* namespace hal */

#endif /* BOARD_HPP_ */
