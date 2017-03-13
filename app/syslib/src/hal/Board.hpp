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

private:
	static int object_counter_;
};

} /* namespace hal */

#endif /* BOARD_HPP_ */
