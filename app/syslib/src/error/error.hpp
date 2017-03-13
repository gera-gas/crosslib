#ifndef ERROR_EXPORT_HPP_
#define ERROR_EXPORT_HPP_
/**
 * @file     error.hpp
 * @brief    Export of error service classes.
 * @author   Gerasimov A.S.
 */
#include "FatalError.hpp"

namespace error {
SINGLETON( FatalError, fatal_error );
}

#endif /* ERROR_EXPORT_HPP_ */
