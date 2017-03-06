/**
 * @file     Zfm70.cpp
 * @brief    Driver for ZFM70 optical fingerprint scanner.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "gmacro.h"
#include "hal/Module.hpp"
#include "hal/Port.hpp"
#include "hal/Device.hpp"
#include "io/InOut.hpp"
#include "fingerprint/Fingerprint.hpp"
#include "fingerprint/zfm70/Zfm70.hpp"
#if defined(USE_BUILTIN_LIBC)
#include <string.h>
#else
#include "memory/memory.h"
#endif

/* The header of data package (magic constant) */
#define PKG_HEADER  ((uint16)0xEF01)

/* Max length of packege */
#define PKG_MAXLEN  ((uint16)64)

namespace dev {

/**
 * @brief
 * Send package with varoius data to the fingerprint scanner.
 *
 * @param   pid  : [in] package identifier.
 * @param   data : [in] pointer to the buffer with data.
 * @param   len  : [in] length of data in bytes.
 */
void Zfm70::package_snd ( enum PID pid, const uint8 *data, size_t len )
{
	size_t i;
	uint16 chksum = 0;

	/* Send header of package */
	port->snd( HPART16( PKG_HEADER ) );
	port->snd( LPART16( PKG_HEADER ) );

	/* Send address */
	port->snd( I32_BYTE1(module_address_) );
	port->snd( I32_BYTE2(module_address_) );
	port->snd( I32_BYTE3(module_address_) );
	port->snd( I32_BYTE4(module_address_) );

	/* Send package identifier */
	port->snd( pid );
	chksum += pid;

	/* Send length */
	uint8 hilen = (uint8)HPART16( len + 2 );
	uint8 lolen = (uint8)LPART16( len + 2 );

	port->snd( hilen );
	chksum += hilen;
	port->snd( lolen );
	chksum += lolen;

	/* Send data */
	for( i = 0; i < len; i++ )
	{
		port->snd( data[i] );
		chksum += data[i];
	}

	/* Send checksum */
	port->snd( HPART16( chksum ) );
	port->snd( LPART16( chksum ) );
}


/**
 * @brief
 * Receive package from the fingerprint scanner.
 *
 * @param  pid : [out] pointer to the buffer with identifier of received package.
 * @param  dst : [out] pointer to the destination buffer of received data.
 * @param  len : [out] pointer to the buffer for length of received data.
 *
 * @retval true  : successfully received package, otherwise '0'.
 * @retval false : bad receive.
 */
bool Zfm70::package_rcv( enum PID *pid, uint8 *data, uint16 *len )
{
	size_t i;
	uint16 chksum = 0;
	uint8  tmp;
	uint16 tmp16;

	/* Wait for header of package */
	if( (uint8)port->rcv( ) != (uint8)HPART16( PKG_HEADER ) ) {
		return false;
	}
	if( (uint8)port->rcv( ) != (uint8)LPART16( PKG_HEADER ) ) {
		return false;
	}

	/* Wait for address */
	if( (uint8)port->rcv( ) != (uint8)I32_BYTE1(module_address_) ) {
		return false;
	}
	if( (uint8)port->rcv( ) != (uint8)I32_BYTE2(module_address_) ) {
		return false;
	}
	if( (uint8)port->rcv( ) != (uint8)I32_BYTE3(module_address_) ) {
		return false;
	}
	if( (uint8)port->rcv( ) != (uint8)I32_BYTE4(module_address_) ) {
		return false;
	}

	*pid = (enum PID)port->rcv( );
	/*
	 * Check PID field.
	 */
	if( *pid != PID_DATA &&
	    *pid != PID_ACK  &&
	    *pid != PID_END_DATA )
	{
        	return false;
	}
	chksum += *pid;

	/* Wait for length of data */
	tmp = port->rcv( );
	chksum += tmp;
	*len = tmp << 8;
	tmp = port->rcv( );
	chksum += tmp;
	*len |= tmp;

	/* Returns length without checksum */
	*len -= 2;

	/* Wait for data */
	for( i = 0; i < *len; i++ )
	{
		data[i] = port->rcv( );
		chksum += data[i];
	}

	/* Wait for checksum */
	tmp16  = port->rcv( ) << 8;
	tmp16 |= port->rcv( );

	/* Match checksum */
	if( tmp16 != chksum )
	{
		return false;
	}

	return true;
}


/**
 * @brief
 * Executing one command transaction.
 *
 * @param data : [in/out] address of data buffer for send/receive data transaction.
 * @param len  : [in/out] length of data buffer in bytes.
 *
 * @return
 * Confirmation code from zfm70.
 */
enum Zfm70::Acknowledge Zfm70::cmd_transaction ( uint8 *data, uint16 *len )
{
	enum PID pid;

	package_snd( PID_COMMAND, data, *len );

	if( !package_rcv( &pid, data, len ) )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	if( pid != PID_ACK )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return (enum Zfm70::Acknowledge)data[0];
}


/**
 * @brief
 * Send 'Handshake' instruction to fingerprint device and wait of acknowledge.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::handshake ( void )
{
	uint8  buffer[2];
	uint16 length;

	buffer[0] = CMD_HANDSHAKE;
	buffer[1] = 0;
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Collects finger image.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::get_image ( void )
{
	uint8  buffer[2];
	uint16 length;

	buffer[0] = CMD_GETIMG;
	buffer[1] = 0;
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Generates character file for compressing image information.
 *
 * @param bufid : [in] number of buffer for character file.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::img2Tz ( uint8 bufid )
{
	uint8  buffer[2];
	uint16 length;

	buffer[0] = CMD_IMG2TZ;
	buffer[1] = bufid;
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Creates model.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::create_model ( void )
{
	uint8  buffer[2];
	uint16 length;

	buffer[0] = CMD_REGMODEL;
	buffer[1] = 0;
	length    = 1;

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Stores model.
 *
 * @param id : [in] Page ID (Flash location of the template).
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::store_model ( uint16 id )
{
	uint8  buffer[4];
	uint16 length;

	buffer[0] = CMD_STORE;
	buffer[1] = 1;
	buffer[2] = (uint8)HPART16( id );
	buffer[3] = (uint8)LPART16( id );
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Loads model.
 *
 * @param id : [in] Page ID (Flash location of the template).
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::load_model ( uint16 id )
{
	uint8  buffer[4];
	uint16 length;

	buffer[0] = CMD_LOADCHAR;
	buffer[1] = 1;
	buffer[2] = (uint8)HPART16( id );
	buffer[3] = (uint8)LPART16( id );
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Deletes model.
 *
 * @param id : [in] Page ID (Flash location of the template).
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::delete_model ( uint16 id )
{
	uint8  buffer[5];
	uint16 length;

	buffer[0] = CMD_DELETECHAR;
	buffer[1] = (uint8)HPART16( id );
	buffer[2] = (uint8)LPART16( id );
	buffer[3] = 0;
	buffer[4] = 1;
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Searches of template in library.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::empty_base ( void )
{
	uint8  buffer[1];
	uint16 length;

	buffer[0] = CMD_EMPTY;
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 1 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	return ack;
}


/**
 * @brief
 * Searches of template in library.
 *
 * @param bufid  : [in] Number of buffer for character file.
 * @param pageid : [out] Page ID (Flash location of the template).
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::search ( uint8 bufid, uint16 *pageid )
{
	uint8  buffer[6];
	uint16 length;

	buffer[0] = CMD_SEARCH;
	buffer[1] = bufid;
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0x03;
	buffer[5] = 0xe8;
	length    = sizeof(buffer);

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 5 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	((uint8 *)pageid)[0] = buffer[2];
	((uint8 *)pageid)[1] = buffer[1];

	return ack;
}


/**
 * @brief
 * Get valid template number.
 *
 * @param tmpnum : [out] Pointer to buffer for the current valid template.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::get_template ( uint16 *tmpnum )
{
	uint8  buffer[3];
	uint16 length;

	buffer[0] = CMD_TEMPLATENUM;
	buffer[1] = 0;
	buffer[2] = 0;
	length    = 1;

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != 3 )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	((uint8 *)tmpnum)[0] = buffer[2];
	((uint8 *)tmpnum)[1] = buffer[1];

	return ack;
}


/**
 * @brief
 * Read module specific parameters.
 *
 * @param sys_param : [out] Pointer to system parameters structure.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum Zfm70::Acknowledge Zfm70::read_info ( SystemParam *sys_param )
{
	uint8  buffer[sizeof(SystemParam) + 1];
	uint16 length;

	buffer[0] = CMD_READSYSPARAM;
	length    = 1;

	enum Acknowledge ack = cmd_transaction( buffer, &length );

	if( length != (sizeof(SystemParam) + 1) )
	{
		return ACK_FAIL_COMMUNICATE;
	}

	memcpy( sys_param, &buffer[1], sizeof(SystemParam) );

	return ack;
}


/**
 * @brief
 * Get device information.
 *
 * @param outbuffer : [out] buffer address for store information.
 *
 * @retval true  : success.
 * @retval false : failed.
 */
bool zfm70_info ( Zfm70 *zfm70, void *outbuffer )
{
	enum Zfm70::Acknowledge ack;

	//delay(1000);

	ack = zfm70->handshake( );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return false;
	}

	//delay(1000);

	ack = zfm70->read_info( (Zfm70::SystemParam *)outbuffer );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return false;
	}

	return true;
}


/**
 * @brief
 * Enroll new fingerprint.
 *
 * @retval >=0 : Page ID (Flash location of the template).
 * @retval  <0 : failed.
 */
int zfm70_enroll ( Zfm70 *zfm70 )
{
	enum Zfm70::Acknowledge ack;

	for( int i = 0; i < 2; )
	{
		/*
		 * Create finger image.
		 */
		do {
			ack = zfm70->get_image( );
		}
		while( ack == Zfm70::ACK_NO_FINGER );

		if( ack != Zfm70::ACK_COMPLETE )
		{
			zfm70->errorcode = ack;
			return -1;
		}

		/*
		 * Image compression.
		 */
		ack = zfm70->img2Tz( ++i );

		if( ack != Zfm70::ACK_COMPLETE )
		{
			zfm70->errorcode = ack;
			return -1;
		}
	}

	/*
	 * Create model.
	 */
	ack = zfm70->create_model( );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	uint16 tmpnum;
	/*
	 * Get template number.
	 */
	ack = zfm70->get_template( &tmpnum );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	/*
	 * Save model.
	 */
	ack = zfm70->store_model( tmpnum );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	return tmpnum;
}


/**
 * @brief
 * Remove fingerprint from base.
 *
 * @param pageid : Page ID (Flash location of the template).
 *
 * @retval true  : success.
 * @retval false : failed.
 */
bool zfm70_remove ( Zfm70 *zfm70, int pageid )
{
	enum Zfm70::Acknowledge ack;

	ack = zfm70->delete_model( pageid );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return false;
	}

	return true;
}


/**
 * @brief
 * Clear device (Remove all fingerprints from base).
 *
 * @retval true  : success.
 * @retval false : failed.
 */
bool zfm70_clear ( Zfm70 *zfm70 )
{
	enum Zfm70::Acknowledge ack;

	ack = zfm70->empty_base( );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return false;
	}

	return true;
}


/**
 * @brief
 * Identify fingerprint.
 *
 * @retval >=0 : Page ID (Flash location of the template).
 * @retval  <0 : failed.
 */
int zfm70_identify ( Zfm70 *zfm70 )
{
	enum Zfm70::Acknowledge ack;
	
	/*
	 * Create finger image.
	 */
	do {
		ack = zfm70->get_image( );
	}
	while( ack == Zfm70::ACK_NO_FINGER );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	/*
	 * Image compression.
	 */
	ack = zfm70->img2Tz( 1 );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	uint16 pageid;
	/*
	 * Serach fingerprint image in base.
	 */
	ack = zfm70->search( 1, &pageid );

	if( ack != Zfm70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	return pageid;
}


/**
 * @brief
 * ZFM70 device descriptor consctructor.
 *
 * @param fp_port        : [in] Point to device IO object.
 * @param module_address : [in] Package address (optional).
 */
Zfm70::Zfm70 ( hal::Port *fp_port, uint32 module_address ) :
	Fingerprint(fp_port),
	module_address_(module_address)
{
	virtual_info     = reinterpret_cast<bool (*)(void*, void*)>(zfm70_info);
	virtual_enroll   = reinterpret_cast<int (*)(void*)>(zfm70_enroll);
	virtual_remove   = reinterpret_cast<bool (*)(void*, int)>(zfm70_remove);
	virtual_clear    = reinterpret_cast<bool (*)(void*)>(zfm70_clear);
	virtual_identify = reinterpret_cast<int (*)(void*)>(zfm70_identify);
}

} /* namespace dev */
