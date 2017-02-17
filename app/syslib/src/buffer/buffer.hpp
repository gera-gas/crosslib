#ifndef BUFFER_HPP_
#define BUFFER_HPP_
/**
 * @file     buffer.hpp
 * @brief    Various data structure.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "gmacro.h"

namespace sys {

/**
 * Implementation of doubly linked list.
 */
template <class T> class List {
public:
	T *prev;
	T *next;

	/**
	 * Default list constructor.
	 */
	List ( void ) : prev(TOCAST(T,this)), next(TOCAST(T,this)), size_(0) { };

	/**
	 * Add element to list tail.
	 */
	void add_tail ( T *e );

	/**
	 * Return head address.
	 */
	T* head ( void )
	{
		return TOCAST(T,this);
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
 * Add element to list tail.
 */
template <class T> void List<T>::add_tail ( T *e )
{
	e->prev = prev;
	e->next = TOCAST(T,this);

	prev->next = e;
	prev       = e;

	size_++;
}

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

} /* namespace sys */

#endif  /* BUFFER_HPP_ */
