#ifndef _CRC_H
#define _CRC_H
/**
 *  @file    crc.h
 *  @brief   CRC header file.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */
#ifdef  __cplusplus
extern "C" {
#endif

 uint8 crc8  ( uint8,  const uint8 *, size_t );
uint16 crc16 ( uint16, const uint8 *, size_t );
uint32 crc32 ( uint32, const uint8 *, size_t );

#ifdef  __cplusplus
}
#endif

#endif  /*  _CRC_H  */
