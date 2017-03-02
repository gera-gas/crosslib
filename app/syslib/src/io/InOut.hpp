#ifndef INOUT_HPP_
#define INOUT_HPP_
/**
 * @file    InOut.hpp
 * @brief   Input/Output service classes.
 * @author  Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "hal/Port.hpp"
 */
#include <stddef.h>

namespace io {

/**
 * Emplementation IO service.
 */
class InOut {
public:
	/**
	 * @brief
	 * IO service contructor.
	 *
	 * @param [in] : address of IO device object.
	 */
	InOut ( hal::Port *port );

	/*
	 * Public IO methods.
	 */
	void   putc  ( char );
	void   puts  ( const char * );
	char   getch ( void );
	size_t write ( const char *, size_t );
	size_t read  ( char *, size_t );
	bool   kbhit ( void );

private:
	/*
	 * Point to IO device.
	 */
	hal::Port *port_;
};

} /* namespace io */

#endif  /* IO_HPP_ */
