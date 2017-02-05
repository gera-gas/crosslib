#ifndef GCC_H_
#define GCC_H_
/**
 *  @file    memory.h
 *  @brief   GCC function prototypes.
 *  @author  Gerasimov A.S.
 *  @date    2013-03-12 23:44:35 +0400
 */
#ifdef  __cplusplus
extern "C" {
#endif

uint32 __mulsi3  ( uint32, uint32 );
uint64 __udivdi3 ( uint64, uint64 );
uint32 __udivsi3 ( uint32, uint32 );
uint64 __umoddi3 ( uint64, uint64 );
uint32 __umodsi3 ( uint32, uint32 );

#ifdef  __cplusplus
}
#endif

#endif  /*  GCC_H_  */
