#ifndef FIFO_HPP_
#define FIFO_HPP_
/**
 * @file     Fifo.hpp
 * @brief    Various data structure.
 * @author   Gerasimov A.S.
 * @note
 * Header dependencies:
 * #include "Array.hpp"
 */
#include <stddef.h>
#include "gmacro.h"

namespace buffer {

/**
 * Implementation of doubly linked list.
 */
template <class T> class Fifo : public Array {
public:

	/**
	 * Create FIFO object.
	 *
	 * @param buffer  : [in] point to FIFO buffer for data allocation.
	 * @param bufsize : [in] buffer size (element numbers).
	 */
	Fifo ( T *buffer, size_t bufsize ) :
		Array(),
		buffer_(buffer),
		bufsize_(bufsize),
		head_(0), tail_(0),
		overflow_(false)
	{ }

	/**
	 * @brief
	 * Put object into FIFO.
	 * 
	 * @param obj [in] : object for store into FIFO.
	 *
	 * @retval true  : success.
	 * @retval false : FIFO is overflow.
	 */
	bool put( T &obj )
	{
		if( overflow_ ) {
			return false;
		}
	
		buffer_[tail_++] = obj;
	
		if( tail_ >= bufsize_ ) {
			tail_ = 0;
		}
		else if( tail_ == head_ ) {
			overflow_ = true;
		}

		length++;

		return true;
	}

	/**
	 * @brief
	 * Get object from FIFO.
	 * 
	 * @param obj [out] : address for store object.
	 *
	 * @retval true  : success.
	 * @retval false : FIFO is empty.
	 */
	bool get( T &obj )
	{
		if( !(overflow_) && (head_ == tail_) ) {
			return false;
		}
		overflow_ = false;
	
		obj = buffer_[head_++];

		if( head_ >= bufsize_ ) {
			head_ = 0;
		}

		length--;

		return true;
	}

	/**
	 * Return true if FIFO full.
	 */
	bool overflow ( void ) const {
		return overflow_;
	}

	/**
	 * Return FIFO size (in elements numbers).
	 */
	size_t size ( void ) const {
		return bufsize_;
	}

	/**
	 * Reload operator for put FIFO.
	 */
	bool operator<< ( T &obj )
	{
		return put( obj );
	}

	/**
	 * Reload operator for get FIFO.
	 */
	bool operator>> ( T &obj )
	{
		return get( obj );
	}

private:
	     T *buffer_;
	size_t  bufsize_;
	size_t  head_;
	size_t  tail_;
	  bool  overflow_;
};

} /* namespace buffer */

#endif  /* FIFO_HPP_ */
