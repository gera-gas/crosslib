/**
 * @file   Timer.cpp
 * @author Gerasimov A.S.
 * @brief  Service to provides timer mechanisms.
 */
#include "dummy.h"
#include "buffer/Array.hpp"
#include "buffer/List.hpp"
#include "time/Timer.hpp"

namespace time {

Timer::Timer ( ulong tick_val, bool autoreload_val, fptr_t function_val )
{
	tick       = tick_val;
	autoreload = autoreload_val;
	function   = function_val;
}

} /* namespace time */
