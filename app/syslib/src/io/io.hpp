#ifndef IO_HPP_
#define IO_HPP_
/**
 * @file    io.hpp
 * @brief   Input/Output service classes.
 * @author  Gerasimov A.S.
 * @note
 * Header dependencies:
 *
 * #include "hal.hpp"
 */
#include <stddef.h>
#include "typedef.h"

namespace sys {

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
	InOut ( DevicePort *device );

	/*
	 * Public (virtual) IO methods.
	 */
	void putc ( char c )
	{
		putc_( this, c );
	}

	void puts ( const char *s )
	{
		puts_( this, s );
	}

	char getch ( void )
	{
		return getch_( this );
	}

	size_t write ( const char *data, size_t size )
	{
		return write_ ( this, data, size );
	}

	size_t read ( char *data, size_t size )
	{
		return read_ ( this, data, size );
	}

	bool kbhit ( void )
	{
		return kbhit_ ( this );
	}

protected:
	/*
	 * Points to IO methods.
	 */
	void   (*putc_)  ( InOut *, char );
	void   (*puts_)  ( InOut *, const char * );
	char   (*getch_) ( InOut * );
	size_t (*write_) ( InOut *, const char *, size_t );
	size_t (*read_)  ( InOut *, char *, size_t );
	bool   (*kbhit_) ( InOut * );

private:
	/*
	 * Point to IO device.
	 */
	DevicePort *device_;

	/*
	 * Default IO methods emplementation.
	 */
	friend void   io_putc  ( InOut *, char );
	friend void   io_puts  ( InOut *, const char * );
	friend char   io_getch ( InOut * );
	friend size_t io_write ( InOut *, const char *, size_t );
	friend size_t io_read  ( InOut *, char *, size_t );
	friend bool   io_kbhit ( InOut * );
};

} /* namespace sys */

#endif  /* IO_HPP_ */