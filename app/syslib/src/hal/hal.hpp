#ifndef HAL_HPP_
#define HAL_HPP_
/**
 * @file     hal.hpp
 * @brief    Export of HAL classes.
 * @author   Gerasimov A.S.
 * @date     2013-08-07 15:26:14 +0400
 */
#include "helpers.hpp"
#include "Module.hpp"
#include "Port.hpp"
#include "Device.hpp"
#include "BoardLayer.hpp"
#include "ServiceLayer.hpp"
#include "ApplicationLayer.hpp"

/**
 * Check method to realization.
 */
#define SUPPORTED( m ) ((m) != dummy_trap)

#endif /* HAL_HPP_ */
