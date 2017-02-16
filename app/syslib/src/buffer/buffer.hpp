#ifndef BUFFER_HPP_
#define BUFFER_HPP_
/**
 * @file     buffer.hpp
 * @brief    Various data structure.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>

namespace sys {

/**
 * Implementation of doubly linked list.
 */
template <class T> class List {
public:
	T *prev;
	T *next;

#define __LIST_THIS  reinterpret_cast<T*>(this)

	/**
	 * Default list constructor.
	 */
	List ( void ) : prev(__LIST_THIS), next(__LIST_THIS) { };

	/**
	 * Check to list empty.
	 *
	 * @retval true  : list is empty.
	 * @retval false : list is not empty.
	 */
	bool is_empty ( void )
	{
		if( next == __LIST_THIS ) {
			return true;
		}

		return false;
	}

	/**
	 * Add element to list tail.
	 */
	void add_tail ( T *e )
	{
		e->prev = prev;
		e->next = __LIST_THIS;

		prev->next = e;
		prev = e;

		size_++;
	}

	/**
	 * Return head address.
	 */
	T* head ( void )
	{
		return __LIST_THIS;
	}

	/**
	 * Return first element from address.
	 */
	T* first ( void )
	{
		return this->next;
	}

	/**
	 * Return last element from address.
	 */
	T* last ( void )
	{
		return this->prev;
	}

	/**
	 * Return list items number (size of list).
	 */
	size_t size ( void )
	{
		return size_;
	}

private:
	size_t size_;
};

/**
 * Walk on list down ( head => tail ).
 */
#define list_foreach_down( item, list )\
	for( item = list.first(); item != list.head(); item = item->next )

#define list_foreach( item, list )\
	list_foreach_down( item, list )

/**
 * Walk on list up ( tail => head ).
 */
#define list_foreach_up( item, list )\
	for( item = list.last(); item != list.head(); item = item->prev )

/**
 * Create list provided variables.
 */
#define LIST_ITEM( type )\
	type prev, next

} /* namespace sys */

#endif  /* BUFFER_HPP_ */
