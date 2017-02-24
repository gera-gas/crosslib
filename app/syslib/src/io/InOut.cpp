/**
 * @file    InOut.cpp
 * @brief   Input/Output methods emplementation.
 * @author  Gerasimov A.S.
 */
#include "hal/Port.hpp"
#include "io/InOut.hpp"

namespace io {

/**
 * @brief
 * Put char to output device.
 *
 * @param ioctx : [in] IO object.
 * @param c     : [in] char for output.
 */
void io_putc ( InOut *ioctx, char c )
{
	while( !ioctx->port_->tx_ready() );

	ioctx->port_->tx( c );
}


/**
 * @brief
 * Put string to output device.
 *
 * @param ioctx : [in] IO object.
 * @param pstr  : [in] string for output.
 */
void io_puts ( InOut *ioctx, const char *pstr )
{
	char c;

	while( true )
	{
		c = *pstr++;

		if( c == '\0' ) {
			break;
		}

		io_putc( ioctx, c );
	}
}


/**
 * @brief
 * Get char from IO device.
 *
 * @param ioctx : [in] IO object.
 * @param pstr  : [in] string for output.
 *
 * @return
 * Return char.
 */
char io_getch ( InOut *ioctx )
{
	while( !ioctx->port_->rx_ready() );

	return ioctx->port_->rx( );
}


/**
 * @brief
 * Read data from IO device.
 *
 * @param ioctx : [in] IO context.
 * @param pdata : [in] address of destination buffer.
 * @param size  : [in] size for reading in bytes.
 *
 * @return
 * Data size wrote to device.
 */
size_t io_read ( InOut *ioctx, char *pdata, size_t size )
{
	size_t i;

	for( i = 0; i < size; i++ )
	{
		pdata[i] = io_getch( ioctx );
	}

	return i;
}


/**
 * @brief
 * Write data to output device.
 *
 * @param ioctx : [in] IO context.
 * @param pdata : [in] address of input buffer.
 * @param size  : [in] size for reading in bytes.
 *
 * @return
 * Data size wrote to device.
 */
size_t io_write ( InOut *ioctx, const char *pdata, size_t size )
{
	size_t i;

	for( i = 0; i < size; i++ )
	{
		io_putc( ioctx, pdata[i] );
	}

	return i;
}


/**
 * @brief
 * Check char exists on receive.
 *
 * @retval true  : char exist.
 * @retval false : no chars on receive.
 */
bool io_kbhit ( InOut *ioctx )
{
	if( ioctx->port_->rx_ready() )
	{
		return true;
	}

	return false;
}


/**
 * @brief
 * IO service contructor.
 *
 * @param [in] : address of IO device object.
 */
InOut::InOut ( hal::Port *port ) :
	port_(port) {
	/*
	 * Set default IO methods.
	 */
	putc_  = io_putc;
	puts_  = io_puts;
	getch_ = io_getch;
	read_  = io_read;
	write_ = io_write;
	kbhit_ = io_kbhit;
};

} /* namespace io */
