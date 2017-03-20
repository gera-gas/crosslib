#ifndef BOARD_LAYER_HPP_
#define BOARD_LAYER_HPP_
/**
 * @file   BoardLayer.hpp
 * @author Gerasimov A.S.
 * @brief  Base interface for hardware layer.
 * @note   This is end point API of hardware layer.
 */
#include <stddef.h>

namespace hal {

/**
 * This class describe hardware layer and
 * should be contained OnBoard or/and FPGA devices.
 */
class BoardLayer : public Module
{
public:
	BoardLayer ( void );

private:
	static int object_counter_;
};

} /* namespace hal */

#endif /* BOARD_LAYER_HPP_ */
