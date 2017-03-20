#ifndef TIME_EXPORT_HPP_
#define TIME_EXPORT_HPP_
/**
 * @file     time.hpp
 * @brief    Export of time service classes.
 * @author   Gerasimov A.S.
 */
#include "helpers.hpp"
#include "buffer.hpp"
#include "hal.hpp"
#include "Clock.hpp"
#include "Timer.hpp"
#include "TimerManager.hpp"

namespace time {
SINGLETON( Clock, clock );
}

/**
 * @brief
 * Convert time to CPU clock.
 *
 * @param cpu_frequence_mhz : [in] CPU frequence in MHz.
 * @param time_range_format : [in] Seconds (1000000) or millisecinds (1000) or microseconds (1).
 * @param converted_time    : [in] Converted time value.
 */
#define TIME_TO_CLOCK( cpu_frequence_mhz, time_range_format, converted_time )\
	((cpu_frequence_mhz) * (time_range_format) * (converted_time))

#define SEC_TO_CLOCK( cpu_frequence_mhz, converted_time )\
	TIME_TO_CLOCK( cpu_frequence_mhz, 1000000, converted_time )

#define MSEC_TO_CLOCK( cpu_frequence_mhz, converted_time )\
	TIME_TO_CLOCK( cpu_frequence_mhz, 1000, converted_time )

#define USEC_TO_CLOCK( cpu_frequence_mhz, converted_time )\
	TIME_TO_CLOCK( cpu_frequence_mhz, 1, converted_time )

#endif /* TIME_EXPORT_HPP_ */
