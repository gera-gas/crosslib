#ifndef RAM_HPP_
#define RAM_HPP_
/**
 * @file    Ram.hpp
 * @brief   RAM service mechanisms.
 * @author  Gerasimov A.S.
 */
#include <stddef.h>

namespace mem {

/**
 * RAM service implementation class.
 */
template <class T> class Ram {
public:
	/**
	 * @brief
	 * RAM class constructor.
	 *
	 * @param value_baddr [in] : base memory address.
	 * @param value_eaddr [in] : end memory address.
	 *
	 * @example
	 * For example, we have memory starting of 0 with range 1024 bytes.
	 * Therefore: value_baddr = 0, value_eaddr = 1023.
	 */
	Ram ( const T *value_baddr, const T *value_eaddr ) :
		ptr_(value_baddr),
		base_(value_baddr),
		end_(value_eaddr) {
		size_ = static_cast<size_t>(base_) - static_cast<size_t>(end_) + 1;
	}

	/**
	 * @brief
	 * RAM class constructor.
	 *
	 * @param value_baddr [in] : base memory address.
	 * @param value_size  [in] : memory size in bytes.
	 */
	Ram ( const T *value_baddr, size_t value_size ) :
		ptr_(value_baddr),
		base_(value_baddr),
		size_(value_size) {
		end_ = static_cast<T*>( static_cast<size_t>(base_) + static_cast<size_t>(size_) );
	}

	/**
	 * Get memory address.
	 */
	T* address ( void ) const {
		return base_;
	}

	/**
	 * Get memory size.
	 */
	size_t size ( void ) const {
		return size_;
	}

private:
	const T *ptr_;       /** Pointer to current free space. */
	const T *base_;      /** Base memory address.           */
	const T *end_;       /** End memory address.            */
	const size_t size_;  /** Memory size in bytes.          */
};

} /* namespace mem */

#endif /* RAM_HPP_ */
