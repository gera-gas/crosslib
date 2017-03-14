#ifndef TIME_EXPORT_HPP_
#define TIME_EXPORT_HPP_
/**
 * @file     service.hpp
 * @brief    Export of time service classes.
 * @author   Gerasimov A.S.
 */
#include "helpers.hpp"
#include "hal.hpp"
#include "Clock.hpp"

namespace time {
SINGLETON( Clock, clock );
}

#endif /* TIME_EXPORT_HPP_ */
