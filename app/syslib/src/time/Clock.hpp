#ifndef CLOCK_HPP_
#define CLOCK_HPP_
/**
 * @file   Clock.hpp
 * @author Gerasimov A.S.
 * @brief  Service to provides clock mechanisms.
 */
#include <stddef.h>

namespace time {

/**
 * Clock service class.
 */
class Clock
{
public:
	typedef void (*uDelayPrototype) ( size_t );

	static void init ( uDelayPrototype );

	static void udelay ( size_t usec );
	static void mdelay ( size_t msec );
	static void  delay ( size_t sec );

private:
	static uDelayPrototype udelay_;
};

} /* namespace time */

#endif /* CLOCK_HPP_ */
