#ifndef SYS_HPP_
#define SYS_HPP_
/**
 * @file    sys.hpp
 * @brief   Export system API classes.
 * @author  Gerasimov A.S.
 */
#include "dummy.h"
#include "io.hpp"
#include "Board.hpp"
#include "Application.hpp"

/**
 * Check method to realization.
 */
#define SUPPORTED( m ) ((m) != dummy_loop)

#endif  /* SYS_HPP_ */
