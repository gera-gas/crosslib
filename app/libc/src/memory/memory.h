#ifndef MEMORY_H_
#define MEMORY_H_
/**
 *  @file    memory.h
 *  @brief   Standard memory LIBC functions.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */
#ifdef  __cplusplus
extern "C" {
#endif

void* memset  ( void *, int,   size_t );
void* memcpy  ( void *, const void *, size_t );
void* memmove ( void *, const void *, size_t );
  int memcmp  ( const void *, const void *, size_t );

#ifdef  __cplusplus
}
#endif

#endif  /*  MEMORY_H_  */
