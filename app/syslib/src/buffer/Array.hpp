#ifndef ARRAY_HPP_
#define ARRAY_HPP_
/**
 * @file     Array.hpp
 * @brief    Various data structure.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "gmacro.h"

namespace buffer {

/**
 * Base (parrent) abstraction API class.
 */
class Array {
public:
	/**
	 * Array constructor.
	 */
	Array ( void ) : length(0) { }

	/**
	 * Return items number (size of list).
	 */
	size_t len ( void ) const {
		return length;
	}

protected:
	size_t length;
};

} /* namespace buffer */

#endif  /* ARRAY_HPP_ */
