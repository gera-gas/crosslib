#ifndef APPLICATION_LAYER_HPP_
#define APPLICATION_LAYER_HPP_
/**
 * @file   ApplicationLayer.hpp
 * @author Gerasimov A.S.
 * @brief  Application (top) layer.
 */
#include <stddef.h>

namespace hal {

/**
 * Application layout.
 */
class ApplicationLayer : public Module
{
public:
	ApplicationLayer ( ServiceLayer* );

	void init  ( void );
	void start ( void );
	void fini  ( void );

protected:
	ModulePrototype virtual_start;

private:
	static int object_counter_;
	ServiceLayer *service_;
};

} /* namespace hal */

#endif /* APPLICATION_LAYER_HPP_ */
