#ifndef CLOCK_HPP_
#define CLOCK_HPP_
/**
 * @file   Clock.hpp
 * @author Gerasimov A.S.
 * @brief  Service to provides clock mechanisms.
 */
#include <stddef.h>

namespace hal {

/**
 * Clock service class.
 */
class Clock
{
public:
	static void init ( Board *board );

	static void udelay ( size_t usec );
	static void mdelay ( size_t msec );
	static void  delay ( size_t sec );

private:
	static Board *m_board;
};

} /* namespace hal */

#endif /* CLOCK_HPP_ */
