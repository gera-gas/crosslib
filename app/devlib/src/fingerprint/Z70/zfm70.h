#ifndef ZFM70_H_
#define ZFM70_H_
/**
 * @file     zfm70.h
 * @brief    Driver for ZFM70 optical fingerprint sanner.
 * @author   Gerasimov A.S.
 * @note
 * More information and DEMO windows application
 * you can find on https://learn.adafruit.com
 *
 * Header dependencies:
 *
 * #include "fingerprint.h"
 */
#include <stddef.h>
#include <stdbool.h>

/**
 * The FingerPrint scanner instructions type definition.
 */
typedef enum {
	ZFM70_CMD_GETIMG           = 0x01,
	ZFM70_CMD_IMG2TZ           = 0x02,
	ZFM70_CMD_MATCH            = 0x03,
	ZFM70_CMD_SEARCH           = 0x04,
	ZFM70_CMD_REGMODEL         = 0x05,
	ZFM70_CMD_STORE            = 0x06,
	ZFM70_CMD_LOADCHAR         = 0x07,
	ZFM70_CMD_UPCHAR           = 0x08,
	ZFM70_CMD_DOWNCHAR         = 0x09,
	ZFM70_CMD_UPIMAGE          = 0x0a,
	ZFM70_CMD_DOWNIMAGE        = 0x0b,
	ZFM70_CMD_DELETECHAR       = 0x0c,
	ZFM70_CMD_EMPTY            = 0x0d,
	ZFM70_CMD_SETSYSPARAM      = 0x0e,
	ZFM70_CMD_READSYSPARAM     = 0x0f,
	ZFM70_CMD_GETRNDCODE       = 0x14,
	ZFM70_CMD_SETADDR          = 0x15,
	ZFM70_CMD_HANDSHAKE        = 0x17,
	ZFM70_CMD_WRITENOTEPAD     = 0x18,
	ZFM70_CMD_READNOTEPAD      = 0x19,
	ZFM70_CMD_TEMPLATENUM      = 0x1d,
} zfm70_cmd_t;

/**
 * The FingerPrint scanner confirmation type definition.
 */
typedef enum {
	ZFM70_ACK_COMPLETE                 = 0x00,
	ZFM70_ACK_ERR_RCVPCK               = 0x01,
	ZFM70_ACK_NO_FINGER                = 0x02,
	ZFM70_ACK_FAIL_ENROLL              = 0x03,
	ZFM70_ACK_FAIL_GENCHRFILE_DISORDER = 0x06,
	ZFM70_ACK_FAIL_GENCHRFILE_SMALL    = 0x07,
	ZFM70_ACK_NOT_MATCH                = 0x08,
	ZFM70_ACK_FAIL_FIND_MATCH_FINGER   = 0x09,
	ZFM70_ACK_FAIL_TO_COMBANE_CHRFILE  = 0x0a,
	ZFM70_ACK_BEYOND_ADDRPAGE_ID       = 0x0b,
	ZFM70_ACK_ERR_READ_TEMPLATE        = 0x0c,
	ZFM70_ACK_ERR_UPLOAD_TEMPLATE      = 0x0d,
	ZFM70_ACK_ERR_RCV_FOLLOW_PCK       = 0x0e,
	ZFM70_ACK_ERR_UPLOAD_IMAGE         = 0x0f,
	ZFM70_ACK_FAIL_DELETE_TEMPLATE     = 0x10,
	ZFM70_ACK_FAIL_CLEAR_LIBRARY       = 0x11,
	ZFM70_ACK_FAIL_GEN_IMAGE           = 0x15,
	ZFM70_ACK_FAIL_ERR_WRITE_FLASH     = 0x18,
	ZFM70_ACK_FAIL_NODEF_ERR           = 0x19,
	ZFM70_ACK_REGNUM_INVALID           = 0x1a,
	ZFM70_ACK_CONFREG_INCORR           = 0x1b,
	ZFM70_ACK_NOTEPAD_PAGENUM_WRONG    = 0x1c,
	ZFM70_ACK_FAIL_COMMUNICATE         = 0x1d,
} zfm70_ack_t;

#ifdef __cplusplus
extern "C" {
#endif

zfm70_ack_t zfm70_handshake    ( const fingerprint_t * );
zfm70_ack_t zfm70_getimage     ( const fingerprint_t * );
zfm70_ack_t zfm70_compress     ( const fingerprint_t *, uint8 );
zfm70_ack_t zfm70_model_create ( const fingerprint_t * );

#ifdef __cplusplus
}
#endif

#endif  /* ZFM70_H_ */
