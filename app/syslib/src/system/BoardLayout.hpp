#ifndef BOARD_LAYOUT_HPP_
#define BOARD_LAYOUT_HPP_
/**
 * @file   BoardLayout.hpp
 * @author Gerasimov A.S.
 * @brief  Board API.
 */
#include <stddef.h>

namespace sys {

/**
 * Board API class.
 */
class BoardLayout
{
public:
	BoardLayout( void );

	void init ( void );
	void fini ( void );

	void udelay ( size_t usec );
	void mdelay ( size_t msec );
	void  delay ( size_t sec );

	typedef void (*udelay_t) ( size_t );
	typedef void (*method_t) ( void* );

protected:
	udelay_t virtual_udelay;
	method_t virtual_init;
	method_t virtual_fini;

private:
	static int object_counter_;
};

} /* namespace sys */

#endif /* BOARD_LAYOUT_HPP_ */
