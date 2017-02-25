#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_
/**
 * @file     Singleton.hpp
 * @brief    Helper for Singleton class creation.
 * @author   Gerasimov A.S.
 */
#include "config.h"
#include "assert.h"

namespace helper {

/**
 * Singleton template class.
 */
template <class T> class Singleton
{
public:
	static T* instance( void )
	{
		assert(singleton_ == NULL);
		return singleton_;
	}

protected:
	Singleton() { }
	~Singleton() { }

private:
	static T* singleton_;

	/* Disable of copy operations. */
	Singleton(Singleton const&);
	Singleton& operator= (Singleton const&);
};

template <class T> T* Singleton<T>::singleton_=NULL;

} /* namespace helper */

#endif /* SINGLETON_HPP_ */
