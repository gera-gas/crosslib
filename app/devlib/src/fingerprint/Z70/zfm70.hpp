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
	 * @brief
	 * ZFM70 device descriptor consctructor.
	 *
	 * @param [in] : Point to device IO object.
	 * @param [in] : Package address (optional).
	 */
	ZFM70 ( sys::DevicePort *fp_port, uint32 package_address = 0xFFFFFFFF ) :
		Fingerprint(fp_port),
		io_(fp_port),
		package_address_(package_address)
	{
		#if 0
		info_     = reinterpret_cast<bool (*)(void*, void*)>(dummy_loop);
		enroll_   = reinterpret_cast<int (*)(void*)>(dummy_loop);
		remove_   = reinterpret_cast<bool (*)(void*, int)>(dummy_loop);
		clear_    = reinterpret_cast<bool (*)(void*)>(dummy_loop);
		identify_ = reinterpret_cast<int (*)(void*)>(dummy_loop);
		#endif;
	}

private:
	/*
	 * Object for IO.
	 */
	sys::InOut io_;

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
	 * Package identifier type definition
	 */
	enum PID {
		PID_COMMAND  = 0x01,
		PID_DATA     = 0x02,
		PID_ACK      = 0x07,
		PID_END_DATA = 0x08,
	};

	/**
	 * Package address.
	 */
	uint32 package_address_;

};

} /* namespace dev */

#endif  /* ZFM70_HPP_ */
