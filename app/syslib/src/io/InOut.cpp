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
 * @param c : [in] char for output.
 */
void InOut::putc ( char c )
{
	while( !port_->tx_ready() );

	port_->tx( c );
}


/**
 * @brief
 * Put string to output device.
 *
 * @param pstr : [in] string for output.
 */
void InOut::puts ( const char *pstr )
{
	char c;

	while( true )
	{
		c = *pstr++;

		if( c == '\0' ) {
			break;
		}

		putc( c );
	}
}


/**
 * @brief
 * Get char from IO device.
 *
 * @return
 * Return received char from IO device.
 */
char InOut::getch ( void )
{
	while( !port_->rx_ready() );

	return port_->rx( );
}


/**
 * @brief
 * Read data from IO device.
 *
 * @param pdata : [in] address of destination buffer.
 * @param size  : [in] size for reading in bytes.
 *
 * @return
 * Data size wrote to device.
 */
size_t InOut::read ( char *pdata, size_t size )
{
	size_t i;

	for( i = 0; i < size; i++ )
	{
		pdata[i] = getch( );
	}

	return i;
}


/**
 * @brief
 * Write data to output device.
 *
 * @param pdata : [in] address of input buffer.
 * @param size  : [in] size for reading in bytes.
 *
 * @return
 * Data size wrote to device.
 */
size_t InOut::write ( const char *pdata, size_t size )
{
	size_t i;

	for( i = 0; i < size; i++ )
	{
		putc( pdata[i] );
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
bool InOut::kbhit ( void )
{
	if( port_->rx_ready() )
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
	port_(port)
{ };

} /* namespace io */
