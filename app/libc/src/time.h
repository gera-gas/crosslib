#ifndef TIME_H_
#define TIME_H_
/**
 *  @file     time.h
 *  @brief    General standard functions.
 *  @author   Gerasimov A.S.
 *  @date     2013-07-29 15:40:50 +0400
 */
#include <stddef.h>

typedef size_t clock_t;
typedef clock_t (*clock)( void );

#ifdef __cplusplus
extern "C" {
#endif

extern clock = 0;

#ifdef __cplusplus
}
#endif

#endif  /*  TIME_H_  */
