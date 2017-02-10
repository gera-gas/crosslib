/**
 * @file     zfm70.c
 * @brief    Driver for Z70 optical fingerprint sanner.
 * @author   Gerasimov A.S.
 */
#include <stddef.h>
#include <stdbool.h>
#include "typedef.h"
#include "gmacro.h"
#include "hal/hal.h"
#include "buffer/buffer.h"
#include "io/io.h"
#include "fingerprint/fingerprint.h"
#include "fingerprint/Z70/zfm70.h"

/**
 * Package identifier type definition
 */
typedef enum {
	PID_COMMAND  = 0x01,
	PID_DATA     = 0x02,
	PID_ACK      = 0x07,
	PID_END_DATA = 0x08,
} pid_t;

/* The default fingerprint device address */
#define PKG_DEFAULT_ADDRESS  ((uint32)0xFFFFFFFF)

/* The header of data package (magic constant) */
#define PKG_HEADER           ((uint16)0xEF01)

/* Max length of packege */
#define PKG_MAXLEN           ((uint16)64)


/**
 * @brief
 * Send package with varoius data to the fingerprint scanner.
 *
 * @param   fp   : [in] point to fingerprint context.
 * @param   pid  : [in] package identifier.
 * @param   data : [in] pointer to the buffer with data.
 * @param   len  : [in] length of data in bytes.
 * @retval  None.
 */
void zfm70_package_snd ( const fingerprint_t *fp, pid_t pid, const uint8 *data, size_t len )
{
	size_t i;
	uint16 chksum = 0;

	/* Send header of package */
	io_putc( fp->ioctx, HPART16( PKG_HEADER ) );
	io_putc( fp->ioctx, LPART16( PKG_HEADER ) );

	/* Send address */
	io_putc( fp->ioctx, (PKG_DEFAULT_ADDRESS >> 24) & 0xFF );
	io_putc( fp->ioctx, (PKG_DEFAULT_ADDRESS >> 16) & 0xFF );
	io_putc( fp->ioctx, (PKG_DEFAULT_ADDRESS >> 8 ) & 0xFF );
	io_putc( fp->ioctx, (PKG_DEFAULT_ADDRESS >> 0 ) & 0xFF );

	/* Send package identifier */
	io_putc( fp->ioctx, pid );
	chksum += pid;

	/* Send length */
	uint8 hilen = (uint8)HPART16( len + 2 );
	uint8 lolen = (uint8)LPART16( len + 2 );

	io_putc( fp->ioctx, hilen );
	chksum += hilen;
	io_putc( fp->ioctx, lolen );
	chksum += lolen;

	/* Send data */
	for( i = 0; i < len; i++ )
	{
		io_putc( fp->ioctx, data[i] );
		chksum += data[i];
	}

	/* Send checksum */
	io_putc( fp->ioctx, HPART16( chksum ) );
	io_putc( fp->ioctx, LPART16( chksum ) );
}


/**
 * @brief
 * Receive package from the fingerprint scanner.
 *
 * @param  fp  : [in] point to fingerprint context.
 * @param  pid : [out] pointer to the buffer with identifier of received package.
 * @param  dst : [out] pointer to the destination buffer of received data.
 * @param  len : [out] pointer to the buffer for length of received data.
 *
 * @retval true  : successfully received package, otherwise '0'.
 * @retval false : bad receive.
 */
bool zfm70_package_rcv( const fingerprint_t *fp, pid_t *pid, uint8 *data, uint16 *len )
{
	size_t i;
	uint16 chksum = 0;
	uint8  tmp;
	uint16 tmp16;

	/* Wait for header of package */
	if( (uint8)io_getch( fp->ioctx ) != (uint8)HPART16( PKG_HEADER ) ) {
		return false;
	}
	if( (uint8)io_getch( fp->ioctx ) != (uint8)LPART16( PKG_HEADER ) ) {
		return false;
	}

	/* Wait for address */
	if( (uint8)io_getch( fp->ioctx ) != (uint8)(PKG_DEFAULT_ADDRESS >> 24) ) {
		return false;
	}
	if( (uint8)io_getch( fp->ioctx ) != (uint8)(PKG_DEFAULT_ADDRESS >> 16) ) {
		return false;
	}
	if( (uint8)io_getch( fp->ioctx ) != (uint8)(PKG_DEFAULT_ADDRESS >> 8) ) {
		return false;
	}
	if( (uint8)io_getch( fp->ioctx ) != (uint8)PKG_DEFAULT_ADDRESS ) {
		return false;
	}

	*pid = (pid_t)io_getch( fp->ioctx );
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
	tmp = io_getch( fp->ioctx );
	chksum += tmp;
	*len = tmp << 8;
	tmp = io_getch( fp->ioctx );
	chksum += tmp;
	*len |= tmp;

	/* Returns length without checksum */
	*len -= 2;

	/* Wait for data */
	for( i = 0; i < *len; i++ )
	{
		data[i] = io_getch( fp->ioctx );
		chksum += data[i];
	}

	/* Wait for checksum */
	tmp16  = io_getch( fp->ioctx ) << 8;
	tmp16 |= io_getch( fp->ioctx );

	/* Match checksum */
	if( tmp16 != chksum )
	{
		return false;
	}

	return true;
}


/**
 * @brief
 * Send 'Handshake' instruction to fingerprint device and wait of acknowledge.
 *
 * @param fp : [in] point to fingerprint context.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
zfm70_ack_t zfm70_handshake ( const fingerprint_t *fp )
{
	uint8 buffer[2];
	pid_t pid;

	uint16 len;
	zfm70_ack_t ack = ZFM70_ACK_FAIL_COMMUNICATE;

	buffer[0] = ZFM70_CMD_HANDSHAKE;
	buffer[1] = 0;
	zfm70_package_snd( fp, PID_COMMAND, buffer, 2 );

	/* Receive acknowledge */
	if( !zfm70_package_rcv(fp, &pid, buffer, &len) )
	{
		return ack;
	}

	if( (pid != PID_ACK) || (len != 1) )
	{
		return ack;
	}

	ack = buffer[0];

	return ack;
}


/**
 * @brief
 * Collects finger image.
 *
 * @param fp : [in] point to fingerprint context.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
zfm70_ack_t zfm70_getimage ( const fingerprint_t *fp )
{
	uint8 buffer[2];
	pid_t pid;

	uint16 len;
	zfm70_ack_t ack = ZFM70_ACK_FAIL_COMMUNICATE;

	buffer[0] = ZFM70_CMD_GETIMG;
	buffer[1] = 0;
	zfm70_package_snd( fp, PID_COMMAND, buffer, 2 );

	/* Receive acknowledge */
	if( !zfm70_package_rcv(fp, &pid, buffer, &len) )
	{
		return ack;
	}

	if( (pid != PID_ACK) || (len != 1) )
	{
		return ack;
	}

	ack = buffer[0];

	return ack;
}


/**
 * @brief
 * Generates character file for compressing image information.
 *
 * @param fp    : [in] point to fingerprint context.
 * @param bufid : [in] number of buffer for character file.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
zfm70_ack_t zfm70_compress ( const fingerprint_t *fp, uint8 bufid )
{
	uint8 buffer[2];
	pid_t pid;

	uint16 len;
	zfm70_ack_t ack = ZFM70_ACK_FAIL_COMMUNICATE;

	buffer[0] = ZFM70_CMD_GETIMG;
	buffer[1] = bufid;
	zfm70_package_snd( fp, PID_COMMAND, buffer, 2 );

	/* Receive acknowledge */
	if( !zfm70_package_rcv(fp, &pid, buffer, &len) )
	{
		return ack;
	}

	if( (pid != PID_ACK) || (len != 1) )
	{
		return ack;
	}

	ack = buffer[0];

	return ack;
}


/**
 * @brief
 * Create model.
 *
 * @param fp : [in] point to fingerprint context.
 *
 * @return
 * Return confirmation from fingerprint device.
 */
zfm70_ack_t zfm70_model_create ( const fingerprint_t *fp )
{
	uint8 buffer[2];
	pid_t pid;

	uint16 len;
	zfm70_ack_t ack = ZFM70_ACK_FAIL_COMMUNICATE;

	buffer[0] = ZFM70_CMD_REGMODEL;
	buffer[1] = 0;
	zfm70_package_snd( fp, PID_COMMAND, buffer, 2 );

	/* Receive acknowledge */
	if( !zfm70_package_rcv(fp, &pid, buffer, &len) )
	{
		return ack;
	}

	if( (pid != PID_ACK) || (len != 1) )
	{
		return ack;
	}

	ack = buffer[0];

	return ack;
}
