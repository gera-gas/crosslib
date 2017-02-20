/**
 * @file     zfm70.cpp
 * @brief    Driver for ZFM70 optical fingerprint sanner.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include "typedef.h"
#include "gmacro.h"
#include "hal/hal.hpp"
#include "io/io.hpp"
#include "fingerprint/fingerprint.hpp"
#include "fingerprint/zfm70/zfm70.hpp"
#if defined(USE_BUILTIN_LIBC)
#include <memory.h>
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
void ZFM70::package_snd ( enum PID pid, const uint8 *data, size_t len )
{
	size_t i;
	uint16 chksum = 0;

	/* Send header of package */
	io_.putc( HPART16( PKG_HEADER ) );
	io_.putc( LPART16( PKG_HEADER ) );

	/* Send address */
	io_.putc( I32_BYTE1(module_address_) );
	io_.putc( I32_BYTE2(module_address_) );
	io_.putc( I32_BYTE3(module_address_) );
	io_.putc( I32_BYTE4(module_address_) );

	/* Send package identifier */
	io_.putc( pid );
	chksum += pid;

	/* Send length */
	uint8 hilen = (uint8)HPART16( len + 2 );
	uint8 lolen = (uint8)LPART16( len + 2 );

	io_.putc( hilen );
	chksum += hilen;
	io_.putc( lolen );
	chksum += lolen;

	/* Send data */
	for( i = 0; i < len; i++ )
	{
		io_.putc( data[i] );
		chksum += data[i];
	}

	/* Send checksum */
	io_.putc( HPART16( chksum ) );
	io_.putc( LPART16( chksum ) );
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
bool ZFM70::package_rcv( enum PID *pid, uint8 *data, uint16 *len )
{
	size_t i;
	uint16 chksum = 0;
	uint8  tmp;
	uint16 tmp16;

	/* Wait for header of package */
	if( (uint8)io_.getch( ) != (uint8)HPART16( PKG_HEADER ) ) {
		return false;
	}
	if( (uint8)io_.getch( ) != (uint8)LPART16( PKG_HEADER ) ) {
		return false;
	}

	/* Wait for address */
	if( (uint8)io_.getch( ) != (uint8)I32_BYTE1(module_address_) ) {
		return false;
	}
	if( (uint8)io_.getch( ) != (uint8)I32_BYTE2(module_address_) ) {
		return false;
	}
	if( (uint8)io_.getch( ) != (uint8)I32_BYTE3(module_address_) ) {
		return false;
	}
	if( (uint8)io_.getch( ) != (uint8)I32_BYTE4(module_address_) ) {
		return false;
	}

	*pid = (enum PID)io_.getch( );
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
	tmp = io_.getch( );
	chksum += tmp;
	*len = tmp << 8;
	tmp = io_.getch( );
	chksum += tmp;
	*len |= tmp;

	/* Returns length without checksum */
	*len -= 2;

	/* Wait for data */
	for( i = 0; i < *len; i++ )
	{
		data[i] = io_.getch( );
		chksum += data[i];
	}

	/* Wait for checksum */
	tmp16  = io_.getch( ) << 8;
	tmp16 |= io_.getch( );

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
enum ZFM70::Acknowledge ZFM70::cmd_transaction ( uint8 *data, uint16 *len )
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

	return (enum ZFM70::Acknowledge)data[0];
}


/**
 * @brief
 * Send 'Handshake' instruction to fingerprint device and wait of acknowledge.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
enum ZFM70::Acknowledge ZFM70::handshake ( void )
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
enum ZFM70::Acknowledge ZFM70::get_image ( void )
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
enum ZFM70::Acknowledge ZFM70::img2Tz ( uint8 bufid )
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
enum ZFM70::Acknowledge ZFM70::create_model ( void )
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
enum ZFM70::Acknowledge ZFM70::store_model ( uint16 id )
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
enum ZFM70::Acknowledge ZFM70::load_model ( uint16 id )
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
enum ZFM70::Acknowledge ZFM70::delete_model ( uint16 id )
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
enum ZFM70::Acknowledge ZFM70::empty_base ( void )
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
enum ZFM70::Acknowledge ZFM70::search ( uint8 bufid, uint16 *pageid )
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
enum ZFM70::Acknowledge ZFM70::get_template ( uint16 *tmpnum )
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
enum ZFM70::Acknowledge ZFM70::read_info ( SystemParam *sys_param )
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
bool zfm70_info ( ZFM70 *zfm70, void *outbuffer )
{
	enum ZFM70::Acknowledge ack;

	//delay(1000);

	ack = zfm70->handshake( );

	if( ack != ZFM70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return false;
	}

	//delay(1000);

	ack = zfm70->read_info( (ZFM70::SystemParam *)outbuffer );

	if( ack != ZFM70::ACK_COMPLETE )
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
int zfm70_enroll ( ZFM70 *zfm70 )
{
	enum ZFM70::Acknowledge ack;

	for( int i = 0; i < 2; )
	{
		/*
		 * Create finger image.
		 */
		do {
			ack = zfm70->get_image( );
		}
		while( ack == ZFM70::ACK_NO_FINGER );

		if( ack != ZFM70::ACK_COMPLETE )
		{
			zfm70->errorcode = ack;
			return -1;
		}

		/*
		 * Image compression.
		 */
		ack = zfm70->img2Tz( ++i );

		if( ack != ZFM70::ACK_COMPLETE )
		{
			zfm70->errorcode = ack;
			return -1;
		}
	}

	/*
	 * Create model.
	 */
	ack = zfm70->create_model( );

	if( ack != ZFM70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	uint16 tmpnum;
	/*
	 * Get template number.
	 */
	ack = zfm70->get_template( &tmpnum );

	if( ack != ZFM70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	/*
	 * Save model.
	 */
	ack = zfm70->store_model( tmpnum );

	if( ack != ZFM70::ACK_COMPLETE )
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
bool zfm70_remove ( ZFM70 *zfm70, int pageid )
{
	enum ZFM70::Acknowledge ack;

	ack = zfm70->delete_model( pageid );

	if( ack != ZFM70::ACK_COMPLETE )
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
bool zfm70_clear ( ZFM70 *zfm70 )
{
	enum ZFM70::Acknowledge ack;

	ack = zfm70->empty_base( );

	if( ack != ZFM70::ACK_COMPLETE )
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
int zfm70_identify ( ZFM70 *zfm70 )
{
	enum ZFM70::Acknowledge ack;
	
	/*
	 * Create finger image.
	 */
	do {
		ack = zfm70->get_image( );
	}
	while( ack == ZFM70::ACK_NO_FINGER );

	if( ack != ZFM70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	/*
	 * Image compression.
	 */
	ack = zfm70->img2Tz( 1 );

	if( ack != ZFM70::ACK_COMPLETE )
	{
		zfm70->errorcode = ack;
		return -1;
	}

	uint16 pageid;
	/*
	 * Serach fingerprint image in base.
	 */
	ack = zfm70->search( 1, &pageid );

	if( ack != ZFM70::ACK_COMPLETE )
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
ZFM70::ZFM70 ( sys::DevicePort *fp_port, uint32 module_address = 0xFFFFFFFF ) :
	Fingerprint(fp_port),
	io_(fp_port),
	module_address_(module_address)
{
	info_     = reinterpret_cast<bool (*)(void*, void*)>(zfm70_info);
	enroll_   = reinterpret_cast<int (*)(void*)>(zfm70_enroll);
	remove_   = reinterpret_cast<bool (*)(void*, int)>(zfm70_remove);
	clear_    = reinterpret_cast<bool (*)(void*)>(zfm70_clear);
	identify_ = reinterpret_cast<int (*)(void*)>(zfm70_identify);
}

} /* namespace dev */
