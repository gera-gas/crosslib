#ifndef LIST_HPP_
#define LIST_HPP_
/**
 * @file     List.hpp
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
template <class T> class List : public Array {
public:
	T *prev;
	T *next;

	/**
	 * Default list constructor.
	 */
	List ( void ) :
		Array(),
		prev(TOCAST(T,this)),
		next(TOCAST(T,this))
	{ }

	/**
	 * Add element to list tail.
	 */
	void add_tail ( T *e )
	{
		e->prev = prev;
		e->next = TOCAST(T,this);

		prev->next = e;
		prev       = e;

		length++;
	}

	/**
	 * Return head address.
	 */
	T* head ( void ) {
		return TOCAST(T,this);
	}

	/**
	 * Return first element from address.
	 */
	T* first ( void ) {
		return this->next;
	}

	/**
	 * Return last element from address.
	 */
	T* last ( void ) {
		return this->prev;
	}
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
 * Must be allocate to up of object.
 */
#define LIST_ITEM( type )\
	type *prev, *next

} /* namespace buffer */

#endif  /* LIST_HPP_ */
