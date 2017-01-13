#ifndef _MEMORY_H
#define _MEMORY_H
/**
 *  @file    memory.h
 *  @brief   Standard memory LIBC functions.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */
#ifdef  __cplusplus
extern "C" {
#endif

void* memset  ( void *, int,   unsigned int );
void* memcpy  ( void *, const void *, unsigned int );
void* memmove ( void *, const void *, unsigned int );
  int memcmp  ( const void *, const void *, unsigned int );

#ifdef  __cplusplus
}
#endif

#endif  /*  _MEMORY_H  */
