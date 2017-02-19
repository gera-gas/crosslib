#ifndef ZFM70_HPP_
#define ZFM70_HPP_
/**
 * @file     zfm70.hpp
 * @brief    Driver for ZFM70 optical fingerprint sanner.
 * @author   Gerasimov A.S.
 * @note
 * More information and DEMO windows application
 * you can find on https://learn.adafruit.com
 *
 * Header dependencies:
 *
 * #include "io.h"
 * #include "fingerprint.h"
 */
#include <stddef.h>
#include "typedef.h"

namespace dev {

/**
 * Driver for ZFM70 optical fingerprint sanner.
 */
class ZFM70 : public Fingerprint {
public:
	/**
	 * ZFM70 device descriptor consctructor.
	 */
	ZFM70 ( sys::DevicePort *, uint32 );

	/**
	 * ZFM70 device commands.
	 */
	enum Commands {
		CMD_GETIMG        = 0x01,
		CMD_IMG2TZ        = 0x02,
		CMD_MATCH         = 0x03,
		CMD_SEARCH        = 0x04,
		CMD_REGMODEL      = 0x05,
		CMD_STORE         = 0x06,
		CMD_LOADCHAR      = 0x07,
		CMD_UPCHAR        = 0x08,
		CMD_DOWNCHAR      = 0x09,
		CMD_UPIMAGE       = 0x0a,
		CMD_DOWNIMAGE     = 0x0b,
		CMD_DELETECHAR    = 0x0c,
		CMD_EMPTY         = 0x0d,
		CMD_SETSYSPARAM   = 0x0e,
		CMD_READSYSPARAM  = 0x0f,
		CMD_GETRNDCODE    = 0x14,
		CMD_SETADDR       = 0x15,
		CMD_HANDSHAKE     = 0x17,
		CMD_WRITENOTEPAD  = 0x18,
		CMD_READNOTEPAD   = 0x19,
		CMD_TEMPLATENUM   = 0x1d,
	};

	/**
	 * The FingerPrint scanner confirmation type definition.
	 */
	enum Acknowledge {
		ACK_COMPLETE                 = 0x00,
		ACK_ERR_RCVPCK               = 0x01,
		ACK_NO_FINGER                = 0x02,
		ACK_FAIL_ENROLL              = 0x03,
		ACK_FAIL_GENCHRFILE_DISORDER = 0x06,
		ACK_FAIL_GENCHRFILE_SMALL    = 0x07,
		ACK_NOT_MATCH                = 0x08,
		ACK_FAIL_FIND_MATCH_FINGER   = 0x09,
		ACK_FAIL_TO_COMBANE_CHRFILE  = 0x0a,
		ACK_BEYOND_ADDRPAGE_ID       = 0x0b,
		ACK_ERR_READ_TEMPLATE        = 0x0c,
		ACK_ERR_UPLOAD_TEMPLATE      = 0x0d,
		ACK_ERR_RCV_FOLLOW_PCK       = 0x0e,
		ACK_ERR_UPLOAD_IMAGE         = 0x0f,
		ACK_FAIL_DELETE_TEMPLATE     = 0x10,
		ACK_FAIL_CLEAR_LIBRARY       = 0x11,
		ACK_FAIL_GEN_IMAGE           = 0x15,
		ACK_FAIL_ERR_WRITE_FLASH     = 0x18,
		ACK_FAIL_NODEF_ERR           = 0x19,
		ACK_REGNUM_INVALID           = 0x1a,
		ACK_CONFREG_INCORR           = 0x1b,
		ACK_NOTEPAD_PAGENUM_WRONG    = 0x1c,
		ACK_FAIL_COMMUNICATE         = 0x1d,
	};

	/**
	 * Describe module specific parameters.
	 */
	struct SystemParam {
		uint16 status_register;
		uint16 system_id;
		uint16 library_size;
		uint16 security_level;
		uint32 device_address;
		uint16 packet_size;
		uint16 baud_settings;
	};

	/*
	 * Below declaration device specifically ZFM70 public API.
	 */
	enum Acknowledge handshake    ( void );
	enum Acknowledge get_image    ( void );
	enum Acknowledge img2Tz       ( uint8 );
	enum Acknowledge create_model ( void );
	enum Acknowledge store_model  ( uint16 );
	enum Acknowledge load_model   ( uint16 );
	enum Acknowledge delete_model ( uint16 );
	enum Acknowledge empty_base   ( void );
	enum Acknowledge search       ( uint8, uint16 * );
	enum Acknowledge get_template ( uint16 * );
	enum Acknowledge read_info    ( SystemParam * );

	/*
	 * Reload public parrent method to read device information.
	 */
	bool info ( SystemParam *sys_param )
	{
		return zfm70_info( this, sys_param );
	}

private:
	/*
	 * Object for IO.
	 */
	sys::InOut io_;

	/**
	 * Package identifier type definition
	 */
	enum PID {
		PID_COMMAND  = 0x01,
		PID_DATA     = 0x02,
		PID_ACK      = 0x07,
		PID_END_DATA = 0x08,
	};

	/**
	 * Module address.
	 */
	const uint32 module_address_;

	/**
	 * @brief
	 * Send package with varoius data to the fingerprint scanner.
	 *
	 * @param   pid  : [in] package identifier.
	 * @param   data : [in] pointer to the buffer with data.
	 * @param   len  : [in] length of data in bytes.
	 */
	void package_snd ( enum PID pid, const uint8 *data, size_t len );

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
	bool package_rcv( enum PID *pid, uint8 *data, uint16 *len );

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
	enum Acknowledge cmd_transaction ( uint8 *data, uint16 *len );

	/*
	 * Functions for overriding parent virtual methods.
	 */
	friend bool zfm70_info     ( ZFM70 *zfm70, void *outbuffer );
	friend int  zfm70_enroll   ( ZFM70 *zfm70 );
	friend bool zfm70_remove   ( ZFM70 *zfm70, int pageid );
	friend bool zfm70_clear    ( ZFM70 *zfm70 );
	friend int  zfm70_identify ( ZFM70 *zfm70 );
};

} /* namespace dev */

#endif  /* ZFM70_HPP_ */
