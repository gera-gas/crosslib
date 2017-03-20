#ifndef TIMER_HPP_
#define TIMER_HPP_
/**
 * @file   Timer.hpp
 * @author Gerasimov A.S.
 * @brief  Service to provides timer mechanisms.
 */
#include <stddef.h>
#include "typedef.h"

namespace time {

/**
 * Timer class.
 * This objects will be handling into TimerManager.
 */
class Timer
{
public:
	LIST_ITEM( Timer );

	ulong tick;
	bool autoreload;
	fptr_t function;

	Timer ( ulong tick_val, bool autoreload_val = false, fptr_t function_val = NULL );

	void reload ( void ) {
		tick = tick_initial_;
	}
private:
	ulong tick_initial_;
};

} /* namespace time */

#endif /* TIMER_HPP_ */
