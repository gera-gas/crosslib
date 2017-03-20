#ifndef SERVICE_LAYER_HPP_
#define SERVICE_LAYER_HPP_
/**
 * @file   ServiceLayer.hpp
 * @author Gerasimov A.S.
 * @brief  Service Layout.
 * @note   This is middle layer between application and hardware layers.
 */
#include <stddef.h>

namespace hal {

/**
 * Service layout class.
 */
class ServiceLayer : public Module
{
public:
	ServiceLayer( BoardLayer* );

	void init ( void );
	void fini ( void );
private:
	static int object_counter_;

	BoardLayer *board_;
};

} /* namespace hal */

#endif /* SERVICE_HPP_ */
